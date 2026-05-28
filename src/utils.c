#include "utils.h"
#include "common.h"

/* Открыть файл или закончить выполнение программы. */
FILE *fopen_or_exit(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);

    if (file == NULL) {
        perror("[utils:fopen_or_exit] fopen: ");
        exit(1);
    }

    return file;
}