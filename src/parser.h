#include <stdio.h>
#include <stdlib.h>

typedef enum type_t {
  F_MARK = 1,
  V_MARK = 2,
  ANOTHER = 3
} type_t;

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
	int count_of_vertexes;
	int count_of_facets;
	matrix_t matrix_3d;
	polygon_t *polygons;
} data;

data parser(char *argv);
int check_string(char *str);



