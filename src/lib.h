#ifndef __LIB_
#define __LIB_

#include <stdio.h>

typedef struct {
    int rows;
    int cols;
    unsigned char *cells;
} Map;

int translate_pos();
void help();
void remove_occurs(char *str, char c);
int start(char *direction, int R, int C, char *filename);
void test(char *arg, char *filename);

#endif
