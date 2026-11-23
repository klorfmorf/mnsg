#include "sys/obj_alloc.h"
#include "sys/task.h"

// clang-format off

// <<<<< data >>>>>

// Capacity of each object kind, indexed by kind.
unsigned short D_8006D350[8] = {
    0, 24, 192, 2, 64, 2, 0, 0,
};

// <<<<< bss >>>>>
Obj  *D_8016DAC0[6];
short D_8016DAD8[6];

// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80035B50.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80035B88.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80035BF8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80035C7C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80035D00.s")

void func_80035D84(void)
{
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80035D8C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80035DFC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80035EEC.s")

Obj *func_80035FDC(ObjSolid *solid)
{
    Obj  *old;
    short kind = solid->header.kind & 0x7F;

    old                = solid->header.next;
    solid->header.next = D_8016DAC0[kind];
    D_8016DAC0[kind]   = &solid->header;
    D_8016DAD8[kind]--;
    if (kind == 2) {
        func_800364FC(solid);
    }
    return old;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80036058.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80036158.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80036260.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_800362DC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80036308.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80036388.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_800363F4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80036448.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_800364FC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80036660.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_8003674C.s")

int func_80036798(ObjSolid *solid)
{
    ObjSolid *sibling = solid->sibling;

    solid->sibling = NULL;
    if (sibling != NULL) {
        if (func_800364FC(sibling) == 0) {
            return 0;
        }
        func_800367E4(sibling);
    }
    return 1;
}

void func_800367E4(ObjSolid *solid)
{
    if (solid != NULL) {
        func_80036660(solid);
        D_8016DAB0--;
        if (D_8006D320 != NULL) {
            func_80035DFC(D_8006D320, 2, 1);
        }
    }
}
