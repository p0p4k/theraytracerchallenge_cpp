#ifndef COLOR_H
#define COLOR_H

#include "tuple.h"
#include "utilities.h"
;

struct Color {
  double r, g, b;

  Color(double r, double g, double b) : r(r), g(g), b(b) {}

  bool operator==(const Color &other) const {
    return equal(r, other.r) && equal(g, other.g) && equal(b, other.b);
  }

  Color operator+(const Color &other) const {
    return Color(r + other.r, g + other.g, b + other.b);
  }
  Color operator-(const Color &other) const {
    return Color(r - other.r, g - other.g, b - other.b);
  }
  Color operator*(const double scalar) const {
    return Color(r * scalar, g * scalar, b * scalar);
  }

  Color operator*(const Color &other) const {
    return Color(r * other.r, g * other.g, b * other.b);
  }

  void print_color() const {
    std::cout << "r: " << r << " g: " << g << " b: " << b << std::endl;
  }
};

const Color COLOR_BLACK = Color(0, 0, 0);
const Color COLOR_WHITE = Color(1, 1, 1);

#endif
