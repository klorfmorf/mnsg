#ifndef FILE_11_H
#define FILE_11_H
// Player overlay.

#include "common.h"
#include "structs.h"

void func_801CB824_587734(Task *task, ObjSolid *obj);
void func_801CBACC_5879DC(Task *task, Obj *obj);

extern int            D_801FC600_5B8510;
extern Task          *D_801FC624_5B8534;
extern ObjSolid      *D_801FC628_5B8538;
extern ObjSolid      *D_801FC634_5B8544;
extern unsigned short D_801FC660_5B8570[4];
extern unsigned short D_801FC668_5B8578[4];
extern char           D_801FC680_5B8590[];
extern PlayerWaveList D_801FC7B8_5B86C8;
extern PlayerByteTable D_801FC7BC_5B86CC;
extern unsigned short D_801FC928_5B8838[][5][4];
extern unsigned char  D_801FCBF0_5B8B00;
extern unsigned short D_80204020_5BFF30[];
extern unsigned int  *D_80204048_5BFF58[];
extern float          D_8020A7D8_5C66E8;
extern float          D_8020A7DC_5C66EC;
extern float          D_8020A7E0_5C66F0;
extern float          D_8020A7E4_5C66F4;
extern float          D_8020A7E8_5C66F8;
extern unsigned short D_8020D1A0_5C90B0;
extern unsigned char  D_8020D1A2_5C90B2;
extern float          D_8020D1B0_5C90C0[3];
extern float          D_8020D1C0_5C90D0[3];
extern float          D_8020D1CC_5C90DC;
extern unsigned short D_8020D1E0_5C90F0;
extern unsigned short D_8020D1E2_5C90F2;
extern float          D_8020D1E4_5C90F4;
extern int            D_8020D220_5C9130[];
extern int            D_8020D224_5C9134[1];
extern int            D_8020D228_5C9138[1][2][2];
extern unsigned char  D_8020D238_5C9148[1][2];
extern int            D_8020D240_5C9150[1][2][2];
extern unsigned char  D_8020D260_5C9170[];

extern unsigned short D_80204060_5BFF70[][4];
extern unsigned short *D_802042A8_5C01B8[];
extern unsigned short *D_80204324_5C0234[];
extern void                (*D_80204868_5C0778[])(Task *, Obj *);
extern Gfx                   D_802049C0_5C08D0[];
extern unsigned int          D_80204AD0_5C09E0[];
extern unsigned int          D_80205000_5C0F10[];
extern PlayerEffectTemplate  D_80205078_5C0F88;
extern PlayerEffectTemplate  D_80205084_5C0F94;
extern PlayerEffectTemplate  D_80205090_5C0FA0;
extern float                 D_802050A0_5C0FB0[][2];
extern Gfx                   D_80205100_5C1010[];
extern Vtx                   D_80205108_5C1018[];
extern Vtx                   D_802051C8_5C10D8[];
extern unsigned char         D_802052A0_5C11B0[][6];
extern AfterlineJoints       D_802052D0_5C11E0;
extern RoomIdleType          D_80209D24_5C5C34[];
extern unsigned char  D_8020CA6C_5C897C;
extern float          D_8020CAC0_5C89D0[4];
extern unsigned char  D_8020D250_5C9160[][4];

#endif // FILE_11_H
