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
  double reflective;
  double transparency;
  double refractive_index;

  Pattern *pattern;

  Material(Color color = Color(1, 1, 1), double ambient = 0.1,
           double diffuse = 0.9, double specular = 0.9,
           double shininess = 200.0, double reflective = 0.0,
           double transparency = 0.0, double refractive_index = 1.0)
      : color(color), ambient(ambient), diffuse(diffuse), specular(specular),
        shininess(shininess), reflective(reflective),
        transparency(transparency), refractive_index(refractive_index),
        pattern(nullptr) {}
};

#endif
