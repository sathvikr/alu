#include "ALU.hpp"
#include "RippleCarryAdder.hpp"
#include <stdexcept>

ALU::ALU() {}

ALU::~ALU() {}

std::pair<uint64_t, bool> ALU::compute(uint64_t a, uint64_t b, uint8_t op) {
    switch (op) {
        case 0: return add(a, b);
        case 1: return sub(a, b);
        case 2: return mul(a, b);
        case 3: return div(a, b);
        case 4: return mod(a, b);
        case 5: return {twosComplement(a), false};
    }
}

std::pair<uint64_t, bool> ALU::add(uint64_t a, uint64_t b) {
    std::vector<bool> avec = intToBoolVector(a, 64);
    std::vector<bool> bvec = intToBoolVector(b, 64);    
    std::pair<std::vector<bool>, bool> result = RippleCarryAdder::add(avec, bvec);
    
    return {boolVectorToInt(result.first), 
        (avec[0] == 0 && bvec[0] == 0 && result.first[0] == 1) ||  // Positive overflow
        (avec[0] == 1 && bvec[0] == 1 && result.first[0] == 0)};   // Negative overflow
}

std::pair<uint64_t, bool> ALU::sub(uint64_t a, uint64_t b) {
    std::vector<bool> avec = intToBoolVector(a, 64);
    std::vector<bool> bvec = intToBoolVector(twosComplement(b), 64);
    std::pair<std::vector<bool>, bool> result = RippleCarryAdder::add(avec, bvec);

    return {boolVectorToInt(result.first), 
        (avec[0] == 0 && bvec[0] == 1 && result.first[0] == 1) ||  // Positive overflow
        (avec[0] == 1 && bvec[0] == 0 && result.first[0] == 0)};   // Negative overflow
}

uint64_t ALU::twosComplement(uint64_t a) {
    std::vector<bool> avec = intToBoolVector(a, 64);
    std::vector<bool> bvec = intToBoolVector(1, 64);

    for (size_t i = 0; i < 64; i++) { avec[i] = !avec[i]; }
    
    std::pair<std::vector<bool>, bool> result = RippleCarryAdder::add(avec, bvec);
    
    return boolVectorToInt(result.first);
}

std::vector<bool> ALU::intToBoolVector(uint64_t num, size_t n) {
    std::vector<bool> result(n);

    for (size_t i = 0; i < n; i++) { result[n - i] = (num >> i) & 1; }

    result[0] = (num >> n) & 1;
    
    return result;
}

uint64_t ALU::boolVectorToInt(const std::vector<bool>& vec) {
    uint64_t result = 0;
    const size_t n = vec.size() - 1;

    for (size_t i = 0; i < n; i++) {
        if (vec[n - i]) { result |= (1ULL << i); }
    }
    
    if (vec[0]) { result |= (1ULL << n); }

    return result;
}