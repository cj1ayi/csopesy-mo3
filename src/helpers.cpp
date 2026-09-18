#include "helpers.h"

#include <algorithm>
#include <iostream>

/**
 * Prints the list of available commands.
 */
void print_help() {
    std::string help_text = "Available commands:\n"
                        "  help          - show list of available commands\n"
                        "  start_marquee - start the animation\n"
                        "  stop_marquee  - stop the animation\n"
                        "  set_text      - set marquee text\n"
                        "  set_speed     - set refresh speed (ms)\n"
                        "  exit          - quit the program\n";
    std::cout << help_text;
}

/**
 * Converts a string to lowercase
 */
std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return s;
}