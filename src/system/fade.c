#include "system/fade.h"
#include "common.h"
#include "system/obj.h"

// clang-format off

// <<<<< data >>>>>
// 8x8 RGBA16 white texture.
unsigned short D_8006D360[64] = {
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

ObjSpritePart D_8006D3E0 = { 0xC001, 8, 8, 0, 0, 0, 0 };

ObjSpriteTex D_8006D3EC[2] = {
    { 8, 8, 16, 0, 0, D_8006D360, 0, 0 },
    { 8, 8, 16, 0, 0, D_8006D360, 0, 0 },
};

// <<<<< rodata >>>>>
const char D_8007C840[] =
    "L->dalpha: %.1f\n\0\0\0\0"
    "INC: %.1f (%.1f)\n\0\0\0"
    "HOLD\n\0\0\0"
    "DEC: %.1f\n\0\0"
    "\0\0\0";
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036840.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036860.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036908.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036928.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_800369B4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_800369F0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036A28.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036B7C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036CB4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036D0C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036D2C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036E2C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/fade/func_80036E34.s")
