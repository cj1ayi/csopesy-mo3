#include "helpers.h"
#include <iostream>
#include <algorithm>
#include <cctype>
using namespace std;

/**
 * Prints the list of available commands.
 */
void printHelp()
{
    cout    << "Available commands:\n"
            << "  help          - show list of available commands\n"
            << "  start_marquee - start the animation\n"
            << "  stop_marquee  - stop the animation\n"
            << "  set_text      - set marquee text\n"
            << "  set_speed     - set refresh speed (ms)\n"
            << "  exit          - quit the program\n";
}

/**
 * Converts a string to lowercase
 */
string toLower(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}