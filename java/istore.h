#ifndef _ISTORE_H_
#define _ISTORE_H_

#include "../util/stack.h"

extern Stack *stack;
extern int *locals;

void istore(int index);
void istore_0();
void istore_1();
void istore_2();
void istore_3();

#endif
