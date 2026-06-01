#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "cylinder.h"
#include "groups.h"
#include "light_source.h"
#include "matrix.h"
#include "plane.h"
#include "sphere.h"
#include "tuple.h"
#include "world.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

// ==========================================
// HEXAGON GENERATOR FUNCTIONS
// ==========================================

Sphere *hexagon_corner(const Material &mat) {
  Sphere *corner = new Sphere();
  corner->material = mat;
  corner->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 0, -1), Matrix::scaling(0.25, 0.25, 0.25)}));
  return corner;
}

Cylinder *hexagon_edge(const Material &mat) {
  Cylinder *edge = new Cylinder();
  edge->minimum = 0;
  edge->maximum = 1;
  edge->material = mat;
  edge->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 0, -1), Matrix::rotation_y(-M_PI / 6.0),
       Matrix::rotation_z(-M_PI / 2.0), Matrix::scaling(0.25, 1, 0.25)}));
  return edge;
}

Group *hexagon_side(const Material &mat) {
  Group *side = new Group();
  side->add_child(hexagon_corner(mat));
  side->add_child(hexagon_edge(mat));
  return side;
}

Group *hexagon(const Material &mat) {
  Group *hex = new Group();
  for (int i = 0; i < 6; ++i) {
    Group *side = hexagon_side(mat);
    side->set_transform(Matrix::rotation_y(i * M_PI / 3.0));
    hex->add_child(side);
  }
  return hex;
}

// ==========================================
// MAIN RENDER LOOP
// ==========================================

int main() {
  World w;
  w.light_source = new LightSource(Color(1.0, 1.0, 1.0), RayPoint(10, 20, -10));

  // --- 1. THE HEXAGON ---
  Material hex_mat;
  hex_mat.color = Color(0.1, 0.5, 0.9); // Brilliant metallic blue
  hex_mat.diffuse = 0.7;
  hex_mat.specular = 0.6;
  hex_mat.shininess = 150;
  hex_mat.reflective = 0.2;

  Group *master_hex = hexagon(hex_mat);

  // Rotate the entire group at once to show off group transformations!
  master_hex->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 1.5, 0), Matrix::rotation_x(M_PI / 6.0),
       Matrix::rotation_z(M_PI / 12.0)}));

  w.objects.push_back(master_hex);

  // --- 2. THE ENVIRONMENT ---
  Plane *floor = new Plane();
  floor->material.color = Color(0.9, 0.9, 0.9);
  floor->material.ambient = 0.1;
  floor->material.diffuse = 0.8;
  floor->material.reflective = 0.3; // Slight reflection to ground the object
  w.objects.push_back(floor);

  Plane *backdrop = new Plane();
  backdrop->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 0, 15), Matrix::rotation_x(M_PI / 2.0)}));
  backdrop->material.color = Color(0.1, 0.1, 0.15); // Dark grey studio wall
  w.objects.push_back(backdrop);

  // --- 3. CAMERA ---
  Camera camera(800, 600, M_PI / 3.0);

  // Looking down slightly at the floating, tilted hexagon
  RayPoint from(0.0, 4.0, -8.0);
  RayPoint to(0.0, 1.0, 0.0);
  RayVector up(0.0, 1.0, 0.0);
  camera.set_transform(Matrix::view_transform(from, to, up));

  std::cout << "Rendering Grouped Hexagon Scene..." << std::endl;
  Canvas c = camera.render(w);

  std::ofstream out_file("hexagon_groups.ppm");
  if (out_file.is_open()) {
    out_file << c.canvas_to_ppm();
    out_file.close();
    std::cout << "Success! Bounding boxes made this fast. Saved to "
                 "'hexagon_groups.ppm'."
              << std::endl;
  } else {
    std::cerr << "Failed to open output file." << std::endl;
  }

  return 0;
}
