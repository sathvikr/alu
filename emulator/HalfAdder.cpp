#include "HalfAdder.hpp"

std::pair<bool, bool> HalfAdder::add(bool a, bool b) {
    return {a ^ b, a & b}; // {sum, carry}
} 