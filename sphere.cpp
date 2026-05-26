#include "sphere.h"

std::vector<Intersection> Sphere::local_intersects(const Ray &local_ray) const {
  std::vector<Intersection> intersections;

  RayVector sphere_to_ray = local_ray.origin - RayPoint(0, 0, 0);

  double a = local_ray.direction.dot(local_ray.direction);
  double b = 2.0 * local_ray.direction.dot(sphere_to_ray);
  double c = sphere_to_ray.dot(sphere_to_ray) - (this->radius * this->radius);

  double discriminant = b * b - 4.0 * a * c;

  if (discriminant < 0.0) {
    return intersections;
  }

  double sqrt_discriminant = std::sqrt(discriminant);
  double two_a = 2.0 * a;

  double t1 = (-b - sqrt_discriminant) / two_a;
  double t2 = (-b + sqrt_discriminant) / two_a;

  intersections.push_back(Intersection(t1, this));
  intersections.push_back(Intersection(t2, this));

  return intersections;
}

RayVector Sphere::local_normal_at(const RayPoint &local_point) const {
  return local_point - RayPoint(0, 0, 0);
}
