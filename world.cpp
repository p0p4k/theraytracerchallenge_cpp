

#include "world.h"

World::World() : light_source(nullptr) {}

World::~World() { clear(); }

void World::clear() {
  if (light_source != nullptr) {
    delete light_source;
    light_source = nullptr;
  }
  for (Shape *obj : objects) {
    delete obj;
  }
  objects.clear();
}

std::vector<Intersection> World::intersect_world(const Ray &r) const {
  std::vector<Intersection> xs;
  for (Shape *o : objects) {
    std::vector<Intersection> obj_xs = o->intersects(r);
    xs.insert(xs.end(), obj_xs.begin(), obj_xs.end());
  }
  std::sort(xs.begin(), xs.end());
  return xs;
}

Color World::shade_hit(const Computations &comps, const bool dont_shadow,
                       int remaining) const {
  if (light_source == nullptr)
    return Color(0, 0, 0);

  bool in_shadow = false;
  if (!dont_shadow) {
    if (is_shadowed(comps.over_point)) {
      in_shadow = true;
    }
  }

  Color surface = light_source->lighting(comps.object->material, comps.object,
                                         comps.over_point, comps.eyev,
                                         comps.normalv, in_shadow);

  Color reflected = reflected_color(comps, remaining);

  Color refracted = refracted_color(comps, remaining);

  Material *m = &(comps.object->material);
  if (m->reflective > 0.0 && m->transparency > 0.0) {
    double reflectance = schlick(comps);
    return surface + reflected * reflectance + refracted * (1 - reflectance);
  } else {
    return surface + reflected + refracted;
  }
}

Color World::color_at(const Ray &ray, int reamining) const {
  std::vector<Intersection> xs = this->intersect_world(ray);
  const Intersection *closest_hit = hit(xs);
  if (!closest_hit) {
    return Color(0, 0, 0);
  }

  Computations comps(*closest_hit, ray, xs);
  return shade_hit(comps, false, reamining);
}

Color World::reflected_color(const Computations &comps, int remaining) const {
  if (remaining <= 0 || comps.object->material.reflective == 0.0) {
    return COLOR_BLACK;
  }
  Ray reflect_ray(Ray(comps.over_point, comps.reflectv));
  Color color = color_at(reflect_ray, remaining - 1);
  return color * comps.object->material.reflective;
}

Color World::refracted_color(const Computations &comps, int remaining) const {
  if (remaining <= 0 || comps.object->material.transparency == 0.0) {
    return COLOR_BLACK;
  }

  double n_ratio = comps.n1 / comps.n2;

  double cos_i = comps.eyev.dot(comps.normalv);

  double sin2_t = (n_ratio * n_ratio) * (1.0 - (cos_i * cos_i));

  if (sin2_t > 1.0) {
    return COLOR_BLACK;
  }

  double cos_t = std::sqrt(1.0 - sin2_t);

  RayVector refract_direction =
      comps.normalv * (n_ratio * cos_i - cos_t) - comps.eyev * n_ratio;

  Ray refract_ray(comps.under_point, refract_direction);

  Color color = color_at(refract_ray, remaining - 1);
  return color * comps.object->material.transparency;
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

bool World::is_shadowed(const RayPoint &p) const {
  RayVector v = light_source->position - p;
  double distance = v.magnitude();
  RayVector direction = v.normalize();

  Ray r(p, direction);
  std::vector<Intersection> intersections = intersect_world(r);

  const Intersection *i = hit(intersections);
  if (i && i->t < distance) {
    if (i->object->casts_shadow) {
      return true;
    }
    return false;
  }
  return false;
}
