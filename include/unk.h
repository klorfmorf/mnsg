#ifndef UNK_H
#define UNK_H

// Declarations of symbols that are not (yet) attributed to a translation unit.

#include "common.h"
#include "structs.h"

float __cosf(float x);
float __sinf(float x);
float _nsqrtf(float x);
void  func_801CB460(void);
Gfx  *func_801CB668(int pool, Gfx *dl);
void  func_801CB6C0(void);
int   func_801CB9C8(void);
int   func_801CBB70(Gfx **dl, unsigned int base);
int   func_801D1580(void);

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
extern unsigned long long D_80053AB0[];
extern ALSynth           *D_8007A230;
extern OSViMode           D_80079500[];
extern unsigned long long D_8007D560[];
extern unsigned long long D_8007DD60[];
extern unsigned long long D_8007DD60[];
extern char               D_801CCB7C[];
extern ObjSolid          *D_801FC61C_5B852C;
extern char               D_8020D2A0[];
extern ColFile           *D_80236984[];
extern unsigned short     g_frame_buffers[3][320 * 240];
extern char               D_802F7000[];
extern unsigned char      D_80301000[];
extern unsigned char      D_80304000[];
extern unsigned char      D_80305500[];

// Addresses in the wave overlays (VRAM 0x08000000 based).
extern void func_080026B8_71FE88(Task *task);
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
extern char D_09000D70_F58A30[];
extern char D_A000640[];
extern char D_A000800[];
extern char D_09000D70_F58A30[];
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

extern Task *D_801FC604_5B8514; // the player task
extern ObjSolid *D_801FC60C_5B851C; // the player
void func_801CBC40_587B50(void);
void func_801D23D4_58E2E4(void);
void func_801D9B78_595A88(ObjSolid *solid);
void func_801E8EC4_5A4DD4(Task *task, Obj *obj);

int func_801E5274(void *arg);
void func_80213C50_5CF120(Task *task, Obj *obj);
void  func_80213ED0_5CF3A0(Task *task, Obj *obj);
void  func_8021B610_5D6AE0(Task *task);
void  func_8021B808_5D6CD8(Task *task);
void  func_8021C444_5D7914(Task *task);
void  func_8021C518_5D79E8(Task *task);
void  func_8021C654_5D7B24(Task *task);
void  func_8021DDE8_5D92B8(Task *task, void (*exec)(Task *, Obj *), int arg2, float arg3, float arg4, float arg5, int arg6);
void  func_80224B88_5E0058(Task *task);
extern unsigned char D_8020CBF0_5C8B00[];
void func_801D98E0_5957F0(void);
void func_801CC30C_58821C(Task *task);
void func_801E3358_59F268(Task *task);
void func_801CC4C0_5883D0(Task *task, float arg1, float arg2);
void func_801CD084_588F94(Task *task);
void func_801D9C54_595B64(Task *task);
void func_801DABDC_596AEC(Task *task);
void func_801FB1C0_5B70D0(unsigned short arg0, void *arg1);
void func_801D9CE8_595BF8(Task *task);
int  func_801D9E9C_595DAC(Task *task);
int  func_801DC120_598030(Task *task);
int  func_801DC27C_59818C(Task *task, Obj *obj);
int  func_801DCE10_598D20(Task *task);
int  func_801E630C_5A221C(Task *task, int arg1);
int  func_801E73BC_5A32CC(Task *task);
void func_801E78DC_5A37EC(Task *task);
void func_801E8D90_5A4CA0(Task *task, int arg1);
void func_801E8E24_5A4D34(Task *task, int arg1);

#endif // UNK_H
