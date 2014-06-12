#include "astore.h"

void astore(uint8_t index)
{
    frame->locals[index] = stack_pop(frame->stack);
}

void astore_0()
{
    astore(0);
}

void astore_1()
{
    astore(1);
}

void astore_2()
{
    astore(2);
}

void astore_3()
{
    astore(3);
}

void iastore()
{
    int value = stack_pop(frame->stack);
    int index = stack_pop(frame->stack);
    int arrayref = stack_pop(frame->stack);
    int* array = (int*)(uintptr_t) arrayref;
    
    // TODO Throw NullPointerException and ArrayOutOfBoundsException
    
    array[index] = value;
}

