#ifndef _FRAME_H_
#define _FRAME_H_

#include "../util/stack.h"
#include "classfile.h"

struct Frame
{
    const ClassFile* classfile;
    const Method* method;
    const AttributeCode* code;
    struct Frame* parent;
    Stack* stack;
    uint32_t* locals;
    
    uint8_t* current;
    uint8_t count;
};

typedef struct Frame Frame;

Frame* frame_init(const ClassFile* classfile, const Method* method, Frame* parent);
void frame_run(Frame* frame);
void frame_destroy(Frame* frame);

#endif
