#include "FullAdder.hpp"

std::pair<bool, bool> FullAdder::add(bool a, bool b, bool cin) {
    // First half adder
    std::pair<bool, bool> ha1 = HalfAdder::add(a, b);
    
    // Second half adder
    std::pair<bool, bool> ha2 = HalfAdder::add(ha1.first, cin);
    
    // Final carry is OR of both carries
    return {ha2.first, ha1.second || ha2.second};
} 