#include <check.h>

#include "parser.h"

#define ck_assert_double_array_eq(a, b, len) \
  do {                                       \
    int i;                                   \
    for (i = 0; i < len; i++) {              \
      ck_assert_double_eq((a)[i], (b)[i]);   \
    }                                        \
  } while (0)

START_TEST(test_parse_float_numbers_for_V_positive) {
  char str[] = "1.23";
  float val;
  char* end = parse_float_numbers_for_V(str, &val);
  ck_assert_float_eq_tol(val, 1.23f, 1e-6);
  ck_assert_ptr_eq(end, str + 4);
}
END_TEST

START_TEST(test_parse_float_numbers_for_V_negative) {
  char str[] = "-1.23";
  float val;
  char* end = parse_float_numbers_for_V(str, &val);
  ck_assert_float_eq_tol(val, -1.23f, 1e-6);
  ck_assert_ptr_eq(end, str + 5);
}
END_TEST

START_TEST(test_parse_float_numbers_for_V_exponent) {
  char str[] = "1.23e4";
  float val;
  char* end = parse_float_numbers_for_V(str, &val);
  ck_assert_float_eq_tol(val, 1.23e4f, 1e-6);
  ck_assert_ptr_eq(end, str + 6);
}
END_TEST

START_TEST(test_parse_float_numbers_for_V_negative_exponent) {
  char str[] = "1.23e-4";
  float val;
  char* end = parse_float_numbers_for_V(str, &val);
  ck_assert_float_eq_tol(val, 1.23e-4f, 1e-6);
  ck_assert_ptr_eq(end, str + 7);
}
END_TEST

START_TEST(test_parse_float_numbers_for_V_leading_whitespace) {
  char str[] = "  1.23";
  float val;
  char* end = parse_float_numbers_for_V(str, &val);
  ck_assert_float_eq_tol(val, 1.23f, 1e-6);
  ck_assert_ptr_eq(end, str + 6);
}
END_TEST

START_TEST(test_parse_float_numbers_for_V_trailing_characters) {
  char str[] = "1.23xyz";
  float val;
  char* end = parse_float_numbers_for_V(str, &val);
  ck_assert_float_eq_tol(val, 1.23f, 1e-6);
  ck_assert_ptr_eq(end, str + 4);
}
END_TEST

START_TEST(test_parse_float_numbers_for_V_invalid) {
  // Test input that is not a number
  {
    char str[] = "abc";
    float val;
    char* end = parse_float_numbers_for_V(str, &val);
    ck_assert_ptr_eq(end, str);
  }

  // Test input that starts with a decimal point
}
END_TEST

START_TEST(test_parse_float_numbers_for_V_leading_trailing_whitespace) {
  // Test input with leading whitespace before the sign
  {
    char str[] = "  -1.23";
    float val;
    char* end = parse_float_numbers_for_V(str, &val);
    ck_assert_float_eq_tol(val, -1.23f, 1e-6);
    ck_assert_ptr_eq(end, str + 7);
  }
}
END_TEST

START_TEST(test_database_parser_with_valid_input) {
  database d = parser("models/cube.obj");

  ck_assert_ptr_nonnull(d.polygons);

  // additional assertions to check the content of d.matrix_3d and d.polygons
}
END_TEST

START_TEST(test_database_parser_with_invalid_input) {
  database d = parser("invalid_input.stl");

  ck_assert_int_eq(d.count_of_vert, 0);
  ck_assert_int_eq(d.count_of_face, 0);
  ck_assert_ptr_null(d.polygons);
}
END_TEST

START_TEST(test_s21_remove_matrix) {
  database d = {0};
  s21_create_matrix(2, &d.matrix_3d);
  s21_remove_matrix(&d.matrix_3d);
  ck_assert(d.matrix_3d.matrix == NULL);
  ck_assert(d.matrix_3d.rows == 0);
  ck_assert(d.matrix_3d.cols == 0);
}
END_TEST

START_TEST(test_model_rotation_x_axis) {
  double arr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  double rotate = 90;
  int index = 0;
  int countVertex = 4;
  double expected[12] = {1, 3, -2, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  model_rotation(arr, rotate, index, countVertex);
  for (int i = 0; i < 12; i++) {
    // printf("%f arr 133, %f expected\n", arr[i], expected[i]);
    ck_assert_float_eq(arr[i], expected[i]);
  }
}
END_TEST

START_TEST(test_model_rotation_y_axis) {
  double arr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  double rotate = 90;
  int index = 1;
  int countVertex = 4;
  double expected[12] = {3, 2, -1, 6, 5, -4, 7, 8, 9, 10, 11, 12};
  model_rotation(arr, rotate, index, countVertex);
  for (int i = 0; i < 12; i++) {
    ck_assert_float_eq(arr[i], expected[i]);
  }
}
END_TEST

START_TEST(test_model_rotation_z_axis) {
  double arr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  double rotate = 90;
  int index = 2;
  int countVertex = 4;
  double expected[12] = {1, 3, -2, 4, 6, -5, 7, 8, 9, 10, 11, 12};
  model_rotation(arr, rotate, index, countVertex);
  for (int i = 0; i < 12; i++) {
    // printf("%f arr, %f expected\n", arr[i], expected[i]);
    ck_assert_float_eq(arr[i], expected[i]);
  }
}
END_TEST

START_TEST(test_model_trans_x) {
  double arr[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
  double translate = 1;
  int index = 0;
  int countVertex = 3;

  model_trans(arr, translate, index, countVertex);

  ck_assert_double_eq(arr[0], 1);
  ck_assert_double_eq(arr[1], 0);
  ck_assert_double_eq(arr[2], 0);
  ck_assert_double_eq(arr[3], 1);
  ck_assert_double_eq(arr[4], 1);
  ck_assert_double_eq(arr[5], 1);
  ck_assert_double_eq(arr[6], 2);
  ck_assert_double_eq(arr[7], 2);
  ck_assert_double_eq(arr[8], 2);
}
END_TEST

START_TEST(test_model_trans_y) {
  double arr[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
  double translate = 1;
  int index = 1;
  int countVertex = 3;

  model_trans(arr, translate, index, countVertex);

  ck_assert_double_eq(arr[0], 0);
  ck_assert_double_eq(arr[1], 1);
  ck_assert_double_eq(arr[2], 0);
  ck_assert_double_eq(arr[3], 1);
  ck_assert_double_eq(arr[4], 1);
  ck_assert_double_eq(arr[5], 1);
  ck_assert_double_eq(arr[6], 2);
  ck_assert_double_eq(arr[7], 2);
  ck_assert_double_eq(arr[8], 2);
}
END_TEST

START_TEST(test_model_trans_z) {
  double arr[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
  double translate = 1;
  int index = 2;
  int countVertex = 3;

  model_trans(arr, translate, index, countVertex);

  ck_assert_double_eq(arr[0], 0);
  ck_assert_double_eq(arr[1], 0);
  ck_assert_double_eq(arr[2], 1);
  ck_assert_double_eq(arr[3], 1);
  ck_assert_double_eq(arr[4], 1);
  ck_assert_double_eq(arr[5], 1);
  ck_assert_double_eq(arr[6], 2);
  ck_assert_double_eq(arr[7], 2);
  ck_assert_double_eq(arr[8], 2);
}
END_TEST

START_TEST(test_model_scale_scales_vertices_by_scale_factor) {
  double arr[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 2.0, 2.0, 2.0};
  double result[] = {0.0, 0.0, 0.0, 9.0, 9.0, 9.0, 2.0, 2.0, 2.0};
  double scale = 9.0;
  int countVertex = 6;
  model_scale(arr, scale, countVertex);
  for (int i = 0; i < 9; i++) {
    // printf("%f\n", arr[i]);
    ck_assert_double_eq_tol(arr[i], result[i], 0.0001);
  }
}
END_TEST

START_TEST(test_model_scale_scales_vertices_by_negative_scale_factor) {
  double arr[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
  double result[] = {0.0, 0.0, 0.0, -1.0, -1.0, -1.0, -2.0, -2.0, -2.0};
  double scale = -1.0;
  int countVertex = 12;
  model_scale(arr, scale, countVertex);
  for (int i = 0; i < 9; i++) {
    // printf("%f\n", arr[i]);
    ck_assert_double_eq_tol(arr[i], result[i], 0.0001);
  }
  // ck_assert_double_eq_tol(arr[0], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[1], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[2], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[3], -1.0, 0.0001);
  // ck_assert_double_eq_tol(arr[4], -1.0, 0.0001);
  // ck_assert_double_eq_tol(arr[5], -1.0, 0.0001);
  // ck_assert_double_eq_tol(arr[6], -2.0, 0.0001);
  // ck_assert_double_eq_tol(arr[7], -2.0, 0.0001);
  // ck_assert_double_eq_tol(arr[8], -2.0, 0.0001);
}
END_TEST

START_TEST(test_model_scale_scales_vertices_by_scale_factor_of_zero) {
  double arr[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
  double result[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double scale = 0.0;
  int countVertex = 12;
  model_scale(arr, scale, countVertex);
  for (int i = 0; i < 9; i++) {
    // printf("%f\n", arr[i]);
    ck_assert_double_eq_tol(arr[i], result[i], 0.0001);
  }
  // ck_assert_double_eq_tol(arr[0], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[1], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[2], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[3], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[4], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[5], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[6], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[7], 0.0, 0.0001);
  // ck_assert_double_eq_tol(arr[8], 0.0, 0.0001);
}

END_TEST

START_TEST(check_amount_test) {
  const char* stringa = "-123456789.";
  const char* vtoraya = "-123456789.zxc";
  const char* no = "--23";
  const char* no_no = "2332.323.3";
  ck_assert_int_eq(check_amount(stringa), 0);
  ck_assert_int_eq(check_amount(vtoraya), 1);
  ck_assert_int_eq(check_amount(no), 1);
  ck_assert_int_eq(check_amount(no_no), 1);
}

END_TEST
int main() {
  Suite* suite = suite_create("parse_float_numbers_for_V");
  TCase* tcase = tcase_create("case");
  tcase_add_test(tcase, test_parse_float_numbers_for_V_positive);
  tcase_add_test(tcase, test_parse_float_numbers_for_V_negative);
  tcase_add_test(tcase, test_parse_float_numbers_for_V_exponent);
  tcase_add_test(tcase, test_parse_float_numbers_for_V_negative_exponent);
  tcase_add_test(tcase, test_parse_float_numbers_for_V_leading_whitespace);
  tcase_add_test(tcase, test_parse_float_numbers_for_V_trailing_characters);
  tcase_add_test(tcase, test_parse_float_numbers_for_V_invalid);
  tcase_add_test(tcase,
                 test_parse_float_numbers_for_V_leading_trailing_whitespace);
  tcase_add_test(tcase, test_database_parser_with_valid_input);
  tcase_add_test(tcase, test_database_parser_with_invalid_input);
  tcase_add_test(tcase, test_s21_remove_matrix);
  tcase_add_test(tcase, test_model_rotation_x_axis);
  tcase_add_test(tcase, test_model_rotation_y_axis);
  tcase_add_test(tcase, test_model_rotation_z_axis);
  tcase_add_test(tcase, test_model_trans_x);
  tcase_add_test(tcase, test_model_trans_y);
  tcase_add_test(tcase, test_model_trans_z);
  tcase_add_test(tcase, test_model_scale_scales_vertices_by_scale_factor);
  tcase_add_test(tcase,
                 test_model_scale_scales_vertices_by_negative_scale_factor);
  tcase_add_test(tcase,
                 test_model_scale_scales_vertices_by_scale_factor_of_zero);
  tcase_add_test(tcase, check_amount_test);
  suite_add_tcase(suite, tcase);

  SRunner* runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int num_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return num_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

// int main() {
//     Suite *s1 = suite_create("s21_3d_Viewer: ");
//     TCase *tc1_1 = tcase_create("s21_3d_Viewer: ");
//     SRunner *sr = srunner_create(s1);
//     int result;
//     suite_add_tcase(s1, tc1_1);
//
//     // tcase_add_test(tc1_1, set_number_test);
//     tcase_add_test(tc1_1, check_parser);
//     tcase_add_test(tc1_1, check_affine);
//
//     srunner_set_fork_status(sr, CK_NOFORK);
//     srunner_run_all(sr, CK_NORMAL);
//     result = srunner_ntests_failed(sr);
//     srunner_free(sr);
//     return result == 0 ? 0 : 1;
// }