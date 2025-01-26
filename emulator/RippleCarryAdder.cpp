#include "RippleCarryAdder.hpp"
#include <stdexcept>

std::pair<std::vector<bool>, bool> RippleCarryAdder::add(const std::vector<bool>& a, const std::vector<bool>& b) {
    const size_t n = a.size(); std::vector<bool> sum(n);
    std::pair<bool, bool> bit0 = FullAdder::add(a[n-1], b[n-1], false);
    sum[n-1] = bit0.first; bool carry = bit0.second;

    for (size_t i = n-2; i < n; --i) {
        std::pair<bool, bool> bit_i = FullAdder::add(a[i], b[i], carry);
        sum[i] = bit_i.first; carry = bit_i.second;
    }

    return {sum, carry};
} 