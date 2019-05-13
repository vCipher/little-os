#pragma once

#include <stddef.h>

/* Type to use for aligned memory operations.
   This should normally be the biggest type supported by a single load
   and store.  */
#define op_t    unsigned long int
#define OPSIZ   (sizeof (op_t))

size_t strlen(const char *str);
void *memcpy(void *dstpp, const void *srcpp, size_t len);
void *memset(void *dstpp, int c, size_t len);
