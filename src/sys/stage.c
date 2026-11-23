#include "sys/stage.h"
#include "common.h"

// clang-format off

// <<<<< data >>>>>
unsigned short D_8005BA10[16] = {
    0x0000, 0x012C, 0x015E, 0x0190, 0x021C, 0x0220, 0x0225, 0x0231, 0x024C, 0x025F, 0x0265, 0x026A,
    0x026B, 0x026C, 0x0000, 0x0000,
};

// <<<<< rodata >>>>>
const char D_8007AB00[] =
    "STAGE_NO & GAME_KIND %d,%d \n\0\0\0\0"
    "GAME_INIT2_SYORI \n\0\0"
    "\0\0\0\0"
    "\0\0\0\0"
    "\0\0\0";

// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/stage/func_8000B2A0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/stage/func_8000B364.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/stage/func_8000B3E4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/stage/func_8000B4A0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/stage/func_8000B4DC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/stage/func_8000B51C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/stage/func_8000B578.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/stage/func_8000B5BC.s")
