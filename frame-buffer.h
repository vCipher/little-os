#pragma once

#include <stddef.h>
#include <stdint.h>

enum vga_color 
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
    char symbol;
    frame_buffer_color color;

} __attribute__((packed)) frame_buffer_cell;

typedef struct frame_buffer
{
    size_t row;
    size_t column;
    frame_buffer_color color;
    frame_buffer_cell *cells;

} frame_buffer;

static const size_t FRAME_BUFFER_WIDTH = 80;
static const size_t FRAME_BUFFER_HEIGHT = 25;
static const void* FRAME_BUFFER_ADDRESS = (const void*)0x000B8000;

void print_char(frame_buffer *buffer, char symbol);
void print_text(frame_buffer *buffer, char* text);

