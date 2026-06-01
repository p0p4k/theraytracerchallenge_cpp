#include "smooth_triangle.h"

SmoothTriangle::SmoothTriangle(RayPoint p1, RayPoint p2, RayPoint p3,
                               RayVector n1, RayVector n2, RayVector n3,
                               const Material &material)
    : Triangle(p1, p2, p3, material), n1(n1), n2(n2), n3(n3) {}

RayVector SmoothTriangle::local_normal_at(const RayPoint &,
                                          const Intersection *hit) const {
  return (n2 * hit->u) + (n3 * hit->v) + (n1 * (1.0 - hit->u - hit->v));
}
