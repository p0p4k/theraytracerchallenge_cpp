#ifndef PLANE_H
#define PLANE_H

#include "material.h"
#include "matrix.h"
#include "shapes.h"
#include "tuple.h"

class Plane : public Shape {
public:
  Plane(const Material &material = Material());

  std::vector<Intersection>
  local_intersects(const Ray &local_ray) const override;
  RayVector local_normal_at(const RayPoint &) const override;
};

#endif
