#include "div.h"

void idiv()
{
    int value2 = stack_pop(frame->stack);
    int value1 = stack_pop(frame->stack);
    
    stack_push(frame->stack, value1 / value2);
}
