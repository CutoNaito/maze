#include <stdio.h>
#include <string.h>
#include "algos.h"
#include "lib.h"

int rpath(Map *map, int R, int C)
{
    /* Correcting values to actual numbers (??) */
    R = R - 1 - 0x30;
    C = C - 1 - 0x30;

    /* Checking if the coordinates are valid */
    if (R < 0 || C < 0 || R >= map->rows || C >= map->cols) {
        fprintf(stderr, "Error: Invalid start coordinates.\n");
        return 0;
    }

    /* Checking if the cell is a wall */
    if ((R != 1 || C != 1) && (R != map->rows - 1 || C != map->cols - 1)) {
        fprintf(stderr, "Error: Start coordinates are not a wall.\n");
        return 0;
    }

    int prev = start_border(map, R, C, 1);
    int current = GETPOS(map, R, C);

    /* Checking if the cell is a border */
    if (prev == -1) {
        return 0;
    }

    /* Checks if the cell has a bottom or top border */
    /* 0 = top, 1 = bottom */
    int has_bottom_border = (R + C) % 2;

    while (!is_exit_cell(map, reverse_pos(map, current)[0], reverse_pos(map, current)[1])) {
        switch (prev) {
        case 0:
            if (has_bottom_border) {
                Cell *cell = convert_to_cell(current);
                if (cell->middle == 1) {
                    current++;
                }
            }

            break;

        case 1:
            break;

        case 2:
            break;
        }

        int steps = 0;
        (void)steps;
        return 0;
    }

    return 0;
}

int lpath(Map *map, int R, int C)
{
    /* Correcting values to actual numbers (??) */
    R = R - 1 - 0x30;
    C = C - 1 - 0x30;

    printf("%d\n", GETPOS(map, R, C));
    printf("%d %d\n", reverse_pos(map, GETPOS(map, R, C))[0], reverse_pos(map, GETPOS(map, R, C))[1]);
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

    return 0;
}
