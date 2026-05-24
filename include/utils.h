#pragma once

#include "common.h"

#define EXIT_FOPEN 101

FILE *fopen_or_exit(const char *name, const char *mode);