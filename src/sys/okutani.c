#include "sys/okutani.h"
#include "common.h"

// clang-format off

// <<<<< data >>>>>
unsigned int D_800636D0[4] = {
    0x00000003, 0x00000004, 0x00000005, 0x00000000,
};

Gfx D_800636E0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetPrimColor(0, 0, 0xFF, 0xFF, 0xFF, 0x00),
    gsSPEndDisplayList(),
};

// <<<<< rodata >>>>>
const char D_8007AC60[] = "KIRAN ANIME TIME = %f\n\0";

const double D_8007AC78[] = { 0.0002204585537918871 };
const double D_8007AC80[] = { 25.6 };
const double D_8007AC88[] = { 255.0 };

// <<<<< bss >>>>>
int D_80167C60[4];
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000DBF0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000DD04.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000DD58.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000DDC0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000DDF0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000DE80.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000DF10.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000DFA0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E030.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E100.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E160.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E1A0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E23C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E28C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E2D4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E39C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E4E4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E630.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E68C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E6F4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E764.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E808.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E9B0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000E9F4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EA34.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EA74.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EABC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EB08.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EB50.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EC04.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000ECB4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000ED00.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000ED5C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EDB0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EDF4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EE50.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EEAC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000EFD0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/okutani/func_8000F178.s")
