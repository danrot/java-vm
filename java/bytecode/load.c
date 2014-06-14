#include "load.h"

void iload(int index)
{
    stack_push(frame->stack, frame->locals[index]);
}

void iload_0()
{
    iload(0);
}

void iload_1()
{
    iload(1);
}

void iload_2()
{
    iload(2);
}

void iload_3()
{
    iload(3);
}

void aload(uint8_t index)
{
    stack_push(frame->stack, frame->locals[index]);
}

void aload_0()
{
    aload(0);
}

void aload_1()
{
    aload(1);
}

void aload_2()
{
    aload(2);
}

void aload_3()
{
    aload(3);
}

void iaload()
{
    int index = stack_pop(frame->stack);
    int arrayref = stack_pop(frame->stack);
    int* array = (int*)(uintptr_t) arrayref;
    int value = array[index];
    
    stack_push(frame->stack, value);
}

