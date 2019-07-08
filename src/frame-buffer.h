#ifndef _FRAME_BUFFER_H
#define _FRAME_BUFFER_H

#include "types.h"

#define FRAME_BUFFER_WIDTH 80
#define FRAME_BUFFER_HEIGHT 25
#define FRAME_BUFFER_ADDRESS 0x000B8000

/* The I/O ports */
#define FRAME_BUFFER_COMMAND_PORT         0x3D4
#define FRAME_BUFFER_DATA_PORT            0x3D5

/* The I/O port commands */
#define FRAME_BUFFER_HIGH_BYTE_COMMAND    14
#define FRAME_BUFFER_LOW_BYTE_COMMAND     15

enum VGA_COLOR 
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15
};

typedef union frame_buffer_color
{
	uint8_t foreground; 
	uint8_t background;

} frame_buffer_color;

typedef struct frame_buffer_cell
{
	union {
		struct {
			char symbol;
			frame_buffer_color color;
		};
		uint16_t data;
	};

} __attribute__((packed)) frame_buffer_cell;

typedef struct frame_buffer
{
	size_t row;
	size_t column;
	frame_buffer_color color;
	frame_buffer_cell *cells;

} frame_buffer;

void frame_buffer_create(frame_buffer *buffer);
void frame_buffer_print_char(frame_buffer *buffer, char symbol);
void frame_buffer_print_text(frame_buffer *buffer, char* text);

#endif /* _FRAME_BUFFER_H */