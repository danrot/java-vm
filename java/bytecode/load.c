#include "load.h"

void ldc(int index)
{
    Constant* constant = frame->classfile->constants[index];
    
    switch (constant->tag) {
        case 3:
            stack_push(frame->stack, ((ConstantInteger*) constant)->bytes);
            break;
        default:
            printf("ldc: missing tag %i\n", constant->tag);
    }
}

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

void lload(int index)
{
    // TODO long should be pushed on twice?
    stack_push(frame->stack, frame->locals[index]);
}

void lload_0()
{
    lload(0);
}

void lload_1()
{
    lload(1);
}

void lload_2()
{
    lload(2);
}

void lload_3()
{
    lload(3);
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

