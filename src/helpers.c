#include "parser.h"

void array_of_coord(double* mas1, database matrix) {
    int n = 0;
    for (int i = 1; i < matrix.count_polygons+1; i++) {
        for (int j = 1; j < 4; j++) {
            for (int k = 0; k < 3; k++) {
                mas1[n] = matrix.matrix_3d.matrix[matrix.polygons[i].vertexes[j]][k];
                n++;
            }
            if (j != 1) {
                for (int k = 0; k < 3; k++) {
                    mas1[n] = matrix.matrix_3d.matrix[matrix.polygons[i].vertexes[j]][k];
                    n++;
                }
            }
        }
        for (int k = 0; k < 3; k++) {
            mas1[n] = matrix.matrix_3d.matrix[matrix.polygons[i].vertexes[1]][k];
            n++;
        }
    }
}