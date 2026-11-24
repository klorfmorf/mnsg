#include "sys/fade.h"
#include "common.h"
#include "sys/obj.h"

int  func_80036860(void *arg0, int arg1);
int  func_80036928(void *arg0, int arg1);
void func_80036E2C(void *arg0);

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

int func_80036840(void *arg0)
{
    return func_80036860(arg0, 0x10);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/fade/func_80036860.s")

int func_80036908(void *arg0)
{
    return func_80036928(arg0, 0x10);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/fade/func_80036928.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/fade/func_800369B4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/fade/func_800369F0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/fade/func_80036A28.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/fade/func_80036B7C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/fade/func_80036CB4.s")

void func_80036D0C(void *arg0)
{
    func_80036E2C(arg0);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/fade/func_80036D2C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/fade/func_80036E2C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/fade/func_80036E34.s")
