#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

class Shape;

class Intersection {
public:
  double t;
  int id;
  const Shape *object;
  Intersection(double t, const Shape *object) : t(t), object(object) {}

  bool operator<(const Intersection &other) const { return t < other.t; }
};
const Intersection *hit(const std::vector<Intersection> &Intersections);

#endif
