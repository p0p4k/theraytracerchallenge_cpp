#ifndef SPHERE_H
#define SPHERE_H

#include "intersection.h"
#include "material.h"
#include "matrix.h"
#include "ray.h"
#include <vector>

class Sphere {
public:
  int id;
  double radius;
  Material material;
  Matrix transform;
  Matrix inverse_transform;
  Matrix inverse_transform_transpose;

  Sphere(double radius = 1.0, const Material &material = Material())
      : radius(radius), material(material), transform(Matrix::identity(4)),
        inverse_transform(Matrix::identity(4)),
        inverse_transform_transpose(Matrix::identity(4)) {
    id = next_id++;
  }

  std::vector<Intersection> intersects(const Ray &ray) const;
  void set_transform(const Matrix &transformation);

  RayVector normal_at(const RayPoint &p) const;

private:
  static int next_id;
};
#endif
