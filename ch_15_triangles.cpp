#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "groups.h"
#include "light_source.h"
#include "matrix.h"
#include "obj_parser.h"
#include "smooth_triangle.h"
#include "triangle.h"
#include "world.h"
#include <cmath>
#include <fstream>
#include <iostream>

void apply_material(Shape *shape, const Material &mat) {
  Group *group = dynamic_cast<Group *>(shape);
  if (group) {
    for (Shape *child : group->child) {
      apply_material(child, mat);
    }
  } else {
    shape->material = mat;
  }
}

int main() {
  World w;

  w.light_source = new LightSource(Color(1.0, 1.0, 1.0), RayPoint(0, 10, -10));

  // 2. THE TEAPOT
  std::cout << "Loading teapot..." << std::endl;
  ObjParser parser;

  parser.parse_file("teapot.obj");

  std::cout << "DEBUG: Loaded " << parser.vertices.size() << " vertices."
            << std::endl;
  if (parser.vertices.size() <= 1) {
    std::cerr << "CRITICAL ERROR: Teapot file not found or empty! Check your "
                 "file path."
              << std::endl;
    return 1;
  }

  Group *model = parser.obj_to_group();
  model->set_transform(Matrix::scaling(0.12, 0.12, 0.12));

  Material red_mat;
  red_mat.color = Color(1.0, 0.2, 0.2);
  red_mat.ambient = 0.2;
  red_mat.diffuse = 0.7;
  red_mat.specular = 0.3;
  red_mat.shininess = 20;

  apply_material(model, red_mat);
  w.objects.push_back(model);

  // 3. CAMERA
  // 500x500 for a fast test render
  Camera camera(500, 500, M_PI / 3.0);

  // Staring straight ahead, slightly elevated
  RayPoint from(0, 3, -10);
  RayPoint to(0, 1, 0);
  RayVector up(0, 1, 0);
  camera.set_transform(Matrix::view_transform(from, to, up));

  std::cout << "Rendering minimal scene..." << std::endl;
  Canvas c = camera.render(w);

  std::ofstream out_file("just_teapot.ppm");
  if (out_file.is_open()) {
    out_file << c.canvas_to_ppm();
    out_file.close();
    std::cout << "Done! Saved to just_teapot.ppm" << std::endl;
  }

  return 0;
}
