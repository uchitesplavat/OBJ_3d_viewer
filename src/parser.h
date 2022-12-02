#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// string size
#define BUFFER_SIZE 70000
#define isspace(c) (c) == ' '

// power for exp
#define MAX_POWER 20

#ifdef __cplusplus
extern "C"
#endif

    // errors
    typedef enum type_t {
      F_MARK = 1,
      V_MARK = 2,
      ANOTHER = 3,
      OK = 0,
      INCORRECT_MATRIX = 1,
      CALC_ERROR = 2,
      MALLOC_FAILED = 3
    } type_t;

// V struct
typedef struct Matrix {
  double** matrix;
  int rows;
  int cols;
} matrix_t;

// F struct
typedef struct facets {
  int* vertexes;
  int* tex;
  int* normals;
  int numbers_of_vertexes_in_facets;  // count of vert in f
} polygon_t;

// main structure with V and F
typedef struct database {
  matrix_t matrix_3d;
  polygon_t* polygons;
  unsigned int count_of_vert;  // remove later for tests
  unsigned int count_of_face;  // remove later for tests
  int count_polygons;
} database;

typedef struct count {
  unsigned int count_of_vertexes;
  unsigned int count_of_facets;
  int error_mark;
  unsigned int count_of_lines_for_memory;
} count;

// psrser
database parser(char* fileName);
database case_F(char* str, struct database d, int counter_polygons);
char* parse_float_numbers_for_V(char* str, float* val);
database parse_vertex(char* str, struct database d, int index_string_number);
int check_string(char* str);
count count_of_vertexes_and_facets(const char* fileName);

// help funcs
int s21_create_matrix(const int rows, matrix_t* result);
char* parse_int(char* ptr, int* val);
int is_whitespace(char c);
int is_newline(char c);
char* skip_whitespace(char* ptr);
int is_digit(char c);
int is_exponent(char c);

// file
unsigned long file_size(void* file);
size_t file_read(void* file, void* dst, size_t bytes);
void file_close(void* file);
void* file_open(const char* path);

// memory alloc
void* memory_realloc(void* ptr, size_t bytes);

// memory dealloc
void memory_dealloc_char(char* ptr);
void memory_dealloc_double(double* ptr);
void memory_dealloc_int(int* ptr);
void memory_dealloc_polygon_t(polygon_t* ptr);
void s21_remove_matrix(matrix_t* const A);
void free_polygons(struct database d);

// helpers
void array_of_coord(double* mas1, database matrix);