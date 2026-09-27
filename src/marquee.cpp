#include "marquee.h"

#include <windows.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

static SHORT marquee_row = 0;
static std::thread worker;
static std::atomic<bool> running{false};
static std::atomic<int> speed_ms{100};
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
 * Reserves the current console line for the marquee.
 */
void reserve_marquee_line() {
    std::cout.flush();
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    marquee_row = csbi.dwCursorPosition.Y;
    std::cout << '\n';
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
        std::this_thread::sleep_for(std::chrono::milliseconds(speed_ms));
    }

    DWORD written;
    FillConsoleOutputCharacterA(out, ' ', last_width, pos, &written);
}

/**
 * Starts the marquee thread. Returns false if already running.
 */
bool start_marquee() {
    if (running) {
        return false;
    }
    running = true;
    worker = std::thread(run_marquee);
    return true;
}

/**
 * Stops the marquee thread. Returns false if it was not running.
 */
bool stop_marquee() {
    if (!running) {
        return false;
    }
    running = false;
    worker.join();
    return true;
}

void set_marquee_text(const std::string &text) {
    std::lock_guard<std::mutex> lock(text_mutex);
    marquee_text = text;
}

void set_marquee_speed(int ms) {
    speed_ms = ms;
}
