#ifndef WAVE_UTY_H
#define WAVE_UTY_H

#include "common.h"
#include "structs.h"

void           func_80013940(void);
void           func_800139A4(unsigned short i);
void           func_80013A24(unsigned short wave_no);
int            func_80013AC4(unsigned short *wave_no_list);
int            func_80013B14(unsigned short wave_no);
void           func_80013C0C(unsigned short arg0);
void           func_80013C70(unsigned short *arg0);
int            func_80013C90(unsigned short *ids, unsigned char steps);
int            func_800141C4(unsigned int wave_no);
int            func_80014218(ObjSolid *solid);
unsigned char *func_800144E8(unsigned int id, unsigned char *src, unsigned char *dst);
unsigned char *func_800145B4(unsigned int id, unsigned char *data);
unsigned int   func_80014698(unsigned int id, int *rom);
void           func_8001481C(Task *task);
int            func_80014840(int arg0, unsigned int wave_no);

extern void *D_80069920[1311];
extern Wave  D_80167FC0[WAVE_DECODE_MAX];

#endif // WAVE_UTY_H
