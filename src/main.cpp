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

        input = to_lower(input);
        std::vector<std::string> extracted_input = parse_command(input);
        std::string command = extracted_input[0];

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
            // TODO
            std::cout << "TODO: set_speed\n";
        } else if (command == "exit") {
            std::cout << "Terminating console..." << std::endl;
            break;
        } else {
            std::cout << "Unknown command. Type HELP to view the list of available commands.\n";
        }
    }

    return 0;
}