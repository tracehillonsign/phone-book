#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STORAGE "contacts.bin"

typedef struct
{
    char *name;
    char *phone;
} Contact;