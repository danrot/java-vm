#include "istore.h"

void istore(int index)
{
    locals[index] = stack_pop(stack);
}

void istore_0()
{
    istore(0);
}

void istore_1()
{
    istore(1);
}

void istore_2()
{
    istore(2);
}

void istore_3()
{
    istore(3);
}
