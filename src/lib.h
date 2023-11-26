#ifndef __LIB_
#define __LIB_

#define GETPOS(map, r, c) c + ((map->cols/2+1) * r)
#define ROW_REMAINDER(r) r % 2

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
int get_border(Map *map, int r, int c);
void help();
bool isborder(Map *map, int r, int c, int border);
int is_exit_cell(Map *map, int r, int c);
void remove_occurs(char *str, char c);
int *reverse_pos(Map *map, int pos);
int start(char *direction, int R, int C, char *filename);
int test(char *filename);
int translate_pos();

#endif
