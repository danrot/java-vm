#ifndef _BIPUSH_H_
#define _BIPUSH_H_

#include "../util/stack.h"

extern Stack *stack;

void bipush(int i);

void iconst_m1(void);
void iconst_0(void);
void iconst_1(void);
void iconst_2(void);
void iconst_3(void);
void iconst_4(void);
void iconst_5(void);

#endif
