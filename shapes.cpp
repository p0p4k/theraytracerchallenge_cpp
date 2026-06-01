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

RayVector Shape::normal_at(const RayPoint &world_point,
                           const Intersection *hit) const {
  RayPoint local_point = world_to_object(world_point);
  RayVector local_normal = this->local_normal_at(local_point, hit);
  return normal_to_world(local_normal);
}

RayPoint Shape::world_to_object(RayPoint point) const {
  if (parent != nullptr) {
    point = parent->world_to_object(point);
  }
  return this->inverse_transform.tuple_multiply(point);
}

RayVector Shape::normal_to_world(RayVector normal) const {
  normal = this->inverse_transform_transpose.tuple_multiply(normal);
  normal.w = 0.0;
  normal = normal.normalize();

  if (parent != nullptr) {
    normal = parent->normal_to_world(normal);
  }
  return normal;
}

BoundingBox Shape::parent_space_bounds_of() const {
  return this->bounds_of().transform(this->transform);
}
