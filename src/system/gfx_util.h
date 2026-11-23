#ifndef GFX_UTIL_H
#define GFX_UTIL_H

#include "common.h"
#include "structs.h"

void func_8001C970(ObjSolid *dst, ObjSolid *src);
void func_8001E2BC(float (*mf)[4], ObjSolid *solid);
void func_8001E380(float (*mf)[4], ObjSolid *solid);
void func_8001E444(float (*mf)[4], float x, float y, float z);
void func_8001E634(float (*mf)[4], unsigned short rx, unsigned short ry, unsigned short rz);
void func_8001EEF4(float *tx, float *ty, float *tz, unsigned short *rx, unsigned short *ry, unsigned short *rz, float *sx, float *sy, float *sz, float (*mf)[4]);
void func_8001F2D8(float (*a)[4], float (*b)[4]);
void func_8001F5F8(float (*mf)[4], Mtx *mtx);
void func_8001F878(unsigned short *rx, unsigned short *ry, unsigned short *rz);

extern unsigned short D_801689F0;
extern unsigned short D_801689F2;
extern unsigned short D_801689F4;

#endif // GFX_UTIL_H
