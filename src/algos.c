#include <stdio.h>
#include <string.h>
#include "algos.h"
#include "lib.h"

int rpath(Map *map, int R, int C)
{
    /* Checking if the coordinates are valid */
    if (R < 0 || C < 0 || R >= map->rows || C >= map->cols) {
        fprintf(stderr, "Error: Invalid start coordinates.\n");
        return 0;
    }

    /* Checking if the cell is a wall */
    if (R != 1 || C != 1 && R != map->rows - 1 || C != map->cols - 1) {
        fprintf(stderr, "Error: Start coordinates are not a wall.\n");
        return 0;
    }

    int steps = 0;
    return 0;
}

int lpath(Map *map, int R, int C)
{
    (void)map;
    (void)R;
    (void)C;
    return 0;
}

int start_border(Map *map, int r, int c, int leftright)
{
    /* Left = 0, Right = 1 */

    /* Borders: 
     * 0 = left
     * 1 = right
     * 2 = middle */
    switch (leftright) {
    case 0:
        if (r % 2 == 1 && c == 1) /* Entry from left, odd row */ {
            return 0;
        }

        if (r % 2 == 1 && c == map->cols && map->cols % 2 == 1) /* Entry from right, odd row, odd row count */ {
            return 2;
        }

        if (r % 2 == 0 && c == 1) /* Entry from left, even row */ {
            return 1;
        }

        if (r % 2 == 0 && c == map->cols && map->cols % 2 == 0) /* Entry from right, even row, even col count */ {
            return 2;
        }

        if (r % 2 == 1 && c == map->cols && map->cols % 2 == 0) /* Entry from right, odd row, even col count */ {
            return 0;
        }

        if (r % 2 == 0 && c == map->cols && map->cols % 2 == 1) /* Entry from right, even row, odd col count */ {
            return 0;
        }

        if (r == 1 && c % 2 == 1) /* Entry from top, odd col */ {
            return 0;
        }

        if (r == 1 && c % 2 == 0) /* Entry from top, even col */ {
            fprintf(stderr, "Error: Invalid start coordinates.\n");
            return -1;
        }

        if (r == map->rows && c % 2 == 1 && map->rows % 2 == 1) /* Entry from bottom, odd col, odd row count */ {
            return 0;
        }

        if (r == map->rows && c % 2 == 0 && map->rows % 2 == 0) /* Entry from bottom, even col, even row count */ {
            return 0;
        }

        if (r == map->rows && c % 2 == 1 && map->rows % 2 == 0) /* Entry from bottom, odd col, even row count */ {
            fprintf(stderr, "Error: Invalid start coordinates.\n");
            return -1;
        }

        if (r == map->rows && c % 2 == 0 && map->rows % 2 == 1) /* Entry from bottom, even col, odd row count */ {
            fprintf(stderr, "Error: Invalid start coordinates.\n");
            return -1;
        }
    }
}
