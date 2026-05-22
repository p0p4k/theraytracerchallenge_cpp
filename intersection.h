#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

class Sphere;

class Intersection {
public:
  double t;
  int id;
  const Sphere *object;
  Intersection(double t, const Sphere *object) : t(t), object(object) {}
};

const Intersection *hit(const std::vector<Intersection> &Intersections);

#endif
