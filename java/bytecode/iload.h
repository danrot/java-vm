#ifndef _ILOAD_H_
#define _ILOAD_H_

#include "../frame.h"

extern Frame *frame;
extern int *locals;

void iload(int index);
void iload_0();
void iload_1();
void iload_2();
void iload_3();

#endif
