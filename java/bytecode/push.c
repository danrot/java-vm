#include "push.h"

void bipush(uint8_t i)
{
    stack_push(frame->stack, i);
}

void iconst_m1(void)
{
    bipush(-1);
}

void iconst_0(void)
{
    bipush(0);
}

void iconst_1(void)
{
    bipush(1);
}

void iconst_2(void)
{
    bipush(2);
}

void iconst_3(void)
{
    bipush(3);
}

void iconst_4(void)
{
    bipush(4);
}

void iconst_5(void)
{
    bipush(5);
}
