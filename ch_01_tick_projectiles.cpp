#include "tuple.h"

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
  // Projectile tick
  int num_ticks = 0;
  RayVector v = RayVector(1, 1, 0);
  RayVector v_norm = v.normalize();
  Projectile p = Projectile(RayPoint(0, 1, 0), v_norm);
  const Environment e =
      Environment(RayVector(0, -0.1, 0), RayVector(-0.01, 0, 0));
  while (p.position.y > 0.0) {
    p = tick_projectile(e, p);
    num_ticks += 1;
    std::cout << p.position.x << ' ' << p.position.y << ' ' << p.position.z
              << std::endl;
  }
  std::cout << "Total ticks :" << num_ticks << std::endl;
  return 0;
}
