#include <stdlib.h>

#include "../frame.h"
#include "return.h"

void returnj()
{
    // TODO monitor handling
    
    Frame* tmp;
    
    if (frame->parent) {
        tmp = frame;
        frame = frame->parent;
        frame_destroy(tmp);
    } else {
        // TODO check why this does not work
        //frame_destroy(tmp);
        exit(0);
    }
}

void ireturn()
{
    // TODO monitor handling
    
    uint32_t value = stack_pop(frame->stack);
    
    stack_push(frame->parent->stack, value);
    
    returnj();
}
