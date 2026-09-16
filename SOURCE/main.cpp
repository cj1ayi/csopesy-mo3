#include <iostream>
#include "helpers.h"

int main()
{
    std::string command;

    while (true)
    {
        std::cout << ">";
        getline(std::cin, command);

        command = toLower(command);

        if (command == "help")
        {
            printHelp();
        }
        else if (command == "start_marquee")
        {
            // TODO
            std::cout << "TODO: start_marquee\n";
        }
        else if (command == "stop_marquee")
        {
            // TODO
            std::cout << "TODO: stop_marquee\n";
        }
        else if (command == "set_text")
        {
            // TODO
            std::cout << "TODO: set_text\n";
        }
        else if (command == "set_speed")
        {
            // TODO
            std::cout << "TODO: set_speed\n";
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            std::cout << "Unknown command. Type HELP to view the list of available commands.\n";
        }
    }

    return 0;
}