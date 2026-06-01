#ifndef CUBE_H
#define CUBE_H

#include "material.h"
#include "shapes.h"

class Cube : public Shape {
public:
  Cube(const Material &material = Material());

  std::vector<Intersection>
  local_intersects(const Ray &local_ray) const override;
  RayVector local_normal_at(const RayPoint &local_point,
                            const Intersection *hit = nullptr) const override;
  BoundingBox bounds_of() const override;
};

std::pair<double, double> check_axis(double origin, double direction);

#endif
