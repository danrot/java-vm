#include <stdlib.h>
#include <inttypes.h>

#include "frame.h"
#include "bytecode/aload.h"
#include "bytecode/bipush.h"
#include "bytecode/iadd.h"
#include "bytecode/iload.h"
#include "bytecode/istore.h"
#include "bytecode/newarray.h"
#include "bytecode/dup.h"
#include "bytecode/return.h"

Frame* frame_init(const ClassFile* classfile, const Method* method, Frame* parent)
{
    Frame* frame = malloc(sizeof(Frame));
    frame->classfile = classfile;
    frame->method = method;
    frame->code = classfile_get_code_from_method(frame->classfile, frame->method);
    frame->parent = parent;
    frame->locals = malloc(sizeof(uint32_t) * frame->code->max_locals);
    frame->stack = stack_init(frame->code->max_stack);
    return frame;
}

void frame_run(Frame* frame)
{
    int i = 0;
    uint8_t* code = frame->code->code;
    int count = frame->code->code_length;
    
    uint8_t v1, v2;
    while (count) {
        printf("frame_run: bytecode %i: %x\n", i, *code);
        switch (*code) {
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
                v1 = *(++code);
                bipush(v1);
                count = count - 1;
                break;
            case 0x15:
                v1 = *(++code);
                iload(v1);
                count = count - 1;
                break;
            case 0x19:
                v1 = *(++code);
                aload(v1);
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
            case 0x2a:
                aload_0();
                break;
            case 0x2b:
                aload_1();
                break;
            case 0x2c:
                aload_2();
                break;
            case 0x2d:
                aload_3();
                break;
            case 0x2e:
                iaload();
                break;
            case 0x36:
                v1 = *(++code);
                istore(v1);
                count = count - 1;
                break;
            case 0x3a:
                v1 = *(++code);
                astore(v1);
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
            case 0x4b:
                astore_0();
                break;
            case 0x4c:
                astore_1();
                break;
            case 0x4d:
                astore_2();
                break;
            case 0x4e:
                astore_3();
                break;
            case 0x4f:
                iastore();
                break;
            case 0x59:
                dupj();
                break;
            case 0x60:
                iadd();
                break;
            case 0x68:
                imul();
                break;
            case 0xac:
                ireturn();
                break;
            case 0xb8:
                v1 = *(++code);
                v2 = *(++code);
                invokestatic(v1, v2);
                count = count - 2;
                break;
            case 0xbc:
                v1 = *(++code);
                newarray(v1);
                break;
        }
        code = code + 1;
        count = count - 1;
    }
}

void frame_destroy(Frame* frame)
{
    stack_destroy(frame->stack);
    free(frame->locals);
    free(frame);
}

