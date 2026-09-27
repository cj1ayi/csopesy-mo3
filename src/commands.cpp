#include "commands.h"

#include <iomanip>
#include <iostream>
#include <vector>

#include "helpers.h"

static std::vector<Command> commands;

/**
 * Adds a command to the registry.
 */
void register_command(const Command &cmd) {
    commands.push_back(cmd);
}

/**
 * Looks up and runs the command in input. Returns false when the program should exit.
 */
bool run_command(std::string &input) {
    std::vector<std::string> parts = parse_command(input);
    std::string name = to_lower(parts[0]);
    std::string args = parts.size() > 1 ? parts[1] : "";

    for (const Command &cmd : commands) {
        if (cmd.name != name) {
            continue;
        }
        if (!cmd.accepts_args && !args.empty()) {
            std::cout << "Command '" << name << "' does not accept any arguments. Usage: " << name
                      << "\n\n";
            return true;
        }
        return cmd.run(args);
    }

    std::cout << "Unknown command. Type 'help' to view the list of available commands.\n";
    return true;
}

/**
 * Prints the usage and description of every registered command.
 */
void print_commands() {
    std::cout << "Available commands:\n";
    for (const Command &cmd : commands) {
        std::cout << "  " << std::left << std::setw(17) << cmd.usage << "- " << cmd.description
                  << "\n";
    }
    std::cout << "\n";
}
