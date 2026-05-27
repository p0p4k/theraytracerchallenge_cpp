#include "computations.h"

Computations::Computations(const Intersection &intersection, const Ray &ray,
                           const std::optional<std::vector<Intersection>> &xs)
    : t(intersection.t), object(intersection.object),
      point(ray.position(intersection.t)), eyev(-ray.direction),
      normalv(intersection.object->normal_at(point)) {
  if (normalv.dot(eyev) < 0.0) {
    inside = true;
    normalv = -normalv;
  } else {
    inside = false;
  }
  over_point = point + normalv * EPSILON;
  under_point = point - normalv * EPSILON;

  reflectv = ray.direction.reflect(normalv);

  n1 = 1.0;
  n2 = 1.0;

  if (xs.has_value()) {

    std::vector<Shape *> containers;
    for (const Intersection &i : *xs) {
      if (i == intersection) {
        if (containers.empty()) {
          n1 = 1.0;
        } else {
          n1 = containers.back()->material.refractive_index;
        }
      }
      auto it = std::find(containers.begin(), containers.end(), i.object);
      if (it != containers.end()) {
        containers.erase(it);
      } else {
        containers.push_back(i.object);
      }
      if (i == intersection) {
        if (containers.empty()) {
          n2 = 1.0;
        } else {
          n2 = containers.back()->material.refractive_index;
        }
        break;
      }
    }
  }
}

double schlick(const Computations &comps) {
  double cos = comps.eyev.dot(comps.normalv);

  if (comps.n1 > comps.n2) {
    double n_ratio = comps.n1 / comps.n2;
    double sin2_t = (n_ratio * n_ratio) * (1.0 - (cos * cos));

    if (sin2_t > 1.0) {
      return 1.0;
    }

    double cos_t = std::sqrt(1.0 - sin2_t);
    cos = cos_t;
  }

  double r0 = ((comps.n1 - comps.n2) / (comps.n1 + comps.n2));
  r0 = r0 * r0;

  return r0 + (1.0 - r0) * std::pow((1.0 - cos), 5);
}
