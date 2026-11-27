#ifndef F_5A4730_H
#define F_5A4730_H

#include "common.h"
#include "structs.h"

void  func_801E8820_5A4730(ObjSolid *solid, unsigned short arg1, unsigned int *arg2);
void  func_801E8858_5A4768(ObjSolid *solid, unsigned short arg1);
void  func_801E8890_5A47A0(ObjSolid *solid, unsigned short arg1, unsigned int *arg2, unsigned char *arg3, short *arg4);
void  func_801E8964_5A4874(Task *task, unsigned char kind);
int   func_801E8C44_5A4B54(Task *task, unsigned char kind);
int   func_801E8C98_5A4BA8(Task *task, unsigned char kind);
Task *func_801E8D30_5A4C40(Task *task, unsigned char kind);
void  func_801E8D90_5A4CA0(Task *task, int arg1);
void  func_801E8E24_5A4D34(Task *task, int arg1);
void  func_801E8EC4_5A4DD4(Task *task, ObjSolid *obj);
void  func_801EA5E4_5A64F4(Task *effect, Task *player, Task *target);

extern void (*D_80204868_5C0778[])(Task *, Obj *);
extern Gfx D_802049C0_5C08D0[];

#endif // F_5A4730_H
