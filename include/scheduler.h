#ifndef SCHEDULER_H
#define SCHEDULER_H


#include "common.h"

#ifdef _FINALROM
#undef _FINALROM
#include <PR/sched.h>
#define _FINALROM
#else
#include <PR/sched.h>
#endif

void         func_80006DF0(void *sched, void *stack, int priority, int mode, int num_fields);
void         func_80006F3C(void *sched, OSScClient *client, OSMesgQueue *queue);
OSMesgQueue *func_80007014(void *sched);
OSMesgQueue *func_80007024(void *sched);

extern OSScTask    D_8008A920[2];
extern OSScMsg     D_8008A8E0[2];
extern OSMesgQueue D_8008A888;
extern OSMesg      D_8008A880[1];
extern OSMesg      D_8008A8A0[8];
extern OSMesg      D_8008A8D8[1];
extern OSMesgQueue D_8008A8C0;
extern OSMesg      D_800548D0;
extern int         D_800548E0;
extern int         D_800548E8;
extern OSMesgQueue D_80167170;

extern unsigned char D_8008A9F0[0x22C0];
extern int           D_800548D8;
extern int           D_800548DC;
extern int           D_800548E4;

extern u64            D_8007D560[];
extern int            D_800548D4;
extern unsigned short D_800548EC;
extern unsigned short D_800548F0;
extern unsigned short D_800548F4;
extern OSMesgQueue   *D_8008CCB0;
extern unsigned char  D_8015CC18[12];

extern char D_2FFFFF[];

extern u64 D_800525B0[];
extern u64 D_80052680[];
extern u64 D_80167450[];
extern u64 D_8015DDF0[];
extern u64 D_8015CDF0[];

#endif // SCHEDULER_H
