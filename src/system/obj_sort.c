#include "system/obj_sort.h"
#include "system/sys.h"

// clang-format off

// <<<<< bss >>>>>
unsigned short D_80167A80[224];
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj_sort/func_8000A680.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj_sort/func_8000A74C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj_sort/func_8000A918.s")

void func_8000A99C(ObjLayer *layer)
{
    short count;

    if (layer->unk_371 & 0x1) {
        if ((count = func_8000A918(layer, D_80167A80)) >= 2) {
            func_8000A74C(layer, D_80167A80, count);
        }
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj_sort/func_8000AA00.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj_sort/func_8000AAE8.s")

void func_8000AB10(void *dst)
{
    func_800041E0(dst, 0x2970);
}

void func_8000AB30(void)
{
    short i;

    for (i = 0; i < 12; i++) {
        g_sys_real.layers[i].unk_371 = 0;
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj_sort/func_8000AB74.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj_sort/func_8000AD08.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj_sort/func_8000AFA8.s")
