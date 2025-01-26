#pragma once
#include "HalfAdder.hpp"
#include <utility>

class FullAdder {
public:
    // Returns {sum, carry}
    static std::pair<bool, bool> add(bool a, bool b, bool cin);
};