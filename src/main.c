#include "common.h"
#include "contact.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        exit(2);
    }

    if (strcmp(argv[1], "init") == 0) {
        init_storage();
    }

    if (strcmp(argv[1], "add") == 0) {
        create_contact(argv[2], argv[3]);
    }

    if (strcmp(argv[1], "read") == 0) {
        FILE *file = fopen_or_exit(FILEBASE, "rb");
        uint16_t contacts_count;
        fread(&contacts_count, sizeof(contacts_count), 1, file);
        fclose(file);

        Contact *contacts = read_contacts();

        for (uint16_t i = 0; i < contacts_count; i++) {
            printf("%s %s\n", contacts[i].name, contacts[i].phone);
            free(contacts[i].name);
            free(contacts[i].phone);
        }

        free(contacts);
    }

    if (strcmp(argv[1], "update") == 0) {
        update_contact_number(argv[2], argv[3]);
    }

    if (strcmp(argv[1], "delete") == 0) {
        delete_contact(argv[2]);
    }

    if (strcmp(argv[1], "sort-by-name") == 0) {
        bubble_sort(cmp_by_name);
    }

    if (strcmp(argv[1], "sort-by-phone") == 0) {
        bubble_sort(cmp_by_phone);
    }
}