#include <stdio.h>
#include <string.h>
#include "algos.h"
#include "lib.h"

int rpath(Map *map, int R, int C)
{
    printf("%d, %c\n", getpos(map, 2, 3), map->cells[getpos(map, 2, 3)]);
    (void)R;
    (void)C;
    return 0;
}

int lpath(Map *map, int R, int C)
{
    (void)map;
    (void)R;
    (void)C;
    return 0;
}
