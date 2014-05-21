#include "invoke.h"
#include "../classfile.h"

void invokestatic(uint8_t indexbyte1, uint8_t indexbyte2)
{
    printf("invokestatic\n");
    uint16_t index = (indexbyte1 << 8) | indexbyte2;
    printf("invokestatic: load constant %i\n", index);
    
    ConstantMethodRef* methodref =  (ConstantMethodRef*) frame->classfile->constants[index];
    
    // TODO load classfile
    
    printf("invokestatic: load method %i\n", methodref->name_and_type_index);
    char* name = classfile_get_constant_string(frame->classfile, ((ConstantNameAndType*) frame->classfile->constants[methodref->name_and_type_index])->name_index);
    const Method* method = classfile_get_method_by_name(frame->classfile, name); // TODO use correct classfile
    
    if (method->access_flags & METHOD_ACCESSFLAG_NATIVE) {
        invokenative(name);
    } else {
        int parameters, i;
        
        // TODO get parameters
        //printf("invokestatic: %s\n", classfile_get_constant_string(frame->classfile, method->descriptor_index));
        parameters = 2;
        
        // create new frame and set it as current
        frame = frame_init(frame->classfile, method, frame);
        
        // TODO load parameters
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

