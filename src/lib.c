#include <stdlib.h>
#include <string.h>
#include "lib.h"

Map *create_map(FILE *fp)
{
    Map *map = (Map *)malloc(sizeof(Map));
    if (map == NULL) {
        return NULL;
    }

    char buffer[255] = {};

    fscanf(fp, "%d %d", &map->rows, &map->cols);

    while (fgets(buffer, 100, fp) != NULL) {
        strcat((char *)map->cells, buffer);
    }

    return map;
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

void test(char *arg, char *filename)
{
    (void)arg;
    (void)filename;

    return;
}
