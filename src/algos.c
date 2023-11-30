#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "algos.h"
#include "lib.h"

int rpath(Map *map, int R, int C)
{
    /* Correcting values to actual numbers */
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

    /* Initial position */
    int prev = start_border(map, R, C, 1);
    int current = GETPOS(map, R, C);

    /* Checking if the cell is a border */
    if (prev == -1) {
        return 0;
    }

    do {
        /* checks if the cell has a bottom or top border */
        /* 0 = top, 1 = bottom */
        int has_bottom_border = ((reverse_pos(map, current)[0]) + (reverse_pos(map, current)[1])) % 2;
        switch (prev) {
        case 0:
            if (has_bottom_border) {
                Cell *cell = convert_to_cell(current);

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
                Cell *cell = convert_to_cell(current);

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
                Cell *cell = convert_to_cell(current);

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
                Cell *cell = convert_to_cell(current);

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
                Cell *cell = convert_to_cell(current);

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
                Cell *cell = convert_to_cell(current);
                
                /* Left border closed, right border open */
                if (cell->left == 1 && cell->right == 0) {
                    RIGHT(current);
                    prev = 0;

                /* Left border open */
                } else if (cell->left == 0) {
                    LEFT(current);
                    prev = 1;

                /* Right border closed && Top border open */
                } else if (cell->right == 1 && cell->middle == 0) {
                    UP(current, map);
                    prev = 2;
                }

                if (cell != NULL)
                    free(cell);
            }

            break;
        }
    } while (!is_exit_cell(map, reverse_pos(map, current)[0], reverse_pos(map, current)[1]));

    return 0;
}

int lpath(Map *map, int R, int C)
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
    if (validate_start(map, R, C) == 0) {
        fprintf(stderr, "Error: Start coordinates are not a wall.\n");
        return 0;
    }

    /* Initial position */
    int prev = start_border(map, R, C, 1);
    int current = GETPOS(map, R, C);

    /* Checking if the cell is a border */
    if (prev == -1) {
        return 0;
    }

    do {
        /* checks if the cell has a bottom or top border */
        /* 0 = top, 1 = bottom */
        int has_bottom_border = ((reverse_pos(map, current)[0]) + (reverse_pos(map, current)[1])) % 2;
        printf("%d, %d\n", reverse_pos(map, current)[0] + 1, reverse_pos(map, current)[1] + 1);
        switch (prev) {
            case 0:
                if (has_bottom_border) {
                    Cell *cell = convert_to_cell(current);

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
                    Cell *cell = convert_to_cell(current);

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
                    Cell *cell = convert_to_cell(current);

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
                    Cell *cell = convert_to_cell(current);

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
                    Cell *cell = convert_to_cell(current);

                    /* Right border closed, left border open */
                    if (cell->right == 0 && cell->left == 1) {
                        RIGHT(current);
                        prev = 0;

                        /* Right border open */
                    } else if (cell->left == 0) {
                        LEFT(current);
                        prev = 1;

                        /* Left border closed, bottom border open */
                    } else if (cell->right == 1 && cell->middle == 0) {
                        DOWN(current, map);
                        prev = 2;
                    }

                    if (cell != NULL)
                        free(cell);
                } else {
                    Cell *cell = convert_to_cell(current);

                    /* Left border closed, right border open */
                    if (cell->left == 0 && cell->right == 1) {
                        LEFT(current);
                        prev = 1;

                        /* Left border open */
                    } else if (cell->right == 0) {
                        RIGHT(current);
                        prev = 0;

                        /* Right border closed && Top border open */
                    } else if (cell->left == 1 && cell->middle == 0) {
                        UP(current, map);
                        prev = 2;
                    }

                    if (cell != NULL)
                        free(cell);
                }

                break;
        }
    } while (!is_exit_cell(map, reverse_pos(map, current)[0], reverse_pos(map, current)[1]));

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

int validate_start(Map *map, int r, int c)
{
    if (r == 0 && c == 0) /* Top left */ {
        return 1;
    }

    if (r == 0 && c == map->cols - 1) /* Top right */ {
        return 1;
    }

    if (r == map->rows - 1 && c == 0) /* Bottom left */ {
        return 1;
    }

    if (r == map->rows - 1 && c == map->cols - 1) /* Bottom right */ {
        return 1;
    }

    return 0;
}
