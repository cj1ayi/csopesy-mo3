#include <iostream>
#include <vector>

#include "helpers.h"

int main() {
    const std::string version_date = "2026-09-18";
    const std::vector<std::string> group_members = {
        "Billones, Francis",
        "Nacasabog, Joshua N.",
        "Santiago, Juan Ramon",
        "Tan, Roberta",
    };

    std::string input;
    std::string marquee_text;
    double animation_speed = 10; // default 10ms

    std::cout << "Welcome to CSOPESY!\n\n";

    // group members
    std::cout << "Group Developer:\n";
    for (auto &mem : group_members) {
        std::cout << mem << '\n';
    }
    std::cout << '\n';

    // version date
    std::cout << "Version date: " << version_date << "\n\n";

    // main loop
    while (true) {
        std::cout << "Command>";
        if (!getline(std::cin, input)) {
            std::cout << "\nEOF reached or input stream failed. Terminating console..." << std::endl;
            break;
        }

        input = to_lower(input);
        std::vector<std::string> extracted_input = parse_command(input);
        std::string command = extracted_input[0];

        // argument count error checking
        if (command == "help" || command == "start_marquee" || command == "stop_marquee") {
            if (extracted_input.size() > 1) {
                std::cout << "Command '" << command << "' does not accept any arguments. Usage: " << command << "\n\n";
                continue;
            }
        }

        if (command == "help") {
            print_help();
        } else if (command == "start_marquee") {
            // TODO
            std::cout << "TODO: start_marquee\n";
        } else if (command == "stop_marquee") {
            // TODO
            std::cout << "TODO: stop_marquee\n";
        } else if (command == "set_text") {
            if (extracted_input.size() < 2) {
                marquee_text = "";
            } else {
                marquee_text = extracted_input[1];
            }
            std::cout << "Text saved for marquee: " << marquee_text << "\n";
        } else if (command == "set_speed") {
            if (parse_to_double(extracted_input[1], animation_speed)) {
                std::cout << "Animation speed set: " << animation_speed << "ms\n";
                // TODO
                std::cout << "TODO: set_speed\n\n";
            } else {
                std::cout << "Invalid argument for 'set_speed.' Usage: set_speed <ms> (Example: set_speed 10)\n\n";
            }

            
        } else if (command == "exit") {
            std::cout << "Terminating console..." << std::endl;
            break;
        } else {
            std::cout << "Unknown command. Type HELP to view the list of available commands.\n";
        }
    }

    return 0;
}