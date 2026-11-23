#include "sys/gbg.h"
#include "common.h"

// clang-format off

// <<<<< data >>>>>
Gfx D_8006D0F0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPEndDisplayList(),
};

unsigned int D_8006D158 = 0;

unsigned int D_8006D15C = 0;

unsigned int D_8006D160 = 0x00000140;

unsigned int D_8006D164 = 0x000000F0;

unsigned int D_8006D168 = 0x000000F0;

// <<<<< rodata >>>>>
const char D_8007BC80[] =
    "gbgDraw: undecoded wave %d\n\0"
    "\0\0\0";

// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_800215D0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_800216B0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_80021740.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_80021894.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_80021B98.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_80022214.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_80022348.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_80022500.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_80022A74.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_80022DF4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gbg/func_80022EC0.s")
