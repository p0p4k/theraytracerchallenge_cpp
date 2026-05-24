#include "camera.h"
#include <cmath>

Camera::Camera(int hsize, int vsize, double field_of_view)
    : hsize(hsize), vsize(vsize), field_of_view(field_of_view),
      transform(Matrix::identity(4)) {
  double half_view = std::tan(field_of_view / 2.0);
  double aspect = static_cast<double>(hsize) / static_cast<double>(vsize);
  if (aspect >= 1.0) {
    half_width = half_view;
    half_height = half_view / aspect;
  } else {
    half_width = half_view * aspect;
    half_height = half_view;
  }
  pixel_size = (half_width * 2.0) / hsize;
};

Ray Camera::ray_for_pixel(double px, double py) const {
  double xoffset = (px + 0.5) * pixel_size;
  double yoffset = (py + 0.5) * pixel_size;

  double world_x = half_width - xoffset;
  double world_y = half_height - yoffset;

  Matrix inv_transform = transform.inverse();

  RayPoint pixel =
      RayPoint(inv_transform.tuple_multiply(RayPoint(world_x, world_y, -1)));
  RayPoint origin = RayPoint(inv_transform.tuple_multiply(RayPoint(0, 0, 0)));
  RayVector direction = (pixel - origin).normalize();

  return Ray(origin, direction);
}

Canvas Camera::render(const World &w) const {
  Canvas image(hsize, vsize);

  for (int y = 0; y < vsize; ++y) {
    for (int x = 0; x < hsize; ++x) {
      Ray ray = ray_for_pixel(x, y);
      Color color = w.color_at(ray);
      image.write_pixel(x, y, color);
    }
  }

  return image;
}

void Camera::set_transform(const Matrix &transformation) {
  transform = transformation;
}
