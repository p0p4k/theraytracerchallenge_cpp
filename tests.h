#ifndef TESTS_H
#define TESTS_H

#include "canvas.h"
#include "color.h"
#include "tuple.h"
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

#endif
