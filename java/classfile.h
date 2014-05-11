#ifndef _CLASSFILE_H_
#define _CLASSFILE_H_

#include <inttypes.h>

#define CONSTANT_CLASS 7
#define CONSTANT_FIELDREF 9
#define CONSTANT_METHODREF 10
#define CONSTANT_INTERFACEMETHODREF 11
#define CONSTANT_STRING 8
#define CONSTANT_INTEGER 3
#define CONSTANT_FLOAT 4
#define CONSTANT_LONG 5
#define CONSTANT_DOUBLE 6
#define CONSTANT_NAMEANDTYPE 12
#define CONSTANT_UTF8 1
#define CONSTANT_METHODHANDLE 15
#define CONSTANT_METHODTYPE 16
#define CONSTANT_INVOKEDYNAMIC 18

typedef struct
{
    uint8_t tag;
} Constant;

typedef struct
{
    uint8_t tag;
    uint16_t name_index;
} ConstantClass;

typedef struct
{
    uint8_t tag;
    uint16_t class_index;
    uint16_t name_and_type_index;
} ConstantMethodRef;

typedef struct
{
    uint8_t tag;
    uint16_t length;
    uint8_t* bytes;
} ConstantUtf8;

typedef struct
{
    uint8_t tag;
    uint16_t name_index;
    uint16_t descriptor_index;
} ConstantNameAndType;

typedef struct
{
} Field;

typedef struct
{
} Method;

typedef struct
{
} Attribute;

typedef struct
{
    uint32_t magic;
    uint16_t minor_version;
    uint16_t major_version;
    uint16_t constant_count;
    Constant** constants;
    uint16_t access_flags;
    uint16_t this_class;
    uint16_t super_class;
    uint16_t interfaces_count;
    uint16_t interfaces;
    uint16_t fields_count;
    Field* fields;
    uint16_t methods_count;
    Method* methods;
    uint16_t attributes_count;
    Attribute* attributes;
} ClassFile;

ClassFile* classfile_init(char* filename);
static void generate_constant_class(ClassFile* classfile, FILE* file, int number);
static void generate_constant_methodref(ClassFile* classfile, FILE* file, int number);
static void generate_constant_utf8(ClassFile* classfile, FILE* file, int number);
static void generate_constant_nameandtype(ClassFile* classfile, FILE* file, int number);
void classfile_destroy(ClassFile* classfile);
static void read8(uint8_t* ptr, size_t count, FILE* stream);
static void read16(uint16_t* ptr, size_t count, FILE* stream);
static void read32(uint32_t* ptr, size_t count, FILE* stream);

#endif
