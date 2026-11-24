#ifndef JOYPAD_H
#define JOYPAD_H

#include "common.h"
#include "structs.h"

void func_80004910(void);
void func_800049D0(void);
void func_80004AF8(void);

extern OSMesgQueue D_80167170;
extern OSPfs       D_801671F0[4];

#endif // JOYPAD_H
