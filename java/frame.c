#include <stdlib.h>

#include "frame.h"

Frame* frame_init()
{
    Frame* frame = malloc(sizeof(Frame));
    frame->locals = malloc(sizeof(int) * 10);
    frame->stack = stack_init(10);
    return frame;
}

void frame_destroy(Frame* frame)
{
    stack_destroy(frame->stack);
    free(frame->locals);
    free(frame);
}
