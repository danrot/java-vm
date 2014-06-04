#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/stack.h"
#include "util/hashtable.h"

#include "java/frame.h"
#include "java/classfile.h"

Frame* frame; // currently running frame

HashTable* classfiles;

void run(ClassFile* classfile);

int main(int argc, char** argv)
{
    char* pos;
    char* classname = malloc(sizeof(char) * strlen(argv[1]) + 1);
    
    strcpy(classname, argv[1]);
    
    while (pos = strstr(classname, ".")) {
        strncpy(pos, "/", 1);
    }
    
    classfiles = hashtable_init(10); // TODO make the length more dynamic

    ClassFile* classfile = classfile_init(classname);
    
    run(classfile);
    
    classfile_destroy(classfile);
    
    hashtable_destroy(classfiles);

    return 0;
}

void run(ClassFile* classfile)
{
    const Method* main = classfile_get_method_by_name(classfile, "main");
    frame = frame_init(classfile, main, NULL);
    frame_run(frame);
    frame_destroy(frame);
}

