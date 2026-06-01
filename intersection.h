#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

class Shape;

class Intersection {
public:
  double t;
  Shape *object;
  double u;
  double v;
  Intersection(double t, Shape *object, double u = 0.0, double v = 0.0)
      : t(t), object(object), u(u), v(v) {}

  bool operator<(const Intersection &other) const { return t < other.t; }
  bool operator==(const Intersection &other) const {
    return (t == other.t) && (object == other.object);
  }
};
const Intersection *hit(const std::vector<Intersection> &Intersections);

#endif
