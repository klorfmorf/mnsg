#ifndef DRACAM_H
#define DRACAM_H

#include "common.h"
#include "structs.h"

void         func_80011B60(void);
void         func_80011BB4(void);
void         func_80011C04(void);
void         func_80011C58(void);
Task        *func_80012304(Task *task);
int          func_80012380(Task *task);
void         func_80012470(Task *task);
void         func_800124A0(Task *task, float steps);
void         func_800124AC(Task *task, float target);
void         func_80012500(Task *task, int value);
void         func_80012518(Task *task, float x, float y, float z);
void         func_800125D0(Task *task, int period, float x, float y, float z);
void         func_800125F0(Task *task, int count, Vec3f *points, float tension, short steps);
void         func_80012628(Task *task, float x, float y, float z);
void         func_800126E0(Task *task, float x, float z);
void         func_80012764(Task *task, float y);
void         func_800127B8(Task *task, float x, float y, float z);
void         func_800127FC(Task *task, float *x, float *y, float *z);
void         func_80012818(Task *task, float x, float y, float z);
void         func_80012848(Task *task, float y);
void         func_8001285C(Task *task, float *x, float *y, float *z);
void         func_80012878(Task *task, AnimeCamera *key);
void         func_80012900(Task *task, AnimeCamera *out);
AnimeCamera *func_80012938(Task *task);
Task        *func_80012940(Task *task, int draw_list);
void         func_800133D4(Task *task, float steps);
void         func_800133E0(Task *task, float x, float y, float z);
void         func_80013400(Task *task, unsigned char r, unsigned char g, unsigned char b);
void         func_80013484(Task *task, unsigned char r, unsigned char g, unsigned char b);
void         func_8001351C(Task *task, float x, float y, float z);
void         func_800135D4(Task *task, unsigned char r, unsigned char g, unsigned char b);
void         func_800136F8(Task *task, unsigned char r, unsigned char g, unsigned char b);
Task        *func_8001381C(Task *task, int draw_list);

#endif // DRACAM_H
