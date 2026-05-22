#include "ray.h"

Ray::Ray(RayPoint o, RayVector d) : origin(o), direction(d) {};

RayPoint Ray::position(const double &t) const {
  RayPoint pos_t = this->origin + this->direction * t;
  return pos_t;
}

Ray Ray::transform(const Matrix &transformation) const {
  RayPoint ray_origin = transformation.transform_point(origin);
  RayVector ray_vector = transformation.transform_vector(direction);
  return Ray(ray_origin, ray_vector);
}
