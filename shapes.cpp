#include "shapes.h"

Shape::Shape(const Material &material)
    : material(material), transform(Matrix::identity(4)),
      inverse_transform(Matrix::identity(4)),
      inverse_transform_transpose(Matrix::identity(4)) {}

void Shape::set_transform(const Matrix &transformation) {
  transform = transformation;
  inverse_transform = transformation.inverse();
  inverse_transform_transpose = inverse_transform.transpose();
}

std::vector<Intersection> Shape::intersects(const Ray &world_ray) const {
  Ray local_ray = world_ray.transform(this->inverse_transform);
  return this->local_intersects(local_ray);
}

RayVector Shape::normal_at(const RayPoint &world_point) const {
  RayPoint local_point = this->inverse_transform.transform_point(world_point);
  RayVector local_normal = this->local_normal_at(local_point);
  RayVector world_normal =
      this->inverse_transform_transpose.transform_vector(local_normal);
  world_normal.w = 0.0;
  return world_normal.normalize();
}
