#include "contact.h"
#include "common.h"
#include "utils.h"

/* Добавить контакт в хранилище. */
int add_contact(const char *name, const char *phone)
{
    FILE *file = fopen_or_exit(STORAGE, "ab");

    // Дополнительный символ нужен для добавление нуль-терминала.
    // Записываем строку вместе с заверщающим '\0'

    // Нужно это для того чтобы даже если в строке есть пробелы,
    // ее все ровно можно было легко записать в структуру.
    size_t name_len = strlen(name) + 1;
    if (fwrite(name, 1, name_len, file) != name_len) {
        perror("[contact:add_contact] Ошибка записи имени в файл: ");
        fclose(file);
        exit(EXIT_FWRITE);
    }

    size_t phone_len = strlen(phone) + 1;
    if (fwrite(phone, 1, phone_len, file) != phone_len) {
        perror("[contact:add_contact] Ошибка записи имени в файл: ");
        fclose(file);
        exit(EXIT_FWRITE);
    }

    fclose(file);

    // Отладочная информация о выполнении программы.
    // Можно в целом убрать но мне больше нравиться видеть,
    // как программа работает в процессе выполнения.
    printf("Записано: '%s' и '%s'\n", name, phone);
    printf("Байт: %ld и %ld\n", name_len, phone_len);
    return 0;
}