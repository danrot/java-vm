#ifndef _INVOKE_H_
#define _INVOKE_H_

#include <inttypes.h>

#include "../frame.h"

extern Frame* frame;

void invokestatic(uint8_t indexbyte1, uint8_t indexbyte2);
static void invokenative(char* name);

#endif
