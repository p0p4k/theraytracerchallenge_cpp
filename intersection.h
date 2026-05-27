#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

class Shape;

class Intersection {
public:
  double t;
  Shape *object;
  Intersection(double t, Shape *object) : t(t), object(object) {}

  bool operator<(const Intersection &other) const { return t < other.t; }
  bool operator==(const Intersection &other) const {
    return (t == other.t) && (object == other.object);
  }
};
const Intersection *hit(const std::vector<Intersection> &Intersections);

#endif
