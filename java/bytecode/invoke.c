#include "invoke.h"
#include "../classfile.h"

void invokestatic(uint8_t indexbyte1, uint8_t indexbyte2)
{
    const ClassFile* classfile;
    uint16_t index = (indexbyte1 << 8) | indexbyte2;
    
    ConstantMethodRef* methodref =  (ConstantMethodRef*) frame->classfile->constants[index];
    char* classname = classfile_get_constant_string(frame->classfile, ((ConstantClass*)frame->classfile->constants[methodref->class_index])->name_index);
    
    classfile = classfile_init(classname);
    
    char* name = classfile_get_constant_string(frame->classfile, ((ConstantNameAndType*) frame->classfile->constants[methodref->name_and_type_index])->name_index);
    const Method* method = classfile_get_method_by_name(classfile, name);
    
    // TODO implement monitor
    
    if (method->access_flags & METHOD_ACCESSFLAG_NATIVE) {
        invokenative(name);
    } else {
        invoke(classfile, method, 0);
    }
}

void invokespecial(uint8_t indexbyte1, uint8_t indexbyte2)
{
    const ClassFile* classfile;

    uint16_t index = (indexbyte1 << 8) | indexbyte2;
    
    ConstantMethodRef* methodref =  (ConstantMethodRef*) frame->classfile->constants[index];
    char* classname = classfile_get_constant_string(frame->classfile, ((ConstantClass*)frame->classfile->constants[methodref->class_index])->name_index);
    
    // TODO check protected
    
    classfile = classfile_init(classname);
    
    char* name = classfile_get_constant_string(frame->classfile, ((ConstantNameAndType*) frame->classfile->constants[methodref->name_and_type_index])->name_index);
    const Method* method = classfile_get_method_by_name(classfile, name);
    
    // TODO check conditions
    
    // TODO implement monitor
    
    if (method->access_flags & METHOD_ACCESSFLAG_NATIVE) {
        invokenative(name);
    } else {
        invoke(classfile, method, 1);
    }
}

void invokevirtual(uint8_t indexbyte1, uint8_t indexbyte2)
{
    const ClassFile* classfile;
    uint16_t index = (indexbyte1 << 8) | indexbyte2;
    
    ConstantMethodRef* methodref =  (ConstantMethodRef*) frame->classfile->constants[index];
    char* classname = classfile_get_constant_string(frame->classfile, ((ConstantClass*)frame->classfile->constants[methodref->class_index])->name_index);
    
    classfile = classfile_init(classname);
    
    char* name = classfile_get_constant_string(frame->classfile, ((ConstantNameAndType*) frame->classfile->constants[methodref->name_and_type_index])->name_index);
    const Method* method = classfile_get_method_by_name(classfile, name);
    
    // TODO check if not initialization method
    
    // TODO check protected
    
    // TODO check signature polymorphy
    
    // TODO check if the method is overriden
    
    // TODO implement monitor
    
    if (method->access_flags & METHOD_ACCESSFLAG_NATIVE) {
        invokenative(name);
    } else {
        invoke(classfile, method, 1);
    }
}

static void invokenative(char* name)
{
    if (strcmp(name, "print") == 0) {
        printf("%i\n", stack_pop(frame->stack));
    }
}

static void invoke(const ClassFile* classfile, const Method* method, int with_object) {
    int parameters, i;
    
    // TODO check correctness of parameters
    parameters = classfile_get_method_parameter_count(classfile, method);
    if (with_object) {
        parameters = parameters + 1;
    }
    
    // create new frame and set it as current
    frame = frame_init(classfile, method, frame);
    
    // load parameters
    for (i = parameters - 1; i >= 0; i--) {
        frame->locals[i] = stack_pop(frame->parent->stack);
    }
    
    // let the frame run
    frame_run(frame);
}

