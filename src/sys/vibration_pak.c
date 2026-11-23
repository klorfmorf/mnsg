#include "sys/vibration_pak.h"
#include "common.h"

// clang-format off

// <<<<< rodata >>>>>
const char D_8007C880[] =
    "vpak_action: undefined action %d\n\0\0\0"
    "motor_control: ???\n\0"
    "\0\0\0\0"
    "\0\0\0";

// <<<<< bss >>>>>
unsigned char D_8016DAF0[4];
int           D_8016DAF4;
int           D_8016DAF8[2];
int           D_8016DB00[28];
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/vibration_pak/func_800379D0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/vibration_pak/func_80037B10.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/vibration_pak/func_80037B54.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/vibration_pak/func_80037B78.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/vibration_pak/func_80037C0C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/vibration_pak/func_80037C20.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/vibration_pak/func_80037C9C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/vibration_pak/func_80037CB0.s")
