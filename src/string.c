#include "string.h"

size_t strlen(const char *str)
{
	size_t len = 0;
	while (str[len])
	{
		len++;
	}

	return len;
}

void memcpy(void *dest, const void *src, uint32_t size)
{
	asm volatile ("cld; rep movsb" : "+c" (size), "+S" (src), "+D" (dest) :: "memory");
}

void memset(void *dest, uint8_t value, uint32_t size)
{
	asm volatile ("cld; rep stosb" : "+c" (size), "+D" (dest) : "a" (value) : "memory");
}

void memcpy16(void *dest, const void *src, uint32_t size)
{
	asm volatile ("cld; rep movsw" : "+c" (size), "+S" (src), "+D" (dest) :: "memory");
}

void memset16(void *dest, uint16_t value, uint32_t size)
{
	asm volatile ("cld; rep stosw" : "+c" (size), "+D" (dest) : "a" (value) : "memory");
}

void memcpy32(void *dest, const void *src, uint32_t size)
{
	asm volatile ("cld; rep movsl" : "+c" (size), "+S" (src), "+D" (dest) :: "memory");
}

void memset32(void *dest, uint32_t value, uint32_t size)
{
	asm volatile ("cld; rep stosl" : "+c" (size), "+D" (dest) : "a" (value) : "memory");
}