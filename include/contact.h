#pragma once

#include "common.h"

typedef struct
{
    char *name;
    char *phone;
} Contact;

void init_storage();
void create_contact(const char *name, const char *phone);
Contact *read_contacts();
void update_contact_number(const char *name, const char *phone);
void delete_contact(const char *name);
int cmp_by_name(const void *a, const void *b);
int cmp_by_phone(const void *a, const void *b);
void bubble_sort(int (*cmp)(const void *a, const void *b));