#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include "intersection.h"
#include "ray.h"
#include "shapes.h"
#include <algorithm>
#include <optional>

class Computations {
public:
  double t;
  Shape *object;
  RayPoint point;
  RayVector eyev;
  RayVector normalv;
  bool inside;
  RayPoint over_point = RayPoint(0, 0, 0);
  RayPoint under_point = RayPoint(0, 0, 0);
  RayVector reflectv = RayVector(0, 0, 0);
  double n1;
  double n2;

  Computations(
      const Intersection &intersection, const Ray &ray,
      const std::optional<std::vector<Intersection>> &xs = std::nullopt);
};

double schlick(const Computations &comps);

#endif
