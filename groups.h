#ifndef GROUPS_H
#define GROUPS_H

#include "intersection.h"
#include "material.h"
#include "shapes.h"
#include "tuple.h"
#include <algorithm>
#include <vector>

class Group : public Shape {
public:
  Group(const Material &material = Material());

  std::vector<Intersection>
  local_intersects(const Ray &local_ray) const override;
  RayVector local_normal_at(const RayPoint &) const override;

  std::vector<Shape *> child;
  void add_child(Shape *shape);

  BoundingBox bounds_of() const override;
};

#endif
