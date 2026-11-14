#ifndef GAME_LOOP_H
#define GAME_LOOP_H


#include "common.h"

typedef struct GameStepTable {
    /* 0x00 */ void (*funcs[18])(void);
} GameStepTable; // size = 0x48

void func_80002040(void);
void func_800020B8(void);
void func_80002138(void);
void func_8000236C(void);
void func_80002454(void);
void func_80002518(void);
void func_80002718(void);
void func_80002938(void);
void func_80002A98(void);
void func_80002AB8(void);
void func_80002C7C(void);
void func_80002D94(void);
void func_80002DE4(void);
void func_80002E70(void);
void func_80002EFC(void);
void func_80002F54(void);
void func_800030F0(void);
void func_80003328(void);
void func_80003358(void);
void func_80003380(unsigned char mode);
void func_800033B0(void);
void func_800033EC(void);
void func_80003428(unsigned char step);
void func_80003478(void);
void func_800034D0(void);
void func_80003528(unsigned char step);
void func_80003578(void);
void func_800035D0(void);
void func_80003628(unsigned char step);
void func_80003678(void);
void func_800036D0(void);
void func_80003728(unsigned char step);
void func_8000378C(void);
void func_800037E4(void);
void func_8000383C(void);
void func_80003880(void);
void func_800038E4(void);
void func_8000394C(void);

void func_801CB460(void);
Gfx *func_801CB668(int pool, Gfx *dl);
void func_801CB6C0(void);
int  func_801CB9C8(void);
int  func_801CBB70(Gfx **dl, unsigned int base);
int  func_801D1580(void);

extern int D_80058868[40];

extern GameStepTable D_80058908;

#endif // GAME_LOOP_H
