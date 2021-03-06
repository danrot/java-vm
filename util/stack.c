#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

Stack* stack_init(int length)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->current = 0;
    stack->length = length;
    stack->values = malloc(sizeof(int) * length);
    return stack;
}

int stack_pop(Stack* stack)
{
    return stack->values[--stack->current];
}

void stack_push(Stack* stack, int value)
{
    stack->values[stack->current++] = value;
}

void stack_destroy(Stack* stack)
{
    //free(stack->values); TODO Check why this does not work
    free(stack);
}
