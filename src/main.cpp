#include <cstdlib>
#include <iostream>
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

    std::system("cls");
    std::cout << "Welcome to CSOPESY!\n\n";
    init_marquee();

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
            std::cout << "\nEOF reached or input stream failed. Terminating console..."
                      << std::endl;
            break;
        }

        std::vector<std::string> extracted_input = parse_command(input);
        std::string command = to_lower(extracted_input[0]);
        std::string args = extracted_input.size() > 1 ? extracted_input[1] : "";

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
            start_marquee(args);
        } else if (command == "stop_marquee") {
            stop_marquee(args);
        } else if (command == "set_text") {
            set_text(args);
        } else if (command == "set_speed") {
            set_speed(args);
        } else if (command == "exit") {
            std::cout << "Terminating console..." << std::endl;
            break;
        } else {
            std::cout << "Unknown command. Type 'help' to view the list of available commands.\n";
        }
    }

    shutdown_marquee();
    return 0;
}