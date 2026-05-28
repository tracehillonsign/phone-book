#pragma once

#include "common.h"

int init_storage();
int add_contant(const char *name, const char *phone);
void test_count_contacts();
void print_contacts();
void sort_by_name(Contact *contacts);
void sort_by_phone(Contact *contacts);
void find_by_name(Contact *contacts);