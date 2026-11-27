#ifndef GFX_UTIL_H
#define GFX_UTIL_H

#include "common.h"
#include "structs.h"

void           func_8001C970(ObjSolid *dst, ObjSolid *src);
void           func_8001C9BC(ObjSolid *dst, ObjSolid *src);
float          func_8001CC38(AnimeCamera *camera, float x, float y, float z, float *screen_x, float *screen_y);
unsigned short func_8001CD4C(Vec3f *out, Vec3f *v, Vec3f *dir, Vec3f *target, float scale);
int            func_8001CF5C(Vec3f *out, Vec3f *v, Vec3f *dir, Vec3f *target, float scale);
int            func_8001D14C(ObjSolid *obj, Vec3f *dir, float x, float y, float z);
int            func_8001D230(Vec3f *v, float x, float y, float z, unsigned short angle);
int            func_8001D394(Vec3f *v);
int            func_8001D460(Vec3f *base, Vec3f *out, Vec3f *dir);
int            func_8001D5B8(Vec3f *a, Vec3f *b, Vec3f *c);
int            func_8001D718(Vec3f *src, Vec3f *dst, Vec3f *vec);
int            func_8001D898(Vec3f *in, Vec3f *out, Vec3f *dir);
unsigned short func_8001DA08(int range);
void           func_8001DB04(unsigned short *rot, float *vec, unsigned short arg2, unsigned short arg3, unsigned short arg4);
void           func_8001E2BC(float (*mf)[4], ObjSolid *solid);
void           func_8001E380(float (*mf)[4], ObjSolid *solid);
void           func_8001E444(float (*mf)[4], float x, float y, float z);
void           func_8001E4A4(float (*mf)[4], unsigned short rx, unsigned short ry, unsigned short rz);
void           func_8001E634(float (*mf)[4], unsigned short rx, unsigned short ry, unsigned short rz);
void           func_8001EEF4(float *tx, float *ty, float *tz, unsigned short *rx, unsigned short *ry, unsigned short *rz, float *sx, float *sy, float *sz, float (*mf)[4]);
void           func_8001F2D8(float (*a)[4], float (*b)[4]);
void           func_8001F5F8(float (*mf)[4], Mtx *mtx);
void           func_8001F878(unsigned short *rx, unsigned short *ry, unsigned short *rz);

extern unsigned short D_801689F0;
extern unsigned short D_801689F2;
extern unsigned short D_801689F4;
extern int            D_801689F8;

#endif // GFX_UTIL_H
