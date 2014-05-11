#include <stdio.h>
#include <stdlib.h>

#include "util/stack.h"

#include "java/frame.h"
#include "java/classfile.h"

#include "java/bytecode/bipush.h"
#include "java/bytecode/iload.h"
#include "java/bytecode/istore.h"

int bytecode_length = 9;
unsigned char bytecode[] = { 0x8, 0x3c, 0x10, 0x06, 0x3d, 0x1b, 0x1c, 0x68, 0x3c };

Frame* frame;

void init(void);
void destroy(void);
void interpret(void);

int main(int argc, char** argv)
{
    ClassFile* classfile = classfile_init(argv[1]);
    
    init();

    interpret();
    
    printf("Result: %i", frame->locals[1]);
    
    destroy();
    
    classfile_destroy(classfile);

    return 0;
}

void init(void)
{
    frame = frame_init();
}

void destroy(void)
{
    frame_destroy(frame);
}

void interpret(void)
{
    int i = 0;
    int v1;
    for (i = 0; i < bytecode_length; ++i) {
        switch (bytecode[i]) {
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
                v1 = bytecode[++i];
                bipush(v1);
                break;
            case 0x15:
                v1 = bytecode[++i];
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
                v1 = bytecode[++i];
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
