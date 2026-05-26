#ifndef WORLD_H
#define WORLD_H

#include "color.h"
#include "intersection.h"
#include "light_source.h"
#include "shapes.h"
#include "sphere.h"
#include "tuple.h"
#include <vector>

class Computations {
public:
  double t;
  Shape *object;
  RayPoint point;
  RayVector eyev;
  RayVector normalv;
  bool inside;
  RayPoint over_point = RayPoint(0, 0, 0);

  Computations(const Intersection &intersection, const Ray &ray);
};

class World {
public:
  std::vector<Shape *> objects;
  LightSource *light_source;

  World();
  virtual ~World();

  void clear();
  std::vector<Intersection> intersect_world(const Ray &r) const;
  Color shade_hit(const Computations &comps,
                  const bool dont_shadow = true) const;
  Color color_at(const Ray &ray) const;
  bool is_shadowed(const RayPoint &p) const;
};

class DefaultWorld : public World {
public:
  DefaultWorld();
};

#endif
