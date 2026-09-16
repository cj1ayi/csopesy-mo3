#include <iostream>
#include "helpers.h"
using namespace std;

int main()
{
    string command;

    while (true)
    {
        cout << ">";
        getline(cin, command);

        command = toLower(command);

        if(command == "help")
        {
            printHelp();
        }
        else if (command == "start_marquee")
        {
            //TODO
            cout << "TODO: start_marquee\n";
        }
        else if (command == "stop_marquee")
        {
            //TODO
            cout << "TODO: stop_marquee\n";
        }
        else if (command == "set_text")
        {
            //TODO
            cout << "TODO: set_text\n";
        }
        else if (command == "set_speed")
        {
            //TODO
            cout << "TODO: set_speed\n";
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            cout << "Unknown command. Type HELP to view the list of available commands.\n";
        }
    }

    return 0;
}