#pragma once

#define STORAGE "contact.bin"
#define EXIT_FWRITE 102

typedef struct
{
    char name[255];
    char phone[15];
} Contact;

int add_contact(const char *name, const char *phone);