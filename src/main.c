#include "common.h"
#include "contacts.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        exit(1);
    }

    if (strcmp(argv[1], "test") == 0) {
        test_count_contacts();
    }

    if (strcmp(argv[1], "init") == 0) {
        init_storage();
    }

    if (strcmp(argv[1], "add") == 0) {
        add_contant(argv[2], argv[3]);
    }

    if (strcmp(argv[1], "print") == 0) {
        print_contacts();
    }

    return 0;
}