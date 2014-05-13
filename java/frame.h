#ifndef _FRAME_H_
#define _FRAME_H_

#include "../util/stack.h"
#include "classfile.h"

typedef struct
{
    const ClassFile* classfile;
    const Method* method;
    const AttributeCode* code;
    Stack* stack;
    int* locals;
} Frame;

Frame* frame_init(const ClassFile* classfile, const Method* method);
void frame_run(Frame* frame);
void frame_destroy(Frame* frame);

#endif
