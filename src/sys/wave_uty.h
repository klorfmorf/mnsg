#ifndef WAVE_UTY_H
#define WAVE_UTY_H

#include "common.h"
#include "structs.h"

void  func_80013940(void);
int   func_80013B14(unsigned short wave_no);
int   func_800141C4(unsigned int wave_no);
int   func_80014218(ObjSolid *solid);
void  func_8001481C(Task *task);
void  func_800148C0(AmemBlock *arg0, char *arg1, unsigned int arg2);
void *amemAlloc(AmemBlock *arg0, int size);
void *amemFree(AmemBlock *arg0, void *arg1);

extern Wave D_80167FC0[WAVE_DECODE_MAX];

#endif // WAVE_UTY_H
