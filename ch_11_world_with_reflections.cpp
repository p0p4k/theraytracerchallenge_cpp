#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "light_source.h"
#include "matrix.h"
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

  // Primary light source illuminating from upper-front-left
  // LightSource *light_source =
  //     new LightSource(Color(1, 1, 1), RayPoint(-10, 10, -10));
  // w.light_source = light_source;

  LightSource *light_source =
      new LightSource(Color(1, 1, 1), RayPoint(0, 12, -2));
  w.light_source = light_source;

  // ==========================================
  // 1. CHECKERED ROOM FOUNDATION
  // ==========================================

  // Floor Plane
  Plane *floor = new Plane();
  floor->material.ambient = 0.1;
  floor->material.diffuse = 0.7;
  floor->material.specular = 0.3;
  floor->material.reflective = 0.1; // Subtle reflection on the floor tiles
  CheckersPattern *floor_p =
      new CheckersPattern(Color(0.1, 0.1, 0.1), Color(0.9, 0.9, 0.9));
  floor_p->set_transform(Matrix::scaling(0.5, 0.5, 0.5));
  floor->material.pattern = floor_p;
  w.objects.push_back(floor);

  // Back Wall Plane (Facing the camera directly)
  Plane *back_wall = new Plane();
  back_wall->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 0, 5), Matrix::rotation_x(M_PI / 2.0)}));
  back_wall->material.ambient = 0.1;
  back_wall->material.diffuse = 0.7;
  back_wall->material.specular = 0.0;
  CheckersPattern *back_wall_p =
      new CheckersPattern(Color(0.1, 0.1, 0.1), Color(0.9, 0.9, 0.9));
  back_wall_p->set_transform(Matrix::scaling(0.5, 0.5, 0.5));
  back_wall->material.pattern = back_wall_p;
  w.objects.push_back(back_wall);

  // Left Wall Plane
  Plane *left_wall = new Plane();
  left_wall->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-5, 0, 0), Matrix::rotation_y(M_PI / 2.0),
       Matrix::rotation_x(M_PI / 2.0)}));
  left_wall->material.ambient = 0.1;
  left_wall->material.diffuse = 0.7;
  left_wall->material.specular = 0.0;
  CheckersPattern *left_wall_p =
      new CheckersPattern(Color(0.1, 0.1, 0.1), Color(0.9, 0.9, 0.9));
  left_wall_p->set_transform(Matrix::scaling(0.5, 0.5, 0.5));
  left_wall->material.pattern = left_wall_p;
  w.objects.push_back(left_wall);

  // ==========================================
  // 2. THE LARGE GLASS ENVELOPE SPHERE
  // ==========================================

  Sphere *inner_air = new Sphere();
  // Scale it slightly smaller (1.95) than the outer glass sphere (2.0)
  inner_air->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 2.0, 0), Matrix::scaling(1.95, 1.95, 1.95)}));

  inner_air->material.ambient = 0.0;
  inner_air->material.diffuse = 0.0;
  inner_air->material.specular = 0.0;
  inner_air->material.transparency = 1.0;
  inner_air->material.reflective = 0.0;

  // Setting this to 1.0 simulates the air inside the hollow glass bubble
  inner_air->material.refractive_index = 1.0;

  // Make sure it doesn't cast a shadow
  inner_air->casts_shadow = false;
  w.objects.push_back(inner_air);

  Sphere *outer_glass = new Sphere();
  outer_glass->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 2.0, 0), Matrix::scaling(2.0, 2.0, 2.0)}));
  outer_glass->material.color = Color(1.0, 1.0, 1.0);
  outer_glass->material.ambient = 0.0;
  outer_glass->material.diffuse = 0.1;
  outer_glass->material.specular = 1.0;
  outer_glass->material.shininess = 300.0;
  outer_glass->material.transparency = 1.0;
  outer_glass->material.reflective = 0.9;
  outer_glass->material.refractive_index = 1.5; // Glass boundary
  // outer_glass->casts_shadow= false;
  w.objects.push_back(outer_glass);

  // ==========================================
  // 3. INTERNAL SPHERES (INSIDE THE GLASS BALL)
  // ==========================================

  // Center Internal Red Sphere

  Sphere *inner_red = new Sphere();
  inner_red->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0.0, 2.0, 0.0), Matrix::scaling(0.5, 0.5, 0.5)}));
  inner_red->material.color = Color(0.8, 0.1, 0.1);
  inner_red->material.ambient = 0.1;
  inner_red->material.diffuse = 0.8;
  inner_red->material.specular = 0.2;
  w.objects.push_back(inner_red);

  // Small Internal Green Sphere: Nudged up and left
  Sphere *inner_green = new Sphere();
  inner_green->set_transform(
      Matrix::chain_transforms({Matrix::translation(-0.6, 2.6, -0.4),
                                Matrix::scaling(0.25, 0.25, 0.25)}));
  inner_green->material.color = Color(0.1, 0.8, 0.1);
  inner_green->material.ambient = 0.1;
  inner_green->material.diffuse = 0.8;
  inner_green->material.specular = 0.6;
  inner_green->material.shininess = 100.0;
  w.objects.push_back(inner_green);

  // Small Internal Blue Sphere: Elongated and shifted right
  Sphere *inner_blue = new Sphere();
  inner_blue->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0.65, 2.3, -0.2), Matrix::scaling(0.2, 0.3, 0.2)}));
  inner_blue->material.color = Color(0.1, 0.1, 0.7);
  inner_blue->material.ambient = 0.1;
  inner_blue->material.diffuse = 0.7;
  inner_blue->material.specular = 0.3;
  w.objects.push_back(inner_blue);

  // ==========================================
  // 4. EXTERNAL HOVERING BLUE SPHERE (LEFT OUTSIDE)
  // ==========================================
  Sphere *external_blue = new Sphere();
  external_blue->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-2.6, 1.1, 0.8), Matrix::scaling(0.8, 0.8, 0.8)}));
  external_blue->material.color = Color(0.1, 0.2, 0.8);
  external_blue->material.ambient = 0.1;
  external_blue->material.diffuse = 0.8;
  external_blue->material.specular = 0.3;
  w.objects.push_back(external_blue);

  // ==========================================
  // 5. CAMERA CONFIGURATION & RENDER
  // ==========================================
  Camera camera(800, 800, M_PI / 3.0);
  RayPoint from(0, 2.5, -6.2); // Backed up from -5.5 to -6.2
  RayPoint to(0, 2.0,
              0); // Look slightly higher at the center of the glass ball
  RayVector up(0, 1, 0);
  camera.set_transform(Matrix::view_transform(from, to, up));

  std::cout << "Rendering definitive Chapter 11 showcase scene (800x800)..."
            << std::endl;
  Canvas c = camera.render(w);

  std::ofstream out_file("world_render_with_reflections.ppm");
  if (out_file.is_open()) {
    out_file << c.canvas_to_ppm();
    out_file.close();
    std::cout << "Scene render completed successfully." << std::endl;
  } else {
    std::cerr << "\n[ERROR] Problems opening out_file template path."
              << std::endl;
  }

  return 0;
}
