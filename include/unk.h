#ifndef UNK_H
#define UNK_H

// Declarations of symbols that are not (yet) attributed to a translation unit.

#include "common.h"
#include "structs.h"

float _nsqrtf(float x);
float __sinf(float x);
float __cosf(float x);
void  func_801CB460(void);
void  func_801CB5A0_63A3F0(void);
void  func_801CB620_5F6A00(void);
Gfx  *func_801CB668(int pool, Gfx *dl);
void  func_801CB6AC_5F6A8C(void);
void  func_801CB6C0(void);
int   func_801CB9C8(void);
int   func_801CBB70(Gfx **dl, unsigned int base);
int   func_801D1580(void);
int   func_801E5274(void *arg);
void  func_8020F170(Task *task, int arg1, int index, int stat, int stage_id, float x, float z);
void  func_8020F170_66E120(Task *task, int arg1, int index, int stat, int stage_id, float x, float z);
void  func_8020F3B8(Task *task, int arg1);
void  func_80211EA0_67B880(void);
void  func_8021373C_69B13C(void);
void  func_80213C50_5CF120(Task *task, ObjSolid *obj);
void  func_80213ED0_5CF3A0(Task *task, ObjSolid *obj);
void  func_8021433C_6732EC(Task *task);
void  func_802160A0_675050(Task *task, int value, int mode1, int mode2, int mode3, int index, int a, int b, unsigned char *data);
void  func_8021B610_5D6AE0(Task *task);
void  func_8021B808_5D6CD8(Task *task);
void  func_8021C444_5D7914(Task *task);
void  func_8021C518_5D79E8(Task *task);
void  func_8021C654_5D7B24(Task *task);
void  func_8021DDE8_5D92B8(Task *task, void (*exec)(Task *, Obj *), int arg2, float arg3, float arg4, float arg5, int arg6);
void  func_80221ED4_5DD3A4(void);
void  func_80224B88_5E0058(Task *task);

extern unsigned char      text_font[][128];
extern unsigned char      save_ext_name[4];
extern unsigned char      save_game_name[16];
extern char               D_2D1800[];
extern char               D_2FFFFF[];
extern char               D_301000[];
extern unsigned char      D_8000048[];
extern unsigned char      D_8000170[];
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
extern OSViMode           D_80079500[];
extern ALSynth           *D_8007A230;
extern unsigned long long D_8007D560[];
extern unsigned long long D_8007DD60[];
extern char               D_801CCB7C[];
extern char               D_8020D2A0[];
extern StageDef          *D_80231300_5EC7D0[]; // by Sys.intended_stage_id
extern ColFile           *D_80236984[];
extern unsigned short     g_frame_buffers[3][320 * 240];
extern char               D_802F7000[];
extern unsigned char      D_80301000[];
extern unsigned char      D_80304000[];
extern unsigned char      D_80305500[];

void func_080026B8_71FE88(Task *task);

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
extern char D_09000D70_F58A30[];
extern char D_A000640[];
extern char D_A000800[];

extern Gfx      D_8020A220_635600[];
extern Gfx      D_8020A258_635638[];
extern Gfx      D_8020A280_635660[];
extern Gfx      D_8020A2A8_635688[];
extern Gfx      D_8020A470_635850[];
extern char     D_8020ABD0_635FB0[];
extern char     D_8020AC70_636050[];
extern Boss3d  *D_8020EED0_63A2B0;
extern int      D_8020EED4_63A2B4;
extern ColStage D_8020EEE0_63A2C0[3];

#endif // UNK_H
