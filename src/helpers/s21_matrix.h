#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
} matrix_t;


int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//  ANOTHER
int check_matrix(matrix_t *A);
int get_minor_matrix(matrix_t *A, matrix_t *result);
double get_minor(int i, int j, matrix_t *A);
double det_two(matrix_t *minor_m);
void calc_complements(int rows, int columns, matrix_t *result, matrix_t *A);

#endif  // SRC_S21_MATRIX_H_
