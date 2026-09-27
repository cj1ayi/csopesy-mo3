#include <cstdlib>
#include <iostream>
#include <vector>

#include "commands.h"
#include "marquee.h"

static bool help(const std::string &) {
    print_commands();
    return true;
}

static bool exit_program(const std::string &) {
    std::cout << "Terminating console..." << std::endl;
    return false;
}

int main() {
    const std::string version_date = "2026-09-18";
    const std::vector<std::string> group_members = {
        "Billones, Francis",
        "Nacasabog, Joshua",
        "Santiago, Juan Ramon",
        "Tan, Roberta",
    };

    std::string input;

    register_command({"help", "help", "show list of available commands", false, help});
    register_command({"start_marquee", "start_marquee", "start the animation", false, start_marquee});
    register_command({"stop_marquee", "stop_marquee", "stop the animation", false, stop_marquee});
    register_command({"set_text", "set_text <text>",
                      "set marquee text (Example: set_text Hello World!)", true, set_text});
    register_command({"set_speed", "set_speed <ms>",
                      "set refresh speed in ms (Example: set_speed 10)", true, set_speed});
    register_command({"exit", "exit", "quit the program", true, exit_program});

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

        if (!run_command(input)) {
            break;
        }
    }

    shutdown_marquee();
    return 0;
}
