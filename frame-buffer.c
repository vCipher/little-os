#include "frame-buffer.h"
#include "string.h"

static void scroll_frame_buffer(frame_buffer *buffer)
{
    void *src = buffer->cells + FRAME_BUFFER_WIDTH;
    void *dst = buffer->cells;
    void *last_line = buffer->cells + ((FRAME_BUFFER_HEIGHT - 1)* FRAME_BUFFER_WIDTH);
    void *last_line_end = buffer->cells + FRAME_BUFFER_HEIGHT * FRAME_BUFFER_WIDTH;
    size_t len = last_line_end - src;

    memcpy(dst, src, len);
    memset(last_line, 0, last_line_end - last_line);
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
}

void print_char(frame_buffer *buffer, char symbol)
{
    if (symbol == '\n')
    {
        move_next_line(buffer);
        return;
    }

    const size_t index = buffer->row * FRAME_BUFFER_WIDTH + buffer->column;
    frame_buffer_cell cell = { .symbol = symbol, .color = buffer->color };

    buffer->cells[index] = cell;
    move_next_char(buffer);
}

void print_text(frame_buffer *buffer, char* text)
{
    for (; *text != '\0'; text++)
    {
        print_char(buffer, *text);
    }
}