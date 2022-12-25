#include "sub.hpp"

namespace {

float subInner(float a, float b) {
    return a - b;  //
}

}  // namespace

float sub(float a, float b) {
    float ret = subInner(a, b);
    return ret;
}
