#include "system/joypad.h"
#include "common.h"

// clang-format off

// <<<<< rodata >>>>>
const char D_8007A8E0[] =
    "demo_key_sys[key].demo_key_time = %d\n\0\0\0"
    "OOOOOOOOOOOOOOOOFFFFFFFFFFFFF %d\n\0\0\0"
    "DEMO_KEY_START\n\0"
    "DEMO_KEY_END\n\0\0\0"
    "DEMO_KEY_DATA[%d] { %d, %d, %d },\n\0";

const double D_8007A970[] = { 1.42222222222222, 0.0 };

// <<<<< bss >>>>>
OSMesgQueue    D_80167170;
unsigned char  D_80167188[8];
unsigned char  D_80167190[2];
unsigned char  D_80167192[2];
int            D_80167194;
unsigned char  D_80167198[8];
unsigned char  D_801671A0[24];
unsigned short D_801671B8;
short          D_801671BA;
unsigned char  D_801671BC;
unsigned char  D_801671BD;
unsigned char  D_801671BE;
unsigned char  D_801671BF;
unsigned char  D_801671C0[32];
int            D_801671E0[4];
unsigned char  D_801671F0[0x1B0];
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/joypad/func_80004910.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/joypad/func_80004964.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/joypad/func_800049D0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/joypad/func_80004AF8.s")
