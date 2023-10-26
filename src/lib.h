#ifndef __LIB_
#define __LIB_

#include <stdio.h>

typedef struct {
    int rows;
    int cols;
    unsigned char *cells;
} Map;

Map *create_map(FILE *fp);
void help();
void test(char *arg, char *filename);

#endif
