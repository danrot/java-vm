#ifndef _ALOAD_H_
#define _ALOAD_H_

#include "../frame.h"

extern Frame *frame;

void aload(uint8_t index);
void aload_0();
void aload_1();
void aload_2();
void aload_3();

void iaload();

#endif
