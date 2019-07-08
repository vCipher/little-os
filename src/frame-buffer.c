#include "frame-buffer.h"
#include "string.h"
#include "io.h"

static void scroll_frame_buffer(frame_buffer *buffer)
{
	void *src = buffer->cells + FRAME_BUFFER_WIDTH;
	void *dst = buffer->cells;
	void *last_line = buffer->cells + ((FRAME_BUFFER_HEIGHT - 1)* FRAME_BUFFER_WIDTH);
	void *last_line_end = buffer->cells + FRAME_BUFFER_HEIGHT * FRAME_BUFFER_WIDTH;
	ptrdiff_t len = last_line_end - src;

	memcpy(dst, src, len);
	memset(last_line, 0, last_line_end - last_line);
}

static void move_cursor(frame_buffer *buffer)
{
 	uint16_t position = buffer->row * FRAME_BUFFER_WIDTH + buffer->column;
	outb(FRAME_BUFFER_COMMAND_PORT, FRAME_BUFFER_HIGH_BYTE_COMMAND);
	outb(FRAME_BUFFER_DATA_PORT,    ((position >> 8) & 0x00FF));
	outb(FRAME_BUFFER_COMMAND_PORT, FRAME_BUFFER_LOW_BYTE_COMMAND);
	outb(FRAME_BUFFER_DATA_PORT,    position & 0x00FF);
}

static void move_next_line(frame_buffer *buffer)
{
	buffer->row++;
	buffer->column = 0;

	if (buffer->row == FRAME_BUFFER_HEIGHT)
	{
		scroll_frame_buffer(buffer);
		buffer->row--;
	}
}

static void move_next_char(frame_buffer *buffer)
{
	buffer->column++;
	if (buffer->column == FRAME_BUFFER_WIDTH)
	{
		move_next_line(buffer);
	}

	move_cursor(buffer);
}

void frame_buffer_create(frame_buffer *buffer)
{
	buffer->color.background = VGA_COLOR_BLACK;
	buffer->color.foreground = VGA_COLOR_WHITE;
	buffer->row = 0;
	buffer->column = 0;
	buffer->cells = (frame_buffer_cell *)FRAME_BUFFER_ADDRESS;

	frame_buffer_cell cell = { .symbol = ' ', .color = buffer->color };
	memset16(buffer->cells, cell.data, FRAME_BUFFER_HEIGHT * FRAME_BUFFER_WIDTH);
	move_cursor(buffer);
}

void frame_buffer_print_char(frame_buffer *buffer, char symbol)
{
	if (symbol == '\n')
	{
		move_next_line(buffer);
		move_cursor(buffer);
		return;
	}

	const size_t index = buffer->row * FRAME_BUFFER_WIDTH + buffer->column;
	frame_buffer_cell cell = { .symbol = symbol, .color = buffer->color };

	buffer->cells[index] = cell;
	move_next_char(buffer);
}

void frame_buffer_print_text(frame_buffer *buffer, char* text)
{
	for (; *text != '\0'; text++)
	{
		frame_buffer_print_char(buffer, *text);
	}
}