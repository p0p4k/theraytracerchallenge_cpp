#ifndef CYLINDER_H
#define CYLINDER_H

#include "intersection.h"
#include "material.h"
#include "ray.h"
#include "shapes.h"
#include "tuple.h"
#include "utilities.h"
#include <limits>
#include <vector>

class Cylinder : public Shape {
public:
  bool closed;

  double minimum = -std::numeric_limits<double>::infinity();
  double maximum = std::numeric_limits<double>::infinity();

  Cylinder(const Material &material = Material(), bool closed = false);

  std::vector<Intersection>
  local_intersects(const Ray &local_ray) const override;
  RayVector local_normal_at(const RayPoint &point) const override;

  void intersect_caps(const Ray &ray, std::vector<Intersection> *xs) const;
  BoundingBox bounds_of() const override;
};

double check_cap(const Ray &ray, double t);

#endif
