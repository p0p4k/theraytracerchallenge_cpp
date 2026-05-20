#include "canvas.h"
#include "tuple.h"
#include <fstream>

struct Projectile {
  RayPoint position;
  RayVector velocity;

  Projectile(RayPoint p, RayVector v) : position(p), velocity(v) {}
};

struct Environment {
  RayVector gravity;
  RayVector wind;

  Environment(RayVector g, RayVector w) : gravity(g), wind(w) {}
};

Projectile tick_projectile(const Environment &e, const Projectile &p) {
  return Projectile(RayPoint(p.position + p.velocity),
                    RayVector(p.velocity + e.gravity + e.wind));
}

int main() {
  // Projectile
  RayVector v = RayVector(1, 1.8, 0);
  RayVector v_norm = v.normalize() * 11.25;
  Projectile p = Projectile(RayPoint(0, 1, 0), v_norm);
  const Environment e =
      Environment(RayVector(0, -0.1, 0), RayVector(-0.01, 0, 0));

  Canvas c = Canvas(900, 550);
  Color color_red = Color(1, 0, 0);

  while (p.position.y > 0.0) {
    p = tick_projectile(e, p);
    std::cout << p.position.x << ' ' << p.position.y << ' ' << p.position.z
              << std::endl;
    int canvas_x = static_cast<int>(p.position.x);
    int canvas_y = c.height - static_cast<int>(p.position.y);
    if ((0 <= canvas_x && canvas_x < c.width) &&
        (0 <= canvas_y && canvas_y < c.height)) {
      c.write_pixel(canvas_x, canvas_y, color_red);
    }
  }
  std::ofstream out_file("projectile.ppm");
  if (out_file.is_open()) {
    out_file << c.canvas_to_ppm();
    out_file.close();
    std::cout << "\n[SUCCESS] Render complete! Trajectory written safely to "
                 "projectile.ppm"
              << std::endl;
  } else {
    std::cerr
        << "\n[ERROR] Failed to open target directory to write image output."
        << std::endl;
  }

  return 0;
}
