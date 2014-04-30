#ifndef _STACK_H_
#define _STACK_H_

typedef struct
{
    int* values;
    int current;
    int length;
} Stack;

Stack* stack_init(int length);
int stack_pop(Stack* stack);
void stack_push(Stack* stack, int value);
void stack_destroy(Stack* stack);

#endif
