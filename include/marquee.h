#ifndef MARQUEE_H
#define MARQUEE_H

#include <cstddef>
#include <string>

constexpr std::size_t marquee_gap = 4;

std::string rotate_left(const std::string &s);
std::string make_ring(const std::string &text, std::size_t width);
std::string current_frame(const std::string &ring, std::size_t width);

void init_marquee();
void shutdown_marquee();

bool start_marquee(const std::string &args);
bool stop_marquee(const std::string &args);
bool set_text(const std::string &args);
bool set_speed(const std::string &args);

#endif
