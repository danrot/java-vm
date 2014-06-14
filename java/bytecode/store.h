#ifndef _STORE_H_
#define _STORE_H_

#include "../frame.h"

extern Frame *frame;

void istore(int index);
void istore_0();
void istore_1();
void istore_2();
void istore_3();

void astore(uint8_t index);
void astore_0();
void astore_1();
void astore_2();
void astore_3();

void iastore();

#endif
