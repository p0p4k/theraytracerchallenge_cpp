#include "plane.h"
#include "intersection.h"
#include "material.h"
#include "tuple.h"

Plane::Plane(const Material &material) : Shape(material) {}

RayVector Plane::local_normal_at(const RayPoint &, const Intersection *) const {
  return RayVector(0, 1, 0);
}

std::vector<Intersection> Plane::local_intersects(const Ray &local_ray) const {
  std::vector<Intersection> intersections;
  if (std::abs(local_ray.direction.y) < EPSILON) {
    return intersections;
  } else {
    double t = -local_ray.origin.y / local_ray.direction.y;
    intersections.push_back(Intersection(t, const_cast<Plane *>(this)));
    return intersections;
  }
}

BoundingBox Plane::bounds_of() const {
  double inf = std::numeric_limits<double>::infinity();
  return BoundingBox(RayPoint(-inf, 0, -inf), RayPoint(inf, 0, inf));
}
