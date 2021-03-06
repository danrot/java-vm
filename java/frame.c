#include <stdlib.h>
#include <inttypes.h>

#include "frame.h"
#include "bytecode/push.h"
#include "bytecode/add.h"
#include "bytecode/sub.h"
#include "bytecode/mul.h"
#include "bytecode/div.h"
#include "bytecode/inc.h"
#include "bytecode/load.h"
#include "bytecode/store.h"
#include "bytecode/new.h"
#include "bytecode/field.h"
#include "bytecode/dup.h"
#include "bytecode/return.h"
#include "bytecode/branch.h"

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
    frame->current = frame->code->code;
    frame->count = frame->code->code_length;
    
    uint8_t v1, v2;
    while (frame->count) {
        switch (*(frame->current)) {
            case 0x0:
                // nop
                break;
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
                v1 = *(++(frame->current));
                bipush(v1);
                frame->count = frame->count - 1;
                break;
            case 0x11:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                sipush(v1, v2);
                frame->count = frame->count - 1;
                break;
            case 0x12:
                v1 = *(++(frame->current));
                ldc(v1);
                frame->count = frame->count -1;
                break;
            case 0x15:
                v1 = *(++(frame->current));
                iload(v1);
                frame->count = frame->count - 1;
                break;
            case 0x16:
                v1 = *(++(frame->current));
                lload(v1);
                frame->count = frame->count - 1;
                break;
            case 0x19:
                v1 = *(++(frame->current));
                aload(v1);
                frame->count = frame->count - 1;
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
            case 0x1e:
                lload_0();
                break;
            case 0x1f:
                lload_1();
                break;
            case 0x20:
                lload_2();
                break;
            case 0x21:
                lload_3();
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
                v1 = *(++(frame->current));
                istore(v1);
                frame->count = frame->count - 1;
                break;
            case 0x3a:
                v1 = *(++(frame->current));
                astore(v1);
                frame->count = frame->count - 1;
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
            case 0x64:
                isub();
                break;
            case 0x68:
                imul();
                break;
            case 0x6c:
                idiv();
                break;
            case 0x84:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                iinc(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0x9c:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                ifge(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0x9e:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                ifle(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0xa2:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                if_icmpge(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0xa7:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                gotoj(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0xac:
                ireturn();
                break;
            case 0xb1:
                returnj();
                break;
            case 0xb4:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                getfield(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0xb5:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                putfield(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0xb6:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                invokevirtual(v1, v2);
                frame->count = frame->count - 2;
                break;    
            case 0xb7:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                invokespecial(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0xb8:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                invokestatic(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0xbb:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                new(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0xbc:
                v1 = *(++(frame->current));
                newarray(v1);
                break;
            case 0xbd:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                anewarray(v1, v2);
                frame->count = frame->count - 2;
                break;
            case 0xc7:
                v1 = *(++(frame->current));
                v2 = *(++(frame->current));
                ifnonnull(v1, v2);
                frame->count = frame->count - 2;
                break;
            default:
                printf("frame_run: bytecode: %x\n", *frame->current);
        }
        frame->current = frame->current + 1;
        frame->count = frame->count - 1;
    }
}

void frame_destroy(Frame* frame)
{
    stack_destroy(frame->stack);
    free(frame->locals);
    free(frame);
}

