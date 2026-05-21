#include "canvas.h"
#include "color.h"
#include "matrix.h"
#include "tuple.h"
#include <fstream>

int main() {

  Canvas c = Canvas(900, 550);
  Color white = Color(1, 1, 1);

  RayPoint center(900.0 / 2, 550.0 / 2, 0.0);
  c.write_pixel(center.x, center.y, white);

  double radius = 200.0;
  RayPoint twelve(0.0, radius, 0.0);

  double angle = -PI / 6.0;
  Matrix rotation_clock = Matrix::rotation_z(angle);

  for (int i = 0; i < 12; ++i) {
    twelve = rotation_clock.transform_point(twelve);
    c.write_pixel(twelve.x + center.x, center.y - twelve.y, white);
  }

  std::ofstream out_file("clock.ppm");
  if (out_file.is_open()) {
    out_file << c.canvas_to_ppm();
    out_file.close();
    std::cout << "clock written" << std::endl;
  } else {
    std::cerr << "\n[ERROR] problems with file" << std::endl;
  }

  return 0;
}
