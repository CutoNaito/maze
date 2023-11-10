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

    printf("%s\n", (char *)map.cells);

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
