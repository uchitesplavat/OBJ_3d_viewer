#include "parser.h"

int main() {
  data d = {0};
  char name[20] = "models/City.obj\000";
  d = parser(name);

  for (unsigned int i = 1; i < d.count_of_vert + 1; i++) {
    printf("%f ", d.matrix_3d.matrix[i][0]);
    printf("%f ", d.matrix_3d.matrix[i][1]);
    printf("%f\n", d.matrix_3d.matrix[i][2]);
  }

  for (int k = 1; k < d.count_polygons + 1; k++) {
    for (int g = 1; g < d.polygons[k].numbers_of_vertexes_in_facets + 1; g++) {
      printf("%d ", d.polygons[k].vertexes[g]);
      printf("%d ", d.polygons[k].tex[g]);
      printf("%d ", d.polygons[k].normals[g]);

      if (g == d.polygons[k].numbers_of_vertexes_in_facets) {
        printf("\n");
      }
    }
  }

  s21_remove_matrix(&d.matrix_3d);

  for (int k = 1; k < d.count_polygons + 1; k++) {
    memory_dealloc_int(d.polygons[k].vertexes);
    memory_dealloc_int(d.polygons[k].tex);
    memory_dealloc_int(d.polygons[k].normals);
  }

  memory_dealloc_polygon_t(d.polygons);
  return 0;
}

double POWER_10_POSITIVE[MAX_POWER] = {
    1.0e0,  1.0e1,  1.0e2,  1.0e3,  1.0e4,  1.0e5,  1.0e6,
    1.0e7,  1.0e8,  1.0e9,  1.0e10, 1.0e11, 1.0e12, 1.0e13,
    1.0e14, 1.0e15, 1.0e16, 1.0e17, 1.0e18, 1.0e19,
};

double POWER_10_NEGATIVE[MAX_POWER] = {
    1.0e0,   1.0e-1,  1.0e-2,  1.0e-3,  1.0e-4,  1.0e-5,  1.0e-6,
    1.0e-7,  1.0e-8,  1.0e-9,  1.0e-10, 1.0e-11, 1.0e-12, 1.0e-13,
    1.0e-14, 1.0e-15, 1.0e-16, 1.0e-17, 1.0e-18, 1.0e-19,
};

data parser(char* fileName) {
  //  char e;
  data d = {0};
  char* str = NULL;
  str = (memory_realloc(str, BUFFER_SIZE * sizeof(char)));
  char* tmp = str;
  FILE* file;
  count c = count_of_vertexes_and_facets(fileName);
  d.count_of_vert = c.count_of_vertexes;
  d.count_of_face = c.count_of_facets;
  int index_string_number = 1;
  if (s21_create_matrix(c.count_of_vertexes, &d.matrix_3d)) {
    printf("create matrix failed\n");
  } else {
    if ((file = file_open(fileName)) != NULL) {
      unsigned long size = file_size(file);
      d.polygons = (memory_realloc(d.polygons,
                                   c.count_of_facets * 2 * sizeof(polygon_t)));
      printf("file size ====== %ld\n", size);
      int counter_polygons = 1;
      //      file_read(file, dst, size)
      while (feof(file) == 0) {
        //          printf("count of while === %d\n", counter_polygons++);
        if (fgets(str, BUFFER_SIZE, file) != NULL) {
          if (check_string(str) == V_MARK) {  // check V line
            d = parse_vertex(str, d, index_string_number);
            index_string_number++;
          } else if (check_string(str) == F_MARK) {  // check F line
            d = case_F(str, d, counter_polygons);
            counter_polygons++;
          }
        }
        str = tmp;
      }
      file_close(file);
      memory_dealloc_char(str);
    } else {
      printf("file not found\n");
    }
  }
  return d;
}

char* parse_float_numbers_for_V(char* str, float* val) {
  double sign;
  double num;
  double fra;
  double div;
  unsigned int eval;
  const double* powers;

  str = skip_whitespace(str);

  switch (*str) {
    case '+':
      sign = 1.0;
      str++;
      break;

    case '-':
      sign = -1.0;
      str++;
      break;

    default:
      sign = 1.0;
      break;
  }
  num = 0.0;
  while (is_digit(*str)) num = 10.0 * num + (double)(*str++ - '0');
  if (*str == '.') str++;
  fra = 0.0;
  div = 1.0;
  while (is_digit(*str)) {
    fra = 10.0 * fra + (double)(*str++ - '0');
    div *= 10.0;
  }
  num += fra / div;
  if (is_exponent(*str)) {
    str++;

    switch (*str) {
      case '+':
        powers = POWER_10_POSITIVE;
        str++;
        break;

      case '-':
        powers = POWER_10_NEGATIVE;
        str++;
        break;

      default:
        powers = POWER_10_POSITIVE;
        break;
    }
    eval = 0;
    while (is_digit(*str)) eval = 10 * eval + (*str++ - '0');
    num *= (eval >= MAX_POWER) ? 0.0 : powers[eval];
  }
  *val = (float)(sign * num);
  return str;
}

data parse_vertex(char* str, struct data d, int index_string_number) {
  unsigned int i;
  float v;
  str++;
  for (i = 0; i < 3; i++) {
    str = parse_float_numbers_for_V(str, &v);
    d.matrix_3d.matrix[index_string_number][i] = v;
  }
  return d;
}

data case_F(char* str, struct data d, int counter_polygons) {
  int count_vtn = 0;  // count v t n combination in one line
  ++str;
  str = skip_whitespace(str);
  int tmp_string_length = strlen(str);
  d.polygons[counter_polygons].vertexes =
      (memory_realloc(0, tmp_string_length * sizeof(int)));
  d.polygons[counter_polygons].tex =
      (memory_realloc(0, tmp_string_length * sizeof(int)));
  d.polygons[counter_polygons].normals =
      (memory_realloc(0, tmp_string_length * sizeof(int)));
  while (!is_newline(*str)) {
    int v = 0;
    int t = 0;
    int n = 0;
    str = parse_int(str, &v);
    if (*str == '/') {
      str++;
      if (*str != '/') {
        str = parse_int(str, &t);
      }
      if (*str == '/') {
        str++;
        str = parse_int(str, &n);
      }
    }
    count_vtn++;
    if (v < 0 || v > 0) {
      d.polygons[counter_polygons].vertexes[count_vtn] = v;
    }
    if (t < 0 || t > 0) {
      d.polygons[counter_polygons].tex[count_vtn] = t;
    } else {
      d.polygons[counter_polygons].tex[count_vtn] = 0;
    }
    if (t < 0 || t > 0) {
      d.polygons[counter_polygons].normals[count_vtn] = n;
    } else {
      d.polygons[counter_polygons].normals[count_vtn] = 0;
    }
    str = skip_whitespace(str);

    d.polygons[counter_polygons].numbers_of_vertexes_in_facets = count_vtn;
  }
  d.count_polygons = counter_polygons;

  return d;
}

// check string first symbol "f" or "v" in .obj return 1 or 2 and return 3 for
// other

int check_string(char* str) {
  int temp;
  if (str[0] == 'v' && str[1] != 'n' && str[1] != 't') {
    temp = V_MARK;
  } else if (str[0] == 'f') {
    temp = F_MARK;
  } else {
    temp = ANOTHER;
  }
  return temp;
}

// count vertexes and facets for easy memory work

count count_of_vertexes_and_facets(const char* fileName) {
  count count = {0};
  count.count_of_lines_for_memory = 0;
  FILE* file;
  char* str = NULL;
  if ((file = file_open(fileName)) != NULL) {
    while (feof(file) == 0) {
      str = calloc(BUFFER_SIZE, sizeof(char));
      if (fgets(str, BUFFER_SIZE, file) != NULL) {
        if (str[0] == 'v' && str[1] != 'n' && str[1] != 't') {
          count.count_of_vertexes++;
        } else if (str[0] == 'f') {
          count.count_of_facets++;
        }
        count.count_of_lines_for_memory++;
      }
      memory_dealloc_char(str);
    }
    file_close(file);
  } else {
    printf("file not found\n");
  }
  return count;
}

int s21_create_matrix(const int rows, matrix_t* result) {
  int ret_code = INCORRECT_MATRIX;
  result->matrix = NULL;
  if (rows > 0) {
    result->cols = 3;  // x;y;z
    result->rows = rows + 1;
    result->matrix = calloc(
        rows + 1,
        sizeof(double*));  // for simple counting (first row - first vert)
    ret_code = MALLOC_FAILED;

    if (result->matrix) {
      for (int i = 0; i < rows + 1; i++) {
        result->matrix[i] = calloc(3, sizeof(double));
        if (!result->matrix[i]) break;
      }
      ret_code = OK;
    }
  }

  return (ret_code);
}

void* file_open(const char* path) { return fopen(path, "rb"); }

size_t file_read(void* file, void* dst, size_t bytes) {
  FILE* f;
  f = (FILE*)(file);
  return fread(dst, 1, bytes, f);
}

unsigned long file_size(void* file) {
  FILE* f;
  long p;
  long n;
  f = (FILE*)(file);
  p = ftell(f);
  fseek(f, 0, SEEK_END);
  n = ftell(f);
  fseek(f, p, SEEK_SET);
  if (n > 0)
    return (unsigned long)(n);
  else
    return 0;
}

void file_close(void* file) {
  FILE* f;
  f = (FILE*)file;
  fclose(f);
}

int is_newline(char c) { return (c == '\n'); }

int is_whitespace(char c) { return (c == ' ' || c == '\t' || c == '\r'); }

int is_digit(char c) { return (c >= '0' && c <= '9'); }

char* skip_whitespace(char* ptr) {
  while (is_whitespace(*ptr)) ptr++;

  return ptr;
}

char* parse_int(char* ptr, int* val) {
  int sign;
  int num;
  if (*ptr == '-') {
    sign = -1;
    ptr++;
  } else {
    sign = +1;
  }
  num = 0;
  while (is_digit(*ptr)) {
    num = 10 * num + (*ptr++ - '0');
  }
  *val = sign * num;

  return ptr;
}

void s21_remove_matrix(matrix_t* const A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);

    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->cols = 0;
  }
}

int is_exponent(char c) { return (c == 'e' || c == 'E'); }

void* memory_realloc(void* ptr, size_t bytes) { return realloc(ptr, bytes); }

void memory_dealloc_char(char* ptr) { free(ptr); }

void memory_dealloc_int(int* ptr) { free(ptr); }

void memory_dealloc_double(double* ptr) { free(ptr); }

void memory_dealloc_polygon_t(polygon_t* ptr) { free(ptr); }
