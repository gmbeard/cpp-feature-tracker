#include "tests.hpp"
#include "config.h"
#include <iterator>
#include <cstring>
#include <iostream>

auto main() -> int {

    std::cout << CMAKE_CXX_COMPILER_ID
        << " (" << CMAKE_CXX_COMPILER_VERSION << ")\n";

    std::cout << "SUPPORTED:\n";
    for (auto f : SUPPORTED) {
        if (f) {
            std::cout << "\t" << f << "\n";
        }
    }

    std::cout << "\nUNSUPPORTED:\n";
    for (auto f : UNSUPPORTED) {
        if (f) {
            std::cout << "\t" << f << "\n";
        }
    }
}
