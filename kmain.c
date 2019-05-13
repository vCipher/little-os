#include "frame-buffer.h"
#include "string.h"

void initilize_frame_buffer(frame_buffer *buffer)
{
    buffer->color.background = VGA_COLOR_BLACK;
    buffer->color.foreground = VGA_COLOR_WHITE;
    buffer->row = 0;
    buffer->column = 0;
    buffer->cells = (frame_buffer_cell *)FRAME_BUFFER_ADDRESS;

    memset(buffer->cells, 0, FRAME_BUFFER_HEIGHT * FRAME_BUFFER_WIDTH);
}

void kmain(void)
{
    frame_buffer buffer;
    initilize_frame_buffer(&buffer);

    char* text = 
        "Before asking for help on the forums or IRC, you should be taking all the possible steps to diagnose the nature of the problem yourself. In the case of problems like triple faults or \"random\" exceptions, it's a common mistake to make assumptions about the cause of a problem, make use of a debugger or print statements to locate the exact point when an exception occurs. Using and emulator and a debugger (such as GDB and Bochs/QEMU) will help you to locate problems which are difficult to trace. If you provide some theory about the problem and actions you have already taken to solve it, people will be able to help you much easier (Even if your theory is not correct, it at least gives people an idea of your views on the problem and the strategies you might have already tried, as well as what you might have missed.)\n"
        "In general, put as much work into solving a problem yourself before asking others for help. Before you post, ask yourself, \"Have I done everything I can to diagnose and solve this problem?\" Often you will learn a lot in the process, and you'll likely be able to solve the problem (and similar problems in the future) yourself, without the help of others, which is a good thing. When you ask for help, provide the code relevant to your problem. However, the problem may be located somewhere else, so give your others a way to look at the other parts of your code as well (if you're using something like GitHub or Bitbucket, this is slightly easier, but there are certainly many other ways.)\n"
        "In regards to the forum, read the forum rules, they are required reading, and will improve the quality of your posts and make people more likely to help you. On the IRC channel, if you ask a question, don't expect an answer within 10 seconds, or even 5 minutes, other people have lives too. If you need to leave to do something, and want to check if you missed anything, there are logs available for you to look through, see the links in the IRC topic for those.\n"
        "For a much more in depth guide on how to be a good community member when asking for help, consult How to ask questions. It's a great read, and ideally, you should read the whole thing before asking for help anywhere (it's not that long, and well worth the read).";

    print_text(&buffer, text);
}