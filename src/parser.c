#include "parser.h"

int main() {
    // int fg = argc;
    data d = {0};
    count c = {0};
    d = parser("cube.obj");
    for (unsigned int i = 1; i < d.count_of_vert + 1; i++) {
        printf("%f ", d.matrix_3d.matrix[i][0]);
        printf("%f ", d.matrix_3d.matrix[i][1]);
        printf("%f\n", d.matrix_3d.matrix[i][2]);
    }
    return 0;
}

data parser(char* fileName) {
    char v;
    data d = {0};
    matrix_t A = {0};
    char *str = calloc(BUFFER_SIZE, sizeof(char));;
    FILE *file;
    unsigned int vert;
    unsigned int face;
    // d.polygons.vertexes = calloc(4096, sizeof(double));
    count c = count_of_vertexes_and_facets(fileName);
    d.count_of_vert = c.count_of_vertexes;
    printf("%d\n", c.count_of_vertexes);
    d.count_of_face = c.count_of_facets;
    int i = 1;
    if (s21_create_matrix(d.count_of_vert, &d.matrix_3d)) {
        printf("create matrix faild\n");
    } else {
        if ((file = fopen(fileName, "r")) != NULL) {
            while (feof(file) == 0) {
                if (fgets (str, BUFFER_SIZE, file)!=NULL) {
                    printf("%s", str);
                    if (check_string(str) == V_MARK) {
                        sscanf(str, "%c %lf %lf %lf", &v, &d.matrix_3d.matrix[i][0], &d.matrix_3d.matrix[i][1], 
                        &d.matrix_3d.matrix[i][2]);
                        i++;
                    } else if (check_string(str) == F_MARK) {

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

int check_string(char *str) {
    int temp;
    if (str[0] == 'v') {
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
                if (str[0] == 'v') {
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

// data add_to_matrix
