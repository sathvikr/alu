#include "TestGenerator.hpp"
#include <iostream>
#include <vector>

std::string TestGenerator::boolVectorToString(const std::vector<bool>& vec) {
    std::string result;
    // Print MSB to LSB (left to right), starting with sign bit
    for (bool b : vec) {
        result += b ? "1" : "0";
    }
    return result;
}

bool TestGenerator::compareVectors(const std::vector<bool>& actual, const std::vector<bool>& expected) {
    if (actual.size() != expected.size()) return false;
    for (size_t i = 0; i < actual.size(); i++) {
        if (static_cast<bool>(actual[i]) != static_cast<bool>(expected[i])) return false;
    }
    return true;
}

void TestGenerator::runTest(const std::vector<bool>& a, const std::vector<bool>& b, 
                          const std::vector<bool>& expected, bool expected_carry,
                          const std::string& testName) {
    std::pair<std::vector<bool>, bool> result = RippleCarryAdder::add(a, b);
    
    bool passed = compareVectors(result.first, expected) && (result.second == expected_carry);
    
    std::cout << "\n=== " << testName << " ===" << std::endl;
    std::cout << "Input A:  " << boolVectorToString(a) << std::endl;
    std::cout << "Input B:  " << boolVectorToString(b) << std::endl;
    std::cout << "Expected: " << boolVectorToString(expected) << " (carry: " << expected_carry << ")" << std::endl;
    std::cout << "Got:      " << boolVectorToString(result.first) << " (carry: " << result.second << ")" << std::endl;
    std::cout << "Status:   " << (passed ? "PASS" : "FAIL") << std::endl;
}

// Helper function to create a vector with n+1 bits (sign bit + n value bits)
std::vector<bool> makeNBitVector(const std::vector<bool>& bits, size_t n) {
    if (bits.size() > n) {
        throw std::invalid_argument("Input bits exceed target size");
    }
    
    std::vector<bool> result(n + 1, false); // +1 for sign bit
    // Place bits at the end (LSB at highest index)
    for (size_t i = 0; i < bits.size(); i++) {
        result[n - i] = bits[i];
    }
    // Sign bit at [0] remains 0 (positive number)
    return result;
}

void TestGenerator::runAllTests() {
    const size_t N = 8; // Use 8-bit numbers (9 bits with sign)
    
    // Test case 1: 0 + 0 = 0
    runTest(makeNBitVector({0}, N), makeNBitVector({0}, N), makeNBitVector({0}, N), false,
            "Test 1: 0 + 0 = 0");
    
    // Test case 2: 1 + 1 = 2
    runTest(makeNBitVector({1}, N), makeNBitVector({1}, N), makeNBitVector({0,1,0}, N), false,
            "Test 2: 1 + 1 = 2");
    
    // Test case 3: 255 + 1 = 256 (overflow for 8-bit)
    runTest(makeNBitVector({1,1,1,1,1,1,1,1}, N), // 255
           makeNBitVector({1}, N),                 // 1
           makeNBitVector({0,0,0,0,0,0,0,0,0}, N), // 0 with overflow
           true,
           "Test 3: 255 + 1 = 256 (overflow)");
    
    // Test case 4: 127 + 1 = 128 (sets sign bit)
    runTest(makeNBitVector({1,1,1,1,1,1,1}, N), // 127
           makeNBitVector({1}, N),               // 1
           makeNBitVector({1,0,0,0,0,0,0,0}, N), // 128 (sign bit set)
           false,
           "Test 4: 127 + 1 = 128 (sets sign bit)");
    
    // Test case 5: Maximum 8-bit number + 1 (overflow)
    std::vector<bool> max8(N+1, true);  // All 1s including sign bit
    std::vector<bool> one = makeNBitVector({1}, N);
    std::vector<bool> zero(N+1, false); // All 0s including sign bit
    runTest(max8, one, zero, true,
            "Test 5: MAX_8BIT + 1 = 0 (overflow)");
} 