#include <stdio.h>
#include <stdlib.h>

#include "util/stack.h"

#include "java/frame.h"
#include "java/classfile.h"

Frame* frame; // currently running frame

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
    frame = frame_init(classfile, main, NULL);
    frame_run(frame);
    frame_destroy(frame);
}

