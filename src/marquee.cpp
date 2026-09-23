#include "marquee.h"

/**
 * Rotates a string one position to the left: the first character
 * is moved to the end.
 */
std::string rotate_left(const std::string &s) {
    if (s.empty()) {
        return s;
    }
    char first_char = s[0];
    std::string rem_str = s.substr(1);
    return rem_str + first_char;
}

/**
 * Builds the marquee's ring: the text, followed by a gap, padded
 * with spaces so the ring is at least marquee_width long.
 */
std::string make_ring(const std::string &text) {
    std::string spaces(marquee_gap, ' ');
    std::string ring = text + spaces; 
    return "";
}

/**
 * Returns the marquee_width characters of the ring that should be
 * shown on screen right now.
 */
std::string current_frame(const std::string &ring) {
    // TODO 
    return "";
}
