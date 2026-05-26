#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "pattern.h"

class Material {
public:
  Color color;
  double ambient;
  double diffuse;
  double specular;
  double shininess;

  Pattern *pattern;

  Material(Color color = Color(1, 1, 1), double ambient = 0.1,
           double diffuse = 0.9, double specular = 0.9,
           double shininess = 200.0)
      : color(color), ambient(ambient), diffuse(diffuse), specular(specular),
        shininess(shininess), pattern(nullptr) {}
};

#endif
