#include "utils.h"
#include "common.h"

FILE *fopen_or_exit(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);

    if (!file) {
        perror("[utils:fopen_or_exit] fopen: ");
        exit(1);
    }

    return file;
}