#ifndef _FIELD_H_
#define _FIELD_H_

#include "../frame.h"

extern Frame* frame;

void putfield(uint8_t indexbyte1, uint8_t indexbyte2);
void getfield(uint8_t indexbyte1, uint8_t indexbyte2);

void getstatic(uint8_t indexbyte1, uint8_t indexbyte2);

#endif
