#include "sys/douchu.h"
#include "common.h"

void func_8001F914();
void func_8001F940();
void func_8001FA3C();

// clang-format off

// <<<<< data >>>>>
void *D_8006B730[3] = {
    func_8001F914, func_8001F940, func_8001FA3C,
};

unsigned int D_8006B73C[17] = {
    0x000B000C, 0x000B000C, 0x000B000C, 0x000B000C, 0x000E0000, 0x000D0000, 0x00000011, 0x000B0012,
    0x000B0013, 0x000D0000, 0x000F0000, 0x000B000C, 0x00100000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000,
};

// <<<<< rodata >>>>>
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/D_8007B970.s")

// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_8001F8B0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_8001F914.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_8001F940.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_8001FA3C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_8001FA80.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_80020308.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_80020364.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_800203D4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_80020440.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_800206D4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_800206FC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_80020724.s")
