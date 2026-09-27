#include "helpers.h"

#include <algorithm>
#include <stdexcept>

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

/**
 * Converts a string into a double if possible.
 */
bool parse_to_double(std::string &input, double &result) {
    try {
        size_t processed_chars = 0;

        // convert to double
        double value = std::stod(input, &processed_chars);

        // check if all characters were parsed
        if (processed_chars != input.length()) {
            return false;
        }

        result = value;
        return true;
    } catch (...) {
        return false;
    }

    return false;
}