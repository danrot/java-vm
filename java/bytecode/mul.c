#include "mul.h"

void imul()
{
    stack_push(frame->stack, stack_pop(frame->stack) * stack_pop(frame->stack));
}
