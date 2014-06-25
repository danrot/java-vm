#ifndef _LOAD_H_
#define _LOAD_H_

#include "../frame.h"

extern Frame *frame;

void ldc(int index);

void iload(int index);
void iload_0();
void iload_1();
void iload_2();
void iload_3();

void lload(int index);
void lload_0();
void lload_1();
void lload_2();
void lload_3();

void aload(uint8_t index);
void aload_0();
void aload_1();
void aload_2();
void aload_3();

void iaload();

#endif
