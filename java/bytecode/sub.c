#include "sub.h"

void isub()
{
    int value2 = stack_pop(frame->stack);
    int value1 = stack_pop(frame->stack);
    
    stack_push(frame->stack, value1 - value2);
}
