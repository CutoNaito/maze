#include <stdlib.h>
#include <string.h>
#include "algos.h"
#include "lib.h"

char *convert_to_bin(int n)
{
    /* Converts a decimal number to binary */
    int c, d, count;
    char *pointer;

    count = 0;
    pointer = (char *)malloc(32 + 1);
    if (pointer == NULL) {
        fprintf(stderr, "Error: could not allocate memory.\n");
        return NULL;
    }

    for (c = 31; c >= 0; c--) {
        d = n >> c;

        if (d & 1)
            *(pointer + count) = 1 + '0';
        else
            *(pointer + count) = 0 + '0';

        count++;
    }
    *(pointer + count) = '\0';

    return pointer;
}

Cell *convert_to_cell(int n)
{
    /* Converts a binary string to a Cell structure */
    Cell *cell = malloc(sizeof(Cell));
    if (cell == NULL) {
        fprintf(stderr, "Error: could not allocate memory.\n");
        return NULL;
    }

    char *bin = convert_to_bin(n);

    cell->left = bin[strlen(bin) - 1] - 0x30;
    cell->right = bin[strlen(bin) - 2] - 0x30;
    cell->middle = bin[strlen(bin) - 3] - 0x30;

    if (bin != NULL)
        free(bin);

    return cell;
}

void help()
{
    printf("Usage: maze <arguments> <filename>\n");
    printf(" --help\t\t\t\t\t\tDisplay this help message.\n");
    printf(" --test <input> <output>\t\t\tTest the maze solver.\n");
    printf(" --rpath <input> <line> <col> <filename>\tFind the path to the exit using the right hand rule.\n");
    printf(" --lpath <input> <line> <col> <filename>\tFind the path to the exit. using the left hand rule.\n");
    printf(" --shortest <input> <line> <col> <filename>\tFind the shortest path to the exit.\n");
}

bool isborder(Map *map, int r, int c, int border)
{
    Cell *cell = convert_to_cell(map->cells[GETPOS(map, r, c)] - 0x30);
    bool result = false;

    switch (border) {
    case 0: /* left */
        if (cell->left == 1)
            result = true;

        break;

    case 1: /* right */
        if (cell->right == 1)
            result = true;

        break;

    case 2: /* middle */
        if (cell->middle == 1)
            result = true;

        break;
    }

    if (cell != NULL)
        free(cell);

    return result;
}

int is_exit_cell(Map *map, int r, int c)
{
    int result = 0;

    /* Checks if the cell is an exit cell */
    Cell *cell = convert_to_cell(map->cells[GETPOS(map, r, c)] - 0x30);
    if (r == 0 && cell->middle == 0 && (r + c) % 2 == 0) 
        result = 1;

    if (r == map->rows - 1 && cell->middle == 0 && (r + c) % 2 == 1)
        result = 1;

    if (c == 0 && cell->left == 0)
        result = 1;

    if (c == map->cols/2 - 1 && cell->right == 0)
        result = 1;

    if (cell != NULL)
        free(cell);

    return result;
}

void remove_occurs(char *str, char c) 
{
    /* Removes all occurences of a given character in a string */
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }

    *pw = '\0';
}

int *reverse_pos(Map *map, int pos)
{
    /* Reverses the position of a cell */
    int *result = malloc(sizeof(int) * 2);
    if (result == NULL) {
        fprintf(stderr, "Error: could not allocate memory.\n");
        return NULL;
    }

    int r = 0;
    int c = 0;

    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            if (GETPOS(map, i, j) == pos) {
                r = i;
                c = j;
            }
        }
    }

    result[0] = r;
    result[1] = c;

    return result;
}

int start(char *arg, int R, int C, char *filename)
{
    /* Getting the size of the maze */
    char RC_count[4];

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file '%s'.\n", filename);
        return 1;
    }

    fgets(RC_count, 4, fp);
    int R_count = RC_count[0] - 0x30;
    int C_count = (RC_count[2] - 0x30) + ((RC_count[2] - 0x30));

    /* Initializing the map */
    Map map = {
        .cols = C_count,
        .rows = R_count,
        .cells = malloc(sizeof(char) * (R_count * C_count))
    };

    if (map.cells == NULL) {
        fprintf(stderr, "Error: could not allocate memory.\n");
        return 1;
    }

    /* Reading the maze */
    char temp[128];
    int i = 0;
    while (fgets(temp, 128, fp) != NULL) {
        if (temp[0] == '\n') {
            continue;
        }

        if (i == 0) {
            strcpy((char *)map.cells, temp);
            i++;
        } else {
            strcat((char *)map.cells, temp);
        }
    }
    
    /* Removing whitespaces */
    remove_occurs((char *)map.cells, ' ');

    /* Eval */
    if (strcmp(arg, "--rpath") == 0) {
        rpath(&map, R, C);
    } else if (strcmp(arg, "--lpath") == 0) {
        lpath(&map, R, C);
    } else if (strcmp(arg, "--shortest") == 0) {
        return 0;
    } else {
        fprintf(stderr, "Invalid argument, use 'maze --help' to get help.");
        return 1;
    }

    if (map.cells != NULL)
        free(map.cells);

    return 0;
}

int test(char *filename)
{
    /* Tests, if given file contains a valid maze */
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file: '%s'\n", filename);
        return 0;
    }

    char RC_count[4];

    fgets(RC_count, 4, fp);
    int R_count = RC_count[0] - 0x30;
    int C_count = (RC_count[2] - 0x30) + (RC_count[2] - 0x30);

    char buf[128];
    int i = 0;
    while (fgets(buf, 128, fp) != NULL) {
        if (buf[0] != '\n')
            i++;
    }

    if (R_count != i || (int)strlen(buf) != C_count) {
        printf("Invalid\n");
        return 0;
    }

    return 1;
}
