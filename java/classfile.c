#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <byteswap.h>

#include "classfile.h"

ClassFile* classfile_init(char* filename) {
    int i;
    ClassFile* classfile = malloc(sizeof(ClassFile));
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Unable to open file!");
        exit(1);
    }
    
    // magic number
    read32(&classfile->magic, 1, file);
    if (classfile->magic != 0xCAFEBABE) {
        printf("Invalid magic number!");
        exit(1);
    }
    
    read16(&classfile->minor_version, 1, file);
    
    read16(&classfile->major_version, 1, file);
    
    read16(&classfile->constant_count, 1, file);
    
    classfile->constants = malloc(classfile->constant_count * sizeof(Constant*));
    for (i = 1; i < classfile->constant_count; i++) {
        uint8_t tag;
        read8(&tag, 1, file);
        
        switch (tag) {
            case CONSTANT_CLASS:
                generate_constant_class(classfile, file, i);
                break;
            case CONSTANT_FIELDREF:
                printf("fieldref");
                break;
            case CONSTANT_METHODREF:
                generate_constant_methodref(classfile, file, i);
                break;
            case CONSTANT_INTERFACEMETHODREF:
                printf("interface methodref");
                break;
            case CONSTANT_STRING:
                printf("string");
                break;
            case CONSTANT_INTEGER:
                printf("integer");
                break;
            case CONSTANT_FLOAT:
                printf("float");
                break;
            case CONSTANT_LONG:
                printf("long");
                break;
            case CONSTANT_DOUBLE:
                printf("double");
                break;
            case CONSTANT_NAMEANDTYPE:
                generate_constant_nameandtype(classfile, file, i);
                break;
            case CONSTANT_UTF8:
                generate_constant_utf8(classfile, file, i);
                break;
            case CONSTANT_METHODHANDLE:
                printf("method handle");
                break;
            case CONSTANT_METHODTYPE:
                printf("method type");
                break;
            case CONSTANT_INVOKEDYNAMIC:
                printf("invoke dynmic");
                break;
        }
    }
    
    read16(&classfile->access_flags, 1, file);
    
    read16(&classfile->this_class, 1, file);
    
    read16(&classfile->super_class, 1, file);
    
    read16(&classfile->interfaces_count, 1, file);
    
    // TODO read interfaces
    
    read16(&classfile->fields_count, 1, file);
    
    // TODO read fields
    
    read16(&classfile->methods_count, 1, file);
    
    classfile->methods = malloc(classfile->methods_count * sizeof(Method));
    for (i = 0; i < classfile->methods_count; i++) {
        
    }
    
    fclose(file);
    
    return classfile;
}

static void generate_constant_class(ClassFile* classfile, FILE* file, int number)
{
    ConstantClass* class = malloc(sizeof(ConstantClass));
    class->tag = CONSTANT_CLASS;
    
    read16(&class->name_index, 1, file);
    
    classfile->constants[number] = (Constant*) class;
}

static void generate_constant_methodref(ClassFile* classfile, FILE* file, int number)
{
    ConstantMethodRef* methodref = malloc(sizeof(ConstantMethodRef));
    methodref->tag = CONSTANT_METHODREF;
    
    read16(&methodref->class_index, 1, file);
    read16(&methodref->name_and_type_index, 1, file);
    
    classfile->constants[number] = (Constant*) methodref;
}

static void generate_constant_utf8(ClassFile* classfile, FILE* file, int number)
{
    int i;
    ConstantUtf8* utf8 = malloc(sizeof(ConstantUtf8));
    utf8->tag = CONSTANT_UTF8;
    
    read16(&utf8->length, 1, file);
    
    utf8->bytes = malloc(utf8->length * sizeof(uint8_t));
    for (i = 0; i < utf8->length; i++) {
        read8(&utf8->bytes[i], 1, file);
    }
    
    classfile->constants[number] = (Constant*) utf8;
}

static void generate_constant_nameandtype(ClassFile* classfile, FILE* file, int number)
{
    ConstantNameAndType* nameandtype = malloc(sizeof(ConstantNameAndType));
    nameandtype->tag = CONSTANT_NAMEANDTYPE;
    
    read16(&nameandtype->name_index, 1, file);
    read16(&nameandtype->descriptor_index, 1, file);
    
    classfile->constants[number] = (Constant*) nameandtype;
}

void classfile_destroy(ClassFile* classfile)
{
    // TODO destroy every single constant
    free(classfile->constants);
    free(classfile);
}

static void read8(uint8_t* ptr, size_t count, FILE* stream)
{
    fread(ptr, sizeof(uint8_t), 1, stream);
}

static void read16(uint16_t* ptr, size_t count, FILE* stream)
{
    fread(ptr, sizeof(uint16_t), 1, stream);
    *ptr = __bswap_16(*ptr);
}

static void read32(uint32_t* ptr, size_t count, FILE* stream)
{
    fread(ptr, sizeof(uint32_t), 1, stream);
    *ptr = __bswap_32(*ptr);
}
