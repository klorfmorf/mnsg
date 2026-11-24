#include "sys/douchu.h"
#include "common.h"
#include "sys/task.h"
#include "sys/sys.h"
#include "sys/step.h"
#include "sys/string.h"
#include "sys/wave_uty.h"
#include "sys/rom_trans.h"
#include "sys/save_file.h"
#include "sys/scenario.h"
#include "sys/sd_main.h"
#include "unk.h"

void func_8001F914();
void func_8001F940();
void func_8001FA3C();
void func_8001FA80(void);

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

#ifdef NON_MATCHING
void func_8001F8B0(void)
{
    void (*table[3])(void) = { func_8001F914, func_8001F940, func_8001FA3C };

    table[g_sys->mode]();
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_8001F8B0.s")
#endif

void func_8001F914(void)
{
    func_80020440();
    g_sys_real.disable_graphics_tasks = 0;
    func_80003478();
}

void func_8001F940(void)
{
    func_8000B7E4();
    if (g_sys_real.paused == 0) {
        if ((g_sys_real.controller[0].button_pressed & START_BUTTON) && (g_sys_real.room_change_flags == 0) && (g_sys_real.intended_room_group != 3) && (g_sys_real.intended_room_group < 4) && (func_8003F1D8() == 0) && (g_sys_real.pause_disabled == 0) && (g_sys_real.room_change_flags == 0) && (g_sys_real.player_dead == 0) && (g_sys_real.demo_mode == 0)) {
            g_sys_real.paused            = 1;
            g_sys_real.pause_state       = 0;
            g_sys_real.pause_close_state = 0;
            func_80038BC8(3);
        }
    } else {
        func_8001FA80();
    }
}

void func_8001FA3C(void)
{
    func_80004240();
    func_80034EF8(g_task_list.head);
    g_sys->mode_end = 1;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_8001FA80.s")

void func_80020308(int data)
{
    unsigned short i;

    i = 0;
    while (D_80167FC0[i].wave_no != 0) {
        i++;
    }
    g_sys_real.temp_wave_slot      = i;
    g_sys_real.temp_wave_slot_addr = D_80167FC0[i].data;
    D_80167FC0[i].data             = data;
}

void func_80020364(void)
{
    unsigned short i;

    i = 0;
    while (D_80167FC0[i].wave_no != 0) {
        i++;
    }
    if (g_sys->pause_wave_clobber_end < D_80167FC0[i].data) {
        g_sys->pause_wave_clobber_end = D_80167FC0[i].data;
    }
}

void func_800203D4(unsigned short file0, unsigned short file1)
{
    unsigned short i;

    if (file0 != 0) {
        func_80001C00(file0, func_801CB460);
    }
    if (file1 != 0) {
        func_80001C00(file1, D_8020D2A0);
    }
    i = 0xFFFF;
    while (1) {
        if (i == 0) {
            break;
        }
        i--;
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/douchu/func_80020440.s")

void func_800206D4(void)
{
    g_sys->task_disabled_status |= 1;
}

void func_800206FC(void)
{
    g_sys->task_disabled_status |= 0x80;
}

void func_80020724(Task *task, Obj *obj)
{
}
