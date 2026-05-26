#include "camera.h"
#include "canvas.h"
#include "light_source.h"
#include "pattern.h"
#include "plane.h"
#include "sphere.h"
#include "tuple.h"
#include "world.h"
#include <fstream>

int main() {
  World w;

  LightSource *light_source =
      new LightSource(Color(1, 1, 1), RayPoint(-10, 10, -10));
  w.light_source = light_source;

  // 1. Floor Plane
  Plane *floor = new Plane();
  floor->material.color = Color(1, 0.9, 0.9);
  floor->material.specular = 0.0;

  // 2. Left Backdrop Plane (Tilted +45 degrees)
  Plane *left_wall = new Plane();
  left_wall->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 0, 10), Matrix::rotation_y(M_PI / 4.0),
       Matrix::rotation_x(M_PI / 2.0)}));
  left_wall->material.color = Color(0.8, 0.8, 0.9);
  left_wall->material.specular = 0.0;
  left_wall->material.ambient = 0.1;

  // 3. Right Backdrop Plane (Reflected: Tilted -45 degrees)
  Plane *right_wall = new Plane();
  right_wall->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 0, 10),
       Matrix::rotation_y(-M_PI /
                          4.0), // Negative angle creates the mirror reflection
       Matrix::rotation_x(M_PI / 2.0)}));
  right_wall->material.color = Color(0.8, 0.8, 0.9);
  right_wall->material.specular = 0.0;
  right_wall->material.ambient = 0.1;

  // 4. Middle Sphere
  Sphere *middle = new Sphere();
  middle->set_transform(Matrix::translation(-0.5, 1.0, 0.5));
  middle->material.color = Color(0.1, 1.0, 0.5);
  middle->material.diffuse = 0.7;
  middle->material.specular = 0.3;
  StripePattern *pattern = new StripePattern(Color(1, 0, 0), Color(0, 0, 1));
  middle->material.pattern = pattern;

  // 5. Right Sphere
  Sphere *right = new Sphere();
  right->set_transform(Matrix::chain_transforms(
      {Matrix::translation(1.5, 0.5, -0.5), Matrix::scaling(1.5, 0.5, 0.5)}));
  right->material.color = Color(0.5, 1.0, 0.1);
  right->material.diffuse = 0.7;
  right->material.specular = 0.3;

  // 6. Left Sphere
  Sphere *left = new Sphere();
  left->set_transform(
      Matrix::chain_transforms({Matrix::translation(-1.5, 0.33, -0.75),
                                Matrix::scaling(0.33, 0.33, 0.33)}));
  left->material.color = Color(1.0, 0.8, 0.1);
  left->material.diffuse = 0.7;
  left->material.specular = 0.3;

  // Add all objects to the world container
  w.objects.insert(w.objects.end(),
                   {floor, left_wall, right_wall, middle, right, left});

  // Camera Setup
  Camera camera(1280, 720, M_PI / 3.0);
  RayPoint from(0, 1.5, -5);
  RayPoint to(0, 1, 0);
  RayVector up(0, 1, 0);
  camera.set_transform(Matrix::view_transform(from, to, up));

  // Render Pipeline
  Canvas c = camera.render(w);

  // File IO Output
  std::ofstream out_file("world_render_with_plane.ppm");
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
