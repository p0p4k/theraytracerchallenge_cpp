#include "material.h"
#include "tuple.h"

struct LightingTestContext {
  Material m;
  RayPoint position; // Position on the surface (at the origin)
  LightingTestContext() : m(Material()), position(RayPoint(0, 0, 0)) {}
};
