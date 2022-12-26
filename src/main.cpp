#include "add.hpp"

#include <iostream>

int main(int argc, char **argv) {
    const float result = add(static_cast<float>(argc), static_cast<float>(argv[0][0]));
    std::cout << "result: " << result << "\n";
    return static_cast<int>(result);
}
