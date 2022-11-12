#include "parser.h"

data parser(char *argv) {
    char str[4096];
    FILE *file;
    if ((file = fopen(argv, "r")) != NULL) {
        while (feof(file) == 0) {
            if (fgets (str, 4096, file)!=NULL ) {
                if (check_string(str) == V_MARK) {

                } else if (check_string(str) == F_MARK) {
                    
                }
            }
        }
    } else {
        printf("file not found\n");
    }
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


