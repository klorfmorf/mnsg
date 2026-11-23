#ifndef SYS_H
#define SYS_H

#include "common.h"
#include "structs.h"

void func_80004170(void);
void func_800041E0(void *dst, int size);
void func_80004208(void *src, void *dst, int size);

extern Sys                g_sys_real;
extern Sys               *g_sys;
extern Gfx               *D_8015C5CC;
extern char               D_8015C5D4;
extern unsigned short     D_8015C80C;
extern unsigned char      D_8015CC18[0x18];
extern unsigned long long D_8015CDF0[];
extern unsigned long long D_8015DDF0[];

#endif // SYS_H
