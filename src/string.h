#ifndef _STRING_H
#define _STRING_H

#include "types.h"

size_t strlen(const char *str);

void memcpy(void *dest, const void *src, uint32_t size);
void memset(void *dest, uint8_t value, uint32_t size);
void memcpy16(void *dest, const void *src, uint32_t size);
void memset16(void *dest, uint16_t value, uint32_t size);
void memcpy32(void *dest, const void *src, uint32_t size);
void memset32(void *dest, uint32_t value, uint32_t size);

#endif /* _STRING_H */