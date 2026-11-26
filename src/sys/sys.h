#ifndef SYS_H
#define SYS_H

#include "common.h"
#include "structs.h"

void func_80004170(void);
void func_800041E0(unsigned char *dst, int size);
void func_80004208(unsigned char *src, unsigned char *dst, int size);

extern Sys                g_sys_real;
extern Sys               *g_sys;
extern Gfx               *D_8015C5CC;
extern char               D_8015C5D4;
extern SaveStats          D_8015C5D8;
extern SaveFile           D_8015C608;
extern SaveFile           D_8015C910;
extern unsigned char      D_8015CC18[0x18];
extern unsigned int       D_8015CC30[36]; // EnemyMgr, see ENEMY_MGR
extern EnemySpawn        *D_8015CDDC;
extern EnemyDef          *D_8015CDE0;
extern unsigned long long D_8015CDF0[];
extern unsigned long long D_8015DDF0[];

#endif // SYS_H
