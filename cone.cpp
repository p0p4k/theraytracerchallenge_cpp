#include "cone.h"

Cone::Cone(const Material &material, bool closed)
    : Shape(material), closed(closed) {}

std::vector<Intersection> Cone::local_intersects(const Ray &local_ray) const {
  std::vector<Intersection> intersections;
  double a = local_ray.direction.x * local_ray.direction.x -
             local_ray.direction.y * local_ray.direction.y +
             local_ray.direction.z * local_ray.direction.z;
  double b = 2 * local_ray.origin.x * local_ray.direction.x -
             2 * local_ray.origin.y * local_ray.direction.y +
             2 * local_ray.origin.z * local_ray.direction.z;
  double c = local_ray.origin.x * local_ray.origin.x -
             local_ray.origin.y * local_ray.origin.y +
             local_ray.origin.z * local_ray.origin.z;

  if (equal(a, 0.0)) {
    if (!equal(b, 0.0)) {
      double t = -c / (2 * b);
      double y = local_ray.origin.y + t * local_ray.direction.y;
      if (this->minimum < y && y < this->maximum) {
        intersections.push_back(Intersection(t, const_cast<Cone *>(this)));
      }
    }

    // Fix 2: ALWAYS check caps before returning if a == 0
    intersect_caps(local_ray, &intersections);
    return intersections;
  } else {
    double disc = b * b - 4 * a * c;
    if (disc < 0) {
      return intersections;
    }

    double sqrtdisc = std::sqrt(disc);
    double t0 = (-b - sqrtdisc) / (2 * a);
    double t1 = (-b + sqrtdisc) / (2 * a);

    if (t0 > t1) {
      std::swap(t0, t1);
    }

    double y0 = local_ray.origin.y + t0 * local_ray.direction.y;
    if (this->minimum < y0 && y0 < this->maximum) {
      intersections.push_back(Intersection(t0, const_cast<Cone *>(this)));
    }

    double y1 = local_ray.origin.y + t1 * local_ray.direction.y;
    if (this->minimum < y1 && y1 < this->maximum) {
      intersections.push_back(Intersection(t1, const_cast<Cone *>(this)));
    }

    intersect_caps(local_ray, &intersections);

    return intersections;
  }
}

bool check_cone_cap(const Ray &ray, double t, double cap_y) {
  double x = ray.origin.x + t * ray.direction.x;
  double z = ray.origin.z + t * ray.direction.z;

  return (x * x + z * z) <= (cap_y * cap_y) + EPSILON;
}

void Cone::intersect_caps(const Ray &ray, std::vector<Intersection> *xs) const {
  if (!closed || equal(ray.direction.y, 0.0)) {
    return;
  }

  double t = (minimum - ray.origin.y) / ray.direction.y;
  if (check_cone_cap(ray, t, minimum)) {
    xs->push_back(Intersection(t, const_cast<Cone *>(this)));
  }

  t = (maximum - ray.origin.y) / ray.direction.y;
  if (check_cone_cap(ray, t, maximum)) {
    xs->push_back(Intersection(t, const_cast<Cone *>(this)));
  }
}

RayVector Cone::local_normal_at(const RayPoint &point) const {
  double dist = point.x * point.x + point.z * point.z;

  if (dist < (point.y * point.y) && point.y >= maximum - EPSILON) {
    return RayVector(0, 1, 0);
  }

  if (dist < (point.y * point.y) && point.y <= minimum + EPSILON) {
    return RayVector(0, -1, 0);
  }

  double y = std::sqrt(dist);
  if (point.y > 0.0) {
    y = -y;
  }

  return RayVector(point.x, y, point.z);
}
