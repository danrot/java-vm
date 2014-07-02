#include <stdlib.h>
#include <stdint.h>

#include "field.h"

void putfield(uint8_t indexbyte1, uint8_t indexbyte2)
{
    int value = stack_pop(frame->stack);
    void* objectref = (void*)(uintptr_t) stack_pop(frame->stack);
    
    const ClassFile* classfile;
    uint16_t index = (indexbyte1 << 8) | indexbyte2;
    ConstantFieldRef* fieldref = (ConstantFieldRef*) frame->classfile->constants[index];
    
    char* classname = classfile_get_constant_string(frame->classfile, ((ConstantClass*)frame->classfile->constants[fieldref->class_index])->name_index);
    
    classfile = classfile_init(classname);
    
    char* name = classfile_get_constant_string(frame->classfile, ((ConstantNameAndType*) frame->classfile->constants[fieldref->name_and_type_index])->name_index);
    const Field* field = classfile_get_field_by_name(classfile, name);
    
    // TODO check objectref
    
    // TODO check types
    
    // TODO check final
    
    // TODO get position
    int position = classfile_get_field_position(classfile, field);
    
    *(int*)(objectref + position) = value;
}

void getfield(uint8_t indexbyte1, uint8_t indexbyte2)
{
    void* objectref = (void*)(uintptr_t)stack_pop(frame->stack);
    
    const ClassFile* classfile;
    uint16_t index = (indexbyte1 << 8) | indexbyte2;
    ConstantFieldRef* fieldref = (ConstantFieldRef*) frame->classfile->constants[index];
    
    char* classname = classfile_get_constant_string(frame->classfile, ((ConstantClass*)frame->classfile->constants[fieldref->class_index])->name_index);
    
    classfile = classfile_init(classname);
    
    char* name = classfile_get_constant_string(frame->classfile, ((ConstantNameAndType*) frame->classfile->constants[fieldref->name_and_type_index])->name_index);
    const Field* field = classfile_get_field_by_name(classfile, name);
    
    // TODO check type
    
    // TODO check protected
    
    int position = classfile_get_field_position(classfile, field);
    
    stack_push(frame->stack, *(int*)(objectref + position));
}

void getstatic(uint8_t indexbyte1, uint8_t indexbyte2)
{
    uint16_t index = (indexbyte1 << 8) | indexbyte2;
    
}

