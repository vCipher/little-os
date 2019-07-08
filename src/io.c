#include "io.h"

void outb(uint16_t port, uint8_t value) 
{
	asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port) 
{
	uint8_t value;
	asm volatile("inb %1, %0" : "=a" (value) : "dN" (port));
	return value;
}

void outw(uint16_t port, uint16_t value) 
{
	asm volatile("outw %w0, %w1":: "a"(value), "Nd"(port));
}

uint16_t inw(uint16_t port)
{
	uint16_t value;
	asm volatile("inw %1, %0" : "=a" (value) : "dN" (port));
	return value;
}

void outl(uint16_t port, uint32_t value)
{
	asm volatile("outl %0, %w1":: "a"(value), "Nd"(port));
}

uint32_t inl(uint16_t port)
{
	uint32_t value;
	asm volatile("inl %1, %0" : "=a" (value) : "dN" (port));
	return value;
}