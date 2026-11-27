#ifndef MAIN_H
#define MAIN_H

#include "common.h"
#include "structs.h"

void func_80000450(void);
void func_80001640(unsigned int rom, void *dst, int size);

extern int                D_800548D8;
extern int                D_800548DC;
extern unsigned long long D_8007E020[0x2000 / sizeof(unsigned long long)];
extern OSThread           D_80080020;
extern OSSched            D_8008A9F0;
extern OSMesgQueue       *D_8008CCB0;

#endif // MAIN_H
