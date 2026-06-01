#ifndef SMOOTH_TRIANGLE_H
#define SMOOTH_TRIANGLE_H

#include "triangle.h"

class SmoothTriangle : public Triangle {
public:
  RayVector n1, n2, n3;
  SmoothTriangle(RayPoint p1, RayPoint p2, RayPoint p3, RayVector n1,
                 RayVector n2, RayVector n3,
                 const Material &material = Material());

  RayVector local_normal_at(const RayPoint &local_point,
                            const Intersection *hit = nullptr) const override;
};

#endif
