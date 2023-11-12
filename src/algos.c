#include <stdio.h>
#include <string.h>
#include "algos.h"
#include "lib.h"

int rpath(Map *map, int R, int C)
{
    printf("%s\n", convert_to_bin(map->cells[0]));

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
