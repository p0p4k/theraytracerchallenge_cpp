#include "triangle.h"
#include "intersection.h"
#include "utilities.h" // For EPSILON and equal()
#include <cmath>

Triangle::Triangle(RayPoint p1, RayPoint p2, RayPoint p3,
                   const Material &material)
    : Shape(material), p1(p1), p2(p2), p3(p3), e1(p2 - p1), e2(p3 - p1),
      normal((p3 - p1).cross(p2 - p1).normalize()) {
  e1 = p2 - p1;
  e2 = p3 - p1;
  normal = e2.cross(e1).normalize();
}

RayVector Triangle::local_normal_at(const RayPoint &,
                                    const Intersection *) const {
  return normal;
}

BoundingBox Triangle::bounds_of() const {
  BoundingBox box;
  box.add(p1);
  box.add(p2);
  box.add(p3);
  return box;
}

std::vector<Intersection>
Triangle::local_intersects(const Ray &local_ray) const {
  std::vector<Intersection> intersections;

  RayVector dir_cross_e2 = local_ray.direction.cross(e2);
  double det = e1.dot(dir_cross_e2);

  if (std::abs(det) < EPSILON) {
    return intersections;
  }

  double f = 1.0 / det;
  RayVector p1_to_origin = local_ray.origin - p1;
  double u = f * p1_to_origin.dot(dir_cross_e2);

  if (u < 0 || u > 1) {
    return intersections;
  }

  RayVector origin_cross_e1 = p1_to_origin.cross(e1);
  double v = f * local_ray.direction.dot(origin_cross_e1);

  if (v < 0 || (u + v) > 1) {
    return intersections;
  }

  double t = f * e2.dot(origin_cross_e1);
  intersections.push_back(Intersection(t, const_cast<Triangle *>(this), u, v));

  return intersections;
}
