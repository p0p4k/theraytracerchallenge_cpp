#ifndef CAMERA_H
#define CAMERA_H

#include "canvas.h"
#include "matrix.h"
#include "ray.h"
#include "world.h"
#include <chrono>
class Camera {
public:
  int hsize;
  int vsize;
  double field_of_view;
  Matrix transform;
  double half_width;
  double half_height;
  double pixel_size;
  Camera(int hsize, int vsize, double field_of_view);

  Ray ray_for_pixel(double px, double py) const;
  Canvas render(const World &w) const;
  void set_transform(const Matrix &transformation);
};

#endif
