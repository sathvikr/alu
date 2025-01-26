#pragma once

#include <vector>
#include <cstdint>
#include <utility>

class ALU {
    public:
        ALU();
        ~ALU();

        std::pair<uint64_t, bool> add(uint64_t a, uint64_t b);
        std::pair<uint64_t, bool> sub(uint64_t a, uint64_t b);
        std::pair<uint64_t, bool> mul(uint64_t a, uint64_t b);
        std::pair<uint64_t, bool> div(uint64_t a, uint64_t b);
        std::pair<uint64_t, bool> mod(uint64_t a, uint64_t b);

        uint64_t twosComplement(uint64_t a);

        std::pair<uint64_t, bool> compute(uint64_t a, uint64_t b, uint8_t op);

    private:
        static std::vector<bool> intToBoolVector(uint64_t num, size_t n);
        static uint64_t boolVectorToInt(const std::vector<bool>& vec);
};