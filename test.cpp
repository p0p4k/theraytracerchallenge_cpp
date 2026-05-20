#include "tests.h"
#include "tuple.h"
#include <cmath>
#include <iostream>
#include <ostream>

void test_tuple_to_point() {
  RayPoint p = RayPoint(4, -4, 3);
  assert((p == RayTuple(4, -4, 3, 1.0)) && "Point is not equal.");
  std::cout << "[PASS 01] Points equal." << std::endl;
}

void test_tuple_to_vector() {
  RayVector v = RayVector(4, -4, 3);
  assert((v == RayTuple(4, -4, 3, 0.0)) && "Vector is not equal.");
  std::cout << "[PASS 02] Vectors are equal." << std::endl;
}

void test_tuple_addition() {
  RayTuple t1 = RayTuple(3, -2, 5, 1);
  RayTuple t2 = RayTuple(-2, 3, 1, 0);
  RayTuple t3 = t1 + t2;
  assert(t3 == RayTuple(1, 1, 6, 1));
  std::cout << "[PASS 03] Tuple addition works perfectly." << std::endl;
}

void test_point_minus_point() {
  RayTuple s1 = RayPoint(3, 2, 1);
  RayTuple s2 = RayPoint(5, 6, 7);
  RayTuple s3 = s1 - s2;
  assert((s3 == RayVector(-2, -4, -6)) && "Point - Point failed.");
  std::cout << "[PASS 04] Point - Point subtraction works perfectly."
            << std::endl;
}

void test_point_minus_vector() {
  RayTuple p1 = RayPoint(3, 2, 1);
  RayTuple v2 = RayVector(5, 6, 7);
  RayTuple x3 = p1 - v2;
  assert((x3 == RayPoint(-2, -4, -6)) && "Point - Vector failed.");
  std::cout << "[PASS 05] Point - Vector subtraction works perfectly."
            << std::endl;
}

void test_subtract_vector_from_zero_vector() {
  RayVector zero = RayVector(0, 0, 0);
  RayVector v = RayVector(1, -2, 3);
  assert((zero - v == RayVector(-1, 2, -3)) && "Zero - Vecotr failed.");
  std::cout << "[PASS 06] Zero Vector - Vector works." << std::endl;
}

void test_negate_tuple() {
  RayTuple t = RayTuple(1, -2, 3, -4);
  assert((-t == RayTuple(-1, 2, -3, 4)) && "Negate failed.");
  std::cout << "[PASS 07] Negate works." << std::endl;
}

void test_multiply_tuple_by_scalar() {
  RayTuple t = RayTuple(1, -2, 3, -4);
  assert((t * 3.5 == RayTuple(3.5, -7, 10.5, -14) &&
          "Multiply with scalar failed."));
  std::cout << "[PASS 08] Multiply Tuple with Scalar works." << std::endl;
}

void test_divide_tuple_by_scalar() {
  RayTuple t = RayTuple(1, -2, 3, -4);
  assert(
      (t / 2.0 == RayTuple(0.5, -1, 1.5, -2) && "Divide with scalar failed."));
  std::cout << "[PASS 09] Divide Tuple with Scalar works." << std::endl;
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

  std::cout << "[PASS 10] Magnitude works." << std::endl;
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

  std::cout << "[PASS 11] Normalize vector works." << std::endl;
}

void test_dot_product_vector() {
  RayVector a = RayVector(1, 2, 3);
  RayVector b = RayVector(2, 3, 4);
  assert((a.dot(b) == 20.0) && "vector dot product failed.");
  std::cout << "[PASS 12] Dot product of Vectors works." << std::endl;
}

void test_cross_product_vector() {
  RayVector a = RayVector(1, 2, 3);
  RayVector b = RayVector(2, 3, 4);
  assert(a.cross(b) == RayVector(-1, 2, -1) &&
         b.cross(a) == RayVector(1, -2, 1) && "Vector cross failed.");
  std::cout << "[PASS 13] Cross product of vectors works." << std::endl;
}
