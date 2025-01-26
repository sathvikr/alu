#pragma once
#include <utility>

class HalfAdder {
public:
    // Returns {sum, carry}
    static std::pair<bool, bool> add(bool a, bool b);
};