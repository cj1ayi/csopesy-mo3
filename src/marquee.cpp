#include "marquee.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#endif

#include <atomic>
#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <thread>

#include "helpers.h"

static std::thread worker;
static std::atomic<bool> running{false};
static std::atomic<double> speed_ms{100};
static std::mutex text_mutex;
static std::string marquee_text;

/**
 * Rotates a string one position to the left: the first character
 * is moved to the end.
 */
std::string rotate_left(const std::string &s) {
    if (s.empty()) {
        return s;
    }
    char first_char = s[0];
    std::string rem_str = s.substr(1);
    return rem_str + first_char;
}

/**
 * Builds the marquee's ring: the text, followed by a gap, padded
 * with spaces so the ring is at least width long.
 */
std::string make_ring(const std::string &text, std::size_t width) {
    std::size_t pad = marquee_gap;
    if (width > text.size() + pad) {
        pad = width - text.size();
    }
    return text + std::string(pad, ' ');
}

/**
 * Returns the width characters of the ring that should be
 * shown on screen right now.
 */
std::string current_frame(const std::string &ring, std::size_t width) {
    return ring.substr(0, width);
}

#ifdef _WIN32

static SHORT marquee_row = 0;

/**
 * Reserves the current console line for the marquee, followed by a blank line.
 */
void init_marquee() {
    std::cout.flush();
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    marquee_row = csbi.dwCursorPosition.Y;
    std::cout << "\n\n";
}

/**
 * Returns the width of the visible console window.
 */
static std::size_t console_width() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

/**
 * Writes line at the start of the marquee row without moving the cursor.
 */
static void draw_line(const std::string &line) {
    COORD pos = {0, marquee_row};
    DWORD written;
    WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), line.data(),
                                 static_cast<DWORD>(line.size()), pos, &written);
}

/**
 * posix branch needs this,
 * we include it here for consistency
 * but it doesn't do anything on windows
 */
static void restore_console() {}

#else

// ANSI escape codes to save and restore the cursor position
static const std::string save_cursor = "\0337";
static const std::string restore_cursor = "\0338";

// 1-based screen row of the marquee; 0 when not drawing to a terminal
static std::int32_t marquee_row = 0;
// screen height the scroll region was last set for
static std::int32_t region_bottom = 0;

/**
 * Writes s to stdout in one call where possible, so it is not split by
 * other output to the terminal.
 */
static void write_all(const std::string &s) {
    std::size_t done = 0;
    while (done < s.size()) {
        ssize_t n = write(STDOUT_FILENO, s.data() + done, s.size() - done);
        if (n <= 0) {
            return;
        }
        done += static_cast<std::size_t>(n);
    }
}

/**
 * Asks the terminal for the cursor's 1-based row.
 */
static bool query_cursor_row(std::int32_t &row) {
    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)) {
        return false;
    }
    termios old_attr;
    if (tcgetattr(STDIN_FILENO, &old_attr) != 0) {
        return false;
    }
    // read the reply without echoing it or waiting for enter; give up after 100ms
    termios raw = old_attr;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    // reply is ESC [ row ; col R
    write_all("\033[6n");
    std::string reply;
    char c;
    while (reply.size() < 32 && read(STDIN_FILENO, &c, 1) == 1) {
        reply += c;
        if (c == 'R') {
            break;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);

    std::size_t start = reply.rfind('\033');
    std::int32_t col;
    return start != std::string::npos &&
           std::sscanf(reply.c_str() + start, "\033[%" SCNd32 ";%" SCNd32 "R", &row,
                       &col) == 2;
}

static winsize terminal_size() {
    winsize ws{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    return ws;
}

/**
 * Confines scrolling to the lines below the marquee and its blank line, so
 * later output cannot scroll the marquee off its row.
 */
static void set_scroll_region(std::int32_t rows) {
    region_bottom = rows;
    std::int32_t top = marquee_row + 2;
    if (rows <= top) {
        return;
    }
    // setting the region moves the cursor to the top left
    write_all(save_cursor + "\033[" + std::to_string(top) + ";" + std::to_string(rows) + "r" +
              restore_cursor);
}

/**
 * Reserves the current terminal line for the marquee, followed by a blank line.
 */
void init_marquee() {
    std::cout << "\n\n" << std::flush;
    // asking after the newlines accounts for any scrolling they caused
    std::int32_t row;
    if (!query_cursor_row(row) || row <= 2) {
        return;
    }
    marquee_row = row - 2;
    set_scroll_region(terminal_size().ws_row);
}

/**
 * Returns the width of the terminal.
 */
static std::size_t console_width() {
    winsize ws = terminal_size();
    return ws.ws_col > 0 ? ws.ws_col : 80;
}

/**
 * Writes line at the start of the marquee row, then puts the cursor back.
 */
static void draw_line(const std::string &line) {
    if (marquee_row == 0) {
        return;
    }
    // resizing the terminal can reset the scroll region
    std::int32_t rows = terminal_size().ws_row;
    if (rows != region_bottom) {
        set_scroll_region(rows);
    }
    write_all(save_cursor + "\033[" + std::to_string(marquee_row) + ";1H" + line +
              restore_cursor);
}

/**
 * Resets the scroll region to the whole terminal.
 */
static void restore_console() {
    if (marquee_row == 0) {
        return;
    }
    write_all(save_cursor + "\033[r" + restore_cursor);
}

#endif

/**
 * Draws the marquee on the reserved line until stopped.
 */
static void run_marquee() {
    std::string ring, last_text;
    std::size_t last_width = 0;

    while (running) {
        std::size_t width = console_width();

        {
            std::lock_guard<std::mutex> lock(text_mutex);
            if (width != last_width || marquee_text != last_text) {
                last_width = width;
                last_text = marquee_text;
                ring = make_ring(last_text, width);
            }
        }

        draw_line(current_frame(ring, width));

        ring = rotate_left(ring);
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(speed_ms));
    }

    draw_line(std::string(last_width, ' '));
}

/**
 * Stops the marquee thread if it is running.
 */
static void stop_worker() {
    if (!running) {
        return;
    }
    running = false;
    worker.join();
}

/**
 * Stops the marquee thread and restores the console.
 */
void shutdown_marquee() {
    stop_worker();
    restore_console();
}

/**
 * Starts the marquee thread.
 */
bool start_marquee(const std::string &) {
    if (running) {
        std::cout << "Marquee is already running.\n";
        return true;
    }
    running = true;
    worker = std::thread(run_marquee);
    std::cout << "Marquee started.\n";
    return true;
}

/**
 * Stops the marquee thread.
 */
bool stop_marquee(const std::string &) {
    if (!running) {
        std::cout << "Marquee is not running.\n";
        return true;
    }
    stop_worker();
    std::cout << "Marquee stopped.\n";
    return true;
}

/**
 * Sets the marquee text to args.
 */
bool set_text(const std::string &args) {
    {
        std::lock_guard<std::mutex> lock(text_mutex);
        marquee_text = args;
    }
    std::cout << "Text saved for marquee: " << args << "\n";
    return true;
}

/**
 * Sets the marquee refresh delay in milliseconds.
 */
bool set_speed(const std::string &args) {
    std::string value = args;
    double ms;
    if (parse_to_double(value, ms) && ms >= 1) {
        speed_ms = ms;
        std::cout << "Animation speed set: " << ms << "ms\n\n";
    } else {
        std::cout << "Invalid argument for 'set_speed.' Usage: set_speed <ms> (Example: set_speed "
                     "10)\n\n";
    }
    return true;
}
