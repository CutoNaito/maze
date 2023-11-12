#ifndef __LIB_
#define __LIB_

#include <stdio.h>

typedef struct {
    int rows;
    int cols;
    unsigned char *cells;
} Map;

char *convert_to_bin(int n);
void help();
void remove_occurs(char *str, char c);
int start(char *direction, int R, int C, char *filename);
int test(char *filename);
int translate_pos();

#endif
