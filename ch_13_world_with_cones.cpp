#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "cone.h"
#include "cube.h"
#include "cylinder.h"
#include "light_source.h"
#include "matrix.h"
#include "pattern.h"
#include "plane.h"
#include "tuple.h"
#include "world.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
  World w;

  // Dual light sources to illuminate the massive structure without harsh black
  // shadows
  w.light_source =
      new LightSource(Color(1.0, 1.0, 0.95), RayPoint(15, 25, -20));

  // ==========================================
  // 1. ENVIRONMENT & LAUNCHPAD
  // ==========================================
  Plane *launchpad = new Plane();
  launchpad->set_transform(Matrix::translation(0, -3.0, 0));
  launchpad->material.ambient = 0.15;
  launchpad->material.diffuse = 0.7;
  // Industrial concrete pad
  CheckersPattern *ground_p =
      new CheckersPattern(Color(0.2, 0.2, 0.2), Color(0.3, 0.3, 0.3));
  ground_p->set_transform(Matrix::scaling(4, 1, 4));
  launchpad->material.pattern = ground_p;
  w.objects.push_back(launchpad);

  Plane *sky = new Plane();
  sky->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 0, 50), Matrix::rotation_x(M_PI / 2.0)}));
  // Deep stratospheric blue
  sky->material.color = Color(0.02, 0.08, 0.15);
  sky->material.ambient = 1.0;
  sky->material.diffuse = 0.0;
  w.objects.push_back(sky);

  // ==========================================
  // 2. MAIN ROCKET HULL (TEXTURED STAGES)
  // ==========================================

  // NASA Roll Pattern (Stretched Checkers)
  CheckersPattern *roll_pattern =
      new CheckersPattern(Color(0.9, 0.9, 0.9), Color(0.05, 0.05, 0.05));
  // Scaling X and Z creates wrapped bands; scaling Y heavily creates long
  // vertical blocks
  roll_pattern->set_transform(Matrix::scaling(0.4, 2.0, 0.4));

  // --- STAGE 1 (S-IC) ---
  Cylinder *stage_1 = new Cylinder();
  stage_1->minimum = -1.0;
  stage_1->maximum = 4.0;
  stage_1->closed = true;
  stage_1->set_transform(Matrix::scaling(1.4, 1.0, 1.4));
  stage_1->material.pattern = roll_pattern;
  stage_1->material.ambient = 0.2;
  stage_1->material.diffuse = 0.8;
  w.objects.push_back(stage_1);

  // --- STAGE 2 (S-II) & STAGE 3 ---
  Cylinder *stage_2_3 = new Cylinder();
  stage_2_3->minimum = 4.0;
  stage_2_3->maximum = 9.0;
  stage_2_3->closed = true;
  stage_2_3->set_transform(
      Matrix::scaling(1.1, 1.0, 1.1)); // Slightly thinner upper stage

  // Use horizontal stripes for the upper stage separation rings
  StripePattern *ring_pattern =
      new StripePattern(Color(0.9, 0.9, 0.9), Color(0.1, 0.1, 0.1));
  ring_pattern->set_transform(Matrix::chain_transforms({
      Matrix::scaling(0.1, 0.2, 0.1),
      Matrix::rotation_z(M_PI / 2.0) // Rotate stripes horizontally
  }));
  stage_2_3->material.pattern = ring_pattern;
  stage_2_3->material.diffuse = 0.8;
  w.objects.push_back(stage_2_3);

  // ==========================================
  // 3. NOSE CONE & ESCAPE SYSTEM
  // ==========================================

  // --- APOLLO COMMAND MODULE ---
  Cone *capsule = new Cone();
  capsule->minimum = -1.0; // Truncate the tip slightly for the escape tower
  capsule->maximum = 0.0;  // Base of the cone
  capsule->closed = true;
  capsule->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 10.1, 0), Matrix::scaling(1.1, 1.1, 1.1)}));
  capsule->material.color = Color(0.6, 0.65, 0.7); // Silver metallic
  capsule->material.diffuse = 0.6;
  capsule->material.specular = 0.8;
  capsule->material.shininess = 200;
  capsule->material.reflective = 0.3; // Mirror finish
  w.objects.push_back(capsule);

  // --- LAUNCH ESCAPE SYSTEM (LES) ---
  Cylinder *escape_mast = new Cylinder();
  escape_mast->minimum = 0.0;
  escape_mast->maximum = 1.0;
  escape_mast->set_transform(Matrix::chain_transforms({
      Matrix::translation(0, 10.1, 0),
      Matrix::scaling(0.05, 1.0, 0.05) // Very thin pole
  }));
  escape_mast->material.color = Color(0.9, 0.9, 0.9);
  w.objects.push_back(escape_mast);

  Cone *escape_tip = new Cone();
  escape_tip->minimum = -0.1;
  escape_tip->maximum = 0.0;
  escape_tip->set_transform(Matrix::chain_transforms(
      {Matrix::translation(0, 11.2, 0), Matrix::scaling(0.6, 1.0, 0.6)}));
  escape_tip->material.color = Color(0.8, 0.1, 0.1); // Red tip
  w.objects.push_back(escape_tip);

  // ==========================================
  // 4. STRAP-ON SOLID ROCKET BOOSTERS
  // ==========================================

  std::vector<std::pair<double, double>> booster_pos = {
      {-1.4, 0.0}, {1.4, 0.0}, {0.0, -1.4}, {0.0, 1.4}};

  for (const auto &[bx, bz] : booster_pos) {
    // Booster Body
    Cylinder *booster = new Cylinder();
    booster->minimum = -1.5;
    booster->maximum = 2.5;
    booster->closed = true;
    booster->set_transform(Matrix::chain_transforms(
        {Matrix::translation(bx, 0.0, bz), Matrix::scaling(0.35, 1.0, 0.35)}));
    booster->material.color = Color(0.8, 0.8, 0.8);
    booster->material.diffuse = 0.7;
    w.objects.push_back(booster);

    // Aerodynamic Nose Cone for Booster
    Cone *b_nose = new Cone();
    b_nose->minimum = -1.0;
    b_nose->maximum = 0.0;
    b_nose->closed = true;
    b_nose->set_transform(Matrix::chain_transforms(
        {Matrix::translation(bx, 3.5, bz), Matrix::scaling(0.35, 1.0, 0.35)}));
    b_nose->material.color = Color(0.2, 0.2, 0.2);
    w.objects.push_back(b_nose);
  }

  // ==========================================
  // 5. ENGINES & EXHAUST PLUMES (TRANSPARENT CONES)
  // ==========================================

  std::vector<std::pair<double, double>> engine_pos = {
      {-0.7, -0.7}, {0.7, -0.7}, {-0.7, 0.7}, {0.7, 0.7}, {0.0, 0.0}};

  for (const auto &[ex, ez] : engine_pos) {
    // Engine Bell
    Cone *nozzle = new Cone();
    nozzle->minimum = 0.0;
    nozzle->maximum = 1.0;
    nozzle->closed = false;
    nozzle->set_transform(Matrix::chain_transforms(
        {Matrix::translation(ex, -2.0, ez), Matrix::scaling(0.4, 1.0, 0.4)}));
    nozzle->material.color = Color(0.1, 0.1, 0.1);
    w.objects.push_back(nozzle);

    // Glowing Exhaust Flame (Inverted semi-transparent cone)
    Cone *flame = new Cone();
    flame->minimum = -1.0;
    flame->maximum = 0.0;
    flame->closed = true;
    flame->set_transform(Matrix::chain_transforms({
        Matrix::translation(ex, -2.0, ez),
        Matrix::scaling(0.3, 3.0, 0.3) // Long, stretched flame
    }));
    flame->material.color = Color(1.0, 0.5, 0.1); // Bright fiery orange
    flame->material.ambient = 1.0;                // Glows in the dark
    flame->material.diffuse = 0.0;
    flame->material.specular = 0.0;
    flame->material.transparency = 0.6; // Semi-transparent fire
    flame->material.refractive_index = 1.0;
    flame->casts_shadow = false; // Fire doesn't cast dark shadows!
    w.objects.push_back(flame);
  }

  // ==========================================
  // 6. CAMERA SETUP & RENDER
  // ==========================================
  Camera camera(1000, 1400, M_PI / 2.8);

  // Placed on the ground far back, looking up to capture the sheer scale
  RayPoint from(6.0, -2.0, -10.0);
  RayPoint to(0.0, 4.0, 0.0);
  RayVector up(0, 1, 0);
  camera.set_transform(Matrix::view_transform(from, to, up));

  std::cout << "Rendering Textured Saturn V Launch Scene..." << std::endl;
  Canvas c = camera.render(w);

  std::ofstream out_file("saturn_v_textured.ppm");
  if (out_file.is_open()) {
    out_file << c.canvas_to_ppm();
    out_file.close();
    std::cout << "Render successful: 'saturn_v_textured.ppm' generated."
              << std::endl;
  }

  return 0;
}
