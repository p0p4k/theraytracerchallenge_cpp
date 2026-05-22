#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
class Intersection {
public:
  double t;
  int id;
  Intersection(double t, int id) : t(t), id(id) {}
};

const Intersection *hit(const std::vector<Intersection> &Intersections);

#endif
