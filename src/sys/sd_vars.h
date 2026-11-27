#ifndef SD_VARS_H
#define SD_VARS_H

/*
 * This does not get included in sd_main.c because the order of declarations changes.
 * On IDO -g3, this causes the layout of variables in .bss to change.
*/

#include "common.h"
#include "structs.h"

extern unsigned char  D_80172970;
extern unsigned char  D_80172971;
extern unsigned char  D_80172972[2];
extern ALBankFile    *D_801729A8[8];
extern unsigned short D_801C09CA;
extern unsigned char  D_801C09CC;
extern unsigned char  D_801C09CD;
extern signed char    D_801C09CE;
extern unsigned char  D_801C09CF;
extern unsigned char  D_801C09D0;
extern unsigned char  D_801C09D1;
extern unsigned char  D_801C09D2;
extern unsigned char  D_801C09D3;
extern unsigned char  D_801C09D4;
extern unsigned char  D_801C09D5;
extern unsigned char  D_801C09D6[2];
extern unsigned short D_801C09D8;
extern unsigned char  D_801C09DA;
extern signed char    D_801C09DB;
extern unsigned char  D_801C09DC[4];
extern unsigned char  D_801C09E0[8];
extern unsigned short D_801C09E8[4];
extern ALVoice        D_801C0A68[16];
extern SoundWork      D_801C0C28[16];
extern SoundWork     *sptr;
extern unsigned char *mptr;
extern void          *D_801C7730[4];

#endif // SD_VARS_H
