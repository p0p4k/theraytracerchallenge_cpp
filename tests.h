#ifndef TESTS_H
#define TESTS_H

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

#endif
