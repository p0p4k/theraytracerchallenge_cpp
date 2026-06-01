#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "bounding_box.h"
#include "shapes.h"
#include "tuple.h"
#include <vector>

class Triangle : public Shape {
public:
  RayPoint p1, p2, p3;
  RayVector e1, e2;
  RayVector normal;

  Triangle(RayPoint p1, RayPoint p2, RayPoint p3,
           const Material &material = Material());

  std::vector<Intersection>
  local_intersects(const Ray &local_ray) const override;
  RayVector local_normal_at(const RayPoint &local_point,
                            const Intersection *hit = nullptr) const override;
  BoundingBox bounds_of() const override;
};

#endif
