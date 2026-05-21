#ifndef TESTS_H
#define TESTS_H

#include "canvas.h"
#include "color.h"
#include "matrix.h"
#include "tuple.h"
#include "utilities.h"

#include <cassert>

void test_tuple_to_point();
void test_tuple_to_vector();
void test_tuple_addition();
void test_point_minus_point();
void test_point_minus_vector();
void test_subtract_vector_from_zero_vector();
void test_negate_tuple();
void test_multiply_tuple_by_scalar();
void test_divide_tuple_by_scalar();
void test_magnitude_of_vector();
void test_normalize_vector();
void test_dot_product_vector();
void test_cross_product_vector();

void test_color_implementation();
void test_color_addition();
void test_color_subtraction();
void test_color_multiplication_by_scalar();
void test_color_multiply_by_color();
void test_create_canvas();
void test_writing_canvas();
void test_canvas_to_ppm_header();

void test_matrix_construction();
void test_matrix_comparision_equal();
void test_matrix_comparision_not_equal();
void test_matrix_multiply();
void test_matrix_tuple_multiply();
void test_identity_matrix_multiplication();
void test_matrix_transpose();
void test_matrix_submatrix();
void test_matrix_determinant_2x2();
void test_matrix_minor_3x3();
void test_matrix_cofactor();
void test_matrix_determinant_large();
void test_matrix_inversion();

void test_matrix_translation();
void test_matrix_scaling();
void test_matrix_rotation_x();
void test_matrix_rotation_y();
void test_matrix_rotation_z();
void test_matrix_rotation_x_inverse();
void test_matrix_shearing();
void test_individual_and_chained_transformations();

#endif
