#include "contact.h"
#include "common.h"
#include "utils.h"

void init_storage()
{
    FILE *file = fopen_or_exit(FILEBASE, "wb");

    /* Записываем в файл счетчик контактов. */
    uint16_t init_count = 0;
    fwrite(&init_count, sizeof(init_count), 1, file);

    fclose(file);
}

void create_contact(const char *name, const char *phone)
{
    FILE *file = fopen_or_exit(FILEBASE, "rb+");

    /* Записываем новый контакт. */
    fseek(file, 0, SEEK_END);
    fwrite(name, strlen(name) + 1, 1, file);
    fwrite(phone, strlen(phone) + 1, 1, file);

    printf("[DEBUG : create_contant] NAME = '%s', PHONE = '%s'\n", name, phone);

    /* Считываем количество контактов. */
    fseek(file, 0, SEEK_SET);
    uint16_t contacts_count;
    fread(&contacts_count, sizeof(contacts_count), 1, file);

    printf("[DEBUG : create_contact] OLD COUNT = '%d'\n", contacts_count);

    /* Увеличиваем количество контактов на 1. */
    contacts_count++;
    fseek(file, 0, SEEK_SET);
    fwrite(&contacts_count, sizeof(contacts_count), 1, file);

    printf("[DEBUG : create_contact] NEW COUNT = '%d'\n", contacts_count);

    fclose(file);
}

Contact *read_contacts()
{
    FILE *file = fopen_or_exit(FILEBASE, "rb");

    /* Считываем количество контактов. */
    uint16_t contact_count;
    fread(&contact_count, sizeof(contact_count), 1, file);

    printf("[DEBUG : read_contacts] COUNT CONTACTS = '%d'\n", contact_count);

    /* Выделяем память под массив контактов. */
    Contact *contacts = (Contact *)calloc(contact_count, sizeof(Contact));
    if (!contacts && contact_count > 0) {
        perror("[contact:read_contacts] contacts CALLOC: ");
        memset(contacts, 0, sizeof(Contact) * contact_count);
        fclose(file);
        exit(1);
    }

    printf("[DEBUG : read_contacts] CONTACTS CALLOC SUCCESS\n");

    /* Считываем контакты из файла в массив структур. */
    for (uint16_t i = 0; i < contact_count; i++) {
        size_t name_len = 0;
        int ch;

        /* Считываем имя контакта. */
        while ((ch = fgetc(file)) != '\0' && ch != EOF) {
            contacts[i].name = realloc(contacts[i].name, name_len + 2);
            contacts[i].name[name_len] = (char)ch;
            name_len++;
        }
        contacts[i].name[name_len] = '\0';

        printf("[DEBUG : read_contacts] READ NAME = '%s'\n", contacts[i].name);

        /* Считываем телефонный номер контакта. */
        size_t phone_len = 0;
        while ((ch = fgetc(file)) != '\0' && ch != EOF) {
            contacts[i].phone = realloc(contacts[i].phone, phone_len + 2);
            contacts[i].phone[phone_len] = (char)ch;
            phone_len++;
        }
        contacts[i].phone[phone_len] = '\0';

        printf("[DEBUG : read_contacts] READ PHONE = '%s'\n", contacts[i].phone);
    }

    fclose(file);
    return contacts;
}

void update_contact_number(const char *name, const char *phone)
{
    FILE *file = fopen_or_exit(FILEBASE, "rb+");

    /* Считываем количество контактов. */
    uint16_t contact_count;
    fread(&contact_count, sizeof(contact_count), 1, file);

    /* Получаем списков всех контактов. */
    printf("--------------------------\n");
    Contact *contacts = read_contacts();
    printf("--------------------------\n");

    /* Проверяем существует ли контакт. */
    int found = 0;
    uint16_t index;
    for (index = 0; index < contact_count; index++) {
        if (strcmp(contacts[index].name, name) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("[DEBUG : update_contact_number] '%s' FOUNDED, INDEX = '%d'\n", contacts[index].name, index);

        printf("[DEBUG : update_contact_number] '%s' SWAP TO '%s'\n", contacts[index].phone, phone);

        free(contacts[index].phone);
        contacts[index].phone = strdup(phone);

        /*
                        Обязательно нужно переоткрыть файл что бы сбросить его длинну.
                        Если мы будем перезаписывать номера разной длинны тогда
                                хвост номера останется в файле и будут мешать работе.
                */
        file = fopen_or_exit(FILEBASE, "wb");

        fseek(file, 0, SEEK_SET);
        fwrite(&contact_count, sizeof(contact_count), 1, file);

        for (uint16_t i = 0; i < contact_count; i++) {
            fwrite(contacts[i].name, strlen(contacts[i].name) + 1, 1, file);
            fwrite(contacts[i].phone, strlen(contacts[i].phone) + 1, 1, file);

            free(contacts[i].name);
            free(contacts[i].phone);
        }

        free(contacts);
    } else {
        printf("[utils:create_contact] Контакт с таким именем не найден\n");

        for (uint16_t i = 0; i < contact_count; i++) {
            free(contacts[i].name);
            free(contacts[i].phone);
        }

        free(contacts);
    }

    fclose(file);
}

void delete_contact(const char *name)
{
    FILE *file = fopen_or_exit(FILEBASE, "rb+");

    /* Считываем количество контактов. */
    uint16_t contact_count;
    fread(&contact_count, sizeof(contact_count), 1, file);

    /* Получаем списков всех контактов. */
    printf("--------------------------\n");
    Contact *contacts = read_contacts();
    printf("--------------------------\n");

    /* Проверяем существует ли контакт. */
    int found = 0;
    uint16_t index;
    for (index = 0; index < contact_count; index++) {
        if (strcmp(contacts[index].name, name) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        file = fopen_or_exit(FILEBASE, "wb");

        fseek(file, 0, SEEK_SET);
        fwrite(&contact_count, sizeof(contact_count), 1, file);

        for (uint16_t i = 0; i < contact_count; i++) {
            if (i == index) {
                continue;
            }

            fwrite(contacts[i].name, strlen(contacts[i].name) + 1, 1, file);
            fwrite(contacts[i].phone, strlen(contacts[i].phone) + 1, 1, file);

            free(contacts[i].name);
            free(contacts[i].phone);
        }

        free(contacts);
    } else {
        printf("[utils:create_contact] Контакт с таким именем не найден\n");

        for (uint16_t i = 0; i < contact_count; i++) {
            free(contacts[i].name);
            free(contacts[i].phone);
        }

        free(contacts);
    }

    fclose(file);
}

int cmp_by_name(const void *a, const void *b)
{
    const Contact *na = (const Contact *)a;
    const Contact *nb = (const Contact *)b;
    return strcmp(na->name, nb->name);
}

int cmp_by_phone(const void *a, const void *b)
{
    const Contact *na = (const Contact *)a;
    const Contact *nb = (const Contact *)b;
    return strcmp(na->phone, nb->phone);
}

void bubble_sort(int (*cmp)(const void *a, const void *b))
{
    FILE *file = fopen_or_exit(FILEBASE, "rb");
    uint16_t contacts_count;
    fread(&contacts_count, sizeof(contacts_count), 1, file);
    fclose(file);

    if (contacts_count == 0) {
        printf("Нет контактов для сортировки.\n");
        return;
    }

    Contact *contacts = read_contacts();

    for (uint16_t i = 0; i < contacts_count - 1; i++) {
        for (uint16_t j = 0; j < contacts_count - i - 1; j++) {
            if (cmp(&contacts[j], &contacts[j + 1]) > 0) {
                Contact tmp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = tmp;
            }
        }
    }

    file = fopen_or_exit(FILEBASE, "wb");

    fseek(file, 0, SEEK_SET);
    fwrite(&contacts_count, sizeof(contacts_count), 1, file);

    for (uint16_t i = 0; i < contacts_count; i++) {
        fwrite(contacts[i].name, strlen(contacts[i].name) + 1, 1, file);
        fwrite(contacts[i].phone, strlen(contacts[i].phone) + 1, 1, file);

        free(contacts[i].name);
        free(contacts[i].phone);
    }
    free(contacts);
    fclose(file);
}