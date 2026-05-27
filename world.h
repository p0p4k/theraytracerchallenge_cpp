#ifndef WORLD_H
#define WORLD_H

#include "color.h"
#include "computations.h"
#include "intersection.h"
#include "light_source.h"
#include "shapes.h"
#include "sphere.h"
#include "tuple.h"
#include <algorithm>
#include <vector>

class World {
public:
  std::vector<Shape *> objects;
  LightSource *light_source;

  World();
  virtual ~World();

  void clear();
  std::vector<Intersection> intersect_world(const Ray &r) const;
  Color shade_hit(const Computations &comps, const bool dont_shadow = true,
                  int remaining = 5) const;
  Color color_at(const Ray &ray, int remaining = 5) const;
  bool is_shadowed(const RayPoint &p) const;
  Color reflected_color(const Computations &comps, int remaining = 5) const;
  Color refracted_color(const Computations &comps, int remaining = 5) const;
};

class DefaultWorld : public World {
public:
  DefaultWorld();
};

#endif
