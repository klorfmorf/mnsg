#include "common.h"

// clang-format off

// <<<<< data >>>>>
Lights1 D_8006D180 = gdSPDefLights1(0x60, 0x60, 0x60, 0, 0, 0, 0, 0, 0);

Gfx D_8006D198[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_CULL_BOTH | G_FOG | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPNumLights(2),
    gsSPLight(&D_8006D180.a, 3),
    gsSPEndDisplayList(),
};

Gfx D_8006D220[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPClearGeometryMode(G_CULL_BOTH | G_FOG | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsSPTexture(0x07C0, 0x07C0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx D_8006D298[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_CULL_BOTH | G_FOG | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx D_8006D308[] = {
    gsSPEndDisplayList(),
};

// <<<<< rodata >>>>>
const char D_8007C050[] =
    "Eripple start\n\0\0"
    "Eripple end\n\0\0\0\0"
    "Eripple died\n\0\0\0"
    "ripple_kill\n\0\0\0\0"
    "KILLED???\n\0";

const float  D_8007C09C[] = { 0.02f };
const float  D_8007C0A0[] = { 0.04f };
const double D_8007C0A8[] = { 127.0 };
const double D_8007C0B0[] = { 127.0, 0.0 };

// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80024160.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80024670.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_800246BC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80024734.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80024848.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80024888.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_800248BC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80024BAC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80024FAC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80025398.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80025790.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_800258D0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_8002599C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80025B38.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80025D74.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80026040.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80026114.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80026AAC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80026FE8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_80027364.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ripple/func_800273D4.s")
