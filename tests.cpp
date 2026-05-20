#include "tests.h"
#include "canvas.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <sstream>

using std::stringstream;

void test_tuple_to_point() {
  RayPoint p = RayPoint(4, -4, 3);
  assert((p == RayTuple(4, -4, 3, 1.0)) && "Point is not equal.");
  std::cout << "[PASS 1.1] Points equal." << std::endl;
}

void test_tuple_to_vector() {
  RayVector v = RayVector(4, -4, 3);
  assert((v == RayTuple(4, -4, 3, 0.0)) && "Vector is not equal.");
  std::cout << "[PASS 1.2] Vectors are equal." << std::endl;
}

void test_tuple_addition() {
  RayTuple t1 = RayTuple(3, -2, 5, 1);
  RayTuple t2 = RayTuple(-2, 3, 1, 0);
  RayTuple t3 = t1 + t2;
  assert(t3 == RayTuple(1, 1, 6, 1));
  std::cout << "[PASS 1.3] Tuple addition works perfectly." << std::endl;
}

void test_point_minus_point() {
  RayTuple s1 = RayPoint(3, 2, 1);
  RayTuple s2 = RayPoint(5, 6, 7);
  RayTuple s3 = s1 - s2;
  assert((s3 == RayVector(-2, -4, -6)) && "Point - Point failed.");
  std::cout << "[PASS 1.4] Point - Point subtraction works perfectly."
            << std::endl;
}

void test_point_minus_vector() {
  RayTuple p1 = RayPoint(3, 2, 1);
  RayTuple v2 = RayVector(5, 6, 7);
  RayTuple x3 = p1 - v2;
  assert((x3 == RayPoint(-2, -4, -6)) && "Point - Vector failed.");
  std::cout << "[PASS 1.5] Point - Vector subtraction works perfectly."
            << std::endl;
}

void test_subtract_vector_from_zero_vector() {
  RayVector zero = RayVector(0, 0, 0);
  RayVector v = RayVector(1, -2, 3);
  assert((zero - v == RayVector(-1, 2, -3)) && "Zero - Vecotr failed.");
  std::cout << "[PASS 1.6] Zero Vector - Vector works." << std::endl;
}

void test_negate_tuple() {
  RayTuple t = RayTuple(1, -2, 3, -4);
  assert((-t == RayTuple(-1, 2, -3, 4)) && "Negate failed.");
  std::cout << "[PASS 1.7] Negate works." << std::endl;
}

void test_multiply_tuple_by_scalar() {
  RayTuple t = RayTuple(1, -2, 3, -4);
  assert((t * 3.5 == RayTuple(3.5, -7, 10.5, -14) &&
          "Multiply with scalar failed."));
  std::cout << "[PASS 1.8] Multiply Tuple with Scalar works." << std::endl;
}

void test_divide_tuple_by_scalar() {
  RayTuple t = RayTuple(1, -2, 3, -4);
  assert(
      (t / 2.0 == RayTuple(0.5, -1, 1.5, -2) && "Divide with scalar failed."));
  std::cout << "[PASS 1.9] Divide Tuple with Scalar works." << std::endl;
}

void test_magnitude_of_vector() {
  RayVector v = RayVector(1, 0, 0);
  assert(v.magnitude() == 1.0 && "Magnitude of vector failed.");

  RayVector v1 = RayVector(0, 1, 0);
  assert(v1.magnitude() == 1.0 && "Magnitude of vector failed.");

  RayVector v2 = RayVector(0, 0, 1);
  assert(v2.magnitude() == 1.0 && "Magnitude of vector failed.");

  RayVector v3 = RayVector(1, 2, 3);
  assert(v3.magnitude() == std::sqrt(14) && "Magnitude of vector failed.");

  RayVector v4 = RayVector(-1, -2, -3);
  assert(v4.magnitude() == std::sqrt(14) && "Magnitude of vector failed.");

  std::cout << "[PASS 1.10] Magnitude works." << std::endl;
}

void test_normalize_vector() {
  RayVector v = RayVector(4, 0, 0);
  assert(v.normalize() == RayVector(1, 0, 0) && "normalize failed.");

  RayVector v1 = RayVector(1, 2, 3);
  assert(v1.normalize() == RayVector(0.26726, 0.53452, 0.80178) &&
         "normalize failed.");

  RayVector v2 = RayVector(1, 2, 3);
  RayTuple v2_norm = v2.normalize();
  assert((v2_norm.magnitude() == 1.0) &&
         "magnitude of norm vector is one, failed.");

  std::cout << "[PASS 1.11] Normalize vector works." << std::endl;
}

void test_dot_product_vector() {
  RayVector a = RayVector(1, 2, 3);
  RayVector b = RayVector(2, 3, 4);
  assert((a.dot(b) == 20.0) && "vector dot product failed.");
  std::cout << "[PASS 1.12] Dot product of Vectors works." << std::endl;
}

void test_cross_product_vector() {
  RayVector a = RayVector(1, 2, 3);
  RayVector b = RayVector(2, 3, 4);
  assert(a.cross(b) == RayVector(-1, 2, -1) &&
         b.cross(a) == RayVector(1, -2, 1) && "Vector cross failed.");
  std::cout << "[PASS 1.13] Cross product of vectors works." << std::endl;
}

void test_color_implementation() {
  Color c = Color(-0.5, 0.4, 1.7);
  assert(c.r == -0.5 && c.g == 0.4 && c.b == 1.7 &&
         "Failed color implementation.");
  std::cout << "[PASS 2.1] Colors implementation works." << std::endl;
}

void test_color_addition() {
  Color c1 = Color(0.9, 0.6, 0.75);
  Color c2 = Color(0.7, 0.1, 0.25);
  assert((c1 + c2 == Color(1.6, 0.7, 1.0)) && "Color addition failed.");
  std::cout << "[PASS 2.2] Colors addition works." << std::endl;
}

void test_color_subtraction() {
  Color c1 = Color(0.9, 0.6, 0.75);
  Color c2 = Color(0.7, 0.1, 0.25);
  assert((c1 - c2 == Color(0.2, 0.5, 0.5)) && "Color subtraction failed.");
  std::cout << "[PASS 2.3] Colors subtraction works." << std::endl;
}

void test_color_multiplication_by_scalar() {
  Color c = Color(0.2, 0.3, 0.4);
  assert((c * 2 == Color(0.4, 0.6, 0.8)) && "Color multiply by scalar failed.");
  std::cout << "[PASS 2.4] Color multiply by scalar works." << std::endl;
}

void test_color_multiply_by_color() {
  Color c1 = Color(1, 0.2, 0.4);
  Color c2 = Color(0.9, 1, 0.1);
  assert((c1 * c2 == Color(0.9, 0.2, 0.04)) &&
         "Color multiply by color failed.");
  std::cout << "[PASS 2.5] Color multiply by color works." << std::endl;
}

void test_create_canvas() {
  Canvas c = Canvas(10, 20);
  assert(
      (c.width == 10 && c.height == 20 && c.pixel_at(0, 0) == Color(0, 0, 0)) &&
      "create canvas failed.");
  std::cout << "[PASS 2.6] Created Canvas works." << std::endl;
}

void test_writing_canvas() {
  Canvas c = Canvas(10, 20);
  Color red = Color(1, 0, 0);
  c.write_pixel(2, 3, red);
  assert((c.pixel_at(2, 3) == red) && "Color at pixel in canvas failed.");
  std::cout << "[PASS 2.7] Writing pixels to canvas works." << std::endl;
}

void test_canvas_to_ppm_header() {
  Canvas c = Canvas(5, 3);
  std::string wh = "";
  wh += std::to_string(c.width);
  wh += " ";
  wh += std::to_string(c.height);
  std::string ppm = c.canvas_to_ppm();
  stringstream ss(ppm);
  std::string line1, line2, line3;

  std::getline(ss, line1);
  std::getline(ss, line2);
  std::getline(ss, line3);

  assert(line1 == "P3");
  assert(line2 == wh);
  assert(line3 == "255");

  std::cout << "[PASS 2.6] Canvas header works." << std::endl;
}
