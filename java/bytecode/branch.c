#include "branch.h"

void ifle(uint8_t branchbyte1, uint8_t branchbyte2)
{
    if (stack_pop(frame->stack) <= 0) {
        jump(branchbyte1, branchbyte2);
    }
}

void ifge(uint8_t branchbyte1, uint8_t branchbyte2)
{
    if (stack_pop(frame->stack) >= 0) {
        jump(branchbyte1, branchbyte2);
    }
}

void if_icmpge(uint8_t branchbyte1, uint8_t branchbyte2)
{
    int value2 = stack_pop(frame->stack);
    int value1 = stack_pop(frame->stack);
    
    if (value1 >= value2) {
        jump(branchbyte1, branchbyte2);
    }
}

void ifnonnull(uint8_t branchbyte1, uint8_t branchbyte2)
{
    if (stack_pop(frame->stack) != 0x0) {
        jump(branchbyte1, branchbyte2);
    }
}

void gotoj(uint8_t branchbyte1, uint8_t branchbyte2)
{
    jump(branchbyte1, branchbyte2);
}

static void jump(uint8_t branchbyte1, uint8_t branchbyte2)
{
    int16_t jump = (int16_t) (branchbyte1 << 8) | branchbyte2;
    
    frame->current = frame->current + jump - 3;
    frame->count = frame->count - jump + 3;
}
