#include "utils.h"
#include <string.h>
#include <stdio.h>

int parse_algorithm(const char *name) {
    if (strcmp(name, "alg1") == 0)  return 1;  
    if (strcmp(name, "alg2") == 0) return 2;  
    return -1;
}

int count_file_lines(FILE *file) {
    if (file == NULL) return 0;
    int lines = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    //ważny rewind żeby czytać znowu bo na tym się wyjebałem na kolos JIMP1
    rewind(file);
    return lines;
}