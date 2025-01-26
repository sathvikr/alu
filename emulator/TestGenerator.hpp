#pragma once
#include "RippleCarryAdder.hpp"
#include <string>
#include <vector>

class TestGenerator {
public:
    void runTest(const std::vector<bool>& a, const std::vector<bool>& b, 
                const std::vector<bool>& expected, bool expected_carry,
                const std::string& testName);
    void runAllTests();

private:
    std::string boolVectorToString(const std::vector<bool>& vec);
    bool compareVectors(const std::vector<bool>& actual, const std::vector<bool>& expected);
}; 