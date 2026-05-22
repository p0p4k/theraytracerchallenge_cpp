#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include "color.h"
#include "material.h"
#include "tuple.h"
class LightSource {
public:
  Color intensity;
  RayPoint position;
  LightSource(Color i = Color(0, 0, 0), RayPoint p = RayPoint(0, 0, 0))
      : intensity(i), position(p) {};

  Color lighting(const Material &m, const RayPoint &p, const RayVector &eyev,
                 const RayVector &normalv) const;
};
#endif
