

#include "world.h"
#include <algorithm>

Computations::Computations(const Intersection &intersection, const Ray &ray)
    : t(intersection.t), object(intersection.object),
      point(ray.position(intersection.t)), eyev(-ray.direction),
      normalv(intersection.object->normal_at(ray.position(intersection.t))) {
  if (normalv.dot(eyev) < 0.0) {
    inside = true;
    normalv = -normalv;
  } else {
    inside = false;
  }
}

World::World() : light_source(nullptr) {}

World::~World() { clear(); }

void World::clear() {
  if (light_source != nullptr) {
    delete light_source;
    light_source = nullptr;
  }
  for (const Sphere *obj : objects) {
    delete obj;
  }
  objects.clear();
}

std::vector<Intersection> World::intersect_world(const Ray &r) const {
  std::vector<Intersection> xs;
  for (const Sphere *o : objects) {
    std::vector<Intersection> obj_xs = o->intersects(r);
    xs.insert(xs.end(), obj_xs.begin(), obj_xs.end());
  }
  std::sort(xs.begin(), xs.end());
  return xs;
}

Color World::shade_hit(const Computations &comps) const {
  if (light_source == nullptr)
    return Color(0, 0, 0);

  return light_source->lighting(comps.object->material, comps.point, comps.eyev,
                                comps.normalv);
}

Color World::color_at(const Ray &ray) const {
  std::vector<Intersection> xs = this->intersect_world(ray);
  const Intersection *closest_hit = hit(xs);
  if (!closest_hit) {
    return Color(0, 0, 0);
  }

  Computations comps(*closest_hit, ray);
  return shade_hit(comps);
}

DefaultWorld::DefaultWorld() {
  light_source = new LightSource(Color(1, 1, 1), RayPoint(-10, 10, -10));

  Sphere *s1 = new Sphere();
  s1->material.color = Color(0.8, 1.0, 0.6);
  s1->material.diffuse = 0.7;
  s1->material.specular = 0.2;
  objects.push_back(s1);

  Sphere *s2 = new Sphere();
  s2->set_transform(Matrix::scaling(0.5, 0.5, 0.5));
  objects.push_back(s2);
}
