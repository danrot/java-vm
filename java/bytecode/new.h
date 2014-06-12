#ifndef _NEW_H_
#define _NEW_H_

#define ATYPE_BOOLEAN 4
#define ATYPE_CHAR 5
#define ATYPE_FLOAT 6
#define ATYPE_DOUBLE 7
#define ATYPE_BYTE 8
#define ATYPE_SHORT 9
#define ATYPE_INT 10
#define ATYPE_LONG 11

#include "../frame.h"

extern Frame* frame;

void newarray(uint8_t atype);
void new(uint8_t indexbyte1, uint8_t indexbyte2);

#endif
