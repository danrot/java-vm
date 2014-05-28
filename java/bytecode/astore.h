#ifndef _ASTORE_H_
#define _ASTORE_H_

#include "../frame.h"

extern Frame *frame;

void astore(uint8_t index);
void astore_0();
void astore_1();
void astore_2();
void astore_3();

void iastore();

#endif
