#include "contacts.h"
#include "common.h"
#include "utils.h"

int init_storage()
{
    FILE *file = fopen_or_exit(STORAGE, "wb");

    uint8_t count_contacts = 0;

    if (fwrite(&count_contacts, sizeof(uint8_t), 1, file) != 1) {
        perror("[contacts:init_storage] Ошибка записи инициализационного значения: ");
        fclose(file);
        exit(1);
    }

    fclose(file);
    return 0;
}

int add_contant(const char *name, const char *phone)
{
    FILE *file = fopen_or_exit(STORAGE, "rb+");

    uint8_t count_countacts;
    fread(&count_countacts, sizeof(uint8_t), 1, file);

    printf("%d\n", count_countacts);

    count_countacts++;
    fseek(file, 0, SEEK_SET);
    fwrite(&count_countacts, sizeof(uint8_t), 1, file);
    fseek(file, 0, SEEK_END);
    fwrite(name, strlen(name) + 1, 1, file);
    fwrite(phone, strlen(phone) + 1, 1, file);

    fclose(file);
    return 0;
}

void print_contacts()
{
    FILE *file = fopen_or_exit(STORAGE, "rb");

    uint8_t count_contacts; // исправлена опечатка
    fread(&count_contacts, sizeof(uint8_t), 1, file);

    for (uint8_t i = 0; i < count_contacts; i++) {
        // ---- чтение имени ----
        char *name = NULL;
        size_t name_len = 0;
        int ch; // int, чтобы корректно обрабатывать EOF
        while ((ch = fgetc(file)) != '\0' && ch != EOF) {
            name = realloc(name, name_len + 2); // +1 на символ, +1 на '\0'
            name[name_len] = (char)ch;
            name_len++;
        }
        if (ch == EOF && name_len == 0) {
            perror("[contacts:print_contacts] unexpected EOF while reading name");
            free(name);
            fclose(file);
            exit(4);
        }
        // Добавляем нуль-терминатор
        name[name_len] = '\0';

        // ---- чтение телефона ----
        char *phone = NULL;
        size_t phone_len = 0;
        while ((ch = fgetc(file)) != '\0' && ch != EOF) {
            phone = realloc(phone, phone_len + 2);
            phone[phone_len] = (char)ch;
            phone_len++;
        }
        if (ch == EOF && phone_len == 0) {
            perror("[contacts:print_contacts] unexpected EOF while reading phone");
            free(name);
            free(phone);
            fclose(file);
            exit(5);
        }

        phone[phone_len] = '\0';

        printf("%s %s\n", name, phone);

        free(name);
        free(phone);
    }

    fclose(file);
}

void sort_by_name(Contact *contacts)
{
}

void sort_by_phone(Contact *contacts)
{
}

void find_by_name(Contact *contacts)
{
}

void test_count_contacts()
{
    FILE *file = fopen(STORAGE, "rb");

    uint8_t countacts_count;
    fread(&countacts_count, sizeof(uint8_t), 1, file);

    printf("%d\n", countacts_count);

    fclose(file);
}