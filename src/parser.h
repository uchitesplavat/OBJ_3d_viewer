#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define isspace(c) (c) == ' '

typedef enum type_t {
  	F_MARK = 1,
  	V_MARK = 2,
  	ANOTHER = 3,
  	OK = 0,
	INCORRECT_MATRIX = 1,
	CALC_ERROR = 2,
	MALLOC_FAILED = 3
} type_t;

// typedef enum type_t {
// 	OK = 0;
// 	INCORRECT_MATRIX = 1;
// 	CALC_ERROR = 2;
// 	MALLOC_FAILED = 3;
// } type_t;

typedef struct Matrix {
	double **matrix;
	int rows;
	int cols;
} matrix_t;

typedef struct facets {
	int *vertexes;
	int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
	matrix_t matrix_3d;
	polygon_t *polygons;
	unsigned int count_of_vert; // remove later for tests
	unsigned int count_of_face; // remove later for tests
} data;

typedef struct count {
	unsigned int count_of_vertexes;
	unsigned int count_of_facets;
	int error_mark;
} count;

data parser(char* fileName);
int check_string(char *str);
count count_of_vertexes_and_facets(char* fileName);
int s21_create_matrix(const int rows, matrix_t *result);


