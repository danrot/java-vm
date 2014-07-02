#ifndef _BRANCH_H_
#define _BRANCH_H_

#include "../frame.h"

extern Frame* frame;

void ifle(uint8_t branchbyte1, uint8_t branchbyte2);
void ifge(uint8_t branchbyte1, uint8_t branchbyte2);

void if_icmpge(uint8_t branchbyte1, uint8_t branchbyte2);

void ifnonnull(uint8_t branchbyte1, uint8_t branchbyte2);

void gotoj(uint8_t branchbyte1, uint8_t branchbyte2);

static void jump(uint8_t branchbyte1, uint8_t branchbyte2);

#endif
