#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "algos.h"
#include "lib.h"

int rpath(Map *map, int R, int C)
{
    /* Correcting values to actual numbers (??) */
    R = R - 1 - 0x30;
    C = C - 1 - 0x30;

    /* Checking if the cell is a wall */
    if (!is_exit_cell(map, R, C)) {
        fprintf(stderr, "Error: Start coordinates are not a wall.\n");
        return 0;
    }

    /* Initial position */
    int prev = start_border(map, R, C);
    int current = GETPOS(map, R, C);

    /* Checking if the cell is a border */
    if (prev == -1) {
        return 0;
    }

    int steps = 0;

    do {
        /* checks if the cell has a bottom or top border */
        /* 0 = top, 1 = bottom */
        int has_bottom_border = ((reverse_pos(map, current)[0]) + (reverse_pos(map, current)[1])) % 2;

        printf("%d,%d\n", reverse_pos(map, current)[0] + 1, reverse_pos(map, current)[1] + 1);
        steps++;

        switch (prev) {
        case 0:
            if (has_bottom_border) {
                Cell *cell = convert_to_cell(map->cells[current] - 0x30);

                /* Bottom border closed, right border open */
                if (cell->middle == 1 && cell->right == 0) {
                    RIGHT(current);
                    prev = 0;

                /* Bottom border open */
                } else if (cell->middle == 0) {
                    DOWN(current, map);
                    prev = 2;

                /* Right border closed, left border open */
                } else if (cell->right == 1 && cell->left == 0) {
                    LEFT(current);
                    prev = 1;
                }

                if (cell != NULL)
                    free(cell);
            } else {
                Cell *cell = convert_to_cell(map->cells[current] - 0x30);

                /* Top border open, right border closed */
                if (cell->right == 1 && cell->middle == 0) {
                    UP(current, map);
                    prev = 2;
                }

                /* Right border open */
                else if (cell->right == 0) {
                    RIGHT(current);
                    prev = 0;
                }

                /* Top border closed, left border open */
                else if (cell->middle == 1 && cell->left == 0) {
                    LEFT(current);
                    prev = 1;
                }

                if (cell != NULL)
                    free(cell);
            }

            break;

        case 1:
            if (has_bottom_border) {
                Cell *cell = convert_to_cell(map->cells[current] - 0x30);

                /* Left border closed, bottom border open */
                if (cell->left == 1 && cell->middle == 0) {
                    DOWN(current, map);
                    prev = 2;

                /* Left border open */
                } else if (cell->left == 0) {
                    LEFT(current);
                    prev = 1;

                /* Bottom border closed, right border open */
                } else if (cell->middle == 1 && cell->right == 0) {
                    RIGHT(current);
                    prev = 0;
                }

                if (cell != NULL)
                    free(cell);
            
            } else {
                Cell *cell = convert_to_cell(map->cells[current]);

                /* Top border closed, left border open */
                if (cell->middle == 1 && cell->left == 0) {
                    LEFT(current);
                    prev = 1;

                /* Top border open */
                } else if (cell->middle == 0) {
                    UP(current, map);
                    prev = 2;

                /* Left border closed, right border open */
                } else if (cell->left == 1 && cell->right == 0) {
                    RIGHT(current);
                    prev = 0;
                }

                if (cell != NULL)
                    free(cell);
            }

            break;

        case 2:
            if (has_bottom_border) {
                Cell *cell = convert_to_cell(map->cells[current]);

                /* Right border closed, left border open */
                if (cell->right == 1 && cell->left == 0) {
                    LEFT(current);
                    prev = 1;

                /* Right border open */
                } else if (cell->right == 0) {
                    RIGHT(current);
                    prev = 0;

                /* Left border closed, bottom border open */
                } else if (cell->left == 1 && cell->middle == 0) {
                    DOWN(current, map);
                    prev = 2;
                }

                if (cell != NULL)
                    free(cell);
            } else {
                Cell *cell = convert_to_cell(map->cells[current]);
                
                /* Left border closed, right border open */
                if (cell->left == 1 && cell->right == 0) {
                    RIGHT(current);
                    prev = 0;

                /* Left border open */
                } else if (cell->left == 0) {
                    LEFT(current);
                    prev = 1;

                /* Right border closed, top border open */
                } else if (cell->right == 1 && cell->middle == 0) {
                    UP(current, map);
                    prev = 2;
                }

                if (cell != NULL)
                    free(cell);
            }

            break;
        }
    } while (!is_exit_cell(map, reverse_pos(map, current)[0], reverse_pos(map, current)[1]) && !is_out(map, reverse_pos(map, current)[0], reverse_pos(map, current)[1]));

    if (steps > 1)
        printf("%d,%d\n", reverse_pos(map, current)[0] + 1, reverse_pos(map, current)[1] + 1);

    return 0;
}

int lpath(Map *map, int R, int C)
{
    /* Correcting values to actual numbers (??) */
    R = R - 1 - 0x30;
    C = C - 1 - 0x30;

    /* Checking if the cell is a wall */
    if (!is_exit_cell(map, R, C)) {
        fprintf(stderr, "Error: Start coordinates are not a wall.\n");
        return 0;
    }

    /* Initial position */
    int prev = start_border(map, R, C);
    int current = GETPOS(map, R, C);

    /* Checking if the cell is a border */
    if (prev == -1) {
        return 0;
    }

    int steps = 0;

    do {
        /* checks if the cell has a bottom or top border */
        /* 0 = top, 1 = bottom */
        int has_bottom_border = ((reverse_pos(map, current)[0]) + (reverse_pos(map, current)[1])) % 2;
        printf("%d,%d\n", reverse_pos(map, current)[0] + 1, reverse_pos(map, current)[1] + 1);
        steps++;

        switch (prev) {
            case 0:
                if (has_bottom_border) {
                    Cell *cell = convert_to_cell(map->cells[current] - 0x30);

                    /* Bottom border open, right border closed */
                    if (cell->middle == 0 && cell->right == 1) {
                        DOWN(current, map);
                        prev = 2;

                    /* Right border open */
                    } else if (cell->right == 0) {
                        RIGHT(current);
                        prev = 0;

                    /* Bottom border closed, left border open */
                    } else if (cell->middle == 1 && cell->left == 0) {
                        LEFT(current);
                        prev = 1;
                    }

                    if (cell != NULL)
                        free(cell);
                } else {
                    Cell *cell = convert_to_cell(map->cells[current] - 0x30);

                    /* Top border closed, right border open */
                    if (cell->right == 0 && cell->middle == 1) {
                        RIGHT(current);
                        prev = 0;
                    }

                    /* Top border open */
                    else if (cell->middle == 0) {
                        UP(current, map);
                        prev = 2;
                    }

                    /* Right border closed, left border open */
                    else if (cell->right == 1 && cell->left == 0) {
                        LEFT(current);
                        prev = 1;
                    }

                    if (cell != NULL)
                        free(cell);
                }

                break;

            case 1:
                if (has_bottom_border) {
                    Cell *cell = convert_to_cell(map->cells[current] - 0x30);

                    /* Left border open, bottom border closed */
                    if (cell->left == 0 && cell->middle == 1) {
                        LEFT(current);
                        prev = 1;

                    /* Bottom border open */
                    } else if (cell->middle == 0) {
                        DOWN(current, map);
                        prev = 2;

                    /* Left border closed, right border open */
                    } else if (cell->left == 1 && cell->right == 0) {
                        RIGHT(current);
                        prev = 0;
                    }

                    if (cell != NULL)
                        free(cell);

                } else {
                    Cell *cell = convert_to_cell(map->cells[current]);

                    /* Top border closed, left border open */
                    if (cell->middle == 1 && cell->left == 0) {
                        LEFT(current);
                        prev = 1;

                    /* Top border open */
                    } else if (cell->middle == 0) {
                        UP(current, map);
                        prev = 2;

                    /* Left border closed, right border open */
                    } else if (cell->left == 1 && cell->right == 0) {
                        RIGHT(current);
                        prev = 0;
                    }

                    if (cell != NULL)
                        free(cell);
                }

                break;

            case 2:
                if (has_bottom_border) {
                    Cell *cell = convert_to_cell(map->cells[current]);

                    /* Right border open, left border closed */
                    if (cell->right == 0 && cell->left == 1) {
                        RIGHT(current);
                        prev = 0;

                    /* Left border open */
                    } else if (cell->left == 0) {
                        LEFT(current);
                        prev = 1;

                    /* Right border closed, bottom border open */
                    } else if (cell->right == 1 && cell->middle == 0) {
                        DOWN(current, map);
                        prev = 2;
                    }

                    if (cell != NULL)
                        free(cell);
                } else {
                    Cell *cell = convert_to_cell(map->cells[current]);

                    /* Left border open, right border closed */
                    if (cell->left == 0 && cell->right == 1) {
                        LEFT(current);
                        prev = 1;

                    /* Right border open */
                    } else if (cell->right == 0) {
                        RIGHT(current);
                        prev = 0;

                    /* Left border closed && Top border open */
                    } else if (cell->left == 1 && cell->middle == 0) {
                        UP(current, map);
                        prev = 2;
                    }

                    if (cell != NULL)
                        free(cell);
                }

                break;
        }
    } while (!is_exit_cell(map, reverse_pos(map, current)[0], reverse_pos(map, current)[1]) && !is_out(map, reverse_pos(map, current)[0], reverse_pos(map, current)[1]));

    if (steps > 1)
        printf("%d,%d\n", reverse_pos(map, current)[0] + 1, reverse_pos(map, current)[1] + 1);

    return 0;
}

int start_border(Map *map, int r, int c)
{
    /* Checks entrance */
    if (c == 0)
        return 0;
    else if (c == map->cols/2 - 1)
        return 1;
    else if (r == 0 && c > 0 && c < map->cols/2 - 1)
        return 2;
    else if (r == map->rows - 1 && c > 0 && c < map->cols/2 - 1)
        return 2;
    else {
        fprintf(stderr, "Error: Start coordinates are not a wall.\n");
        return -1;
    }
}

int is_out(Map *map, int r, int c)
{
    /* Checks if cell is out of the maze borders */
    if (r < 0 || c < 0 || r > map->rows - 1 || c > map->cols/2 - 1) {
        return 1;
    }

    return 0;
}
