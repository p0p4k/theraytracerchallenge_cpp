#include "camera.h"
#include "canvas.h"
#include "intersection.h"
#include "light_source.h"
#include "sphere.h"
#include "tuple.h"
#include "world.h"
#include <fstream>

int main() {
  World w;

  LightSource *light_source =
      new LightSource(Color(1, 1, 1), RayPoint(-10, 10, -10));
  w.light_source = light_source;

  // 1. Floor setup
  Sphere *floor = new Sphere();
  floor->set_transform(Matrix::scaling(10, 0.01, 10));
  floor->material.color = Color(1, 0.9, 0.9);
  floor->material.specular = 0.0;

  // 2. Left Wall setup
  Sphere *left_wall = new Sphere();
  left_wall->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0.0, 0.0, 5), Matrix::rotation_y(-PI / 4.0),
       Matrix::rotation_x(PI / 2.0), Matrix::scaling(10.0, 0.01, 10.0)}));
  left_wall->material = floor->material;

  // 3. Right Wall setup
  Sphere *right_wall = new Sphere();
  right_wall->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0.0, 0.0, 5), Matrix::rotation_y(PI / 4.0),
       Matrix::rotation_x(PI / 2.0), Matrix::scaling(10.0, 0.01, 10.0)}));
  right_wall->material = floor->material;

  // 4. Middle Sphere setup
  Sphere *middle = new Sphere();
  middle->set_transform(Matrix::translation(-0.5, 1.0, 0.5));
  middle->material.color = Color(0.1, 1.0, 0.5);
  middle->material.diffuse = 0.7;
  middle->material.specular = 0.3;

  // 5. Right Sphere setup
  Sphere *right = new Sphere();
  right->set_transform(Matrix::chain_transforms(
      {Matrix::translation(1.5, 0.5, -0.5), Matrix::scaling(0.5, 0.5, 0.5)}));
  right->material.color = Color(0.5, 1.0, 0.1);
  right->material.diffuse = 0.7;
  right->material.specular = 0.3;

  // 6. Left Sphere setup
  Sphere *left = new Sphere();
  left->set_transform(
      Matrix::chain_transforms({Matrix::translation(-1.5, 0.33, -0.75),
                                Matrix::scaling(0.33, 0.33, 0.33)}));
  left->material.color = Color(1.0, 0.8, 0.1);
  left->material.diffuse = 0.7;
  left->material.specular = 0.3;

  // Pass the raw heap pointers straight into the objects vector
  w.objects.insert(w.objects.end(),
                   {floor, left_wall, right_wall, middle, right, left});

  Camera camera(1280, 720, PI / 3);
  RayPoint from(0, 1.5, -5);
  RayPoint to(0, 1, 0);
  RayVector up(0, 1, 0);
  camera.set_transform(Matrix::view_transform(from, to, up));

  Canvas c = camera.render(w);

  std::ofstream out_file("world_render_sphere_no_shadows.ppm");
  if (out_file.is_open()) {
    out_file << c.canvas_to_ppm();
    out_file.close();
    std::cout << "sphere written" << std::endl;
  } else {
    std::cerr << "\n[ERROR] problems with file" << std::endl;
  }

  return 0;
}
