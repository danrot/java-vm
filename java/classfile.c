#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <byteswap.h>
#include <string.h>

#include "classfile.h"

ClassFile* classfile_init(const char* filename) {
    void* classfile_address = hashtable_get(classfiles, filename);
    if (classfile_address == NULL) {
        printf("classfile_init: load new file\n");
        int i;
        char* tmp = malloc(sizeof(char) * strlen(filename) + 1);
        ClassFile* classfile = malloc(sizeof(ClassFile));
        
        strcpy(tmp, filename);
            
        // get path to class file
        strcat(tmp, ".class");
        
        FILE* file = fopen(tmp, "r");
        if (!file) {
            printf("classfile_init: Unable to open file!");
            exit(1);
        }
        
        // magic number
        read32(&classfile->magic, 1, file);
        if (classfile->magic != 0xCAFEBABE) {
            printf("classfile_init: Invalid magic number!");
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
                    generate_constant_fieldref(classfile, file, i);
                    break;
                case CONSTANT_METHODREF:
                    generate_constant_methodref(classfile, file, i);
                    break;
                case CONSTANT_INTERFACEMETHODREF:
                    printf("interface methodref\n");
                    break;
                case CONSTANT_STRING:
                    printf("string\n");
                    break;
                case CONSTANT_INTEGER:
                    printf("integer\n");
                    break;
                case CONSTANT_FLOAT:
                    printf("float\n");
                    break;
                case CONSTANT_LONG:
                    printf("long\n");
                    break;
                case CONSTANT_DOUBLE:
                    printf("double\n");
                    break;
                case CONSTANT_NAMEANDTYPE:
                    generate_constant_nameandtype(classfile, file, i);
                    break;
                case CONSTANT_UTF8:
                    generate_constant_utf8(classfile, file, i);
                    break;
                case CONSTANT_METHODHANDLE:
                    printf("method handle\n");
                    break;
                case CONSTANT_METHODTYPE:
                    printf("method type\n");
                    break;
                case CONSTANT_INVOKEDYNAMIC:
                    printf("invoke dynmic\n");
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
            int j = 0;
        
            read16(&classfile->methods[i].access_flags, 1, file);
            read16(&classfile->methods[i].name_index, 1, file);
            read16(&classfile->methods[i].descriptor_index, 1, file);
            read16(&classfile->methods[i].attributes_count, 1, file);
            
            if (classfile->methods[i].attributes_count) {
                classfile->methods[i].attributes = malloc(classfile->methods[i].attributes_count * sizeof(Attribute*));
                for (j = 0; j < classfile->methods[i].attributes_count; j++) {
                    classfile->methods[i].attributes[j] = generate_attribute(classfile, file);
                }
            }
        }
        
        read16(&classfile->attributes_count, 1, file);
        
        if (classfile->attributes_count) {
            classfile->attributes = malloc(classfile->attributes_count * sizeof(Attribute*));
            for (i = 0; i < classfile->attributes_count; i++) {
                classfile->attributes[i] = generate_attribute(classfile, file);
            }
        }
        
        fclose(file);
        
        free(tmp);
        
        printf("classfile_init: put new file for %s to %x\n", filename, classfile);
        hashtable_put(classfiles, filename, classfile);
        
        return classfile;
    } else {
        printf("classfile_init: load existing file for %s from %x\n", filename, classfile_address);
        return (ClassFile*) classfile_address;
    }
}

char* classfile_get_constant_string(const ClassFile* classfile, int index)
{
    return ((ConstantUtf8*) classfile->constants[index])->bytes;
}

const Method* classfile_get_method_by_name(const ClassFile* classfile, char* name)
{
    int i;
        
    for (i = 0; i < classfile->methods_count; i++) {
        if (strcmp(classfile_get_constant_string(classfile, classfile->methods[i].name_index), name) == 0) {
            return &classfile->methods[i];
        }
    }
}

int classfile_get_method_parameter_count(const ClassFile* classfile, const Method* method)
{
    int count;
    char* descriptor = classfile_get_constant_string(classfile, method->descriptor_index);
    
    count = strlen(descriptor) - 3; // TODO make sure if this is working all the time (probably not...)
    
    return count;
}

void classfile_destroy(ClassFile* classfile)
{
    // TODO destroy every single constant
    free(classfile->constants);
    // TODO destroy every method and attribute
    free(classfile);
}

const AttributeCode* classfile_get_code_from_method(const ClassFile* classfile, const Method* method)
{
    int i;
    
    for (i = 0; i < method->attributes_count; i++) {
        if (strcmp(classfile_get_constant_string(classfile, method->attributes[i]->attribute_name_index), ATTRIBUTE_CODE) == 0) {
            return (AttributeCode*) method->attributes[i];
        }
    }
}

static void generate_constant_class(ClassFile* classfile, FILE* file, int number)
{
    ConstantClass* class = malloc(sizeof(ConstantClass));
    class->tag = CONSTANT_CLASS;
    
    read16(&class->name_index, 1, file);
    
    classfile->constants[number] = (Constant*) class;
}

static void generate_constant_fieldref(ClassFile* classfile, FILE* file, int number)
{
    ConstantFieldRef* fieldref = malloc(sizeof(ConstantFieldRef));
    fieldref->tag = CONSTANT_FIELDREF;
    
    read16(&fieldref->class_index, 1, file);
    read16(&fieldref->name_and_type_index, 1, file);
    
    classfile->constants[number] = (Constant*) fieldref;
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
    
    utf8->bytes = malloc((utf8->length + 1) * sizeof(uint8_t));
    for (i = 0; i < utf8->length; i++) {
        read8(&utf8->bytes[i], 1, file);
    }
    utf8->bytes[utf8->length] = '\0';
    
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

static Attribute* generate_attribute(ClassFile* classfile, FILE* file)
{
    uint16_t attribute_name_index;
    char* attribute_name; // TODO should be const
    read16(&attribute_name_index, 1, file);
    
    attribute_name = classfile_get_constant_string(classfile, attribute_name_index);
    
    if (strcmp(attribute_name, ATTRIBUTE_CODE) == 0) {
        return ((Attribute*) generate_attribute_code(classfile, file, attribute_name_index)); //FIXME is this really correct?
    } else if(strcmp(attribute_name, ATTRIBUTE_SOURCEFILE) == 0) {
        return ((Attribute*) generate_attribute_sourcefile(classfile, file, attribute_name_index));
    } else {
        // TODO handle other attributes as well
        printf("generate_attributes: missing attribute %s\n", attribute_name);
    }
}

static AttributeSourceFile* generate_attribute_sourcefile(ClassFile* classfile, FILE* file, int attribute_name_index)
{
    AttributeSourceFile* source = malloc(sizeof(AttributeSourceFile));
    
    source->attribute_name_index = attribute_name_index;
    read32(&source->attribute_length, 1, file);
    read16(&source->sourcefile_index, 1, file);
    
    return source;
}

static AttributeCode* generate_attribute_code(ClassFile* classfile, FILE* file, int attribute_name_index)
{
    int i;
    AttributeCode* code = malloc(sizeof(AttributeCode));
    
    code->attribute_name_index = attribute_name_index;
    read32(&code->attribute_length, 1, file);
    read16(&code->max_stack, 1, file);
    read16(&code->max_locals, 1, file);
    read32(&code->code_length, 1, file);
    
    code->code = malloc(code->code_length * sizeof(uint8_t));
    for (i = 0; i < code->code_length; i++) {
        read8(&code->code[i], 1, file);
    }
    
    read16(&code->exception_table_length, 1, file);
    
    if (code->exception_table_length) {
        code->exception_table = malloc(code->exception_table_length * sizeof(ExceptionTable));
        for (i = 0; i < code->exception_table_length; i++) {
            read16(&code->exception_table[i].start_pc, 1, file);
            read16(&code->exception_table[i].end_pc, 1, file);
            read16(&code->exception_table[i].handler_pc, 1, file);
            read16(&code->exception_table[i].catch_type, 1, file);
        }
    }
    
    read16(&code->attributes_count, 1, file);
    
    code->attributes = malloc(code->attributes_count * sizeof(Attribute*));
    for (i = 0; i < code->attributes_count; i++) {
        uint16_t attribute_name_index;
        char* attribute_name;
        
        read16(&attribute_name_index, 1, file);
        attribute_name = classfile_get_constant_string(classfile, attribute_name_index);
        
        if (strcmp(attribute_name, ATTRIBUTE_LINENUMBERTABLE) == 0) {
            code->attributes[i] = ((Attribute*) generate_attribute_linenumbertable(classfile, file, attribute_name_index)); //FIXME is that really correct?
        } else {
            // TODO add other attributes
            printf("generate_attribute_code: missing attribute %s\n", attribute_name);
        }
    }
    
    return code;
}

static AttributeLineNumberTable* generate_attribute_linenumbertable(ClassFile* classfile, FILE* file, int attribute_name_index)
{
    int i;
    AttributeLineNumberTable* linenumbertable = malloc(sizeof(AttributeLineNumberTable));
    linenumbertable->attribute_name_index = attribute_name_index;
    
    read32(&linenumbertable->attribute_length, 1, file);
    read16(&linenumbertable->line_number_table_length, 1, file);
    
    if (linenumbertable->line_number_table_length) {
        linenumbertable->line_number_table = malloc(linenumbertable->line_number_table_length * sizeof(LineNumberTable));
        for (i = 0; i < linenumbertable->line_number_table_length; i++) {
            read16(&linenumbertable->line_number_table[i].start_pc, 1, file);
            read16(&linenumbertable->line_number_table[i].line_number, 1, file);
        }
    }
    
    return linenumbertable;
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
