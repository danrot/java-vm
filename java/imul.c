#include "imul.h"

void imul()
{
    stack_push(stack, stack_pop(stack) * stack_pop(stack));
}
