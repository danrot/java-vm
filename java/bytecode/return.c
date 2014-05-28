#include "../frame.h"
#include "return.h"

void ireturn()
{
    Frame* tmp;
    // TODO monitor handling
    
    uint32_t value = stack_pop(frame->stack);
    
    stack_push(frame->parent->stack, value);
    
    tmp = frame;
    frame = frame->parent;
    
    frame_destroy(tmp);
}
