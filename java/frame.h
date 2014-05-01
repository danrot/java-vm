#ifndef _FRAME_H_
#define _FRAME_H_

#include "../util/stack.h"

typedef struct
{
    Stack* stack;
    int* locals;
} Frame;

Frame* frame_init();
void frame_destroy(Frame* frame);

#endif
