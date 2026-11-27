#ifndef JOYPAD_H
#define JOYPAD_H

#include "common.h"
#include "structs.h"

void func_80004910(void);
void func_80004964(unsigned char arg0, DemoKey *arg1);
int  func_800049D0(void);
void func_80004AF8(void);

extern OSMesgQueue    D_80167170;
extern unsigned char  D_80167190[2];
extern unsigned char  D_80167192[2];
extern unsigned short D_801671B8;
extern unsigned char  D_801671BC;
extern OSPfs          D_801671F0[4];
extern unsigned char  D_80167390[0x10];

#endif // JOYPAD_H
