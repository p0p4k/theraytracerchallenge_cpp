#include "pattern.h"
#include "shapes.h"

Color Pattern::pattern_at_object(Shape *object,
                                 const RayPoint &world_point) const {
  RayPoint object_point = object->inverse_transform.tuple_multiply(world_point);
  RayPoint pattern_point = inverse_transform.tuple_multiply(object_point);

  return pattern_at(pattern_point);
}
