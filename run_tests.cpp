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

  test_create_and_query_ray();
  test_ray_point_from_dist();
  test_sphere_ray_intersect_at_two_points();
  test_sphere_ray_intersect_at_tangent();
  test_sphere_ray_miss();
  test_sphere_behind_ray();
  test_hit_all_positive_t();
  test_hit_some_negative_t();
  test_hit_all_negative_t();
  test_hit_lowest_non_negative_t();
  test_translating_a_ray();
  test_scaling_a_ray();
  test_sphere_default_transformation();
  test_sphere_transformation();
  test_intersect_scaled_sphere_with_ray();
  test_intersect_translated_sphere_with_ray();

  test_normal_on_sphere_at_point_on_x_axis();
  test_normal_on_sphere_at_point_on_y_axis();
  test_normal_on_sphere_at_point_on_z_axis();
  test_normal_on_sphere_at_non_axial_point();
  test_normal_is_a_normalized_vector();
  test_computing_normal_on_translated_sphere();
  test_computing_normal_on_transformed_sphere();
  test_reflecting_a_vector_approaching_at_45_degrees();
  test_reflecting_a_vector_off_a_slanted_surface();
  test_point_light_source();
  test_default_material();
  test_sphere_has_default_material();
  test_sphere_may_be_assigned_a_material();
  test_lighting_with_eye_between_light_and_surface();
  test_lighting_with_eye_between_light_and_surface_eye_offset_45_degrees();
  test_lighting_with_eye_opposite_surface_light_offset_45_degrees();
  test_lighting_with_eye_in_the_path_of_the_reflection_vector();
  test_lighting_with_the_light_behind_the_surface();

  test_world_empty_on_creation();
  test_default_world();
  test_intersect_world_with_ray();
  test_shading_an_intersection();
  test_shading_an_intersection_from_the_inside();
  test_color_at_ray_misses();
  test_color_at_ray_hits();
  test_color_with_intersection_behind_the_ray();
  test_view_transformation_default();
  test_view_transformation_positive_z();
  test_view_transformation_translation();
  test_pixel_size_horizontal();
  test_pixel_size_vertical();
  test_ray_through_center_of_canvas();
  test_ray_through_corner_of_canvas();
  test_ray_with_transformed_camera();
  test_rendering_a_world_with_a_camera();

  test_lighting_with_surface_in_shadow();
  test_no_shadow_collinear_point_and_light();
  test_is_shadowed_with_obstruction();
  test_is_shadowed_object_behind_light();
  test_is_shadowed_object_behind_point();
  test_hit_offset_point();

  test_default_shape_transformation();
  test_assigning_a_transformation_on_base_shape();
  test_default_shape_has_default_material();
  test_assigning_a_material_to_a_shape();
  test_shape_intersection_encapsulates_material();
  test_intersecting_a_scaled_shape_with_a_ray();
  test_intersecting_a_translated_shape_with_a_ray();
  test_computing_the_normal_on_a_translated_shape();
  test_computing_the_normal_on_a_transformed_shape();
  test_the_normal_of_a_plane_is_constant_everywhere();
  test_intersect_with_a_ray_parallel_to_the_plane();
  test_intersect_with_a_coplanar_ray();
  test_a_ray_intersecting_a_plane_from_above();
  test_a_ray_intersecting_a_plane_from_below();
}
