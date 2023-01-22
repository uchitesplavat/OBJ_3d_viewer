#include "parser.h"

// int main() {
//     view_data data1 = {0};
//     data1.xbc = 1.9;
//     save_data(data1);
//     return 0;
// }

void save_data(view_data data1) {
  FILE *file;
  if ((file = fopen("../view_config.txt", "w")) != NULL) {
    fprintf(
        file,
        "%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%d\n%lf\n%d\n%d\n",
        data1.xbc, data1.ybc, data1.zbc, data1.xl, data1.yl, data1.zl, data1.xv,
        data1.yv, data1.zv, data1.lWidth, data1.lineMark, data1.pointSize,
        data1.pointMark, data1.camMark);
    fclose(file);
  } else {
    printf("file for save data not found\n");
  }
}

void open_data(view_data *data1) {
  FILE *file;
  int count = 0;
  char str[20];
  if ((file = fopen("../view_config.txt", "r")) != NULL) {
    while (feof(file) == 0) {
      fgets(str, 20, file);
      count++;
      if (count == 1) {
        data1->xbc = atof(str);
      } else if (count == 2) {
        data1->ybc = atof(str);
      } else if (count == 3) {
        data1->zbc = atof(str);
      } else if (count == 4) {
        data1->xl = atof(str);
      } else if (count == 5) {
        data1->yl = atof(str);
      } else if (count == 6) {
        data1->zl = atof(str);
      } else if (count == 7) {
        data1->xv = atof(str);
      } else if (count == 8) {
        data1->yv = atof(str);
      } else if (count == 9) {
        data1->zv = atof(str);
      } else if (count == 10) {
        data1->lWidth = atof(str);
      } else if (count == 11) {
        data1->lineMark = atoi(str);
      } else if (count == 12) {
        data1->pointSize = atof(str);
      } else if (count == 13) {
        data1->pointMark = atoi(str);
      } else if (count == 14) {
        data1->camMark = atoi(str);
      }
    }

    fclose(file);
  } else {
    printf("file for save data not found\n");
  }
}
