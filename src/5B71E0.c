// Player overlay (5B71E0).
#include "common.h"
#include "sys/sys.h"
#include "file_11.h"
#include "unk.h"

extern double D_8020C828_5C8738;
extern double D_8020C830_5C8740;

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5B71E0/func_801FB2D0_5B71E0.s")

void func_801FB934_5B7844(void)
{
    unsigned char i;

    g_sys_real.room_player_idle_type = 0;
    i                                = 0;
    while (D_80209D24_5C5C34[i].room_id != 0xFFFF) {
        if (g_sys_real.intended_room_id == D_80209D24_5C5C34[i].room_id) {
            g_sys_real.room_player_idle_type = D_80209D24_5C5C34[i].type;
            return;
        }
        i++;
    }
}

double func_801FB9AC_5B78BC(double x)
{
    double r;
    int    sign;
    int    i;

    r = 0.0;
    if (x > 1.0) {
        sign = 1;
        x    = 1.0 / x;
    } else if (x < -1.0) {
        sign = -1;
        x    = 1.0 / x;
    } else {
        sign = 0;
    }
    for (i = 24; i > 0; i--) {
        r = (i * i * x * x) / ((2 * i + 1) + r);
    }
    if (sign > 0) {
        return D_8020C828_5C8738 - x / (1.0 + r);
    }
    if (sign < 0) {
        return D_8020C830_5C8740 - x / (1.0 + r);
    }
    return x / (1.0 + r);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5B71E0/func_801FBB30_5B7A40.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5B71E0/func_801FBD50_5B7C60.s")

void func_801FC578_5B8488(Task *task, Obj *obj)
{
}

void func_801FC584_5B8494(Task *task, Obj *obj)
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

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5B71E0/D_8020C6A0_5C85B0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5B71E0/jtbl_8020C7F8_5C8708.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5B71E0/D_8020C820_5C8730.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5B71E0/D_8020C824_5C8734.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5B71E0/D_8020C828_5C8738.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5B71E0/D_8020C830_5C8740.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5B71E0/D_8020C858_5C8768.s")

