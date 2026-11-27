#include "douchu/5B7A40.h"
#include "common.h"
#include "sys/sys.h"
#include "unk.h"

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B7A40/func_801FBB30_5B7A40.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B7A40/func_801FBD50_5B7C60.s")

void func_801FC578_5B8488(Task *task, ObjSolid *obj)
{
}

void func_801FC584_5B8494(Task *task, ObjSolid *obj)
{
}

void func_801FC590_5B84A0(void)
{
    Task *task = g_sys->hud_graphics_task;

    if (task != NULL) {
        task->status &= ~0x14;
    }
}

void func_801FC5C0_5B84D0(void)
{
    Task *task = g_sys->hud_graphics_task;

    if (task != NULL) {
        task->status |= 0x14;
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B7A40/D_8020C840_5C8750.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B7A40/D_8020C858_5C8768.s")
