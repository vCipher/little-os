#include "gdt.h"
#include "frame-buffer.h"

void kmain(void)
{
	gdt_init();

	frame_buffer buffer;
	frame_buffer_create(&buffer);

	frame_buffer_print_text(&buffer, "text\n");
	frame_buffer_print_text(&buffer, "text\n");
	frame_buffer_print_text(&buffer, "text\n");
}