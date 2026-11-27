#ifndef YAMAMOTO_H
#define YAMAMOTO_H

#include "common.h"
#include "structs.h"

void         func_800101AC(void);
int          func_80010230(unsigned short a, unsigned short b, unsigned char c, unsigned char d, void *e, unsigned short f);
void         func_800102E0(int index);
void         func_80010358(int list);
void         func_80010374(int list);
int          func_800103DC(Task *owner, unsigned int max, int pri);
void         func_800105AC(int index);
int          func_800106F0(int list, int x, int y, int w, int h, int tex, int s, int t);
int          func_80010784(int list, int index, int x, int y, int w, int h, int tex, int s, int t);
int          func_8001080C(int list, int index);
int          func_80010864(int list, int index);
Gfx         *func_800108BC(Gfx *gfx);
Gfx         *func_800108E4(Gfx *gdl, int x, int y, int w, int h, int r, int g, int b, int a);
void         func_80010980(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
Gfx         *func_800109A4(Gfx *gdl, int idx);
Gfx         *func_80010B60(Gfx *gdl);
Gfx         *func_80010C6C(Gfx *gfx, int x, int y, int code);
Gfx         *func_80010E9C(Gfx *gfx, int x, int y, unsigned char *text);
Gfx         *func_8001110C(Gfx *gfx, int x, int y, int value, int place);
int          func_8001136C(Task *task);
AnimeCamera *func_800114B8(Task *task, int count, int draw_list);
void         func_800115B8(YamamotoWork *obj, int dx, int dy);
void         func_800115E0(int *p, int a, int b);
void         func_800115F8(int *p, int a, int b);
void         func_80011610(YamamotoWork *obj, YamamotoWork *src);
int          func_800116AC(YamamotoObj *obj);
void         func_80011734(YamamotoWork *obj, int val);
int          func_80011760(Task *task);
void         func_80011908(YamamotoObj *obj, float x, float y, float z);
void         func_80011968(YamamotoWork *obj, YamamotoWork *src);
void         connect_magicfix(void);
ObjSolid    *func_800119D4(void *arg0, int pri);
ObjSolid    *func_80011A38(void *arg0, int pri);
void         func_80011A9C(void);

extern AnimeCamera    D_80063740;
extern unsigned int   D_8006391C;
extern unsigned int   D_80063924;
extern Gfx            D_80063930[];
extern unsigned short D_80167C70[4];
extern ObjSpriteTex   D_80167C78[40];

#endif // YAMAMOTO_H
