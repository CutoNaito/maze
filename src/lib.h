#ifndef __LIB_
#define __LIB_

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int rows;
    int cols;
    unsigned char *cells;
} Map;

typedef struct {
    int left;
    int right;
    int middle;
} Cell;

char *convert_to_bin(int n);
Cell *convert_to_cell(int n);
int getpos(Map *map, int r, int c);
void help();
bool isborder(Map *map, int r, int c, int border);
void remove_occurs(char *str, char c);
int start(char *direction, int R, int C, char *filename);
int test(char *filename);
int translate_pos();

#endif
