#ifndef _PUSH_H_
#define _PUSH_H_

#include "../frame.h"

extern Frame *frame;

void bipush(uint8_t i);

void iconst_m1(void);
void iconst_0(void);
void iconst_1(void);
void iconst_2(void);
void iconst_3(void);
void iconst_4(void);
void iconst_5(void);

void sipush(uint8_t byte1, uint8_t byte2);

#endif
