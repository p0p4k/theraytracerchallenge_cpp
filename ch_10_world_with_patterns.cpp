#include "camera.h"
#include "canvas.h"
#include "light_source.h"
#include "pattern.h"
#include "plane.h"
#include "sphere.h"
#include "tuple.h"
#include "world.h"
#include <cmath>
#include <fstream>
#include <iostream>

int main() {
  World w;

  // Primary Studio Light
  LightSource *light_source =
      new LightSource(Color(1, 1, 1), RayPoint(-10, 12, -10));
  w.light_source = light_source;

  // ==========================================
  // 1. FLOOR & BACKGROUND PLANES
  // ==========================================

  // Floor with a classic checkered foundation
  Plane *floor = new Plane();
  floor->material.specular = 0.0;
  floor->material.ambient = 0.1;
  CheckersPattern *floor_p =
      new CheckersPattern(Color(0.15, 0.15, 0.15), Color(0.85, 0.85, 0.85));
  floor_p->set_transform(
      Matrix::scaling(0.5, 0.5, 0.5)); // Shrink checkers to repeat tightly
  floor->material.pattern = floor_p;

  // Left Backdrop Plane
  Plane *left_wall = new Plane();
  left_wall->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 0, 10), Matrix::rotation_y(M_PI / 4.0),
       Matrix::rotation_x(M_PI / 2.0)}));
  left_wall->material.color = Color(0.12, 0.14, 0.18); // Moody deep slate
  left_wall->material.specular = 0.0;
  left_wall->material.ambient = 0.1;

  // Right Backdrop Plane
  Plane *right_wall = new Plane();
  right_wall->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 0, 10), Matrix::rotation_y(-M_PI / 4.0),
       Matrix::rotation_x(M_PI / 2.0)}));
  right_wall->material.color = Color(0.12, 0.14, 0.18);
  right_wall->material.specular = 0.0;
  right_wall->material.ambient = 0.1;

  // ==========================================
  // 2. THE SIX SPHERES WITH PATTERNS
  // ==========================================

  // Sphere 1: The Big Centerpiece (Stripe Pattern)
  Sphere *s1 = new Sphere();
  s1->set_transform(Matrix::translation(-0.2, 1.2, 0.8));
  s1->material.diffuse = 0.7;
  s1->material.specular = 0.4;
  StripePattern *s1_p =
      new StripePattern(Color(1, 0, 0), Color(0, 0, 1)); // Bold Red & Blue
  s1_p->set_transform(Matrix::chain_transforms(
      {Matrix::rotation_z(M_PI / 4.0), Matrix::scaling(0.15, 1.0, 1.0)}));
  s1->material.pattern = s1_p;

  // Sphere 2: Right Oblong (Ring Pattern)
  Sphere *s2 = new Sphere();
  s2->set_transform(Matrix::chain_transforms(
      {Matrix::translation(2.2, 0.9, 0.4), Matrix::scaling(1.4, 0.9, 0.9)}));
  s2->material.diffuse = 0.8;
  s2->material.specular = 0.2;
  RingPattern *s2_p = new RingPattern(
      Color(0.9, 0.8, 0.1), Color(0.3, 0.0, 0.4)); // Gold & Deep Purple
  s2_p->set_transform(Matrix::chain_transforms(
      {Matrix::rotation_x(M_PI / 3.0), Matrix::scaling(0.1, 0.1, 0.1)}));
  s2->material.pattern = s2_p;

  // Sphere 3: Left Small Foreground (Checkers Pattern)
  Sphere *s3 = new Sphere();
  s3->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-1.4, 0.4, -0.8), Matrix::scaling(0.4, 0.4, 0.4)}));
  s3->material.diffuse = 0.8;
  s3->material.specular = 0.5;
  CheckersPattern *s3_p =
      new CheckersPattern(Color(1, 0.5, 0), Color(1, 1, 1)); // Orange & White
  s3_p->set_transform(Matrix::scaling(0.25, 0.25, 0.25));
  s3->material.pattern = s3_p;

  // Sphere 4: Far Right Background (Gradient Pattern)
  Sphere *s4 = new Sphere();
  s4->set_transform(Matrix::chain_transforms(
      {Matrix::translation(3.5, 0.6, 2.5), Matrix::scaling(0.6, 0.6, 0.6)}));
  s4->material.diffuse = 0.8;
  s4->material.specular = 0.1;
  GradientPattern *s4_p = new GradientPattern(
      Color(0, 0.8, 0.8), Color(0.8, 0, 0.8)); // Cyan to Magenta
  s4_p->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-0.5, 0, 0), Matrix::scaling(2.0, 1.0, 1.0)}));
  s4->material.pattern = s4_p;

  // Sphere 5: Center Front Low-boy (Smooth Solid Complement)
  Sphere *s5 = new Sphere();
  s5->set_transform(
      Matrix::chain_transforms({Matrix::translation(0.7, 0.35, -0.6),
                                Matrix::scaling(0.35, 0.35, 0.35)}));
  s5->material.color = Color(0.1, 0.8, 0.4); // Jade Green
  s5->material.diffuse = 0.9;
  s5->material.specular = 0.1;

  // Sphere 6: Extreme Left Background (Vertical Tall Stripe)
  Sphere *s6 = new Sphere();
  s6->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-2.8, 0.8, 1.5), Matrix::scaling(0.5, 0.8, 0.5)}));
  s6->material.diffuse = 0.7;
  s6->material.specular = 0.3;
  StripePattern *s6_p = new StripePattern(
      Color(0.1, 0.1, 0.1), Color(0.9, 0.5, 0.1)); // Dark Slate & Coral
  s6_p->set_transform(Matrix::scaling(0.1, 1.0, 1.0));
  s6->material.pattern = s6_p;

  // Collect All Entities
  w.objects.insert(w.objects.end(),
                   {floor, left_wall, right_wall, s1, s2, s3, s4, s5, s6});

  // ==========================================
  // 3. CAMERA SETUP & RENDERING
  // ==========================================
  Camera camera(1280, 720, M_PI / 3.0);
  RayPoint from(
      0, 2.0, -5.5); // Elevated vantage point to look down on the floor pattern
  RayPoint to(0, 1.0, 0);
  RayVector up(0, 1, 0);
  camera.set_transform(Matrix::view_transform(from, to, up));

  std::cout << "Starting scene render (1280x720) with multiple active pattern "
               "spaces..."
            << std::endl;
  Canvas c = camera.render(w);

  // Output to standard path
  std::ofstream out_file("world_render_with_plane.ppm");
  if (out_file.is_open()) {
    out_file << c.canvas_to_ppm();
    out_file.close();
    std::cout << "Scene render completed successfully." << std::endl;
  } else {
    std::cerr << "\n[ERROR] Problems opening out_file path." << std::endl;
  }

  return 0;
}
