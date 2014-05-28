#include "aload.h"

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
    
    printf("iaload: index: %i\n", index);
    printf("iaload: arrayref: %i\n", arrayref);
    printf("iaload: result: %i\n", array[index]);
    
    stack_push(frame->stack, array[index]);
}

