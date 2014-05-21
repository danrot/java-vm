#ifndef _CLASSFILE_H_
#define _CLASSFILE_H_

#include <inttypes.h>
#include <stdio.h>

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

#define ATTRIBUTE_CONSTANTVALUE "ConstantValue"
#define ATTRIBUTE_CODE "Code"
#define ATTRIBUTE_STACKMAPTABLE "StackMapTable"
#define ATTRIBUTE_EXCEPTIONS "Exceptions"
#define ATTRIBUTE_INNERCLASSES "InnerClasses"
#define ATTRIBUTE_ENCLOSINGMETHOD "EnclosingMethod"
#define ATTRIBUTE_SYNTHETIC "Synthetic"
#define ATTRIBUTE_SIGNATURE "Signature"
#define ATTRIBUTE_SOURCEFILE "SourceFile"
#define ATTRIBUTE_SOURCEDEBUGEXTENSION "SourceDebugExtension"
#define ATTRIBUTE_LINENUMBERTABLE "LineNumberTable"
#define ATTRIBUTE_LOCALVARIABLETABLE "LocalVariableTable"
#define ATTRIBUTE_LOCALVARIABLETYPETABLE "LocalVariableTypeTable"
#define ATTRIBUTE_DEPRECATED "Deprecated"
#define ATTRIBUTE_RUNTIMEVISIBLEANNOTATIONS "RuntimeVisibleAnnotations"
#define ATTRIBUTE_RUNTIMEINVISIBLEANNOTATIONS "RuntimeInvisibleAnnotations"
#define ATTRIBUTE_RUNTIMEVISIBLEPARAMETERANNOTATIONS "RuntimeVisibleParameterAnnotations"
#define ATTRIBUTE_RUNTIMEINVISIBLEPARAMETERANNOTATIONS "RuntimeInvisibleParameterAnnotations"
#define ATTRIBUTE_ANNOTATIONDEFAULT "AnnotationDefault"
#define ATTRIBUTE_BOOTSTRAPMETHODS "BootstrapMethods"

#define METHOD_ACCESSFLAG_NATIVE 0x100

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
    uint16_t class_index;
    uint16_t name_and_type_index;
} ConstantFieldRef;

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
    uint16_t attribute_name_index;
    uint32_t attribute_length;
} Attribute;

typedef struct
{
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;
} ExceptionTable;

typedef struct
{
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t max_stack;
    uint16_t max_locals;
    uint32_t code_length;
    uint8_t* code;
    uint16_t exception_table_length;
    ExceptionTable* exception_table;
    uint16_t attributes_count;
    Attribute** attributes;
} AttributeCode;

typedef struct
{
    uint16_t start_pc;
    uint16_t line_number;
} LineNumberTable;

typedef struct
{
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t line_number_table_length;
    LineNumberTable* line_number_table;
} AttributeLineNumberTable;

typedef struct
{
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t sourcefile_index;
} AttributeSourceFile;

typedef struct
{
} Field;

typedef struct
{
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    Attribute** attributes;
} Method;

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
    Attribute** attributes;
} ClassFile;

ClassFile* classfile_init(char* filename);
char* classfile_get_constant_string(const ClassFile* classfile, int index);
const Method* classfile_get_method_by_name(const ClassFile* classfile, char* name);
int classfile_get_method_parameter_count(const ClassFile* classfile, const Method* method);
const AttributeCode* classfile_get_code_from_method(const ClassFile* classfile, const Method* method);
void classfile_destroy(ClassFile* classfile);

static void generate_constant_class(ClassFile* classfile, FILE* file, int number);
static void generate_constant_fieldref(ClassFile* classfile, FILE* file, int number);
static void generate_constant_methodref(ClassFile* classfile, FILE* file, int number);
static void generate_constant_utf8(ClassFile* classfile, FILE* file, int number);
static void generate_constant_nameandtype(ClassFile* classfile, FILE* file, int number);
static Attribute* generate_attribute(ClassFile* classfile, FILE* file);
static AttributeSourceFile* generate_attribute_sourcefile(ClassFile* classfile, FILE* file, int attribute_name_index);
static AttributeCode* generate_attribute_code(ClassFile* classfile, FILE* file, int attribute_name_index);
static AttributeLineNumberTable* generate_attribute_linenumbertable(ClassFile* classfile, FILE* file, int attribute_name_index);
static void read8(uint8_t* ptr, size_t count, FILE* stream);
static void read16(uint16_t* ptr, size_t count, FILE* stream);
static void read32(uint32_t* ptr, size_t count, FILE* stream);

#endif
