#include "common.h"
#include "contact.h"

/* Точка входа в программу. */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("[main:main] Недостаточное количество аргументво.\n");
        exit(EXIT_NO_ARGS);
    }

    if (strcmp(argv[1], "add") == 0) {
        add_contact(argv[2], argv[3]);
    }
    return 0;
}