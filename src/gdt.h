#ifndef _GDT_H
#define _GDT_H

#include "types.h"

typedef struct gdt_entry
{
	uint16_t limit_low;		// The lower 16 bits of the limit.
	uint16_t base_low;		// The lower 16 bits of the base.
	uint8_t  base_middle;	// The next 8 bits of the base.
	uint8_t  access;		// Access flags, determine what ring this segment can be used in.
	uint8_t  granularity;
	uint8_t  base_high;		// The last 8 bits of the base.
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr
{
   uint16_t limit;			// The upper 16 bits of all selector limits.
   uint32_t base;			// The address of the first gdt_entry_t struct.
} __attribute__((packed)) gdt_ptr_t;

void gdt_init();

#endif