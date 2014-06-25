#include "inc.h"

void iinc(uint8_t index, uint8_t inc)
{
    int8_t change = (int8_t) inc;
    frame->locals[index] += inc;
}
