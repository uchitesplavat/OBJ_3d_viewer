#include "parser.h"

data parser(char *argv) {
    data d = {0};
    count c = {0};
    matrix_t A = {0};
    char str[4096];
    FILE *file;
    unsigned int vert;
    unsigned int face;
    count_of_vertexes_and_facets(argv);
    vert = c.count_of_vertexes;
    face = c.count_of_facets;
    if (s21_create_matrix(vert, &A)) {
        printf("create matrix faild\n");
    } else {
        if ((file = fopen(argv, "r")) != NULL) {
            while (feof(file) == 0) {
                if (fgets (str, 4096, file)!=NULL) {
                    if (check_string(str) == V_MARK) {

                    } else if (check_string(str) == F_MARK) {
                        
                    }
                }
            }
        } else {
            printf("file not found\n");
        }
    }
    fclose(file);
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

count count_of_vertexes_and_facets(char *argv) {
    count count = {0};
    unsigned int vert = 0;
    unsigned int face = 0;
    char str[4096];
    FILE *file;
    if ((file = fopen(argv, "r")) != NULL) {
        while (feof(file) == 0) {
            if (fgets (str, 4096, file)!=NULL) {
                if (str[0] == 'v') {
                    count.count_of_vertexes++;
                } else if (str[0] == 'f') {
                    count.count_of_facets++;
                }
            }
        }

    } else {
        printf("file not found\n");
    }
    fclose(file);
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
