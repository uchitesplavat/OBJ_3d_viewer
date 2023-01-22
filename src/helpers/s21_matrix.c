#include"s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        free(A->matrix);
        A->matrix = NULL;
    }
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int error_mark = 0;
    if (columns && rows) {
        result->columns = columns;
        result->rows = rows;
        result->matrix = (double**)calloc(rows, sizeof(double*));
        if (result->matrix) {
            for (int i = 0; i < rows; i++) {
                result->matrix[i] = (double*)calloc(columns, sizeof(double));
                if (!result->matrix[i]) {
                    error_mark = 1;
                }
            }
        } else {
            error_mark = 1;
        }
    } else {
        error_mark = 1;
    }
    return error_mark;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    double epsilon = 1e-6;
    int error_mark = SUCCESS;
    if (!check_matrix(A) && !check_matrix(B) &&
            A->rows == B->rows && A->columns == B->columns) {
        int rows = A->rows;
        int columns = A->columns;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if ((fabs(A->matrix[i][j] - B->matrix[i][j])) >= epsilon) {
                    error_mark = FAILURE;
                }
            }
        }
    } else {
        error_mark = FAILURE;
    }
    return error_mark;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int error_mark = 0;
    if (A->columns == B->columns && A->rows == B->rows) {
        error_mark = s21_create_matrix(A->rows, A->columns, result);
        if (!error_mark) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                }
            }
        }
    } else {
        error_mark = 2;
    }
    return error_mark;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int error_mark = 0;
    if (A->columns == B->columns && A->rows == B->rows) {
        error_mark = s21_create_matrix(A->rows, A->columns, result);
        if (!error_mark) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                }
            }
        }
    } else {
        error_mark = 2;
    }
    return error_mark;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int error_mark = 0;
    error_mark = s21_create_matrix(A->rows, A->columns, result);
    if (!error_mark) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
    }
    return error_mark;
}
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int error_mark = 0;
    if (A->columns == B->rows) {
        error_mark = s21_create_matrix(A->rows, B->columns, result);
        if (!error_mark) {
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < B->columns; j++) {
                    for (int k = 0; k < A->columns; k++) {
                        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                    }
                }
            }
        }
    } else {
        error_mark = 2;
    }
    return error_mark;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int error_mark = 0;
    if (A->matrix) {
        error_mark = s21_create_matrix(A->columns, A->rows, result);
        if (!error_mark) {
            for (int i = 0; i < A->columns; i++) {
                for (int j = 0; j < A->rows; j++) {
                    result->matrix[i][j] = A->matrix[j][i];
                }
            }
        }
    } else {
        error_mark = 1;
    }
    return error_mark;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int error_mark = 0;
    if (!check_matrix(A)) {
        if (A->columns == A->rows) {
            error_mark = s21_create_matrix(A->rows, A->columns, result);
            if (!error_mark) {
                if (A->rows == 1 && A->columns == 1) {
                    result->matrix[0][0] = A->matrix[0][0];
                } else {
                    calc_complements(A->rows, A->columns, result, A);
                }
            }
        } else {
            error_mark = 2;
        }
    } else {
        error_mark = 1;
    }
    return error_mark;
}

int s21_determinant(matrix_t *A, double *result) {
    int error_mark = 0;
    if (!check_matrix(A)) {
        if (A->columns == A->rows) {
            matrix_t compl1 = {0};
            if (A->rows == 1 && A->columns == 1) {
                *result = A->matrix[0][0];
            } else {
                error_mark = s21_calc_complements(A, &compl1);
                if (!error_mark) {
                    for (int i = 0; i < A->rows; i++) {
                        *result += compl1.matrix[i][0] * A->matrix[i][0];
                    }
                }
                s21_remove_matrix(&compl1);
            }
        } else {
            error_mark = 2;
        }
    } else {
        error_mark = 1;
    }
    return error_mark;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int error_mark = 0;
    if (!check_matrix(A)) {
        if (A->columns == A->rows) {
            if (A->columns == 1) {
                s21_create_matrix(1, 1, result);
                result->matrix[0][0] = 1/A->matrix[0][0];
            } else {
                double det = 0.0;
                s21_determinant(A, &det);
                if (fabs(det) >= 1e-6) {
                    matrix_t compl1 = {0};
                    matrix_t trans = {0};
                    s21_calc_complements(A, &compl1);
                    s21_transpose(&compl1, &trans);
                    s21_mult_number(&trans, (1/det), result);
                    s21_remove_matrix(&compl1);
                    s21_remove_matrix(&trans);
                } else {
                    error_mark = 2;
                }
            }
        } else {
            error_mark = 2;
        }
    } else {
        error_mark = 1;
    }
    return error_mark;
}

/* ANOTHER*/

int check_matrix(matrix_t *A) {
    int error_mark = 0;
    if (!A || A->rows < 1 || A->columns < 1 || !A->matrix) {
        error_mark = 1;
    }
    return error_mark;
}

int get_minor_matrix(matrix_t *A, matrix_t *result) {
    int error_mark = 0;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = get_minor(i, j, A);
        }
    }
    return error_mark;
}

double get_minor(int i, int j, matrix_t *A) {
    int error_mark = 0;
    double minor = 0.0;
    if (A->columns == 2) {
        for (int m = 0; m < A->rows; m++) {
            for (int n = 0; n < A->columns; n++) {
                if (m != i && n != j) {
                    minor = A->matrix[m][n];
                }
            }
        }
    } else {
        matrix_t minor_m = {0};
        int x = 0;
        int y = 0;
        error_mark = s21_create_matrix(A->rows-1, A->columns-1, &minor_m);
        if (!error_mark) {
            for (int m = 0; x < A->rows-1; m++) {
                if (m != i) {
                    for (int n = 0; y < A->columns-1; n++) {
                        if (n != j) {
                            minor_m.matrix[x][y] = A->matrix[m][n];
                            y++;
                        }
                    }
                    x++;
                    y = 0;
                }
            }
            if (minor_m.columns > 2) {
                s21_determinant(&minor_m, &minor);
            } else {
                minor = det_two(&minor_m);
            }
            s21_remove_matrix(&minor_m);
        }
    }
    return minor;
}

double det_two(matrix_t *minor_m) {
    return (minor_m->matrix[0][0] * minor_m->matrix[1][1] - minor_m->matrix[1][0] * minor_m->matrix[0][1]);
}

void calc_complements(int rows, int columns, matrix_t *result, matrix_t *A) {
    get_minor_matrix(A, result);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result->matrix[i][j] *= pow(-1, i+j);
        }
    }
}

