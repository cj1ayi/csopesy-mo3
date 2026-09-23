#ifndef MARQUEE_H
#define MARQUEE_H

#include <cstddef>
#include <string>

constexpr std::size_t marquee_width = 40;
constexpr std::size_t marquee_gap = 4;

std::string rotate_left(const std::string &s);
std::string make_ring(const std::string &text);
std::string current_frame(const std::string &ring);

#endif
