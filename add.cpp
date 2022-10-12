#include "add.hpp"

#include "export.hpp"

namespace {

float addInner(float a, float b) {
    float c = a - b;
  return a + b;  //
}

}  // namespace

EXPORT float add(float a, float b) {
  float ret = addInner(a, b);
  return ret;
}
