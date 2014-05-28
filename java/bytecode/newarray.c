#include <stdlib.h>
#include <stdint.h>

#include "newarray.h"

void newarray(uint8_t atype)
{
    int count = stack_pop(frame->stack);
    void* array;
    
    int size = 0;
    // TODO add all the types
    if (atype == ATYPE_INT) {
        size = sizeof(int) * count;
    }
    
    array = malloc(size);
    stack_push(frame->stack, (int)(uintptr_t) array);
}
