#include <stdlib.h>

#include "stack.h"

Stack* stack_init(int length)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->current = 0;
    stack->length = length;
    stack->values = malloc(sizeof(int) * length);
}

int stack_pop(Stack* stack)
{
    return stack->values[--stack->length];
}

void stack_push(Stack* stack, int value)
{
    stack->values[stack->length++] = value;
}

void stack_destroy(Stack* stack)
{
    free(stack->values);
    stack->values = 0;
    free(stack);
    stack = 0;
}
