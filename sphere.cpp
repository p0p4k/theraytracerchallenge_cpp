#include "sphere.h"
#include "intersection.h"
#include "tuple.h"
#include <cmath>
#include <pthread.h>

int Sphere::next_id = 0;

std::vector<Intersection> Sphere::intersects(const Ray &incoming_ray) const {
  Ray ray = incoming_ray.transform(inverse_transform);
  std::vector<Intersection> intersections;

  RayVector sphere_to_ray = ray.origin - RayPoint(0, 0, 0);

  double a = ray.direction.dot(ray.direction);
  double b = 2 * ray.direction.dot(sphere_to_ray);
  double c = sphere_to_ray.dot(sphere_to_ray) - 1.0;

  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0.0) {
    return intersections;
  }

  double sqrt_discriminant = std::sqrt(discriminant);
  double two_a = 2.0 * a;

  double t1 = (-b - sqrt_discriminant) / two_a;
  double t2 = (-b + sqrt_discriminant) / two_a;

  Intersection i1(t1, id);
  Intersection i2(t2, id);
  intersections.push_back(i1);
  intersections.push_back(i2);

  return intersections;
}

void Sphere::set_transform(const Matrix &transformation) {
  transform = transformation;
  inverse_transform = transformation.inverse();
}
