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
    std::string marquee_text;

    std::system("cls");
    std::cout << "Welcome to CSOPESY!\n\n";
    reserve_marquee_line();
    std::cout << '\n';

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
            stop_marquee();
            break;
        }

        std::vector<std::string> extracted_input = parse_command(input);
        std::string command = to_lower(extracted_input[0]);

        if (command == "help") {
            print_help();
        } else if (command == "start_marquee") {
            if (start_marquee()) {
                std::cout << "Marquee started.\n";
            } else {
                std::cout << "Marquee is already running.\n";
            }
        } else if (command == "stop_marquee") {
            if (stop_marquee()) {
                std::cout << "Marquee stopped.\n";
            } else {
                std::cout << "Marquee is not running.\n";
            }
        } else if (command == "set_text") {
            if (extracted_input.size() < 2) {
                marquee_text = "";
            } else {
                marquee_text = extracted_input[1];
            }
            set_marquee_text(marquee_text);
            std::cout << "Text saved for marquee: " << marquee_text << "\n";
        } else if (command == "set_speed") {
            int ms = 0;
            try {
                ms = extracted_input.size() < 2 ? 0 : std::stoi(extracted_input[1]);
            } catch (const std::exception &) {
            }
            if (ms <= 0) {
                std::cout << "Usage: set_speed <milliseconds greater than 0>\n";
            } else {
                set_marquee_speed(ms);
                std::cout << "Marquee speed set to " << ms << " ms.\n";
            }
        } else if (command == "exit") {
            stop_marquee();
            std::cout << "Terminating console..." << std::endl;
            break;
        } else {
            std::cout << "Unknown command. Type HELP to view the list of available commands.\n";
        }
    }

    return 0;
}