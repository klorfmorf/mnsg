#ifndef SOLID_ATARI_H
#define SOLID_ATARI_H

#include "common.h"
#include "structs.h"

int  func_80032B20(Task *task, unsigned char *out, float a, float b, int c);
void func_80033024(Task *list, Task *other);
void func_80033898(unsigned short rx, unsigned short ry, unsigned short rz, float *x, float *y, float *z);
void func_80033A3C(unsigned short rx, unsigned short ry, unsigned short rz, float *x, float *y, float *z);
int  func_8003454C(Task *task, int index, short delta, short limit);

#endif // SOLID_ATARI_H
