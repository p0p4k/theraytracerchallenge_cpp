#ifndef PATTERN_H
#define PATTERN_H

#include "color.h"
#include "matrix.h"
#include "tuple.h"
#include <cmath>

class Shape;

class Pattern {
public:
  Matrix transform = Matrix::identity(4);
  Matrix inverse_transform = Matrix::identity(4);

  virtual ~Pattern() = default;

  void set_transform(const Matrix &t) {
    transform = t;
    inverse_transform = t.inverse(); // Cache it for performance
  }

  virtual Color pattern_at(const RayPoint &point) const = 0;
  Color pattern_at_object(Shape *object, const RayPoint &world_point) const;
};

class TestPattern : public Pattern {
public:
  TestPattern() = default;

  Color pattern_at(const RayPoint &point) const override {
    return Color(point.x, point.y, point.z);
  }
};

class StripePattern : public Pattern {
public:
  Color a;
  Color b;

  StripePattern(const Color &a, const Color &b) : a(a), b(b) {}

  Color pattern_at(const RayPoint &point) const override {
    if (static_cast<int>(std::floor(point.x)) % 2 == 0) {
      return a;
    }
    return b;
  }
};

class GradientPattern : public Pattern {
public:
  Color a;
  Color b;
  Color distance;

  GradientPattern(const Color &a, const Color &b)
      : a(a), b(b), distance(b - a) {}

  Color pattern_at(const RayPoint &point) const override {
    double fraction = point.x - std::floor(point.x);
    return a + distance * fraction;
  }
};

class RingPattern : public Pattern {
public:
  Color a;
  Color b;

  RingPattern(const Color &a, const Color &b) : a(a), b(b) {}

  Color pattern_at(const RayPoint &point) const override {
    double distance = std::sqrt(point.x * point.x + point.z * point.z);

    if (std::abs(static_cast<int>(std::floor(distance))) % 2 == 0) {
      return a;
    }
    return b;
  }
};

class CheckersPattern : public Pattern {
public:
  Color a;
  Color b;

  CheckersPattern(const Color &a, const Color &b) : a(a), b(b) {}

  Color pattern_at(const RayPoint &point) const override {
    int sum = static_cast<int>(std::floor(point.x)) +
              static_cast<int>(std::floor(point.y)) +
              static_cast<int>(std::floor(point.z));

    if (std::abs(sum) % 2 == 0) {
      return a;
    }
    return b;
  }
};

#endif
