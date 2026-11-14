#ifndef WAVE_UTY_H
#define WAVE_UTY_H


#include "common.h"

#define WAVE_DECODE_MAX 48

struct ObjSolid;
struct Task;

typedef struct Wave {
    /* 0x00 */ unsigned short wave_no;
    /* 0x04 */ int            data;
} Wave; // size = 0x8

typedef struct AmemBlock {
    /* 0x00 */ char             *pt;
    /* 0x04 */ unsigned int      size;
    /* 0x08 */ struct AmemBlock *next;
    /* 0x0C */ struct AmemBlock *up;
} AmemBlock; // size = 0x10

void           func_80013940(void);
void           func_800139A4(unsigned short i);
void           func_80013A24(unsigned short wave_no);
int            func_80013AC4(unsigned short *wave_no_list);
int            func_80013B14(unsigned short arg0);
void           func_80013C0C(unsigned short arg0);
void           func_80013C70(unsigned short *arg0);
void          *func_80013C90(unsigned short *, char);
int            func_800141C4(unsigned int wave_no);
int            func_80014218(struct ObjSolid *solid);
int            func_800142BC(unsigned short, int);
unsigned char *func_800144E8(unsigned int id, unsigned char *src, unsigned char *dst);
unsigned char *func_800145B4(unsigned int id, unsigned char *data);
short          func_80014698(unsigned int id, int *rom);
void           func_8001481C(struct Task *task);
int            func_80014840(int arg0, unsigned int wave_no);
void           func_800148C0(AmemBlock *arg0, char *arg1, unsigned int arg2);
void          *amemAlloc(AmemBlock *arg0, int size);
void          *func_80014A28(AmemBlock *arg0, int size);
void          *amemFree(AmemBlock *arg0, char *arg1);
void           func_80014C00(AmemBlock *arg0);

extern Wave          D_80167FC0[WAVE_DECODE_MAX];
extern unsigned char D_80168140[];

extern unsigned short D_80063940[];
extern unsigned int   D_800639D4[];

#endif // WAVE_UTY_H
