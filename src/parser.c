#include "parser.h"

int main() {
    // int fg = argc;
    data d = {0};
    count c = {0};
    d = parser("Gun.obj");
    // for (unsigned int i = 1; i < d.count_of_vert + 1; i++) {
    //     printf("%f ", d.matrix_3d.matrix[i][0]);
    //     printf("%f ", d.matrix_3d.matrix[i][1]);
    //     printf("%f\n", d.matrix_3d.matrix[i][2]);
    // }
    
    for (int k = 1; k < d.count_polygons + 1; k++) {
        printf("count_polygons ==== %d\n", d.count_polygons);
        for (int g = 1; g < d.polygons[k].numbers_of_vertexes_in_facets + 1; g++) {
            printf("numbers_of_vertexes_in_facets ==== %d\n", d.polygons[k].numbers_of_vertexes_in_facets);
            printf("%d ", d.polygons[k].vertexes[g]);
            printf("%d ", d.polygons[k].tex[g]);
            printf("%d ", d.polygons[k].normals[g]);

            if (g == d.polygons[k].numbers_of_vertexes_in_facets) {
                printf("\n");
            }
        }
    }
    return 0;
}

data parser(char* fileName) {
    int v;
    int t;
    int n;
    char e;
    data d = {0};
    matrix_t A = {0};
    polygon_t P = {0};
    const char *str = calloc(BUFFER_SIZE, sizeof(char));
    FILE *file;
    unsigned int vert;
    unsigned int face;
    // d.polygons.vertexes = calloc(4096, sizeof(double));
    count c = count_of_vertexes_and_facets(fileName);
    d.count_of_vert = c.count_of_vertexes;
    printf("%d\n", c.count_of_vertexes);
    d.count_of_face = c.count_of_facets;
    d.polygons = calloc(c.count_of_facets + 1, sizeof(polygon_t));
    int i = 1;
    if (s21_create_matrix(c.count_of_vertexes, &d.matrix_3d)) {
        printf("create matrix faild\n");
    } else {
        if ((file = fopen(fileName, "r")) != NULL) {
            int counter_polygons = 1;
            // for (int mem_tmp = 0; mem_tmp < BUFFER_SIZE; mem_tmp++) {
            //     d.polygons[counter_polygons].vertexes = calloc(5000, sizeof(int));
            //     d.polygons[counter_polygons].tex = calloc(5000, sizeof(int));
            //     d.polygons[counter_polygons].normals = calloc(5000, sizeof(int));
            // }
            while (feof(file) == 0) {
                if (fgets (str, BUFFER_SIZE, file)!=NULL) {
                    // printf("%s", str);
                    if (check_string(str) == V_MARK) {
                        sscanf(str, "%c %lf %lf %lf", &e, &d.matrix_3d.matrix[i][0], &d.matrix_3d.matrix[i][1], 
                        &d.matrix_3d.matrix[i][2]);
                        i++;
                    } else if (check_string(str) == F_MARK) {
                        int count_vtn = 0; // count v t n combination in one line
                        ++str;
                        str = skip_whitespace(str);
                        d.polygons[counter_polygons].vertexes = calloc(BUFFER_SIZE, sizeof(int));
                        d.polygons[counter_polygons].tex = calloc(BUFFER_SIZE, sizeof(int));
                        d.polygons[counter_polygons].normals = calloc(BUFFER_SIZE, sizeof(int));
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
                                    // count_vtn++;
                                }
                                if (t < 0 || t > 0) {
                                    // realloc(d.polygons[counter_polygons].tex[count_vtn], sizeof(int));
                                    d.polygons[counter_polygons].tex[count_vtn] = t;
                                } else {
                                    // realloc(d.polygons[counter_polygons].tex[count_vtn], sizeof(int));
                                    // d.polygons[counter_polygons].tex = calloc(BUFFER_SIZE, sizeof(int));
                                    d.polygons[counter_polygons].tex[count_vtn] = 0;
                                }
                                if (t < 0 || t > 0) {
                                    // realloc(d.polygons[counter_polygons].normals[count_vtn], sizeof(int));
                                    d.polygons[counter_polygons].normals[count_vtn] = n;
                                } else {
                                    // realloc(d.polygons[counter_polygons].normals[count_vtn], sizeof(int));
                                    // d.polygons[counter_polygons].normals = calloc(BUFFER_SIZE, sizeof(int));
                                    d.polygons[counter_polygons].normals[count_vtn] = 0;
                                }
                                str = skip_whitespace(str);
                                printf("v = %d t = %d n = %d\n", d.polygons[counter_polygons].vertexes[count_vtn],
                                 d.polygons[counter_polygons].tex[count_vtn], d.polygons[counter_polygons].normals[count_vtn]);
                                printf("%d %d %d\n", v, t, n);
                            
                            d.polygons[counter_polygons].numbers_of_vertexes_in_facets = count_vtn;
                        }
                        d.count_polygons = counter_polygons;
                        counter_polygons++;
                    }
                }
            }
        fclose(file);
        } else {
            printf("file not found\n");
        }
    }
    return d;
}

// check string first simbol "f" or "v" in .obj return 1 or 2 and retern 3 for other 

int check_string(const char *str) {
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

count count_of_vertexes_and_facets(char* fileName) {
    count count = {0};
    unsigned int vert = 0;
    unsigned int face = 0;
    char str[4096];
    FILE *file;
    if ((file = fopen(fileName, "r")) != NULL) {
        while (feof(file) == 0) {
            if (fgets (str, 4096, file)!=NULL) {
                if (str[0] == 'v' && str[1] != 'n' && str[1] != 't') {
                    count.count_of_vertexes++;
                    printf("%d\n", count.count_of_vertexes);
                } else if (str[0] == 'f') {
                    count.count_of_facets++;
                    printf("%d\n", count.count_of_facets);
                }
            }
        }

    } else {
        printf("file not found\n");
    }
    fclose(file);
    return count;
}

int s21_create_matrix(const int rows, matrix_t *result) {
  int ret_code = INCORRECT_MATRIX;

  if (rows > 0) {
    result->cols = 3; // x;y;z
    result->rows = rows + 1;
    result->matrix = calloc(rows + 1, sizeof(double *)); // for simple counting (first row - first vert)
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

int is_newline(char c) {
    return (c == '\n');
}

int is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\r');
}

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

const char* skip_whitespace(const char* ptr) {
    while (is_whitespace(*ptr))
        ptr++;

    return ptr;
}

const char* parse_int(const char* ptr, int* val) {
    int sign;
    int num;
    if (*ptr == '-') {
        sign = -1;
        ptr++;
    }
    else {
        sign = +1;
    }
    num = 0;
    while (is_digit(*ptr)) {
        num = 10 * num + (*ptr++ - '0');
    }
    *val = sign * num;

    return ptr;
}

// data add_to_matrix
