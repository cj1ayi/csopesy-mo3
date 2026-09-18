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

/**
 * Separate command from arguments
 */
std::vector<std::string> parse_command(std::string &input) {
    std::vector<std::string> result;

    auto idx = input.find(' ');
    if (idx == std::string::npos) {
        result.push_back(input);
        return result;
    }

    std::string command = std::string(input.begin(), input.begin() + idx);
    result.push_back(command);

    if (idx + 1 == input.size()) {
        return result;
    }

    std::string unparsed_arguments = std::string(input.begin() + idx + 1, input.end());
    result.push_back(unparsed_arguments);

    return result;
}