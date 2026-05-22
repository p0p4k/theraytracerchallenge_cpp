#include "intersection.h"

const Intersection *hit(const std::vector<Intersection> &Intersections) {
  const Intersection *closest_hit = nullptr;
  for (const auto &i : Intersections) {
    if (i.t >= 0.0) {
      if (closest_hit == nullptr || i.t < closest_hit->t) {
        closest_hit = &i;
      }
    }
  }

  return closest_hit;
}
