#include <cstdlib>
#include <iostream>
#include <vector>

#include "commands.h"
#include "helpers.h"
#include "marquee.h"

static bool help(const std::string &) {
    print_help();
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

    register_command({"help", false, help});
    register_command({"start_marquee", false, start_marquee});
    register_command({"stop_marquee", false, stop_marquee});
    register_command({"set_text", true, set_text});
    register_command({"set_speed", true, set_speed});
    register_command({"exit", true, exit_program});

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
