#ifndef VRAM_H
#define VRAM_H

#include "common.h"
#include "structs.h"

float          func_800273E0(ColHit *hit, Task *task, unsigned char arg2, float arg3);
unsigned short func_800277C0(float x, float y, float z, Task *task);
ColHit         func_80028B28(float x, float y, float z, float move_x, float move_y, float move_z);
int            func_80029E08(float x, float y, float z);
ColHit         func_8002A458(float x, float y, float z, float move_x, float move_y, float move_z);
ColHit         func_8002A718(float x, float y, float z);
void           func_8002A7BC(ColHit *ray, Task *task);

extern ColPlane *D_80168F60;
extern ColNode  *D_80168F64;

#endif // VRAM_H
