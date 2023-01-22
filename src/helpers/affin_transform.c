#include "../parser.h"

#define ROTATE_VERTEX(arr, i, cos_rotate, sin_rotate)         \
  do {                                                        \
    double x = arr[i] * cos_rotate + arr[i + 1] * sin_rotate; \
    double y = arr[i + 1] * cos_rotate - arr[i] * sin_rotate; \
    arr[i] = x;                                               \
    arr[i + 1] = y;                                           \
  } while (0)

#define ROTATE_VERTEX_X(arr, i, cos_rotate, sin_rotate)       \
  do {                                                        \
    double x = arr[i] * cos_rotate + arr[i + 2] * sin_rotate; \
    double y = arr[i + 2] * cos_rotate - arr[i] * sin_rotate; \
    arr[i] = x;                                               \
    arr[i + 2] = y;                                           \
  } while (0)

#define pidel 3.14159265 / 180

void model_rotation(double* arr, double rotate, int index1, int countVertex) {
    rotate = rotate * pidel;
    double cos_rotate = cos(rotate);
    double sin_rotate = sin(rotate);

    int i;
    if (index1 == 0) {
        i = 1;
        while (i < countVertex) {
            ROTATE_VERTEX(arr, i, cos_rotate, sin_rotate);
            i += 3;
        }
    } else if (index1 == 1) {
        i = 0;
        while (i < countVertex) {
            ROTATE_VERTEX_X(arr, i , cos_rotate, sin_rotate);
            i += 3;
        }
    } else if (index1 == 2) {
        i = 0;
        while (i < countVertex) {
            ROTATE_VERTEX(arr, i + 1, cos_rotate, sin_rotate);
            i += 3;
        }
    }
}
void model_trans (double* arr, double translate, int index, int countVertex) {
    if (index == 0) {
        for (int i = 0; i < countVertex; i+=3) {
            arr[i] += translate;
        }
    } else if (index == 1) {
        for (int i = 1; i < countVertex; i+=3) {
            arr[i] += translate;
        }
    } else if (index == 2) {
        for (int i = 2; i < countVertex; i+=3) {
            arr[i] += translate;
        }
    }
}

void model_scale(double* arr, double scale, int countVertex) {
    for (int i = 0; i < countVertex; i++) {
        arr[i] *= scale;
    }
}
int check_amount(const char *str) {
    char *number_string = "-+0123456789.";
    char *sign = "+-";
    int error_mark = 0;
    int count = 0;
    int count1 = 0;
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (!strchr(number_string, str[i])) {
            error_mark = 1;
        }
        if (strchr(sign, str[i])) {
            count++;
        }
        if (str[i] == '.') {
            count1++;
        }
    }
    if (count > 1 || count1 > 1) {
        error_mark = 1;
    }
    return error_mark;
}

