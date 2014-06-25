#include <stdlib.h>
#include <stdint.h>

#include "new.h"

void newarray(uint8_t atype)
{
    int count = stack_pop(frame->stack);
    void* array;
    
    int size = 0;
    // TODO add all the types
    if (atype == ATYPE_INT) {
        size = sizeof(int) * count;
    }
    
    array = malloc(size);
    stack_push(frame->stack, (int)(uintptr_t) array);
}

void anewarray(uint8_t indexbyte1, uint8_t indexbyte2)
{
    int count = stack_pop(frame->stack);
    uint16_t index = (indexbyte1 << 8) | indexbyte2;
    int size;
    void* array;
    
    char* classname = classfile_get_constant_string(frame->classfile, ((ConstantClass*) frame->classfile->constants[index])->name_index);
    
    size = calculate_object_size(classname);
    
    array = malloc(size * count);
    
    stack_push(frame->stack, (int)(uintptr_t) array);
}

void new(uint8_t indexbyte1, uint8_t indexbyte2)
{
    int size;
    void* object;

    uint16_t index = (indexbyte1 << 8) | indexbyte2;
    
    char* classname = classfile_get_constant_string(frame->classfile, ((ConstantClass*) frame->classfile->constants[index])->name_index);
    
    size = calculate_object_size(classname);
    
    object = malloc(size);
    
    stack_push(frame->stack, (int)(uintptr_t) object);
}

static int calculate_object_size(const char* classname) {
    int i, size;
    const ClassFile* classfile;
    
    // TODO check access    
    classfile = classfile_init(classname);
    
    // TODO throw InstantiationError if neccessarry
    
    size = 0;
    // TODO initialize with default values
    for (i = 0; i < classfile->fields_count; i++) {
        char* descriptor = classfile_get_constant_string(classfile, classfile->fields[i].descriptor_index);
        
        if (strcmp(descriptor, "I") == 0) {
            // TODO save index to access these variables faster
            size += sizeof(uint32_t);
        }
    }
    
    return size;
}

