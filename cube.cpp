#include "cube.h"
#include "material.h"
#include "tuple.h"
#include <algorithm>

Cube::Cube(const Material &material) : Shape(material) {}

RayVector Cube::local_normal_at(const RayPoint &point) const {
  double maxc =
      std::max({std::abs(point.x), std::abs(point.y), std::abs(point.z)});

  if (maxc == std::abs(point.x)) {
    return RayVector(point.x > 0 ? 1.0 : -1.0, 0.0, 0.0);
  }
  if (maxc == std::abs(point.y)) {
    return RayVector(0.0, point.y > 0 ? 1.0 : -1.0, 0.0);
  }

  return RayVector(0.0, 0.0, point.z > 0 ? 1.0 : -1.0);
}

std::pair<double, double> check_axis(double origin, double direction) {
  double tmin_numerator = (-1.0 - origin);
  double tmax_numerator = (1.0 - origin);

  double tmin, tmax;

  if (std::abs(direction) >= EPSILON) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  } else {
    tmin = tmin_numerator * INF;
    tmax = tmax_numerator * INF;
  }

  if (tmin > tmax) {
    std::swap(tmin, tmax);
  }

  return {tmin, tmax};
}

std::vector<Intersection> Cube::local_intersects(const Ray &local_ray) const {
  std::vector<Intersection> intersections;
  auto [xtmin, xtmax] = check_axis(local_ray.origin.x, local_ray.direction.x);
  auto [ytmin, ytmax] = check_axis(local_ray.origin.y, local_ray.direction.y);
  auto [ztmin, ztmax] = check_axis(local_ray.origin.z, local_ray.direction.z);

  double tmin = std::max({xtmin, ytmin, ztmin});
  double tmax = std::min({xtmax, ytmax, ztmax});

  if (tmin > tmax) {
    return intersections;
  }

  intersections.push_back(Intersection(tmin, const_cast<Cube *>(this)));
  intersections.push_back(Intersection(tmax, const_cast<Cube *>(this)));

  return intersections;
}
