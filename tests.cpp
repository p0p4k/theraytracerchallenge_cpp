#include "tests.h"
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
  RayVector v = RayVector(4, 0, 0);
  assert(v.normalize() == RayVector(1, 0, 0) && "normalize failed.");

  RayVector v1 = RayVector(1, 2, 3);
  assert(v1.normalize() == RayVector(0.26726, 0.53452, 0.80178) &&
         "normalize failed.");

  RayVector v2 = RayVector(1, 2, 3);
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
