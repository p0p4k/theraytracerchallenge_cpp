#include "utilities.h"

bool equal(double a, double b) {
  if (std::abs(a - b) < EPSILON)
    return true;
  else {
    return false;
  }
}
