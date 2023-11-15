#include <stdio.h>
#include <string.h>
#include "algos.h"
#include "lib.h"

int rpath(Map *map, int R, int C)
{
    printf("%d, %c\n", GETPOS(map, 3, 3), map->cells[GETPOS(map, 3, 3)]);
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
