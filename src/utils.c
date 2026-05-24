#include "utils.h"
#include "common.h"

/* Открывает файл или заканчивает программу с ошибкой. */
FILE *fopen_or_exit(const char *name, const char *mode)
{
    FILE *file = fopen(name, mode);

    if (file == NULL) {
        perror("[utils:fopen_or_exit] Ошибка открытия файла: ");
        exit(EXIT_FOPEN);
    }

    return file;
}