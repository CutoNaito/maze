#include <stdlib.h>
#include <string.h>
#include "lib.h"

void help()
{
    printf("Usage: maze <arguments> <filename>\n");
    printf(" --help\t\t\t\t\t\tDisplay this help message.\n");
    printf(" --test <input> <output>\t\t\tTest the maze solver.\n");
    printf(" --rpath <input> <line> <col> <filename>\tFind the path to the exit using the right hand rule.\n");
    printf(" --lpath <input> <line> <col> <filename>\tFind the path to the exit. using the left hand rule.\n");
    printf(" --shortest <input> <line> <col> <filename>\tFind the shortest path to the exit.\n");
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

    /* Declaring the maze */
    char maze[R_count][C_count];

    /* Reading the maze */
    int i = 0;
    while (i < R_count) {
        fgets(maze[i], C_count, fp);

        if (strcmp(maze[i], "\n") != 0)
            i++;
    }

    (void)arg;
    (void)R;
    (void)C;

    return 0;
}

void test(char *arg, char *filename)
{
    (void)arg;
    (void)filename;

    return;
}
