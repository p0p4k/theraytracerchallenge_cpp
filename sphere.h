#ifndef SPHERE_H
#define SPHERE_H

#include "intersection.h"
#include "matrix.h"
#include "ray.h"
#include <vector>

class Sphere {
public:
  int id;
  double radius;
  Matrix transform;
  Matrix inverse_transform;

  Sphere(double radius = 1.0)
      : radius(radius), transform(Matrix::identity(4)),
        inverse_transform(transform.inverse()) {
    id = next_id++;
  }

  std::vector<Intersection> intersects(const Ray &ray) const;
  void set_transform(const Matrix &transformation);

private:
  static int next_id;
};
#endif
