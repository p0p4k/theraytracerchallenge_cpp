#include "tests.h"

void run_tests() {
  test_tuple_to_point();
  test_tuple_to_vector();
  test_tuple_addition();
  test_point_minus_point();
  test_point_minus_vector();
  test_subtract_vector_from_zero_vector();
  test_negate_tuple();
  test_multiply_tuple_by_scalar();
  test_divide_tuple_by_scalar();
  test_magnitude_of_vector();
  test_normalize_vector();
  test_dot_product_vector();
  test_cross_product_vector();

  test_color_implementation();
  test_color_addition();
  test_color_subtraction();
  test_color_multiplication_by_scalar();
  test_color_multiply_by_color();

  test_create_canvas();
  test_writing_canvas();
  test_canvas_to_ppm_header();
}
