#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000000
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
  double** matrix;
  int rows;
  int cols;
} matrix_t;

typedef struct facets {
  int* vertexes;
  int* tex;
  int* normals;
  int numbers_of_vertexes_in_facets;  // count of vert in f
} polygon_t;

typedef struct data {
  matrix_t matrix_3d;
  polygon_t* polygons;
  unsigned int count_of_vert;  // remove later for tests
  unsigned int count_of_face;  // remove later for tests
  int count_polygons;
} data;

typedef struct count {
  unsigned int count_of_vertexes;
  unsigned int count_of_facets;
  int error_mark;
  unsigned int count_of_lines_for_memory;
} count;

data parser(char* fileName);
int check_string(const char* str);
count count_of_vertexes_and_facets(const char* fileName);
int s21_create_matrix(const int rows, matrix_t* result);
const char* parse_int(const char* ptr, int* val);
int is_whitespace(char c);
int is_newline(char c);
const char* skip_whitespace(const char* ptr);
int is_digit(char c);
unsigned long file_size(void* file);
size_t file_read(void* file, void* dst, size_t bytes);
void file_close(void* file);
void* file_open(const char* path);