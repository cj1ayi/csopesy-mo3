#ifndef MARQUEE_H
#define MARQUEE_H

#include <cstddef>
#include <string>

constexpr std::size_t marquee_gap = 4;

std::string rotate_left(const std::string &s);
std::string make_ring(const std::string &text, std::size_t width);
std::string current_frame(const std::string &ring, std::size_t width);

void reserve_marquee_line();
bool start_marquee();
bool stop_marquee();
void set_marquee_text(const std::string &text);
void set_marquee_speed(int ms);

#endif
