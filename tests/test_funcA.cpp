#include "../MyTrigFunction.h"
#include <iostream>
#include <cmath>
#include <cassert>

int main() {
    MyTrigFunction trigFunc;

    // Test FuncA with 5 terms
    double result = trigFunc.FuncA(5);
    double expected = 0.58984;
    double tolerance = 1e-5;

    // Assert that the result is within the tolerance
    assert(std::abs(result - expected) < tolerance && "FuncA(5) test failed!");

    std::cout << "Test passed for FuncA(5)" << std::endl;
    return 0;
}
