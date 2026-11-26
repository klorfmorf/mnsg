#ifndef _5D1B10_H
#define _5D1B10_H
// Enemy overlay: shared enemy code (spawn setup, per-frame update, death and respawn).

#include "common.h"
#include "structs.h"

void  func_80216E1C_5D22EC(Task *task, int arg1);
void  func_802176C4_5D2B94(Task *task, int arg1);
void  func_80218A54_5D3F24(Task *task, EnemySpawn *spawn);
void func_8021925C_5D472C(Task *task, Obj *obj);
void  func_80218D7C_5D424C(Task *task, int arg1, int arg2, int arg3);
void  func_802192B4_5D4784(int arg0);
Task *func_80219CA0_5D5170(Task *task, unsigned char category);

#endif // _5D1B10_H
