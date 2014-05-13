#include <stdlib.h>
#include <inttypes.h>

#include "frame.h"
#include "bytecode/bipush.h"
#include "bytecode/iload.h"
#include "bytecode/istore.h"

Frame* frame_init(const ClassFile* classfile, const Method* method)
{
    Frame* frame = malloc(sizeof(Frame));
    frame->classfile = classfile;
    frame->method = method;
    frame->code = classfile_get_code_from_method(frame->classfile, frame->method);
    frame->locals = malloc(sizeof(uint32_t) * frame->code->max_locals);
    frame->stack = stack_init(frame->code->max_stack);
    return frame;
}

void frame_run(Frame* frame)
{
    printf("frame_run\n");
    int i = 0;
    int v1;
    for (i = 0; i < frame->code->code_length; ++i) {
        printf("frame_run: bytecode %i: %x\n", i, frame->code->code[i]);
        switch (frame->code->code[i]) {
            case 0x2:
                iconst_m1();
                break;
            case 0x3:
                iconst_0();
                break;
            case 0x4:
                iconst_1();
                break;
            case 0x5:
                iconst_2();
                break;
            case 0x6:
                iconst_3();
                break;
            case 0x7:
                iconst_4();
                break;
            case 0x8:
                iconst_5();
                break;
            case 0x10:
                v1 = frame->code->code[++i];
                bipush(v1);
                break;
            case 0x15:
                v1 = frame->code->code[++i];
                iload(v1);
                break;
            case 0x1a:
                iload_0();
                break;
            case 0x1b:
                iload_1();
                break;
            case 0x1c:
                iload_2();
                break;
            case 0x1d:
                iload_3();
                break;
            case 0x36:
                v1 = frame->code->code[++i];
                istore(v1);
                break;
            case 0x3b:
                istore_0();
                break;
            case 0x3c:
                istore_1();
                break;
            case 0x3d:
                istore_2();
                break;
            case 0x3e:
                istore_3();
                break;
            case 0x68:
                imul();
                break;
        }
    }
}

void frame_destroy(Frame* frame)
{
    stack_destroy(frame->stack);
    free(frame->locals);
    free(frame);
}

