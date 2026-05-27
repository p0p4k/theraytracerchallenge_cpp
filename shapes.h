#ifndef SHAPES_H
#define SHAPES_H

#include "intersection.h"
#include "material.h"
#include "matrix.h"
#include "ray.h"
#include "tuple.h"
#include <vector>

class Shape {
public:
  Material material;
  Matrix transform;
  Matrix inverse_transform;
  Matrix inverse_transform_transpose;
  bool casts_shadow = true;

  Shape(const Material &material = Material());

  virtual ~Shape() = default;

  void set_transform(const Matrix &transformation);
  std::vector<Intersection> intersects(const Ray &world_ray) const;
  RayVector normal_at(const RayPoint &p) const;

protected:
  virtual std::vector<Intersection>
  local_intersects(const Ray &local_ray) const = 0;

  virtual RayVector local_normal_at(const RayPoint &local_point) const = 0;
};

class TestShape : public Shape {
public:
  mutable Ray saved_ray;

  TestShape(const Material &material = Material())
      : Shape(material), saved_ray(RayPoint(0, 0, 0), RayVector(0, 0, 0)) {}

protected:
  std::vector<Intersection>
  local_intersects(const Ray &local_ray) const override {
    saved_ray = local_ray;
    return std::vector<Intersection>();
  }

  RayVector local_normal_at(const RayPoint &local_point) const override {
    return RayVector(local_point.x, local_point.y, local_point.z);
  }
};
#endif
