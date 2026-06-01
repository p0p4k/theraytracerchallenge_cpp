#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "matrix.h"
#include "ray.h"
#include "tuple.h"
#include <algorithm>
#include <limits>

class BoundingBox {
public:
  RayPoint min_point;
  RayPoint max_point;

  BoundingBox();
  BoundingBox(RayPoint min_p, RayPoint max_p);

  void add(const RayPoint &p);
  void add(const BoundingBox &box);
  bool contains(const RayPoint &p) const;
  bool contains(const BoundingBox &box) const;

  BoundingBox transform(const Matrix &m) const;

  bool intersects(const Ray &ray) const;
};

#endif
