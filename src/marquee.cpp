#include "marquee.h"

#include <windows.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "helpers.h"

static SHORT marquee_row = 0;
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
 * Draws the marquee on the reserved line until stopped.
 */
static void run_marquee() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string ring, last_text;
    std::size_t last_width = 0;
    COORD pos = {0, marquee_row};

    while (running) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(out, &csbi);
        std::size_t width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        {
            std::lock_guard<std::mutex> lock(text_mutex);
            if (width != last_width || marquee_text != last_text) {
                last_width = width;
                last_text = marquee_text;
                ring = make_ring(last_text, width);
            }
        }

        // writes at pos without moving the cursor
        std::string frame = current_frame(ring, width);
        DWORD written;
        WriteConsoleOutputCharacterA(out, frame.data(), frame.size(), pos, &written);

        ring = rotate_left(ring);
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(speed_ms));
    }

    DWORD written;
    FillConsoleOutputCharacterA(out, ' ', last_width, pos, &written);
}

/**
 * Stops the marquee thread if it is running.
 */
void shutdown_marquee() {
    if (!running) {
        return;
    }
    running = false;
    worker.join();
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
    shutdown_marquee();
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
        std::cout << "Invalid argument for 'set_speed.' Usage: set_speed <ms> (Example: set_speed 10)\n\n";
    }
    return true;
}
