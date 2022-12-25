#include "add.hpp"

int main(int argc, char **argv) {
    const float result = add(static_cast<float>(argc), static_cast<float>(argv[0][0]));
    return static_cast<int>(result);
}
