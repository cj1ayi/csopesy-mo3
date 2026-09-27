#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <vector>

std::string to_lower(std::string);
std::vector<std::string> parse_command(std::string &);
bool parse_to_double(std::string &, double &);

#endif