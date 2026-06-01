#ifndef CONE_H
#define CONE_H

#include "intersection.h"
#include "material.h"
#include "ray.h"
#include "shapes.h"
#include "tuple.h"
#include <limits>
#include <vector>

class Cone : public Shape {
public:
  bool closed;

  double minimum = -std::numeric_limits<double>::infinity();
  double maximum = std::numeric_limits<double>::infinity();

  Cone(const Material &material = Material(), bool closed = false);

  std::vector<Intersection>
  local_intersects(const Ray &local_ray) const override;
  RayVector local_normal_at(const RayPoint &point) const override;

  void intersect_caps(const Ray &ray, std::vector<Intersection> *xs) const;
  BoundingBox bounds_of() const override;
};

bool check_cone_cap(const Ray &ray, double t, double cap_y);

#endif
