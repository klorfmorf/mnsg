#ifndef FADE_H
#define FADE_H

#include "common.h"
#include "structs.h"

int   func_80036840(void *arg0);
int   func_80036860(Task *task, unsigned char step);
int   func_80036908(void *arg0);
int   func_80036928(Task *task, unsigned char step);
void  func_800369B4(void *arg0);
void  func_800369F0(void *arg0);
void  func_80036A28(Task *task);
void  func_80036B7C(Task *task);
Task *func_80036CB4(Task *task, int r, int g, int b, int frames);
Task *func_80036D2C(Task *parent, int r, int g, int b, int rise_frames, int hold_frames, int fall_frames);
int   func_80036E2C(Task *task);

#endif // FADE_H
