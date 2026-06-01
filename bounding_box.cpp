#include "bounding_box.h"
#include "utilities.h"
#include <limits>

BoundingBox::BoundingBox()
    : min_point(RayPoint(std::numeric_limits<double>::infinity(),
                         std::numeric_limits<double>::infinity(),
                         std::numeric_limits<double>::infinity())),
      max_point(RayPoint(-std::numeric_limits<double>::infinity(),
                         -std::numeric_limits<double>::infinity(),
                         -std::numeric_limits<double>::infinity())) {
  double inf = std::numeric_limits<double>::infinity();
  min_point = RayPoint(inf, inf, inf);
  max_point = RayPoint(-inf, -inf, -inf);
}

BoundingBox::BoundingBox(RayPoint min_p, RayPoint max_p)
    : min_point(min_p), max_point(max_p) {}

void BoundingBox::add(const RayPoint &p) {
  min_point.x = std::min(min_point.x, p.x);
  min_point.y = std::min(min_point.y, p.y);
  min_point.z = std::min(min_point.z, p.z);

  max_point.x = std::max(max_point.x, p.x);
  max_point.y = std::max(max_point.y, p.y);
  max_point.z = std::max(max_point.z, p.z);
}

void BoundingBox::add(const BoundingBox &box) {
  add(box.min_point);
  add(box.max_point);
}

BoundingBox BoundingBox::transform(const Matrix &m) const {
  RayPoint corners[8] = {min_point,
                         RayPoint(min_point.x, min_point.y, max_point.z),
                         RayPoint(min_point.x, max_point.y, min_point.z),
                         RayPoint(min_point.x, max_point.y, max_point.z),
                         RayPoint(max_point.x, min_point.y, min_point.z),
                         RayPoint(max_point.x, min_point.y, max_point.z),
                         RayPoint(max_point.x, max_point.y, min_point.z),
                         max_point};

  BoundingBox result;
  for (int i = 0; i < 8; ++i) {
    result.add(m.tuple_multiply(corners[i]));
  }
  return result;
}

bool BoundingBox::intersects(const Ray &ray) const {
  auto check_axis = [](double origin, double direction, double min_val,
                       double max_val) {
    double tmin_num = min_val - origin;
    double tmax_num = max_val - origin;
    double tmin, tmax;

    if (std::abs(direction) >= EPSILON) {
      tmin = tmin_num / direction;
      tmax = tmax_num / direction;
    } else {
      tmin = tmin_num * std::numeric_limits<double>::infinity();
      tmax = tmax_num * std::numeric_limits<double>::infinity();
    }

    if (tmin > tmax)
      std::swap(tmin, tmax);
    return std::pair<double, double>(tmin, tmax);
  };

  auto [xtmin, xtmax] =
      check_axis(ray.origin.x, ray.direction.x, min_point.x, max_point.x);
  auto [ytmin, ytmax] =
      check_axis(ray.origin.y, ray.direction.y, min_point.y, max_point.y);
  auto [ztmin, ztmax] =
      check_axis(ray.origin.z, ray.direction.z, min_point.z, max_point.z);

  double tmin = std::max({xtmin, ytmin, ztmin});
  double tmax = std::min({xtmax, ytmax, ztmax});

  return tmin <= tmax;
}

bool BoundingBox::contains(const RayPoint &p) const {
  return p.x >= min_point.x && p.x <= max_point.x && p.y >= min_point.y &&
         p.y <= max_point.y && p.z >= min_point.z && p.z <= max_point.z;
}

bool BoundingBox::contains(const BoundingBox &box) const {
  return contains(box.min_point) && contains(box.max_point);
}
