#include "add.h"

void iadd()
{
    stack_push(frame->stack, stack_pop(frame->stack) + stack_pop(frame->stack));
}
