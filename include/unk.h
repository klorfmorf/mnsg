#ifndef UNK_H
#define UNK_H

// Declarations of symbols that are not (yet) attributed to a translation unit.

#include "common.h"
#include "structs.h"

void func_801CB460(void);
Gfx *func_801CB668(int pool, Gfx *dl);
void func_801CB6C0(void);
int  func_801CB9C8(void);
int  func_801CBB70(Gfx **dl, unsigned int base);
int  func_801D1580(void);

extern char               D_2D1800[];
extern char               D_2FFFFF[];
extern char               D_301000[];
extern Gfx                D_8005588[];
extern Gfx                D_9002410[];
extern Gfx                D_9004958[];
extern Gfx                D_9004A88[];
extern Gfx                D_9004AA8[];
extern Gfx                D_90050F8[];
extern Gfx                D_90056E8[];
extern unsigned long long D_800525B0[];
extern unsigned long long D_80052680[];
extern OSViMode           D_80079500[];
extern unsigned long long D_8007D560[];
extern char               D_801CCB7C[];
extern ObjSolid          *D_801FC61C_5B852C;
extern char               D_8020D2A0[];
extern ColFile           *D_80236984[];
extern unsigned short     g_frame_buffers[3][320 * 240];
extern char               D_802F7000[];
extern unsigned char      D_80301000[];
extern unsigned char      D_80304000[];

// Addresses in the wave overlays (VRAM 0x08000000 based).
extern char D_0800041C[];
extern char D_08000430[];
extern char D_08000610[];
extern char D_08000C78[];
extern char D_08002FC0[];
extern char D_080031C0[];
extern char D_08003D64[];
extern char D_08019B70[];
extern char D_0801A804[];
extern char D_0801B0A0[];
extern char D_0801BE38[];

// Data and bss of the 3dboss overlay (`file_13`), which no TU owns yet.
extern Gfx      D_8020A220_635600[];
extern Gfx      D_8020A258_635638[];
extern Gfx      D_8020A280_635660[];
extern Gfx      D_8020A2A8_635688[];
extern Gfx      D_8020A470_635850[];
extern char     D_8020ABD0_635FB0[];
extern char     D_8020AC70_636050[];
extern Boss3d  *D_8020EED0_63A2B0;
extern int      D_8020EED4_63A2B4;
extern ColStage D_8020EEE0_63A2C0;

extern struct {
    unsigned char unk_00[0x60];
    unsigned char unk_60;
} *D_801FC604_5B8514;

#endif // UNK_H
