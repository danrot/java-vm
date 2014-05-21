#include "invoke.h"
#include "../classfile.h"

void invokestatic(uint8_t indexbyte1, uint8_t indexbyte2)
{
    const ClassFile* classfile;
    
    printf("invokestatic\n");
    uint16_t index = (indexbyte1 << 8) | indexbyte2;
    printf("invokestatic: load constant %i\n", index);
    
    ConstantMethodRef* methodref =  (ConstantMethodRef*) frame->classfile->constants[index];
    
    // TODO load classfile
    classfile = frame->classfile;
    
    printf("invokestatic: load method %i\n", methodref->name_and_type_index);
    char* name = classfile_get_constant_string(classfile, ((ConstantNameAndType*) classfile->constants[methodref->name_and_type_index])->name_index);
    const Method* method = classfile_get_method_by_name(classfile, name);
    
    if (method->access_flags & METHOD_ACCESSFLAG_NATIVE) {
        invokenative(name);
    } else {
        int parameters, i;
        
        // TODO get parameters
        parameters = classfile_get_method_parameter_count(classfile, method);
        printf("invokestatic: %i\n", parameters);
        
        // create new frame and set it as current
        frame = frame_init(classfile, method, frame);
        
        // load parameters
        for (i = 0; i < parameters; i++) {
            frame->locals[i] = stack_pop(frame->parent->stack);
        }
        
        // let the frame run
        frame_run(frame);
    }
}

static void invokenative(char* name)
{
    if (strcmp(name, "print") == 0) {
        printf("%i\n", stack_pop(frame->stack));
    }
}

