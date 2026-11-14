#ifndef IMPACT_BATTLE_H
#define IMPACT_BATTLE_H


#include "common.h"
#include "task.h"

typedef struct Boss3dView {
    /* 0x00 */ unsigned char unk_00[0x48];
    /* 0x48 */ short         viewport_x0;
    /* 0x4A */ short         viewport_y0;
    /* 0x4C */ short         viewport_x1;
    /* 0x4E */ short         viewport_y1;
} Boss3dView; // size = 0x50

typedef struct Boss3d {
    /* 0x000 */ unsigned char  unk_000[0x2E];
    /* 0x02E */ unsigned short unk_02e;
    /* 0x030 */ unsigned char  unk_030[0x48];
    /* 0x078 */ float          unk_078;
    /* 0x07C */ unsigned char  unk_07c[0xC];
    /* 0x088 */ float          unk_088;
    /* 0x08C */ float          unk_08c;
    /* 0x090 */ unsigned char  unk_090[0x10];
    /* 0x0A0 */ Boss3dView     view;
    /* 0x0F0 */ unsigned char  unk_0f0[0xFC];
    /* 0x1EC */ unsigned int   letterbox_x0;
    /* 0x1F0 */ unsigned int   letterbox_y0;
    /* 0x1F4 */ unsigned int   letterbox_x1;
    /* 0x1F8 */ unsigned int   letterbox_y1;
    /* 0x1FC */ unsigned int   letterbox_y1_limit;
    /* 0x200 */ Gfx            viewport_glist[4];
    /* 0x220 */ unsigned char  unk_220[0x20];
    /* 0x240 */ Gfx            unk_240[3];
    /* 0x258 */ unsigned char  unk_258[0x28];
    /* 0x280 */ Gfx            scissor_glist[4];
    /* 0x2A0 */ unsigned char  unk_2a0[0x20];
    /* 0x2C0 */ unsigned char  cutscene_lock;
} Boss3d; // size = 0x2C8

void func_801D1F58_5FD338(Task *task);

void func_801D2178_5FD558(Task *task);
void func_801D2384_5FD764(Task *task);

extern Boss3d *D_8020EED0_63A2B0;
extern int     D_8020EED4_63A2B4;

extern Gfx D_8020A220_635600[];
extern Gfx D_8020A470_635850[];
extern Gfx D_8020A258_635638[];
extern Gfx D_8020A280_635660[];
extern Gfx D_8020A2A8_635688[];

#endif // IMPACT_BATTLE_H
