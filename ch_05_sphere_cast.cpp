#include "canvas.h"
#include "sphere.h"
#include "tuple.h"
#include <fstream>

int main() {
  int width = 100;
  int height = 100;
  Canvas c(width, height);
  Color red(1, 0, 0);

  Sphere s(1);
  // Matrix raw_transform = Matrix::shearing(1, 0, 0, 0, 0, 0)
  //                            .matrix_multiply(Matrix::scaling(0.5, 1, 1));
  // s.set_transform(raw_transform);

  double camera_x = 0.0;
  double camera_y = 0.0;
  double camera_z = -5.0;
  RayPoint ray_origin(camera_x, camera_y, camera_z);

  double wall_z = 10.0;
  double wall_size = 7.0;

  double pixel_size = wall_size / width;
  double half_wall = wall_size / 2.0;

  for (auto y = 0; y < height; ++y) {
    double world_y = half_wall - pixel_size * y;
    for (auto x = 0; x < width; ++x) {
      double world_x = -half_wall + pixel_size * x;
      RayPoint position(world_x, world_y, wall_z);
      Ray r(ray_origin, (position - ray_origin).normalize());
      std::vector<Intersection> xs = s.intersects(r);
      const Intersection *i = hit(xs);
      if (i != nullptr) {
        c.write_pixel(x, y, red);
      }
    }
  }

  std::ofstream out_file("sphere_wall.ppm");
  if (out_file.is_open()) {
    out_file << c.canvas_to_ppm();
    out_file.close();
    std::cout << "sphere written" << std::endl;
  } else {
    std::cerr << "\n[ERROR] problems with file" << std::endl;
  }

  return 0;
}
