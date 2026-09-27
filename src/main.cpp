#include <iostream>
#include <stdexcept>
#include <vector>

#include "helpers.h"
#include "marquee.h"

int main() {
    const std::string version_date = "2026-09-18";
    const std::vector<std::string> group_members = {
        "Billones, Francis",
        "Nacasabog, Joshua",
        "Santiago, Juan Ramon",
        "Tan, Roberta",
    };

    std::string input;
    std::string marquee_text;
    std::string marquee_ring = make_ring(marquee_text);
    int marquee_speed_ms = 100;

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
        getline(std::cin, input);

        // only the command is case-insensitive; arguments (e.g. marquee text) keep their case
        std::vector<std::string> extracted_input = parse_command(input);
        std::string command = to_lower(extracted_input[0]);

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
            marquee_ring = make_ring(marquee_text);
            std::cout << "Text saved for marquee: " << marquee_text << "\n";

        } else if (command == "set_speed") {
            if (extracted_input.size() < 2) {
                std::cout << "Usage: set_speed <milliseconds>\n";
                continue;
            }
            try {
                std::size_t parsed_len = 0;
                int new_speed = std::stoi(extracted_input[1], &parsed_len);
                if (parsed_len != extracted_input[1].size() || new_speed <= 0) {
                    throw std::invalid_argument("not a positive integer");
                }
                marquee_speed_ms = new_speed;
                std::cout << "Marquee refresh set to " << marquee_speed_ms << " ms\n";
            } catch (const std::exception &) {
                std::cout << "Invalid speed. Enter a positive whole number of milliseconds.\n";
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