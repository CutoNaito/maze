#ifndef __ALGOS_
#define __ALGOS_

#define LEFT(x) x--
#define RIGHT(x) x++
#define UP(x, map) x = x - (map->cols/2+1)
#define DOWN(x, map) x = x + (map->cols/2+1)

#include "lib.h"

int is_out(Map *map, int r, int c);
int rpath(Map *map, int R, int C);
int lpath(Map *map, int R, int C);
int start_border(Map *map, int r, int c);
int validate_start(Map *map, int r, int c);

#endif
