#include <iostream>
#include "TestGenerator.hpp"

int main() {
    // Create test generator for 64-bit RCA
    TestGenerator tester;
    
    // Run all predefined tests
    tester.runAllTests();
    
    return 0;
}
