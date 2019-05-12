typedef struct frame_buffer_cell
{
    char symbol;
    union
    {
        unsigned char foreground; 
        unsigned char background;
    };
} __attribute__((packed)) frame_buffer_cell;

void print_text(frame_buffer_cell *buffer, char* text)
{
    for (int index = 0; ; index++)
    {
        char sym = text[index];
        if (sym == '\0')
        {
            return;
        }

        buffer[index].symbol = sym;
    }
}

void kmain() 
{
    print_text((frame_buffer_cell *)0x000B8000, "Hello");
}