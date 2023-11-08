#include <stdlib.h>
#include <string.h>
#include "lib.h"

int main(int argc, char* argv[])
{
    switch (argc) {
    case 1:
        fprintf(stderr, "Invalid argument count.\n");
        return 1;

    case 2:
        if (strcmp(argv[1], "--help") == 0) {
            help();
        } else {
            fprintf(stderr, "Invalid argument, use 'maze --help' to get help.\n");
            return 1;
        }

        break;

    case 3:
        test(argv[1], argv[2]);
        break;

    case 5:
        start(argv[1], (int)argv[2][0], (int)argv[3][0], argv[4]);
        break;

    default:
        fprintf(stderr, "Invalid argument count.\n");
        return 1;
    }
    return 0;
}
