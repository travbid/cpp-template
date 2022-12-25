#include "add.hpp"

namespace {

float addInner(float a, float b) {
    return a + b;  //
}

}  // namespace

float add(float a, float b) {
    float ret = addInner(a, b);
    return ret;
}
