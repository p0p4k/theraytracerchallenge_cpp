#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "cube.h"
#include "light_source.h"
#include "matrix.h"
#include "pattern.h"
#include "tuple.h"
#include "world.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
  World w;

  // Moved the light source to cast distinct, dramatic shadows across the table
  w.light_source = new LightSource(Color(1.0, 1.0, 0.95), RayPoint(-2, 8, -5));

  // ==========================================
  // 1. THE ROOM SURFACES
  // ==========================================

  Cube *floor = new Cube();
  floor->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 0, 0), Matrix::scaling(20, 0.01, 20)}));
  floor->material.ambient = 0.2;
  floor->material.diffuse = 0.6;
  CheckersPattern *floor_p =
      new CheckersPattern(Color(0.1, 0.1, 0.1), Color(0.7, 0.7, 0.7));
  floor_p->set_transform(Matrix::scaling(0.4, 1, 0.4));
  floor->material.pattern = floor_p;
  w.objects.push_back(floor);

  StripePattern *wall_p =
      new StripePattern(Color(0.4, 0.3, 0.25), Color(0.5, 0.4, 0.35));
  wall_p->set_transform(Matrix::scaling(0.25, 1.0, 1.0));

  Cube *left_wall = new Cube();
  left_wall->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-8.0, 5.0, 0.0), Matrix::scaling(0.01, 5.0, 20.0)}));
  left_wall->material.ambient = 0.15;
  left_wall->material.diffuse = 0.65;
  left_wall->material.pattern = wall_p;
  w.objects.push_back(left_wall);

  Cube *back_wall = new Cube();
  back_wall->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0.0, 5.0, 8.0), Matrix::scaling(20.0, 5.0, 0.01)}));
  back_wall->material.ambient = 0.15;
  back_wall->material.diffuse = 0.65;
  back_wall->material.pattern = wall_p;
  w.objects.push_back(back_wall);

  // ==========================================
  // 2. WALL ACCENTS
  // ==========================================

  Cube *mirror = new Cube();
  mirror->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-2.0, 4.0, 7.9), Matrix::scaling(2.5, 1.5, 0.05)}));
  mirror->material.color = Color(0.0, 0.0, 0.0);
  mirror->material.ambient = 0.0;
  mirror->material.diffuse = 0.0;
  mirror->material.reflective = 0.95;
  w.objects.push_back(mirror);

  Cube *frame_red = new Cube();
  frame_red->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-7.9, 5.0, 3.0), Matrix::scaling(0.05, 1.0, 1.0)}));
  frame_red->material.color = Color(0.7, 0.15, 0.15);
  frame_red->material.diffuse = 0.7;
  w.objects.push_back(frame_red);

  Cube *frame_green = new Cube();
  frame_green->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-7.9, 6.0, 5.0), Matrix::scaling(0.05, 0.4, 0.4)}));
  frame_green->material.color = Color(0.15, 0.5, 0.2);
  frame_green->material.diffuse = 0.7;
  w.objects.push_back(frame_green);

  // ==========================================
  // 3. THE TABLE (WITH WOOD PATTERN)
  // ==========================================

  double table_center_x = -1.5;
  double table_center_z = 2.5;
  double table_y = 1.5;

  Cube *tabletop = new Cube();
  tabletop->set_transform(Matrix::chain_transforms(
      {Matrix::translation(table_center_x, table_y, table_center_z),
       Matrix::scaling(3.0, 0.05, 2.0)}));
  // Simulate wood grain using a very tightly scaled stripe pattern
  StripePattern *wood_p =
      new StripePattern(Color(0.45, 0.35, 0.22), Color(0.40, 0.30, 0.18));
  wood_p->set_transform(Matrix::chain_transforms(
      {Matrix::scaling(0.05, 1.0, 1.0), Matrix::rotation_y(0.1)}));
  tabletop->material.pattern = wood_p;
  tabletop->material.ambient = 0.1;
  tabletop->material.diffuse = 0.7;
  tabletop->material.specular = 0.3;
  tabletop->material.reflective = 0.1;
  w.objects.push_back(tabletop);

  std::vector<std::pair<double, double>> legs = {
      {-4.3, 0.7}, {1.3, 0.7}, {-4.3, 4.3}, {1.3, 4.3}};
  for (const auto &[lx, lz] : legs) {
    Cube *leg = new Cube();
    leg->set_transform(Matrix::chain_transforms(
        {Matrix::translation(lx, 0.75, lz), Matrix::scaling(0.1, 0.75, 0.1)}));
    leg->material.color = Color(0.32, 0.24, 0.15);
    leg->material.diffuse = 0.6;
    w.objects.push_back(leg);
  }

  // ==========================================
  // 4. ITEMS ON TOP OF THE TABLE
  // ==========================================
  double surface_y = table_y + 0.05;

  // 1. The Glass Block
  // Positioned near the front edge so it refracts the patterned floor beneath
  // it
  Cube *glass_block = new Cube();
  glass_block->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-0.5, surface_y + 0.4, 0.8), Matrix::rotation_y(0.3),
       Matrix::scaling(0.4, 0.4, 0.4)}));
  // High-fidelity glass settings: dark color, zero diffuse, high specular &
  // transmission
  glass_block->material.color = Color(0.02, 0.02, 0.02);
  glass_block->material.ambient = 0.0;
  glass_block->material.diffuse = 0.02;
  glass_block->material.specular = 1.0;
  glass_block->material.shininess = 300.0;
  glass_block->material.transparency = 0.95;
  glass_block->material.reflective = 0.9;
  glass_block->material.refractive_index = 1.5;
  glass_block->casts_shadow =
      false; // Prevents a solid black shadow for transparent objects
  w.objects.push_back(glass_block);

  // 2. Patterned Toy Block
  Cube *patterned_block = new Cube();
  patterned_block->set_transform(Matrix::chain_transforms(
      {Matrix::translation(-2.5, surface_y + 0.2, 1.5), Matrix::rotation_y(0.6),
       Matrix::scaling(0.2, 0.2, 0.2)}));
  CheckersPattern *block_p =
      new CheckersPattern(Color(0.8, 0.2, 0.2), Color(0.9, 0.9, 0.9));
  block_p->set_transform(Matrix::scaling(0.2, 0.2, 0.2));
  patterned_block->material.pattern = block_p;
  patterned_block->material.diffuse = 0.8;
  w.objects.push_back(patterned_block);

  // 3. Standing Elongated Pillar (Cyan)
  Cube *standing_pillar = new Cube();
  standing_pillar->set_transform(Matrix::chain_transforms({
      Matrix::translation(-3.5, surface_y + 0.5, 3.5), Matrix::rotation_y(-0.2),
      Matrix::scaling(0.1, 0.5, 0.1) // Tall and thin
  }));
  standing_pillar->material.color = Color(0.1, 0.7, 0.6);
  standing_pillar->material.diffuse = 0.8;
  w.objects.push_back(standing_pillar);

  // 4. Fallen Elongated Pillar (Magenta)
  Cube *fallen_pillar = new Cube();
  fallen_pillar->set_transform(Matrix::chain_transforms({
      Matrix::translation(-1.5, surface_y + 0.1, 3.2), Matrix::rotation_y(0.8),
      Matrix::scaling(0.5, 0.1, 0.1) // Long flat
  }));
  fallen_pillar->material.color = Color(0.6, 0.2, 0.6);
  fallen_pillar->material.diffuse = 0.8;
  w.objects.push_back(fallen_pillar);

  // ==========================================
  // 5. RENDER PIPELINE
  // ==========================================
  Camera camera(100, 50, PI / 3.0);

  RayPoint from(3.0, 4.0, -4.0);
  RayPoint to(-1.5, 1.5, 2.5); // Aim directly at the table center
  RayVector up(0, 1, 0);
  camera.set_transform(Matrix::view_transform(from, to, up));

  std::cout << "Rendering upgraded patterned scene..." << std::endl;
  Canvas c = camera.render(w);

  std::ofstream out_file("world_render_with_cubes.ppm");
  if (out_file.is_open()) {
    out_file << c.canvas_to_ppm();
    out_file.close();
    std::cout << "Success! Saved to 'world_render_with_cubes.ppm'."
              << std::endl;
  } else {
    std::cerr << "Failed to open output file." << std::endl;
  }

  return 0;
}
