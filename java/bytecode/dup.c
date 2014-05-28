#include "dup.h"

void dupj()
{
    int value = stack_pop(frame->stack);
    
    stack_push(frame->stack, value);
    stack_push(frame->stack, value);
}
