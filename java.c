#include <stdio.h>
#include <stdlib.h>

#include "util/stack.h"

#include "java/frame.h"
#include "java/classfile.h"

int bytecode_length = 9;
unsigned char bytecode[] = { 0x8, 0x3c, 0x10, 0x06, 0x3d, 0x1b, 0x1c, 0x68, 0x3c };

Frame* frame; //currently running frame

void run(ClassFile* classfile);

int main(int argc, char** argv)
{
    ClassFile* classfile = classfile_init(argv[1]);
    
    run(classfile);
    
    classfile_destroy(classfile);

    return 0;
}

void run(ClassFile* classfile)
{
    const Method* main = classfile_get_method_by_name(classfile, "main");
    frame = frame_init(classfile, main);
    frame_run(frame);
    frame_destroy(frame);
}

