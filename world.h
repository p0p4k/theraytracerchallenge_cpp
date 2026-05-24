#ifndef WORLD_H
#define WORLD_H

#include "color.h"
#include "intersection.h"
#include "light_source.h"
#include "sphere.h"
#include "tuple.h"
#include <vector>

class Computations {
public:
  double t;
  const Sphere *object;
  RayPoint point;
  RayVector eyev;
  RayVector normalv;
  bool inside;

  Computations(const Intersection &intersection, const Ray &ray);
};

class World {
public:
  std::vector<const Sphere *> objects;
  LightSource *light_source;

  World();
  virtual ~World();

  void clear();
  std::vector<Intersection> intersect_world(const Ray &r) const;
  Color shade_hit(const Computations &comps) const;
  Color color_at(const Ray &ray) const;
};

class DefaultWorld : public World {
public:
  DefaultWorld();
};

#endif
