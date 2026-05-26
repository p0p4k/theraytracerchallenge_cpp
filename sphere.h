#ifndef SPHERE_H
#define SPHERE_H

#include "shapes.h"
#include <cmath>

class Sphere : public Shape {
public:
  double radius;

  Sphere(double radius = 1.0, const Material &material = Material())
      : Shape(material), radius(radius) {}

  std::vector<Intersection>
  local_intersects(const Ray &local_ray) const override;
  RayVector local_normal_at(const RayPoint &p) const override;
};

#endif
