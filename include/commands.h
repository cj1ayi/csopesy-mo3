#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

// returns false to end the program loop
using CommandFn = bool (*)(const std::string &args);

struct Command {
    std::string name;
    std::string usage;
    std::string description;
    bool accepts_args;
    CommandFn run;
};

void register_command(const Command &cmd);
bool run_command(std::string &input);
void print_commands();

#endif
