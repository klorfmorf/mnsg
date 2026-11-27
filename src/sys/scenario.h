#ifndef SCENARIO_H
#define SCENARIO_H

#include "common.h"
#include "structs.h"

void  func_8003D01C(Task *task, Obj *obj);
int   func_8003D310(int index);
int   func_8003D388(int index, int controller);
void  func_8003D428(void);
void  func_8003EFB0(void);
int   func_8003F0FC(void);
int   func_8003F1D8(void);
short func_8003F1FC(int value);
void  func_8003F5FC(int frames);

extern Task         *D_80077860;
extern unsigned int  D_801C7740;
extern int           D_801C7748;
extern int           D_801C774C;
extern int           D_801C7750;
extern int           D_801C7770;
extern int           D_801C7798;
extern int           D_801C77A0[2];
extern int           D_801C77D8;
extern int           D_801C7900;
extern int           D_801C7920;
extern int           D_801C792C;
extern unsigned char D_801C7930[16];

#endif // SCENARIO_H
