#include "groups.h"

Group::Group(const Material &material) : Shape(material) {}

std::vector<Intersection> Group::local_intersects(const Ray &local_ray) const {
  if (!bounds_of().intersects(local_ray)) {
    return std::vector<Intersection>();
  }

  std::vector<Intersection> intersections;
  for (auto s : child) {
    std::vector<Intersection> s_intersect = s->intersects(local_ray);
    intersections.insert(intersections.end(), s_intersect.begin(),
                         s_intersect.end());
  }

  std::sort(
      intersections.begin(), intersections.end(),
      [](const Intersection &a, const Intersection &b) { return a.t < b.t; });

  return intersections;
}

RayVector Group::local_normal_at(const RayPoint &) const {
  throw std::logic_error(
      "Method local_normal_at should never be called on a Group directly.");
}

void Group::add_child(Shape *shape) {
  child.push_back(shape);
  shape->parent = this;
}

BoundingBox Group::bounds_of() const {
  BoundingBox box;
  for (auto s : child) {
    box.add(s->parent_space_bounds_of());
  }
  return box;
}
