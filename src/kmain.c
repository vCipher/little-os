#include "gdt.h"
#include "printf.h"

void kmain(void)
{
	gdt_init();
	printf("%s\n", "Hello, world!");
}