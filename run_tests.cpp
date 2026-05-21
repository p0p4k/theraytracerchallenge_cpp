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

  test_matrix_construction();
  test_matrix_comparision_equal();
  test_matrix_comparision_not_equal();
  test_matrix_multiply();
  test_matrix_tuple_multiply();
  test_identity_matrix_multiplication();
  test_matrix_transpose();
  test_matrix_submatrix();
  test_matrix_determinant_2x2();
  test_matrix_minor_3x3();
  test_matrix_cofactor();
  test_matrix_determinant_large();
  test_matrix_inversion();

  test_matrix_translation();
  test_matrix_scaling();
  test_matrix_rotation_x();
  test_matrix_rotation_y();
  test_matrix_rotation_z();
  test_matrix_rotation_x_inverse();
  test_matrix_shearing();
  test_individual_and_chained_transformations();
}
