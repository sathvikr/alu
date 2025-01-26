#pragma once
#include "FullAdder.hpp"
#include <vector>
#include <utility>

class RippleCarryAdder {
public:
    static std::pair<std::vector<bool>, bool> add(const std::vector<bool>& a, const std::vector<bool>& b);
};