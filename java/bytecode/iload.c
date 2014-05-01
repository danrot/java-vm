#include "iload.h"

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
