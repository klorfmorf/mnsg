#ifndef OKUTANI_H
#define OKUTANI_H

#include "common.h"
#include "structs.h"

ObjSolid      *func_8000DBF0(Task *task, unsigned int id, Gfx *gfx, float x, float y, float z, unsigned short rot_x, unsigned short rot_y, unsigned short rot_z, float scale_x, float scale_y, float scale_z, unsigned short file0, unsigned short file1);
void           func_8000DD04(ObjSolid *src, ObjSolid *dst);
int            func_8000DD58(int range);
int            func_8000DDC0(void);
Gfx           *func_8000DDF0(Task *task, Gfx *dl, int r, int g, int b, int a);
Gfx           *func_8000DF10(Task *task, Gfx *dl, int r, int g, int b, int a);
Gfx           *func_8000DFA0(Task *task, Gfx *dl, int r, int g, int b, int a);
Gfx           *func_8000E030(Task *task, Gfx *dl, int prim_r, int prim_g, int prim_b, int prim_a, int env_r, int env_g, int env_b, int env_a);
void           func_8000E100(ObjSolid *obj, unsigned int id, unsigned char frame_count, unsigned short file_id);
void           func_8000E160(ObjSolid *obj, unsigned int *images, int i);
void           func_8000E23C(ObjSolid *obj, unsigned int *images, int i, unsigned char frame);
unsigned short func_8000E28C(float x1, float y1, float x2, float y2);
int            func_8000E2D4(float speed, unsigned short pitch, unsigned short yaw, Task *task);
int            func_8000E39C(float length, float x, float y, float z, Task *task);
int            func_8000E4E4(float length, float x, float y, float z, float *out_x, float *out_y, float *out_z);
int            func_8000E630(float radius, unsigned short angle, float *out_cos, float *out_sin);
int            func_8000E68C(float radius, unsigned short yaw, unsigned short pitch, float *out_x, float *out_y, float *out_z);
int            func_8000E764(unsigned short angle, float x, float z, float *out_x, float *out_z);
int            func_8000E808(unsigned short rot_x, unsigned short rot_y, unsigned short rot_z, float *x, float *y, float *z);
unsigned short func_8000E9B0(float y, float z, ObjSolid *obj);
unsigned short func_8000E9F4(float x, float z, ObjSolid *obj);
unsigned short func_8000EABC(float x1, float y1, float x2, float y2);
unsigned short func_8000EB08(float x1, float y1, float x2, float y2);
void           func_8000EB50(float x, float y, float z, ObjSolid *obj);
void           func_8000EC04(float x1, float y1, float z1, float x2, float y2, float z2, unsigned short *pitch, unsigned short *yaw);
void           func_8000ECB4(unsigned short *pitch, unsigned short *yaw);
float          func_8000ED00(Task *a, Task *b);
float          func_8000ED5C(ObjSolid *a, ObjSolid *b);
float          func_8000EDB0(ObjSolid *a, ObjSolid *b);
float          func_8000EDF4(float x1, float y1, float z1, float x2, float y2, float z2);
void           func_8000EE50(ObjSolid *obj, float x, float y, float z, unsigned short roll);
int            func_8000EEAC(Task *parent, float x, float y, float z, float growth, float scale, unsigned char draw_list, unsigned char draw_list2);

extern Gfx D_800636E0[];
extern int D_80167C60[4];

#endif // OKUTANI_H
