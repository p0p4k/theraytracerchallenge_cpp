
#include "tests.h"
#include "camera.h"
#include "color.h"
#include "computations.h"
#include "cube.h"
#include "intersection.h"
#include "light_source.h"
#include "matrix.h"
#include "pattern.h"
#include "plane.h"
#include "ray.h"
#include "shapes.h"
#include "sphere.h"
#include "tuple.h"
#include "utilities.h"
#include "world.h"
#include <cassert>
#include <vector>

void test_tuple_to_point() {
  RayPoint p = RayPoint(4, -4, 3);
  assert(equal(p.w, 1.0) && "Point is not equal.");
  std::cout << "[PASS 1.1] Points equal." << std::endl;
}

void test_tuple_to_vector() {
  RayVector v = RayVector(4, -4, 3);
  assert(equal(v.w, 0.0) && "Vector is not equal.");
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
  RayPoint s1(3, 2, 1);
  RayPoint s2(5, 6, 7);
  RayVector s3 = s1 - s2;
  assert((s3 == RayVector(-2, -4, -6)) && "Point - Point failed.");
  std::cout << "[PASS 1.4] Point - Point subtraction works perfectly."
            << std::endl;
}

void test_point_minus_vector() {
  RayPoint p1(3, 2, 1);
  RayVector v2(5, 6, 7);
  RayPoint x3 = p1 - v2;
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
  assert(equal(v.magnitude(), 1.0) && "Magnitude of vector failed.");

  RayVector v1 = RayVector(0, 1, 0);
  assert(equal(v1.magnitude(), 1.0) && "Magnitude of vector failed.");

  RayVector v2 = RayVector(0, 0, 1);
  assert(equal(v2.magnitude(), 1.0) && "Magnitude of vector failed.");

  RayVector v3 = RayVector(1, 2, 3);
  assert(equal(v3.magnitude(), std::sqrt(14)) && "Magnitude of vector failed.");

  RayVector v4 = RayVector(-1, -2, -3);
  assert(equal(v4.magnitude(), std::sqrt(14)) && "Magnitude of vector failed.");

  std::cout << "[PASS 1.10] Magnitude works." << std::endl;
}

void test_normalize_vector() {
  RayVector v(4, 0, 0);
  assert(v.normalize() == RayVector(1, 0, 0) && "normalize failed.");

  RayVector v1(1, 2, 3);
  assert(v1.normalize() == RayVector(0.26726, 0.53452, 0.80178) &&
         "normalize failed.");

  RayVector v2(1, 2, 3);
  RayTuple v2_norm = v2.normalize();
  assert(equal(v2_norm.magnitude(), 1.0) &&
         "magnitude of norm vector is one, failed.");

  std::cout << "[PASS 1.11] Normalize vector works." << std::endl;
}

void test_dot_product_vector() {
  RayVector a = RayVector(1, 2, 3);
  RayVector b = RayVector(2, 3, 4);
  assert(equal(a.dot(b), 20.0) && "vector dot product failed.");
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
  std::stringstream ss(ppm);
  std::string line1, line2, line3;

  std::getline(ss, line1);
  std::getline(ss, line2);
  std::getline(ss, line3);

  assert(line1 == "P3");
  assert(line2 == wh);
  assert(line3 == "255");

  std::cout << "[PASS 2.6] Canvas header works." << std::endl;
}

void test_matrix_construction() {
  Matrix m = Matrix(4, 4);
  assert(m.rows == 4);
  assert(m.columns == 4);

  for (unsigned int i = 0; i < m.rows; i++) {
    for (unsigned int j = 0; j < m.columns; j++) {
      assert(m[i][j] == 0.0);
    }
  }

  std::cout
      << "[PASS 3.1] Matrix construction and default initialization works."
      << std::endl;
}

void test_matrix_comparision_equal() {
  Matrix m1(4, 4);
  Matrix m2(4, 4);
  m1[0][0] = 1.0;
  m1[0][1] = 2.0;
  m1[0][2] = 3.0;
  m1[0][3] = 4.0;
  m2[0][0] = 1.0;
  m2[0][1] = 2.0;
  m2[0][2] = 3.0;
  m2[0][3] = 4.0;

  m1[1][0] = 5.5;
  m1[1][1] = 6.5;
  m1[1][2] = 7.5;
  m1[1][3] = 8.5;
  m2[1][0] = 5.5;
  m2[1][1] = 6.5;
  m2[1][2] = 7.5;
  m2[1][3] = 8.5;

  m1[2][0] = 9.0;
  m1[2][1] = 10.0;
  m1[2][2] = 11.0;
  m1[2][3] = 12.0;
  m2[2][0] = 9.0;
  m2[2][1] = 10.0;
  m2[2][2] = 11.0;
  m2[2][3] = 12.0;

  m1[3][0] = 13.5;
  m1[3][1] = 14.5;
  m1[3][2] = 15.5;
  m1[3][3] = 16.5;
  m2[3][0] = 13.5;
  m2[3][1] = 14.5;
  m2[3][2] = 15.5;
  m2[3][3] = 16.5;

  assert((m1 == m2) && "comparision equal failed.");
  std::cout << "[PASS 3.2] Matrix comparision works." << std::endl;
}

void test_matrix_comparision_not_equal() {
  Matrix m1(4, 4);
  Matrix m2(4, 4);
  m1[0][0] = 1.0;
  m1[0][1] = 2.0;
  m1[0][2] = 3.0;
  m1[0][3] = 4.0;
  m2[0][0] = 1.0;
  m2[0][1] = 6.0;
  m2[0][2] = 3.0;
  m2[0][3] = 4.0;
  m1[1][0] = 5.5;
  m1[1][1] = 6.5;
  m1[1][2] = 7.5;
  m1[1][3] = 5.5;
  m2[1][0] = 5.5;
  m2[1][1] = 6.5;
  m2[1][2] = 7.5;
  m2[1][3] = 8.5;

  m1[2][0] = 9.0;
  m1[2][1] = 10.0;
  m1[2][2] = 11.0;
  m1[2][3] = 2.0;
  m2[2][0] = 9.0;
  m2[2][1] = 10.0;
  m2[2][2] = 11.0;
  m2[2][3] = 2.0;

  m1[3][0] = 13.5;
  m1[3][1] = 14.5;
  m1[3][2] = 5.5;
  m1[3][3] = 16.5;
  m2[3][0] = 13.5;
  m2[3][1] = 14.5;
  m2[3][2] = 15.5;
  m2[3][3] = 16.5;

  assert((m1 != m2) && "comparision not equal failed.");
  std::cout << "[PASS 3.3] Matrix comparision not equal works." << std::endl;
}

void test_matrix_multiply() {
  Matrix m1(4, 4);
  m1[0][0] = 1.0;
  m1[0][1] = 2.0;
  m1[0][2] = 3.0;
  m1[0][3] = 4.0;
  m1[1][0] = 5.0;
  m1[1][1] = 6.0;
  m1[1][2] = 7.0;
  m1[1][3] = 8.0;
  m1[2][0] = 9.0;
  m1[2][1] = 8.0;
  m1[2][2] = 7.0;
  m1[2][3] = 6.0;
  m1[3][0] = 5.0;
  m1[3][1] = 4.0;
  m1[3][2] = 3.0;
  m1[3][3] = 2.0;

  Matrix m2(4, 4);
  m2[0][0] = -2.0;
  m2[0][1] = 1.0;
  m2[0][2] = 2.0;
  m2[0][3] = 3.0;
  m2[1][0] = 3.0;
  m2[1][1] = 2.0;
  m2[1][2] = 1.0;
  m2[1][3] = -1.0;
  m2[2][0] = 4.0;
  m2[2][1] = 3.0;
  m2[2][2] = 6.0;
  m2[2][3] = 5.0;
  m2[3][0] = 1.0;
  m2[3][1] = 2.0;
  m2[3][2] = 7.0;
  m2[3][3] = 8.0;

  Matrix result = m1.matrix_multiply(m2);

  assert(result.rows == 4);
  assert(result.columns == 4);

  assert(equal(result[0][0], 20.0));
  assert(equal(result[0][1], 22.0));
  assert(equal(result[0][2], 50.0));
  assert(equal(result[0][3], 48.0));
  assert(equal(result[1][0], 44.0));
  assert(equal(result[1][1], 54.0));
  assert(equal(result[1][2], 114.0));
  assert(equal(result[1][3], 108.0));
  assert(equal(result[2][0], 40.0));
  assert(equal(result[2][1], 58.0));
  assert(equal(result[2][2], 110.0));
  assert(equal(result[2][3], 102.0));
  assert(equal(result[3][0], 16.0));
  assert(equal(result[3][1], 26.0));
  assert(equal(result[3][2], 46.0));
  assert(equal(result[3][3], 42.0));

  std::cout << "[PASS 3.4] Matrix multiplication works." << std::endl;
}

void test_matrix_tuple_multiply() {
  Matrix m(4, 4);
  m[0][0] = 1.0;
  m[0][1] = 2.0;
  m[0][2] = 3.0;
  m[0][3] = 4.0;
  m[1][0] = 2.0;
  m[1][1] = 4.0;
  m[1][2] = 4.0;
  m[1][3] = 2.0;
  m[2][0] = 8.0;
  m[2][1] = 6.0;
  m[2][2] = 4.0;
  m[2][3] = 1.0;
  m[3][0] = 0.0;
  m[3][1] = 0.0;
  m[3][2] = 0.0;
  m[3][3] = 1.0;

  RayTuple t(1.0, 2.0, 3.0, 1.0);

  RayTuple result = m.tuple_multiply(t);

  assert(equal(result.x, 18.0));
  assert(equal(result.y, 24.0));
  assert(equal(result.z, 33.0));
  assert(equal(result.w, 1.0));

  std::cout << "[PASS 3.5] Matrix multiplied by RayTuple works." << std::endl;
}

void test_identity_matrix_multiplication() {
  Matrix m(4, 4);
  m[0][0] = 0.0;
  m[0][1] = 1.0;
  m[0][2] = 2.0;
  m[0][3] = 4.0;
  m[1][0] = 1.0;
  m[1][1] = 2.0;
  m[1][2] = 4.0;
  m[1][3] = 8.0;
  m[2][0] = 2.0;
  m[2][1] = 4.0;
  m[2][2] = 8.0;
  m[2][3] = 16.0;
  m[3][0] = 4.0;
  m[3][1] = 8.0;
  m[3][2] = 16.0;
  m[3][3] = 32.0;

  Matrix id = Matrix::identity(4);
  Matrix result_matrix = m.matrix_multiply(id);

  assert(result_matrix == m);

  RayTuple t(1.0, 2.0, 3.0, 4.0);
  RayTuple result_tuple = id.tuple_multiply(t);

  assert(equal(result_tuple.x, 1.0));
  assert(equal(result_tuple.y, 2.0));
  assert(equal(result_tuple.z, 3.0));
  assert(equal(result_tuple.w, 4.0));

  std::cout << "[PASS 3.6] Identity matrix multiplications works." << std::endl;
}

void test_matrix_transpose() {
  Matrix m(4, 4);
  m[0][0] = 0.0;
  m[0][1] = 9.0;
  m[0][2] = 3.0;
  m[0][3] = 0.0;
  m[1][0] = 9.0;
  m[1][1] = 8.0;
  m[1][2] = 0.0;
  m[1][3] = 8.0;
  m[2][0] = 1.0;
  m[2][1] = 8.0;
  m[2][2] = 5.0;
  m[2][3] = 3.0;
  m[3][0] = 0.0;
  m[3][1] = 0.0;
  m[3][2] = 5.0;
  m[3][3] = 8.0;
  Matrix current = m.transpose();

  assert(current[0][0] == 0.0);
  assert(current[0][1] == 9.0);
  assert(current[0][2] == 1.0);
  assert(current[0][3] == 0.0);
  assert(current[1][0] == 9.0);
  assert(current[1][1] == 8.0);
  assert(current[1][2] == 8.0);
  assert(current[1][3] == 0.0);
  assert(current[2][0] == 3.0);
  assert(current[2][1] == 0.0);
  assert(current[2][2] == 5.0);
  assert(current[2][3] == 5.0);
  assert(current[3][0] == 0.0);
  assert(current[3][1] == 8.0);
  assert(current[3][2] == 3.0);
  assert(current[3][3] == 8.0);

  Matrix id = Matrix::identity(4);
  assert(id.transpose() == id);

  std::cout << "[PASS 3.7] Matrix transpositions works." << std::endl;
}

void test_matrix_submatrix() {
  Matrix m1(3, 3);
  m1[0][0] = 1.0;
  m1[0][1] = 5.0;
  m1[0][2] = 0.0;
  m1[1][0] = -3.0;
  m1[1][1] = 2.0;
  m1[1][2] = 7.0;
  m1[2][0] = 0.0;
  m1[2][1] = 6.0;
  m1[2][2] = -3.0;

  Matrix sub1 = m1.submatrix(0, 2);

  assert(sub1.rows == 2);
  assert(sub1.columns == 2);
  assert(equal(sub1[0][0], -3.0));
  assert(equal(sub1[0][1], 2.0));
  assert(equal(sub1[1][0], 0.0));
  assert(equal(sub1[1][1], 6.0));

  Matrix m2(4, 4);
  m2[0][0] = -6.0;
  m2[0][1] = 1.0;
  m2[0][2] = 1.0;
  m2[0][3] = 6.0;
  m2[1][0] = -8.0;
  m2[1][1] = 5.0;
  m2[1][2] = 8.0;
  m2[1][3] = 6.0;
  m2[2][0] = -1.0;
  m2[2][1] = 0.0;
  m2[2][2] = 8.0;
  m2[2][3] = 2.0;
  m2[3][0] = -7.0;
  m2[3][1] = 1.0;
  m2[3][2] = -1.0;
  m2[3][3] = 1.0;

  Matrix sub2 = m2.submatrix(2, 1);

  assert(sub2.rows == 3);
  assert(sub2.columns == 3);
  assert(equal(sub2[0][0], -6.0));
  assert(equal(sub2[0][1], 1.0));
  assert(equal(sub2[0][2], 6.0));
  assert(equal(sub2[1][0], -8.0));
  assert(equal(sub2[1][1], 8.0));
  assert(equal(sub2[1][2], 6.0));
  assert(equal(sub2[2][0], -7.0));
  assert(equal(sub2[2][1], -1.0));
  assert(equal(sub2[2][2], 1.0));

  std::cout << "[PASS 3.8] Matrix submatrix extraction works." << std::endl;
}

void test_matrix_determinant_2x2() {
  Matrix m(2, 2);
  m[0][0] = 1.0;
  m[0][1] = 5.0;
  m[1][0] = -3.0;
  m[1][1] = 2.0;

  double det = m.determinant();

  assert(equal(det, 17.0));

  std::cout << "[PASS 3.9] 2x2 Matrix determinant calculation works."
            << std::endl;
}

void test_matrix_minor_3x3() {
  Matrix m(3, 3);
  m[0][0] = 3.0;
  m[0][1] = 5.0;
  m[0][2] = 0.0;
  m[1][0] = 2.0;
  m[1][1] = -1.0;
  m[1][2] = -7.0;
  m[2][0] = 6.0;
  m[2][1] = -1.5;
  m[2][2] = 5.0;

  Matrix sub = m.submatrix(1, 0);
  assert(equal(sub.determinant(), 25.0));

  assert(equal(m.minor(1, 0), 25.0));

  std::cout << "[PASS 3.10] 3x3 Matrix minor calculation works." << std::endl;
}

void test_matrix_cofactor() {
  Matrix m(3, 3);
  m[0][0] = 3.0;
  m[0][1] = 5.0;
  m[0][2] = 0.0;
  m[1][0] = 2.0;
  m[1][1] = -1.0;
  m[1][2] = -7.0;
  m[2][0] = 6.0;
  m[2][1] = -1.5;
  m[2][2] = 5.0;

  assert(equal(m.minor(0, 0), -15.5));
  assert(equal(m.cofactor(0, 0), -15.5));

  assert(equal(m.minor(1, 0), 25.0));
  assert(equal(m.cofactor(1, 0), -25.0));

  std::cout << "[PASS 3.11] Matrix cofactor calculations works." << std::endl;
}

void test_matrix_determinant_large() {
  Matrix m1(3, 3);
  m1[0][0] = 1.0;
  m1[0][1] = 2.0;
  m1[0][2] = 6.0;
  m1[1][0] = -5.0;
  m1[1][1] = 8.0;
  m1[1][2] = -4.0;
  m1[2][0] = 2.0;
  m1[2][1] = 6.0;
  m1[2][2] = 4.0;

  assert(equal(m1.cofactor(0, 0), 56.0));
  assert(equal(m1.cofactor(0, 1), 12.0));
  assert(equal(m1.cofactor(0, 2), -46.0));

  assert(equal(m1.determinant(), -196.0));

  Matrix m2(4, 4);
  m2[0][0] = -2.0;
  m2[0][1] = -8.0;
  m2[0][2] = 3.0;
  m2[0][3] = 5.0;
  m2[1][0] = -3.0;
  m2[1][1] = 1.0;
  m2[1][2] = 7.0;
  m2[1][3] = 3.0;
  m2[2][0] = 1.0;
  m2[2][1] = 2.0;
  m2[2][2] = -9.0;
  m2[2][3] = 6.0;
  m2[3][0] = -6.0;
  m2[3][1] = 7.0;
  m2[3][2] = 7.0;
  m2[3][3] = -9.0;

  assert(m2.cofactor(0, 0) == 690.0);
  assert(m2.cofactor(0, 1) == 447.0);
  assert(m2.cofactor(0, 2) == 210.0);
  assert(m2.cofactor(0, 3) == 51.0);

  assert(equal(m2.determinant(), -4071.0));

  std::cout << "[PASS 3.12] Large matrix determinant calculations works."
            << std::endl;
}

void test_matrix_inversion() {
  Matrix invertible_m(4, 4);
  invertible_m[0][0] = 6.0;
  invertible_m[0][1] = 4.0;
  invertible_m[0][2] = 4.0;
  invertible_m[0][3] = 4.0;
  invertible_m[1][0] = 5.0;
  invertible_m[1][1] = 5.0;
  invertible_m[1][2] = 7.0;
  invertible_m[1][3] = 6.0;
  invertible_m[2][0] = 4.0;
  invertible_m[2][1] = -9.0;
  invertible_m[2][2] = 3.0;
  invertible_m[2][3] = -7.0;
  invertible_m[3][0] = 9.0;
  invertible_m[3][1] = 1.0;
  invertible_m[3][2] = 7.0;
  invertible_m[3][3] = -6.0;

  assert(equal(invertible_m.determinant(), -2120.0));
  assert(invertible_m.is_invertible() == true);

  Matrix non_invertible_m(4, 4);
  non_invertible_m[0][0] = -4.0;
  non_invertible_m[0][1] = 2.0;
  non_invertible_m[0][2] = -2.0;
  non_invertible_m[0][3] = -3.0;
  non_invertible_m[1][0] = 9.0;
  non_invertible_m[1][1] = 6.0;
  non_invertible_m[1][2] = 2.0;
  non_invertible_m[1][3] = 6.0;
  non_invertible_m[2][0] = 0.0;
  non_invertible_m[2][1] = -5.0;
  non_invertible_m[2][2] = 1.0;
  non_invertible_m[2][3] = -5.0;
  non_invertible_m[3][0] = 0.0;
  non_invertible_m[3][1] = 0.0;
  non_invertible_m[3][2] = 0.0;
  non_invertible_m[3][3] = 0.0;

  assert(equal(non_invertible_m.determinant(), 0.0));
  assert(non_invertible_m.is_invertible() == false);

  Matrix A(4, 4);
  A[0][0] = -5.0;
  A[0][1] = 2.0;
  A[0][2] = 6.0;
  A[0][3] = -8.0;
  A[1][0] = 1.0;
  A[1][1] = -5.0;
  A[1][2] = 1.0;
  A[1][3] = 8.0;
  A[2][0] = 7.0;
  A[2][1] = 7.0;
  A[2][2] = -6.0;
  A[2][3] = -7.0;
  A[3][0] = 1.0;
  A[3][1] = -3.0;
  A[3][2] = 7.0;
  A[3][3] = 4.0;

  Matrix B = A.inverse();

  assert(equal(A.determinant(), 532.0));

  assert(equal(B[0][0], 0.21805));
  assert(equal(B[0][1], 0.45113));
  assert(equal(B[2][3], 0.197368));
  assert(equal(B[3][3], 0.306391));

  Matrix C(4, 4);
  C[0][0] = 3.0;
  C[0][1] = -9.0;
  C[0][2] = 7.0;
  C[0][3] = 3.0;
  C[1][0] = 3.0;
  C[1][1] = -8.0;
  C[1][2] = 2.0;
  C[1][3] = -9.0;
  C[2][0] = -4.0;
  C[2][1] = 4.0;
  C[2][2] = 4.0;
  C[2][3] = 1.0;
  C[3][0] = -6.0;
  C[3][1] = 5.0;
  C[3][2] = -1.0;
  C[3][3] = 1.0;

  Matrix D(4, 4);
  D[0][0] = 8.0;
  D[0][1] = 2.0;
  D[0][2] = 2.0;
  D[0][3] = 2.0;
  D[1][0] = 3.0;
  D[1][1] = -1.0;
  D[1][2] = 7.0;
  D[1][3] = 0.0;
  D[2][0] = 7.0;
  D[2][1] = 0.0;
  D[2][2] = 5.0;
  D[2][3] = 4.0;
  D[3][0] = 6.0;
  D[3][1] = -2.0;
  D[3][2] = 0.5;
  D[3][3] = 1.0;

  Matrix Product = C.matrix_multiply(D);
  Matrix Original_C = Product.matrix_multiply(D.inverse());

  assert(Original_C == C);
}

void test_matrix_translation() {
  Matrix transform = Matrix::translation(5, -3, 2);
  RayPoint p(-3, 4, 5);
  RayPoint result = transform.transform_point(p);

  assert(equal(result.x, 2.0));
  assert(equal(result.y, 1.0));
  assert(equal(result.z, 7.0));
  assert(equal(result.w, 1.0));

  Matrix inv = transform.inverse();
  RayPoint back_result = inv.transform_point(p);
  assert(equal(back_result.x, -8.0));
  assert(equal(back_result.y, 7.0));
  assert(equal(back_result.z, 3.0));
  assert(equal(back_result.w, 1.0));

  RayVector v(-3, 4, 5);
  RayVector vec_result = transform.transform_vector(v);
  assert(equal(vec_result.x, -3.0));
  assert(equal(vec_result.y, 4.0));
  assert(equal(vec_result.z, 5.0));
  assert(equal(vec_result.w, 0.0));

  std::cout << "[PASS 4.1] Matrix translation works." << std::endl;
}

void test_matrix_scaling() {
  Matrix transform = Matrix::scaling(2, 3, 4);

  RayPoint p(-4, 6, 8);
  RayPoint point_result = transform.transform_point(p);
  assert(equal(point_result.x, -8.0));
  assert(equal(point_result.y, 18.0));
  assert(equal(point_result.z, 32.0));
  assert(equal(point_result.w, 1.0));

  RayVector v(-4, 6, 8);
  RayVector vec_result = transform.transform_vector(v);
  assert(equal(vec_result.x, -8.0));
  assert(equal(vec_result.y, 18.0));
  assert(equal(vec_result.z, 32.0));
  assert(equal(vec_result.w, 0.0));

  Matrix inv = transform.inverse();
  RayVector inv_result = inv.transform_vector(v);
  assert(equal(inv_result.x, -2.0));
  assert(equal(inv_result.y, 2.0));
  assert(equal(inv_result.z, 2.0));
  assert(equal(inv_result.w, 0.0));

  Matrix reflect = Matrix::scaling(-1, 1, 1);
  RayPoint p2(2, 3, 4);
  RayPoint reflect_result = reflect.transform_point(p2);
  assert(equal(reflect_result.x, -2.0));
  assert(equal(reflect_result.y, 3.0));
  assert(equal(reflect_result.z, 4.0));
  assert(equal(reflect_result.w, 1.0));

  std::cout << "[PASS 4.2] Matrix scaling and reflection works." << std::endl;
}

void test_matrix_rotation_x() {
  Matrix half_quater = Matrix::rotation_x(PI / 4);
  Matrix full_quarter = Matrix::rotation_x(PI / 2);
  RayPoint p(0, 1, 0);
  RayPoint point_result = half_quater.transform_point(p);
  RayPoint point_result_2 = full_quarter.transform_point(p);

  assert(equal(point_result.x, 0));
  assert(equal(point_result.y, std::sqrt(2) / 2));
  assert(equal(point_result.z, std::sqrt(2) / 2));

  assert(equal(point_result_2.x, 0));
  assert(equal(point_result_2.y, 0));
  assert(equal(point_result_2.z, 1));

  std::cout << "[PASS 4.3] Matrix rotation_x works." << std::endl;
}

void test_matrix_rotation_x_inverse() {
  Matrix half_quarter = Matrix::rotation_x(PI / 4.0);
  Matrix inv = half_quarter.inverse();
  RayPoint p(0, 1, 0);

  RayPoint point_result = inv.transform_point(p);

  assert(equal(point_result.x, 0.0));
  assert(equal(point_result.y, std::sqrt(2.0) / 2.0));
  assert(equal(point_result.z, -std::sqrt(2.0) / 2.0));
  assert(equal(point_result.w, 1.0));

  std::cout << "[PASS 4.4] Matrix rotation_x inverse works." << std::endl;
}

void test_matrix_rotation_y() {
  Matrix half_quarter = Matrix::rotation_y(PI / 4.0);
  Matrix full_quarter = Matrix::rotation_y(PI / 2.0);
  RayPoint p(0, 0, 1);

  RayPoint point_result = half_quarter.transform_point(p);
  RayPoint point_result_2 = full_quarter.transform_point(p);

  assert(equal(point_result.x, std::sqrt(2.0) / 2.0));
  assert(equal(point_result.y, 0.0));
  assert(equal(point_result.z, std::sqrt(2.0) / 2.0));
  assert(equal(point_result.w, 1.0));

  assert(equal(point_result_2.x, 1.0));
  assert(equal(point_result_2.y, 0.0));
  assert(equal(point_result_2.z, 0.0));
  assert(equal(point_result_2.w, 1.0));

  std::cout << "[PASS 4.5] Matrix rotation_y works." << std::endl;
}

void test_matrix_rotation_z() {
  Matrix half_quarter = Matrix::rotation_z(PI / 4.0);
  Matrix full_quarter = Matrix::rotation_z(PI / 2.0);
  RayPoint p(0, 1, 0);

  RayPoint point_result = half_quarter.transform_point(p);
  RayPoint point_result_2 = full_quarter.transform_point(p);

  assert(equal(point_result.x, -std::sqrt(2.0) / 2.0));
  assert(equal(point_result.y, std::sqrt(2.0) / 2.0));
  assert(equal(point_result.z, 0.0));
  assert(equal(point_result.w, 1.0));

  assert(equal(point_result_2.x, -1.0));
  assert(equal(point_result_2.y, 0.0));
  assert(equal(point_result_2.z, 0.0));
  assert(equal(point_result_2.w, 1.0));

  std::cout << "[PASS 4.6] Matrix rotation_z works." << std::endl;
}

void test_matrix_shearing() {
  RayPoint p(2, 3, 4);

  Matrix s_xy = Matrix::shearing(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  RayPoint r_xy = s_xy.transform_point(p);
  assert(equal(r_xy.x, 5.0));
  assert(equal(r_xy.y, 3.0));
  assert(equal(r_xy.z, 4.0));

  Matrix s_xz = Matrix::shearing(0.0, 1.0, 0.0, 0.0, 0.0, 0.0);
  RayPoint r_xz = s_xz.transform_point(p);
  assert(equal(r_xz.x, 6.0));
  assert(equal(r_xz.y, 3.0));
  assert(equal(r_xz.z, 4.0));

  Matrix s_yx = Matrix::shearing(0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
  RayPoint r_yx = s_yx.transform_point(p);
  assert(equal(r_yx.x, 2.0));
  assert(equal(r_yx.y, 5.0));
  assert(equal(r_yx.z, 4.0));

  Matrix s_yz = Matrix::shearing(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
  RayPoint r_yz = s_yz.transform_point(p);
  assert(equal(r_yz.x, 2.0));
  assert(equal(r_yz.y, 7.0));
  assert(equal(r_yz.z, 4.0));

  Matrix s_zx = Matrix::shearing(0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  RayPoint r_zx = s_zx.transform_point(p);
  assert(equal(r_zx.x, 2.0));
  assert(equal(r_zx.y, 3.0));
  assert(equal(r_zx.z, 6.0));

  Matrix s_zy = Matrix::shearing(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  RayPoint r_zy = s_zy.transform_point(p);
  assert(equal(r_zy.x, 2.0));
  assert(equal(r_zy.y, 3.0));
  assert(equal(r_zy.z, 7.0));

  std::cout << "[PASS 4.7] Matrix shearing transformations works." << std::endl;
}

void test_individual_and_chained_transformations() {
  RayPoint p(1.0, 0.0, 1.0);

  Matrix A = Matrix::rotation_x(PI / 2.0);
  Matrix B = Matrix::scaling(5.0, 5.0, 5.0);
  Matrix C = Matrix::translation(10.0, 5.0, 7.0);

  RayPoint p2 = A.transform_point(p);
  assert(equal(p2.x, 1.0));
  assert(equal(p2.y, -1.0));
  assert(equal(p2.z, 0.0));

  RayPoint p3 = B.transform_point(p2);
  assert(equal(p3.x, 5.0));
  assert(equal(p3.y, -5.0));
  assert(equal(p3.z, 0.0));

  RayPoint p4 = C.transform_point(p3);
  assert(equal(p4.x, 15.0));
  assert(equal(p4.y, 0.0));
  assert(equal(p4.z, 7.0));

  Matrix T = C.matrix_multiply(B.matrix_multiply(A));

  RayPoint chained_result = T.transform_point(p);
  assert(equal(chained_result.x, 15.0));
  assert(equal(chained_result.y, 0.0));
  assert(equal(chained_result.z, 7.0));
  assert(equal(chained_result.w, 1.0));

  std::cout << "[PASS 4.8] Individual and chained transformations works."
            << std::endl;
}

void test_create_and_query_ray() {
  RayPoint origin(0, 0, 0);
  RayVector direction(4, 5, 6);
  Ray r(origin, direction);

  assert(r.origin == origin);
  assert(r.direction == direction);

  std::cout << "[PASS 5.1] Ray create and query works." << std::endl;
}

void test_ray_point_from_dist() {
  Ray r(RayPoint(2, 3, 4), RayVector(1, 0, 0));
  assert(r.position(0) == RayPoint(2, 3, 4));
  assert(r.position(1) == RayPoint(3, 3, 4));
  assert(r.position(-1) == RayPoint(1, 3, 4));
  assert(r.position(2.5) == RayPoint(4.5, 3, 4));

  std::cout << "[PASS 5.2] Ray point fron dist works." << std::endl;
}

void test_sphere_ray_intersect_at_two_points() {
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  Sphere s(1);
  std::vector<Intersection> xs = s.intersects(r);

  assert(xs.size() == 2);
  assert(equal(xs[0].t, 4.0));
  assert(equal(xs[1].t, 6.0));

  std::cout << "[PASS 5.3] Ray intersects sphere at two points works."
            << std::endl;
}

void test_sphere_ray_intersect_at_tangent() {
  Ray r(RayPoint(0, 1, -5), RayVector(0, 0, 1));
  Sphere s(1);

  std::vector<Intersection> xs = s.intersects(r);

  assert(xs.size() == 2);
  assert(equal(xs[0].t, 5.0));
  assert(equal(xs[1].t, 5.0));

  std::cout << "[PASS 5.4] Ray intersects sphere at a tangent works."
            << std::endl;
}

void test_sphere_ray_miss() {
  Ray r(RayPoint(0, 2, -5), RayVector(0, 0, 1));
  Sphere s(1);

  std::vector<Intersection> xs = s.intersects(r);

  assert(xs.size() == 0);

  std::cout << "[PASS 5.5] Ray missing a sphere works." << std::endl;
}

void test_sphere_behind_ray() {
  Ray r(RayPoint(0, 0, 5), RayVector(0, 0, 1));
  Sphere s(1);

  std::vector<Intersection> xs = s.intersects(r);

  assert(xs.size() == 2);
  assert(equal(xs[0].t, -6.0));
  assert(equal(xs[1].t, -4.0));

  std::cout
      << "[PASS 5.6] Ray originating inside or in front of a sphere works."
      << std::endl;
}

void test_hit_all_positive_t() {
  Sphere s(1);
  Intersection i1(1.0, &s);
  Intersection i2(2.0, &s);
  std::vector<Intersection> xs = {i1, i2};

  const Intersection *i = hit(xs);

  assert(i != nullptr);
  assert(equal(i->t, 1.0));

  std::cout << "[PASS 5.7] Hit all positive works." << std::endl;
}

void test_hit_some_negative_t() {
  Sphere s(1);
  Intersection i1(-1.0, &s);
  Intersection i2(1.0, &s);
  std::vector<Intersection> xs = {i1, i2};

  const Intersection *i = hit(xs);

  assert(i != nullptr);
  assert(equal(i->t, 1.0));

  std::cout << "[PASS 5.8] Hit some negative works." << std::endl;
}

void test_hit_all_negative_t() {
  Sphere s(1);
  Intersection i1(-2.0, &s);
  Intersection i2(-1.0, &s);
  std::vector<Intersection> xs = {i1, i2};

  const Intersection *i = hit(xs);

  assert(i == nullptr);

  std::cout << "[PASS 5.10] Hit all negative works." << std::endl;
}

void test_hit_lowest_non_negative_t() {
  Sphere s(1);
  Intersection i1(5.0, &s);
  Intersection i2(7.0, &s);
  Intersection i3(0.3, &s);
  Intersection i4(2.0, &s);
  std::vector<Intersection> xs = {i1, i2, i3, i4};

  const Intersection *i = hit(xs);

  assert(i != nullptr);
  assert(equal(i->t, 0.3));

  std::cout << "[PASS 5.11] Hit lowest non negative works." << std::endl;
}

void test_translating_a_ray() {
  Ray r(RayPoint(1, 2, 3), RayVector(0, 1, 0));
  Matrix m = Matrix::translation(3, 4, 5);

  Ray r2 = r.transform(m);

  assert(equal(r2.origin.x, 4.0));
  assert(equal(r2.origin.y, 6.0));
  assert(equal(r2.origin.z, 8.0));
  assert(equal(r2.direction.x, 0.0));
  assert(equal(r2.direction.y, 1.0));
  assert(equal(r2.direction.z, 0.0));

  std::cout << "[PASS 5.12] Translating a ray works." << std::endl;
}

void test_scaling_a_ray() {
  Ray r(RayPoint(1, 2, 3), RayVector(0, 1, 0));
  Matrix m = Matrix::scaling(2, 3, 4);

  Ray r2 = r.transform(m);

  assert(equal(r2.origin.x, 2.0));
  assert(equal(r2.origin.y, 6.0));
  assert(equal(r2.origin.z, 12.0));
  assert(equal(r2.direction.x, 0.0));
  assert(equal(r2.direction.y, 3.0));
  assert(equal(r2.direction.z, 0.0));

  std::cout << "[PASS 5.13] Scaling a ray works." << std::endl;
}

void test_sphere_default_transformation() {
  Sphere s(1);
  assert(s.transform == Matrix::identity(4));

  std::cout << "[PASS 5.14] Sphere default transformation works." << std::endl;
}

void test_sphere_transformation() {
  Sphere s(1);
  Matrix t = Matrix::translation(2, 3, 4);
  s.set_transform(t);
  assert(s.transform == t);

  std::cout << "[PASS 5.15] Sphere translation transformation works."
            << std::endl;
}

void test_intersect_scaled_sphere_with_ray() {
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  Sphere s(1);
  s.set_transform(Matrix::scaling(2, 2, 2));
  std::vector<Intersection> xs = s.intersects(r);

  assert(xs.size() == 2);
  assert(xs[0].t == 3.0);
  assert(xs[1].t == 7.0);

  std::cout << "[PASS 5.16] Sphere scaled intersection works." << std::endl;
}

void test_intersect_translated_sphere_with_ray() {
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  Sphere s(1);
  s.set_transform(Matrix::translation(5, 0, 0));
  std::vector<Intersection> xs = s.intersects(r);

  assert(xs.size() == 0);

  std::cout << "[PASS 5.17] Intersecting a translated sphere with a ray works."
            << std::endl;
}

void test_normal_on_sphere_at_point_on_x_axis() {
  Sphere s(1);
  RayVector n = s.normal_at(RayPoint(1, 0, 0));

  assert(equal(n.x, 1.0));
  assert(equal(n.y, 0.0));
  assert(equal(n.z, 0.0));
  assert(equal(n.w, 0.0));

  std::cout << "[PASS 6.1] Normal on a sphere at a point on the X axis works."
            << std::endl;
}

void test_normal_on_sphere_at_point_on_y_axis() {
  Sphere s(1);
  RayVector n = s.normal_at(RayPoint(0, 1, 0));

  assert(equal(n.x, 0.0));
  assert(equal(n.y, 1.0));
  assert(equal(n.z, 0.0));
  assert(equal(n.w, 0.0));

  std::cout << "[PASS 6.2] Normal on a sphere at a point on the Y axis works."
            << std::endl;
}

void test_normal_on_sphere_at_point_on_z_axis() {
  Sphere s(1);
  RayVector n = s.normal_at(RayPoint(0, 0, 1));

  assert(equal(n.x, 0.0));
  assert(equal(n.y, 0.0));
  assert(equal(n.z, 1.0));
  assert(equal(n.w, 0.0));

  std::cout << "[PASS 6.3] Normal on a sphere at a point on the Z axis works."
            << std::endl;
}

void test_normal_on_sphere_at_non_axial_point() {
  Sphere s(1);
  double val = std::sqrt(3) / 3.0;
  RayVector n = s.normal_at(RayPoint(val, val, val));

  assert(equal(n.x, val));
  assert(equal(n.y, val));
  assert(equal(n.z, val));
  assert(equal(n.w, 0.0));

  std::cout << "[PASS 6.4] Normal on a sphere at a non-axial point works."
            << std::endl;
}

void test_normal_is_a_normalized_vector() {
  Sphere s(1);
  double val = std::sqrt(3) / 3.0;
  RayVector n = s.normal_at(RayPoint(val, val, val));

  double magnitude = std::sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
  assert(equal(magnitude, 1.0));

  std::cout << "[PASS 6.5] The normal safely normalized works." << std::endl;
}

void test_computing_normal_on_translated_sphere() {
  Sphere s(1);
  s.set_transform(Matrix::translation(0, 1, 0));

  RayVector n = s.normal_at(RayPoint(0, 1.70711, -0.70711));

  assert(equal(n.x, 0.0));
  assert(equal(n.y, 0.70711));
  assert(equal(n.z, -0.70711));
  assert(equal(n.w, 0.0));

  std::cout << "[PASS 6.6] Computing the normal on a translated sphere works."
            << std::endl;
}

void test_computing_normal_on_transformed_sphere() {
  Sphere s(1);
  Matrix m = Matrix::chain_transforms(
      {Matrix::scaling(1, 0.5, 1), Matrix::rotation_z(0.785398)});
  s.set_transform(m);

  double val = std::sqrt(2) / 2.0;
  RayVector n = s.normal_at(RayPoint(0, val, -val));

  assert(equal(n.x, 0.0));
  assert(equal(n.y, 0.97014));
  assert(equal(n.z, -0.24254));
  assert(equal(n.w, 0.0));

  std::cout
      << "[PASS 6.7] Computing the normal on a scaled and rotated sphere works."
      << std::endl;
}

void test_reflecting_a_vector_approaching_at_45_degrees() {
  RayVector v(1, -1, 0);
  RayVector n(0, 1, 0);
  RayVector r = v.reflect(n);

  assert(equal(r.x, 1.0));
  assert(equal(r.y, 1.0));
  assert(equal(r.z, 0.0));
  assert(equal(r.w, 0.0)); // Strict invariant check

  std::cout << "[PASS 6.8] Reflecting a vector approaching at 45 degrees works."
            << std::endl;
}

void test_reflecting_a_vector_off_a_slanted_surface() {
  double val = std::sqrt(2) / 2.0;
  RayVector v(0, -1, 0);
  RayVector n(val, val, 0);
  RayVector r = v.reflect(n);

  assert(equal(r.x, 1.0));
  assert(equal(r.y, 0.0));
  assert(equal(r.z, 0.0));
  assert(equal(r.w, 0.0));

  std::cout << "[PASS 6.9] Reflecting a vector off a slanted surface works."
            << std::endl;
}

void test_point_light_source() {
  LightSource point_light;
  assert(point_light.position == RayPoint(0, 0, 0));
  assert(point_light.intensity == Color(0, 0, 0));

  std::cout << "[PASS 6.10] Point light source works." << std::endl;
}

void test_default_material() {
  Material m;

  assert(equal(m.color.r, 1.0) && equal(m.color.g, 1.0) &&
         equal(m.color.b, 1.0));
  assert(equal(m.ambient, 0.1));
  assert(equal(m.diffuse, 0.9));
  assert(equal(m.specular, 0.9));
  assert(equal(m.shininess, 200.0));

  std::cout << "[PASS 6.11] Default material instantiation works." << std::endl;
}

void test_sphere_has_default_material() {
  Sphere s;
  Material m = s.material;

  assert(equal(m.color.r, 1.0) && equal(m.color.g, 1.0) &&
         equal(m.color.b, 1.0));
  assert(equal(m.ambient, 0.1));
  assert(equal(m.diffuse, 0.9));
  assert(equal(m.specular, 0.9));
  assert(equal(m.shininess, 200.0));

  std::cout << "[PASS 6.12] A sphere safely defaults to a standard material."
            << std::endl;
}

void test_sphere_may_be_assigned_a_material() {
  Sphere s;
  Material m;
  m.ambient = 1.0;

  s.material = m;

  assert(equal(s.material.ambient, 1.0));
  assert(equal(s.material.diffuse, 0.9));

  std::cout << "[PASS 6.13] A sphere can be assigned a modified material "
               "successfully."
            << std::endl;
}

void test_lighting_with_eye_between_light_and_surface() {
  TestShape *s = new TestShape();
  Material m;
  RayPoint position(0, 0, 0);
  RayVector eyev(0, 0, -1);
  RayVector normalv(0, 0, -1);
  LightSource light(Color(1, 1, 1), RayPoint(0, 0, -10));

  Color result = light.lighting(m, s, position, eyev, normalv);

  assert(equal(result.r, 1.9) && equal(result.g, 1.9) && equal(result.b, 1.9));
  std::cout << "[PASS 6.14] Lighting with eye between light and surface works."
            << std::endl;
  delete s;
}

void test_lighting_with_eye_between_light_and_surface_eye_offset_45_degrees() {
  TestShape *s = new TestShape();
  Material m;
  RayPoint position(0, 0, 0);
  double val = std::sqrt(2) / 2.0;
  RayVector eyv(0, val, -val);
  RayVector normalv(0, 0, -1);
  LightSource light(Color(1, 1, 1), RayPoint(0, 0, -10));

  Color result = light.lighting(m, s, position, eyv, normalv);

  assert(equal(result.r, 1.0) && equal(result.g, 1.0) && equal(result.b, 1.0));
  std::cout << "[PASS 6.15] Lighting with eye offset 45 degrees works."
            << std::endl;
  delete s;
}

void test_lighting_with_eye_opposite_surface_light_offset_45_degrees() {
  TestShape *s = new TestShape();
  Material m;
  RayPoint position(0, 0, 0);
  RayVector eyev(0, 0, -1);
  RayVector normalv(0, 0, -1);
  LightSource light(Color(1, 1, 1), RayPoint(0, 10, -10));

  Color result = light.lighting(m, s, position, eyev, normalv);

  assert(equal(result.r, 0.7364) && equal(result.g, 0.7364) &&
         equal(result.b, 0.7364));
  std::cout << "[PASS 6.16] Lighting with light source offset 45 degrees works."
            << std::endl;
  delete s;
}

void test_lighting_with_eye_in_the_path_of_the_reflection_vector() {
  TestShape *s = new TestShape();
  Material m;
  RayPoint position(0, 0, 0);
  double val = std::sqrt(2) / 2.0;
  RayVector eyev(0, -val, -val);
  RayVector normalv(0, 0, -1);
  LightSource light(Color(1, 1, 1), RayPoint(0, 10, -10));

  Color result = light.lighting(m, s, position, eyev, normalv);

  assert(equal(result.r, 1.6364) && equal(result.g, 1.6364) &&
         equal(result.b, 1.6364));
  std::cout << "[PASS 6.17] Lighting with eye in the direct path of the "
               "reflection vector works."
            << std::endl;
  delete s;
}

void test_lighting_with_the_light_behind_the_surface() {
  Material m;
  TestShape *s = new TestShape();
  RayPoint position(0, 0, 0);
  RayVector eyev(0, 0, -1);
  RayVector normalv(0, 0, -1);
  LightSource light(Color(1, 1, 1),
                    RayPoint(0, 0, 10)); // Light behind the wall

  Color result = light.lighting(m, s, position, eyev, normalv);

  assert(equal(result.r, 0.1) && equal(result.g, 0.1) && equal(result.b, 0.1));
  std::cout << "[PASS 6.18] Lighting with the light source completely behind "
               "the surface works."
            << std::endl;
  delete s;
}

void test_world_empty_on_creation() {
  World w;
  assert((w.objects.size() == 0));
  assert((w.light_source == nullptr));

  std::cout << "[PASS 7.1] World empty on creation works." << std::endl;
}

void test_default_world() {
  DefaultWorld w;
  assert(*w.light_source ==
         LightSource(Color(1, 1, 1), RayPoint(-10, 10, -10)));
  assert(w.objects.size() == 2);
  assert(w.objects[0]->material.color == Color(0.8, 1.0, 0.6));
  assert(equal(w.objects[0]->material.diffuse, 0.7));
  assert(equal(w.objects[0]->material.specular, 0.2));
  assert(w.objects[1]->transform == Matrix::scaling(0.5, 0.5, 0.5));

  std::cout << "[PASS 7.2] Default world configuration works." << std::endl;
}

void test_intersect_world_with_ray() {
  DefaultWorld w;
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  std::vector<Intersection> xs = w.intersect_world(r);
  assert(xs.size() == 4);
  assert(equal(xs[0].t, 4.0));
  assert(equal(xs[1].t, 4.5));
  assert(equal(xs[2].t, 5.5));
  assert(equal(xs[3].t, 6.0));

  std::cout << "[PASS 7.3] Default world intersect with ray works."
            << std::endl;
}

void test_precomputing_state_of_intersection() {
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  Sphere s;
  Intersection i(4.0, &s);

  Computations comps(i, r);
  assert(equal(comps.t, i.t));
  assert(comps.object == i.object);
  assert(comps.point == RayPoint(0, 0, -1));
  assert(comps.eyev == RayVector(0, 0, -1));
  assert(comps.normalv == RayVector(0, 0, -1));
  assert(comps.inside == false);
  std::cout << "[PASS 7.4] Precomputing intersection state works (outside hit)."
            << std::endl;
}

void test_precomputing_state_of_intersection_inside() {
  Ray r(RayPoint(0, 0, 0), RayVector(0, 0, 1));
  Sphere s;
  Intersection i(1.0, &s);

  Computations comps(i, r);
  assert(comps.point == RayPoint(0, 0, 1));
  assert(comps.eyev == RayVector(0, 0, -1));
  assert(comps.inside == true);
  assert(comps.normalv == RayVector(0, 0, -1));
  std::cout << "[PASS 7.5] Precomputing intersection state works (inside hit)."
            << std::endl;
}

void test_shading_an_intersection() {
  DefaultWorld w;
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  Intersection i(4.0, w.objects[0]);

  Computations comps(i, r);
  Color c = w.shade_hit(comps);
  assert(equal(c.r, 0.38066) && equal(c.g, 0.47583) && equal(c.b, 0.2855));
  std::cout << "[PASS 7.6] Shading an intersection works." << std::endl;
}

void test_shading_an_intersection_from_the_inside() {
  DefaultWorld w;
  delete w.light_source;
  w.light_source = new LightSource(Color(1, 1, 1), RayPoint(0, 0.25, 0));

  Ray r(RayPoint(0, 0, 0), RayVector(0, 0, 1));
  Intersection i(0.5, w.objects[1]);

  Computations comps(i, r);
  Color c = w.shade_hit(comps);
  assert(equal(c.r, 0.90498) && equal(c.g, 0.90498) && equal(c.b, 0.90498));
  std::cout << "[PASS 7.7] Shading an intersection from the inside works."
            << std::endl;
}

void test_color_at_ray_misses() {
  DefaultWorld w;
  Ray r(RayPoint(0, 0, -5), RayVector(0, 1, 0));
  Color c = w.color_at(r);
  assert(equal(c.r, 0.0) && equal(c.g, 0.0) && equal(c.b, 0.0));
  std::cout << "[PASS 7.8] color_at when a ray misses returns black."
            << std::endl;
}

void test_color_at_ray_hits() {
  DefaultWorld w;
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  Color c = w.color_at(r);
  assert(equal(c.r, 0.38066) && equal(c.g, 0.47583) && equal(c.b, 0.2855));
  std::cout << "[PASS 7.9] color_at when a ray hits returns correct color."
            << std::endl;
}

void test_color_with_intersection_behind_the_ray() {
  DefaultWorld w;

  const_cast<Shape *>(w.objects[0])->material.ambient = 1.0;
  const_cast<Shape *>(w.objects[1])->material.ambient = 1.0;

  Ray r(RayPoint(0, 0, 0.75), RayVector(0, 0, -1));
  Color c = w.color_at(r);

  assert(equal(c.r, 1.0) && equal(c.g, 1.0) && equal(c.b, 1.0));
  std::cout << "[PASS 7.10] color_at with an intersection behind the ray works."
            << std::endl;
}

void test_view_transformation_default() {
  RayPoint from(0, 0, 0);
  RayPoint to(0, 0, -1);
  RayVector up(0, 1, 0);

  Matrix t = Matrix::view_transform(from, to, up);
  assert(t == Matrix::identity(4));
  std::cout << "[PASS 7.11] Default view transform works." << std::endl;
}

void test_view_transformation_positive_z() {
  RayPoint from(0, 0, 0);
  RayPoint to(0, 0, 1);
  RayVector up(0, 1, 0);

  Matrix t = Matrix::view_transform(from, to, up);
  assert(t == Matrix::scaling(-1, 1, -1));
  std::cout << "[PASS 7.12] View transform looking at positive Z works."
            << std::endl;
}

void test_view_transformation_translation() {
  RayPoint from(0, 0, 8);
  RayPoint to(0, 0, 0);
  RayVector up(0, 1, 0);

  Matrix t = Matrix::view_transform(from, to, up);
  assert(t == Matrix::translation(0, 0, -8));
  std::cout << "[PASS 7.13] View transform translation works." << std::endl;
}

void test_pixel_size_horizontal() {
  Camera c(200, 125, M_PI / 2.0);
  assert(equal(c.pixel_size, 0.01));
  std::cout << "[PASS 7.14] Horizontal camera pixel size calculation works."
            << std::endl;
}

void test_pixel_size_vertical() {
  Camera c(125, 200, M_PI / 2.0);
  assert(equal(c.pixel_size, 0.01));
  std::cout << "[PASS 7.15] Vertical camera pixel size calculation works."
            << std::endl;
}

void test_ray_through_center_of_canvas() {
  Camera c(201, 101, M_PI / 2.0);
  Ray r = c.ray_for_pixel(100, 50);
  assert(r.origin == RayPoint(0, 0, 0));
  assert(r.direction == RayVector(0, 0, -1));
  std::cout << "[PASS 7.16] Ray through canvas center works." << std::endl;
}

void test_ray_through_corner_of_canvas() {
  Camera c(201, 101, M_PI / 2.0);
  Ray r = c.ray_for_pixel(0, 0);
  assert(r.origin == RayPoint(0, 0, 0));
  assert(r.direction == RayVector(0.66519, 0.33259, -0.66851));
  std::cout << "[PASS 7.17] Ray through canvas corner works." << std::endl;
}

void test_ray_with_transformed_camera() {
  Camera c(201, 101, M_PI / 2.0);
  c.transform = Matrix::rotation_y(M_PI / 4.0)
                    .matrix_multiply(Matrix::translation(0, -2, 5));
  Ray r = c.ray_for_pixel(100, 50);
  assert(r.origin == RayPoint(0, 2, -5));
  assert(r.direction == RayVector(sqrt(2) / 2.0, 0, -sqrt(2) / 2.0));
  std::cout << "[PASS 7.18] Ray with transformed camera works." << std::endl;
}

void test_rendering_a_world_with_a_camera() {
  DefaultWorld w;
  Camera c(11, 11, M_PI / 2.0);

  RayPoint from(0, 0, -5);
  RayPoint to(0, 0, 0);
  RayVector up(0, 1, 0);
  c.transform = Matrix::view_transform(from, to, up);

  Canvas image = c.render(w);
  Color center_pixel = image.pixel_at(5, 5);

  assert(equal(center_pixel.r, 0.38066));
  assert(equal(center_pixel.g, 0.47583));
  assert(equal(center_pixel.b, 0.2855));
  std::cout << "[PASS 7.19] Full world rendering pipeline works." << std::endl;
}

void test_lighting_with_surface_in_shadow() {
  Sphere *s = new Sphere();
  RayVector eyev(0, 0, -1);
  RayVector normalv(0, 0, -1);
  LightSource light(Color(1, 1, 1), RayPoint(0, 0, -10));
  bool in_shadow = true;
  Material m;
  RayPoint position(0, 0, 0);
  Color result = light.lighting(m, s, position, eyev, normalv, in_shadow);

  assert(result == Color(0.1, 0.1, 0.1));

  std::cout << "[PASS 8.1] Lighting with surface in shadow basic works."
            << std::endl;
  delete s;
}

void test_no_shadow_collinear_point_and_light() {
  DefaultWorld w;
  RayPoint p(0, 10, 0);
  assert(w.is_shadowed(p) == false);

  std::cout << "[PASS 8.2] No shadow in collinear works." << std::endl;
}

void test_is_shadowed_with_obstruction() {
  DefaultWorld w;
  RayPoint p(10, -10, 10);
  assert(w.is_shadowed(p) == true);
  std::cout << "[PASS 8.3] Shadow detected when object blocks light."
            << std::endl;
}

void test_is_shadowed_object_behind_light() {
  DefaultWorld w;
  RayPoint p(-20, 20, -20);
  assert(w.is_shadowed(p) == false);

  std::cout << "[PASS 8.4] No shadow when object is behind the light source."
            << std::endl;
}

void test_is_shadowed_object_behind_point() {
  DefaultWorld w;
  RayPoint p(-2, 2, -2);
  assert(w.is_shadowed(p) == false);

  std::cout << "[PASS 8.5] No shadow when object is behind point." << std::endl;
}

void test_hit_offset_point() {
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  Sphere s;
  s.set_transform(Matrix::translation(0, 0, 1));
  Intersection i(5, &s);
  Computations comps(i, r);

  assert(comps.over_point.z < -EPSILON / 2.0);
  assert(comps.point.z > comps.over_point.z);

  std::cout << "[PASS 8.6] Hit offsets the point works." << std::endl;
}

void test_default_shape_transformation() {
  TestShape s;

  assert(s.transform == Matrix::identity(4));
  std::cout << "[PASS 9.1] Default shape transformation is identity works."
            << std::endl;
}

void test_assigning_a_transformation_on_base_shape() {
  TestShape s;
  s.set_transform(Matrix::translation(2, 3, 4));

  assert(s.transform == Matrix::translation(2, 3, 4));
  std::cout << "[PASS 9.2] Shape transformation assignment works." << std::endl;
}

void test_default_shape_has_default_material() {
  TestShape s;

  assert(s.material.ambient == 0.1);
  assert(s.material.diffuse == 0.9);
  assert(s.material.specular == 0.9);
  assert(s.material.shininess == 200.0);
  assert(s.material.color == Color(1, 1, 1));

  std::cout << "[PASS 9.3] Default shape has a default material." << std::endl;
}

void test_assigning_a_material_to_a_shape() {
  TestShape s;
  Material m;
  m.ambient = 1.0;

  s.material = m;

  assert(s.material.ambient == 1.0);
  std::cout << "[PASS 9.4] Assigning a material to a shape works." << std::endl;
}

void test_shape_intersection_encapsulates_material() {
  TestShape s;
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));

  Intersection i(3.5, &s);

  assert(i.object->material.ambient == 0.1);
  assert(i.object == &s);

  std::cout << "[PASS 9.5] Intersection points to the correct shape material "
               "context works."
            << std::endl;
}

void test_intersecting_a_scaled_shape_with_a_ray() {
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  TestShape s;

  s.set_transform(Matrix::scaling(2.0, 2.0, 2.0));

  s.intersects(r);

  assert(s.saved_ray.origin == RayPoint(0, 0, -2.5));
  assert(s.saved_ray.direction == RayVector(0, 0, 0.5));

  std::cout << "[PASS 9.6] Intersecting a scaled shape transforms the ray "
               "works."
            << std::endl;
}

void test_intersecting_a_translated_shape_with_a_ray() {
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  TestShape s;

  s.set_transform(Matrix::translation(0, 0, 5));

  s.intersects(r);

  assert(s.saved_ray.origin == RayPoint(0, 0, -10));
  assert(s.saved_ray.direction == RayVector(0, 0, 1));

  std::cout << "[PASS 9.7] Intersecting a translated shape transforms the ray "
               "works."
            << std::endl;
}

void test_computing_the_normal_on_a_translated_shape() {
  TestShape s;
  s.set_transform(Matrix::translation(0, 1, 0));

  RayVector n = s.normal_at(RayPoint(0, 1.70711, -0.70711));

  assert(equal(n.x, 0.0) && equal(n.y, 0.70711) && equal(n.z, -0.70711));
  std::cout << "[PASS 9.8] Computing the normal on a translated shape works."
            << std::endl;
}

void test_computing_the_normal_on_a_transformed_shape() {
  TestShape s;

  Matrix m = Matrix::chain_transforms(
      {Matrix::scaling(1, 0.5, 1), Matrix::rotation_z(PI / 5.0)});
  s.set_transform(m);

  double sqrt_2_over_2 = std::sqrt(2.0) / 2.0;
  RayVector n = s.normal_at(RayPoint(0, sqrt_2_over_2, -sqrt_2_over_2));

  assert(equal(n.x, 0.0) && equal(n.y, 0.97014) && equal(n.z, -0.24254));
  std::cout << "[PASS 9.9] Computing the normal on a transformed shape works."
            << std::endl;
}

void test_the_normal_of_a_plane_is_constant_everywhere() {
  Plane p;

  RayVector n1 = p.local_normal_at(RayPoint(0, 0, 0));
  RayVector n2 = p.local_normal_at(RayPoint(10, 0, -5));
  RayVector n3 = p.local_normal_at(RayPoint(-5, 0, 150));

  assert(n1 == RayVector(0, 1, 0));
  assert(n2 == RayVector(0, 1, 0));
  assert(n3 == RayVector(0, 1, 0));

  std::cout << "[PASS 9.10] The normal of a plane is constant everywhere works."
            << std::endl;
}

void test_intersect_with_a_ray_parallel_to_the_plane() {
  Plane p;
  Ray r(RayPoint(0, 1, 0), RayVector(0, 0, 1));

  std::vector<Intersection> xs = p.local_intersects(r);

  assert(xs.empty());
  std::cout << "[PASS 9.11] Intersecting a ray parallel to the plane returns "
               "no hits works."
            << std::endl;
}

void test_intersect_with_a_coplanar_ray() {
  Plane p;
  Ray r(RayPoint(0, 0, 0), RayVector(0, 0, 1));

  std::vector<Intersection> xs = p.local_intersects(r);

  assert(xs.empty());
  std::cout << "[PASS 9.12] Intersecting a coplanar ray returns no hits works."
            << std::endl;
}

void test_a_ray_intersecting_a_plane_from_above() {
  Plane p;
  Ray r(RayPoint(0, 1, 0), RayVector(0, -1, 0));

  std::vector<Intersection> xs = p.local_intersects(r);

  assert(xs.size() == 1);
  assert(equal(xs[0].t, 1.0));
  assert(xs[0].object == &p);

  std::cout << "[PASS 9.13] A ray intersecting a plane from above hits "
               "correctly works."
            << std::endl;
}

void test_a_ray_intersecting_a_plane_from_below() {
  Plane p;
  Ray r(RayPoint(0, -1, 0), RayVector(0, 1, 0));

  std::vector<Intersection> xs = p.local_intersects(r);

  assert(xs.size() == 1);
  assert(equal(xs[0].t, 1.0));
  assert(xs[0].object == &p);

  std::cout << "[PASS 9.14] A ray intersecting a plane from below hits "
               "correctly works."
            << std::endl;
}

void test_create_stripe_pattern() {
  StripePattern p(COLOR_WHITE, COLOR_BLACK);
  assert(p.a == COLOR_WHITE);
  assert(p.b == COLOR_BLACK);

  std::cout << "[PASS 10.1] Stripe pattern creation works." << std::endl;
}

void test_stripe_pattern_is_constant_in_y() {
  StripePattern p(COLOR_WHITE, COLOR_BLACK);
  assert(p.pattern_at(RayPoint(0, 0, 0)) == COLOR_WHITE);
  assert(p.pattern_at(RayPoint(0, 1, 0)) == COLOR_WHITE);
  assert(p.pattern_at(RayPoint(0, 2, 0)) == COLOR_WHITE);

  std::cout << "[PASS 10.2] Stripe pattern constant in y works." << std::endl;
}

void test_stripe_pattern_is_constant_in_z() {
  StripePattern p(COLOR_WHITE, COLOR_BLACK);
  assert(p.pattern_at(RayPoint(0, 0, 0)) == COLOR_WHITE);
  assert(p.pattern_at(RayPoint(0, 0, 1)) == COLOR_WHITE);
  assert(p.pattern_at(RayPoint(0, 0, 2)) == COLOR_WHITE);

  std::cout << "[PASS 10.3] Stripe pattern constant in z works." << std::endl;
}

void test_stripe_pattern_alternates_in_x() {
  StripePattern p(COLOR_WHITE, COLOR_BLACK);

  assert(p.pattern_at(RayPoint(0, 0, 0)) == COLOR_WHITE);
  assert(p.pattern_at(RayPoint(0.9, 0, 0)) == COLOR_WHITE);
  assert(p.pattern_at(RayPoint(1, 0, 0)) == COLOR_BLACK);
  assert(p.pattern_at(RayPoint(-0.1, 0, 0)) == COLOR_BLACK);
  assert(p.pattern_at(RayPoint(-1, 0, 0)) == COLOR_BLACK);
  assert(p.pattern_at(RayPoint(-1.1, 0, 0)) == COLOR_WHITE);

  std::cout << "[PASS 10.4] Stripe pattern alternates in x works." << std::endl;
}

void test_lightning_with_pattern_applied() {
  Sphere *s = new Sphere();
  Material m;
  StripePattern *pattern = new StripePattern(COLOR_WHITE, COLOR_BLACK);
  m.pattern = pattern;
  m.ambient = 1.0;
  m.diffuse = 0.0;
  m.specular = 0.0;
  RayVector eyev(0, 0, -1);
  RayVector normalv(0, 0, -1);
  LightSource light(Color(1, 1, 1), RayPoint(0, 0, -10));
  Color c1 = light.lighting(m, s, RayPoint(0.9, 0, 0), eyev, normalv, false);
  Color c2 = light.lighting(m, s, RayPoint(1.1, 0, 0), eyev, normalv, false);

  assert(c1 == COLOR_WHITE);
  assert(c2 == COLOR_BLACK);

  std::cout << "[PASS 10.5] Lighting with pattern works." << std::endl;
  delete s;
}

void test_stripe_pattern_with_object_transformation() {
  Sphere *object = new Sphere();
  object->set_transform(Matrix::scaling(2, 2, 2));
  StripePattern pattern(COLOR_WHITE, COLOR_BLACK);

  // When an object is scaled up by 2, a world point at X=1.5 is local X=0.75
  Color c = pattern.pattern_at_object(object, RayPoint(1.5, 0, 0));
  assert(c == COLOR_WHITE);

  std::cout << "[PASS 10.6] Stripes with object transformation works."
            << std::endl;
  delete object;
}

void test_stripe_pattern_with_pattern_transformation() {
  Sphere *object = new Sphere();
  StripePattern pattern(COLOR_WHITE, COLOR_BLACK);
  pattern.set_transform(Matrix::scaling(2, 2, 2));

  // When pattern is scaled up by 2, world point X=1.5 maps to pattern space
  // X=0.75
  Color c = pattern.pattern_at_object(object, RayPoint(1.5, 0, 0));
  assert(c == COLOR_WHITE);

  std::cout << "[PASS 10.7] Stripes with pattern transformation works."
            << std::endl;
  delete object;
}

void test_stripe_pattern_with_both_transformations() {
  Sphere *object = new Sphere();
  object->set_transform(Matrix::scaling(2, 2, 2));
  StripePattern pattern(COLOR_WHITE, COLOR_BLACK);
  pattern.set_transform(Matrix::translation(0.5, 0, 0));

  // Combined matrix: pattern_inverse * object_inverse * world_point
  Color c = pattern.pattern_at_object(object, RayPoint(2.5, 0, 0));
  assert(c == COLOR_WHITE);

  std::cout << "[PASS 10.8] Stripes with both object and pattern "
               "transformations works."
            << std::endl;

  delete object;
}

void test_default_pattern_transformation() {
  TestPattern pattern;

  assert(pattern.transform == Matrix::identity(4));

  std::cout << "[PASS 10.9] Default pattern transformation is identity."
            << std::endl;
}

void test_assigning_a_transformation() {
  TestPattern pattern;
  pattern.set_transform(Matrix::translation(1, 2, 3));

  assert(pattern.transform == Matrix::translation(1, 2, 3));

  std::cout << "[PASS 10.10] Assigning a transformation to a pattern works."
            << std::endl;
}

void test_pattern_with_an_object_transformation() {
  Sphere *object = new Sphere();
  object->set_transform(Matrix::scaling(2, 2, 2));
  TestPattern pattern;

  Color c = pattern.pattern_at_object(object, RayPoint(2, 3, 4));
  assert(c == Color(1, 1.5, 2));

  std::cout << "[PASS 10.11] Base pattern with object transformation works."
            << std::endl;
}

void test_pattern_with_a_pattern_transformation() {
  Sphere *object = new Sphere();
  TestPattern pattern;
  pattern.set_transform(Matrix::scaling(2, 2, 2));

  Color c = pattern.pattern_at_object(object, RayPoint(2, 3, 4));
  assert(c == Color(1, 1.5, 2));

  std::cout << "[PASS 10.12] Base pattern with pattern transformation works."
            << std::endl;
}

void test_pattern_with_both_transformations() {
  Sphere *object = new Sphere();
  object->set_transform(Matrix::scaling(2, 2, 2));
  TestPattern pattern;
  pattern.set_transform(Matrix::translation(0.5, 1, 1.5));

  Color c = pattern.pattern_at_object(object, RayPoint(2.5, 3, 3.5));
  assert(c == Color(0.75, 0.5, 0.25));

  std::cout << "[PASS 10.13] Base pattern with both object and pattern "
               "transformations works."
            << std::endl;
}

void test_gradient_pattern_interpolates() {
  GradientPattern pattern(COLOR_WHITE, COLOR_BLACK);

  assert(pattern.pattern_at(RayPoint(0, 0, 0)) == COLOR_WHITE);
  assert(pattern.pattern_at(RayPoint(0.25, 0, 0)) == Color(0.75, 0.75, 0.75));
  assert(pattern.pattern_at(RayPoint(0.5, 0, 0)) == Color(0.5, 0.5, 0.5));
  assert(pattern.pattern_at(RayPoint(0.75, 0, 0)) == Color(0.25, 0.25, 0.25));

  std::cout << "[PASS 10.14] Gradient pattern interpolation works."
            << std::endl;
}

void test_ring_pattern_alternates_in_both_x_and_z() {
  RingPattern pattern(COLOR_WHITE, COLOR_BLACK);

  assert(pattern.pattern_at(RayPoint(0, 0, 0)) == COLOR_WHITE);
  assert(pattern.pattern_at(RayPoint(1, 0, 0)) == COLOR_BLACK);
  assert(pattern.pattern_at(RayPoint(0, 0, 1)) == COLOR_BLACK);
  assert(pattern.pattern_at(RayPoint(0.708, 0, 0.708)) == COLOR_BLACK);

  std::cout << "[PASS 10.15] Ring pattern concentric checks works."
            << std::endl;
}

void test_checkers_pattern_alternates_in_x() {
  CheckersPattern pattern(COLOR_WHITE, COLOR_BLACK);

  assert(pattern.pattern_at(RayPoint(0, 0, 0)) == COLOR_WHITE);
  assert(pattern.pattern_at(RayPoint(0.99, 0, 0)) == COLOR_WHITE);
  assert(pattern.pattern_at(RayPoint(1.01, 0, 0)) == COLOR_BLACK);

  std::cout << "[PASS 10.16] Checkers pattern alternates in X works."
            << std::endl;
}

void test_checkers_pattern_alternates_in_y() {
  CheckersPattern pattern(COLOR_WHITE, COLOR_BLACK);

  assert(pattern.pattern_at(RayPoint(0, 0, 0)) == COLOR_WHITE);
  assert(pattern.pattern_at(RayPoint(0, 0.99, 0)) == COLOR_WHITE);
  assert(pattern.pattern_at(RayPoint(0, 1.01, 0)) == COLOR_BLACK);

  std::cout << "[PASS 10.17] Checkers pattern alternates in Y works."
            << std::endl;
}

void test_checkers_pattern_alternates_in_z() {
  CheckersPattern pattern(COLOR_WHITE, COLOR_BLACK);

  assert(pattern.pattern_at(RayPoint(0, 0, 0)) == COLOR_WHITE);
  assert(pattern.pattern_at(RayPoint(0, 0, 0.99)) == COLOR_WHITE);
  assert(pattern.pattern_at(RayPoint(0, 0, 1.01)) == COLOR_BLACK);

  std::cout << "[PASS 10.18] Checkers pattern alternates in Z works."
            << std::endl;
}

void test_reflectivity_for_default_material() {
  Material m;
  assert(equal(m.reflective, 0.0));

  std::cout << "[PASS 11.1] Material is 0.0 reflectivity by default works."
            << std::endl;
}

void test_precomupting_reflection_vector() {
  Plane *shape = new Plane();
  double sqrt_two_by_two = std::sqrt(2) / 2.0;
  Ray r(RayPoint(0, 1, -1), RayVector(0, -sqrt_two_by_two, sqrt_two_by_two));
  Intersection i(std::sqrt(2), shape);
  Computations comps = Computations(i, r);
  assert(comps.reflectv == RayVector(0, sqrt_two_by_two, sqrt_two_by_two));

  std::cout << "[PASS 11.2] Precomputing reflection vector works." << std::endl;

  delete shape;
}

void test_reflected_color_for_nonreflective_material() {
  DefaultWorld w;
  Ray r(RayPoint(0, 0, 0), RayVector(0, 0, 1));
  Shape *shape = w.objects[1];
  shape->material.ambient = 1.0;
  Intersection i(1, shape);
  Computations comps = Computations(i, r);
  Color color = w.reflected_color(comps);
  assert(color == COLOR_BLACK);

  std::cout
      << "[PASS 11.3] Refected color is black for nonreflective material works."
      << std::endl;
}

void test_reflected_color_for_reflective_material() {
  DefaultWorld w;
  Material m;
  m.reflective = 0.5;
  Plane *plane = new Plane(m);
  plane->set_transform(Matrix::translation(0, -1, 0));
  w.objects.push_back(plane);
  double sqrt_two_by_two = std::sqrt(2) / 2.0;
  Ray r(RayPoint(0, 0, -3), RayVector(0, -sqrt_two_by_two, sqrt_two_by_two));
  Intersection i(std::sqrt(2.0), plane);
  Computations comps = Computations(i, r);
  Color color = w.reflected_color(comps);

  assert(equal(color.r, 0.19032));
  assert(equal(color.g, 0.2379));
  assert(equal(color.b, 0.14274));
  std::cout << "[PASS 11.4] Refected color for reflective material works."
            << std::endl;
}

void test_shade_hit_with_reflective_material() {
  DefaultWorld w;
  Material m;
  m.reflective = 0.5;

  Plane *plane = new Plane(m);
  plane->set_transform(Matrix::translation(0, -1, 0));
  w.objects.push_back(plane);

  double sqrt_two_by_two = std::sqrt(2) / 2.0;
  Ray r(RayPoint(0, 0, -3), RayVector(0, -sqrt_two_by_two, sqrt_two_by_two));

  Intersection i(std::sqrt(2.0), plane);
  Computations comps = Computations(i, r);

  Color color = w.shade_hit(comps);

  assert(equal(color.r, 0.87677));
  assert(equal(color.g, 0.92436));
  assert(equal(color.b, 0.82918));

  std::cout << "[PASS 11.5] shade_hit() with a reflective material works."
            << std::endl;
}

void test_reflected_color_prevents_infinite_recursion() {
  World w;
  w.light_source = new LightSource(Color(1, 1, 1), RayPoint(0, 0, 0));

  Material reflecting_material;
  reflecting_material.reflective = 1.0;

  Plane *lower = new Plane(reflecting_material);
  lower->set_transform(Matrix::translation(0, -1, 0));
  w.objects.push_back(lower);

  Plane *upper = new Plane(reflecting_material);
  upper->set_transform(Matrix::translation(0, 1, 0));
  w.objects.push_back(upper);

  Ray r(RayPoint(0, 0, 0), RayVector(0, 1, 0));

  Intersection i(1.0, upper);
  Computations comps = Computations(i, r);

  Color color = w.reflected_color(comps, 0);

  assert(color == COLOR_BLACK);

  std::cout << "[PASS 11.6] reflected_color() terminates at recursion limit."
            << std::endl;
}

void test_transparency_and_refractive_index_for_default_material() {
  Material m;
  assert(m.transparency == 0.0);
  assert(m.refractive_index == 1.0);

  std::cout << "[PASS 11.7] Transparency and refractive index for default "
               "material works."
            << std::endl;
}

void test_glass_sphere_init() {
  Sphere *s = Sphere::glass_sphere();

  assert(s->transform == Matrix::identity(4));
  assert(s->material.transparency == 1.0);
  assert(s->material.refractive_index == 1.5);

  std::cout << "[PASS 11.8] Glass sphere init works." << std::endl;

  delete s;
}

void test_finding_n1_and_n2_at_various_intersections() {
  Sphere *A = Sphere::glass_sphere();
  A->set_transform(Matrix::scaling(2, 2, 2));
  A->material.refractive_index = 1.5;

  Sphere *B = Sphere::glass_sphere();
  B->set_transform(Matrix::translation(0, 0, -0.25));
  B->material.refractive_index = 2.0;

  Sphere *C = Sphere::glass_sphere();
  C->set_transform(Matrix::translation(0, 0, 0.25));
  C->material.refractive_index = 2.5;

  Ray r(RayPoint(0, 0, -4), RayVector(0, 0, 1));

  std::vector<Intersection> xs = {Intersection(2.0, A),  Intersection(2.75, B),
                                  Intersection(3.25, C), Intersection(4.75, B),
                                  Intersection(5.25, C), Intersection(6.0, A)};

  double expected_n1[6] = {1.0, 1.5, 2.0, 2.5, 2.5, 1.5};
  double expected_n2[6] = {1.5, 2.0, 2.5, 2.5, 1.5, 1.0};

  for (size_t idx = 0; idx < xs.size(); ++idx) {
    Computations comps(xs[idx], r, xs);

    assert(equal(comps.n1, expected_n1[idx]));
    assert(equal(comps.n2, expected_n2[idx]));
  }

  std::cout << "[PASS 11.9] Finding entry (n1) and exit (n2) index layers "
               "works perfectly."
            << std::endl;

  delete A;
  delete B;
  delete C;
}

void test_under_point_offset_precomputation() {
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));
  Sphere *shape = Sphere::glass_sphere();
  shape->set_transform(Matrix::translation(0, 0, 1));

  Intersection i(5.0, shape);
  std::vector<Intersection> xs = {i};
  Computations comps(i, r, xs);

  assert(comps.under_point.z > EPSILON / 2.0); // EPSILON check
  assert(comps.point.z < comps.under_point.z);

  std::cout << "[PASS 11.10] Precomputing under_point boundary shift works."
            << std::endl;
  delete shape;
}

void test_refracted_color_of_opaque_surface_is_black() {
  DefaultWorld w;
  Shape *shape = w.objects[0];
  Ray r(RayPoint(0, 0, -5), RayVector(0, 0, 1));

  Intersection i1(4.0, shape);
  Intersection i2(6.0, shape);
  std::vector<Intersection> xs = {i1, i2};

  Computations comps(xs[0], r, xs);
  Color c = w.refracted_color(comps, 5);

  assert(c == COLOR_BLACK);
  std::cout
      << "[PASS 11.11] Refracted color for completely opaque material is black."
      << std::endl;
}

void test_refracted_color_under_total_internal_reflection() {
  DefaultWorld w;
  Shape *shape = w.objects[0];
  shape->material.transparency = 1.0;
  shape->material.refractive_index = 1.5;

  Ray r(RayPoint(0, 0, std::sqrt(2) / 2.0), RayVector(0, 1, 0));

  std::vector<Intersection> xs = {Intersection(-std::sqrt(2) / 2.0, shape),
                                  Intersection(std::sqrt(2) / 2.0, shape)};

  Computations comps(xs[1], r, xs);
  Color c = w.refracted_color(comps, 5);

  assert(c == COLOR_BLACK);
  std::cout << "[PASS 11.12] Refracted color under total internal reflection "
               "is black."
            << std::endl;
}

void test_refracted_color_with_a_refracted_ray() {
  DefaultWorld w;

  Shape *A = w.objects[0];
  A->material.ambient = 1.0;
  A->material.pattern = new TestPattern();

  Shape *B = w.objects[1];
  B->material.transparency = 1.0;
  B->material.refractive_index = 1.5;

  Ray r(RayPoint(0, 0, 0.1), RayVector(0, 1, 0));
  std::vector<Intersection> xs = {
      Intersection(-0.9899, A), Intersection(-0.4899, B),
      Intersection(0.4899, B), Intersection(0.9899, A)};

  Computations comps(xs[2], r, xs);
  Color c = w.refracted_color(comps, 5);

  assert(equal(c.r, 0.0));
  assert(equal(c.g, 0.99888));
  assert(equal(c.b, 0.04725));

  std::cout << "[PASS 11.13] Refracted color with a refracted ray calculates "
               "correctly."
            << std::endl;
}

void test_shade_hit_with_a_transparent_material() {
  DefaultWorld w;

  Plane *floor = new Plane();
  floor->set_transform(Matrix::translation(0, -1, 0));
  floor->material.transparency = 0.5;
  floor->material.refractive_index = 1.5;
  w.objects.push_back(floor);

  Sphere *ball = new Sphere();
  ball->set_transform(Matrix::translation(0, -3.5, -0.5));
  ball->material.color = Color(1, 0, 0);
  ball->material.ambient = 0.5;
  w.objects.push_back(ball);

  double sqrt_two_by_two = std::sqrt(2) / 2.0;
  Ray r(RayPoint(0, 0, -3), RayVector(0, -sqrt_two_by_two, sqrt_two_by_two));
  std::vector<Intersection> xs = {Intersection(std::sqrt(2), floor)};

  Computations comps(xs[0], r, xs);
  Color c = w.shade_hit(comps);

  assert(equal(c.r, 0.93642));
  assert(equal(c.g, 0.68642));
  assert(equal(c.b, 0.68642));

  std::cout << "[PASS 11.14] shade_hit() handles transparent surfaces properly."
            << std::endl;
}

void test_schlick_approximation_under_total_internal_reflection() {
  Sphere *shape = Sphere::glass_sphere();
  Ray r(RayPoint(0, 0, std::sqrt(2) / 2.0), RayVector(0, 1, 0));
  std::vector<Intersection> xs = {Intersection(-std::sqrt(2) / 2.0, shape),
                                  Intersection(std::sqrt(2) / 2.0, shape)};

  Computations comps(xs[1], r, xs);
  double reflectance = schlick(comps);

  assert(equal(reflectance, 1.0));

  std::cout << "[PASS 11.15] Schlick approximation under TIR is 1.0."
            << std::endl;
  delete shape;
}

void test_schlick_approximation_with_a_perpendicular_viewing_angle() {
  Sphere *shape = Sphere::glass_sphere();
  Ray r(RayPoint(0, 0, 0), RayVector(0, 1, 0));
  std::vector<Intersection> xs = {Intersection(-1.0, shape),
                                  Intersection(1.0, shape)};

  Computations comps(xs[0], r, xs);
  double reflectance = schlick(comps);

  assert(equal(reflectance, 0.04));

  std::cout << "[PASS 11.16] Schlick approximation perpendicular angle is 0.04."
            << std::endl;
  delete shape;
}

void test_schlick_approximation_with_a_grazing_angle() {
  Sphere *shape = Sphere::glass_sphere();
  Ray r(RayPoint(0, 0.99, -2), RayVector(0, 0, 1));
  std::vector<Intersection> xs = {Intersection(1.8589, shape)};

  Computations comps(xs[0], r, xs);
  double reflectance = schlick(comps);

  assert(equal(reflectance, 0.48873));

  std::cout << "[PASS 11.17] Schlick approximation grazing angle works."
            << std::endl;
  delete shape;
}

void test_shade_hit_with_a_reflective_transparent_material() {
  DefaultWorld w;

  Plane *floor = new Plane();
  floor->set_transform(Matrix::translation(0, -1, 0));
  floor->material.reflective = 0.5;
  floor->material.transparency = 0.5;
  floor->material.refractive_index = 1.5;
  w.objects.push_back(floor);

  Sphere *ball = new Sphere();
  ball->set_transform(Matrix::translation(0, -3.5, -0.5));
  ball->material.color = Color(1, 0, 0);
  ball->material.ambient = 0.5;
  w.objects.push_back(ball);

  double sqrt_two_by_two = std::sqrt(2) / 2.0;
  Ray r(RayPoint(0, 0, -3), RayVector(0, -sqrt_two_by_two, sqrt_two_by_two));
  std::vector<Intersection> xs = {Intersection(std::sqrt(2), floor)};

  Computations comps(xs[0], r, xs);
  Color c = w.shade_hit(comps);

  assert(equal(c.r, 0.93391));
  assert(equal(c.g, 0.69643));
  assert(equal(c.b, 0.69243));

  std::cout << "[PASS 11.18] shade_hit() with Schlick Fresnel integration "
               "works."
            << std::endl;
}

void test_check_axis_behavior() {
  auto [t1_min, t1_max] = check_axis(5.0, -1.0);
  assert(equal(t1_min, 4.0));
  assert(equal(t1_max, 6.0));

  auto [t2_min, t2_max] = check_axis(-5.0, 1.0);
  assert(equal(t2_min, 4.0));
  assert(equal(t2_max, 6.0));

  auto [t3_min, t3_max] = check_axis(0.0, 1.0);
  assert(equal(t3_min, -1.0));
  assert(equal(t3_max, 1.0));

  std::cout << "[PASS 12.1] check_axis helper functions works." << std::endl;
}

void test_cube_intersections() {
  Cube cube;

  Ray r1(RayPoint(5, 0.5, 0), RayVector(-1, 0, 0));
  auto xs1 = cube.local_intersects(r1);
  assert(xs1.size() == 2);
  assert(equal(xs1[0].t, 4.0));
  assert(equal(xs1[1].t, 6.0));

  Ray r2(RayPoint(0, -5, 0), RayVector(0, 1, 0));
  auto xs2 = cube.local_intersects(r2);
  assert(xs2.size() == 2);
  assert(equal(xs2[0].t, 4.0));
  assert(equal(xs2[1].t, 6.0));

  Ray r3(RayPoint(2, 2, 0), RayVector(-1, 0, 0));
  auto xs3 = cube.local_intersects(r3);
  assert(xs3.empty());

  std::cout << "[PASS 12.2] Cube local_intersects logic works." << std::endl;
}

void test_cube_normals() {
  Cube cube;

  assert(cube.local_normal_at(RayPoint(1, 0.5, -0.8)) == RayVector(1, 0, 0));
  assert(cube.local_normal_at(RayPoint(-1, -0.2, 0.1)) == RayVector(-1, 0, 0));
  assert(cube.local_normal_at(RayPoint(0.4, 1, -0.1)) == RayVector(0, 1, 0));
  assert(cube.local_normal_at(RayPoint(0.3, -1, -0.7)) == RayVector(0, -1, 0));
  assert(cube.local_normal_at(RayPoint(-0.6, 0.3, 1)) == RayVector(0, 0, 1));
  assert(cube.local_normal_at(RayPoint(0.4, 0.6, -1)) == RayVector(0, 0, -1));

  std::cout << "[PASS 12.3] Cube local_normal_at works." << std::endl;
}
