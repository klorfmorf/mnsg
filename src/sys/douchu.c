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
#include "douchu/5B30E0.h"
#include "sys/fade.h"
#include "sys/main.h"
#include "sys/obj_alloc.h"
#include "sys/yamamoto.h"
#include "douchu/587B50.h"
#include "unk.h"

void func_8001F914();
void func_8001F940();
void func_8001FA3C();
void func_8001FA80(void);
void func_80020308(int data);
void func_80020364(void);

// clang-format off

// <<<<< data >>>>>

// clang-format on

void func_8001F8B0(void)
{
    void (*table[3])(void) = { func_8001F914, func_8001F940, func_8001FA3C };

    table[g_sys->mode]();
}

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
        if ((g_sys_real.controller[0].button_pressed & START_BUTTON) && (g_sys_real.stage_change_flags == 0) && (g_sys_real.intended_stage_group != 3) && (g_sys_real.intended_stage_group < 4) && (func_8003F1D8() == 0) && (g_sys_real.pause_disabled == 0) && (g_sys_real.stage_change_flags == 0) && (g_sys_real.player_dead == 0) && (g_sys_real.demo_mode == 0)) {
            PRINTF(("PAUSE ON\n"));
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

void func_8001FA80(void)
{
    unsigned short delay;
    unsigned short count;
    Wave          *entry;

    switch (g_sys->pause_state) {
        case 0:
            func_800369F0(g_task_list.head);
            g_sys_real.task_disabled_status |= TASK_STATUS_FIELD_UPDATE;
            g_sys_real.pause_state++;
            break;
        case 1:
            if (func_80036908(g_task_list.head) == 0) {
                g_sys->task_disabled_status |= TASK_STATUS_FIELD_DRAW;
                func_8003D428();
                g_sys_real.disable_graphics_tasks = 1;
                osViBlack(1);
                g_sys_real.pause_state++;
            }
            break;
        case 2:
            if (D_800548D8 == 0) {
                func_80036158(g_task_list.head, &g_sys->fade->header, 1);
                func_80034EF8(g_sys_real.menu_tasks[2]);
                func_80034EF8(g_sys_real.menu_tasks[3]);
                func_80034EF8(g_sys_real.menu_tasks[4]);
                func_80034EF8(g_sys_real.menu_tasks[5]);
                func_80034EF8(g_sys_real.menu_tasks[6]);
                func_80034EF8(g_sys_real.menu_tasks[7]);
                g_sys->pause_wave_clobber_end = 0;
                g_sys->wait_frames            = 3;
                g_sys->pause_state++;
                g_sys->retraces_per_game_step = 1;
            }
            break;
        case 3:
            if (g_sys->wait_frames-- == 0) {
                func_80001C00(FILE_17, D_8020D2A0);
                PRINTF(("ATLAS RAM %08x\n", D_8020D2A0));
                g_sys->pause_state++;
            }
            break;
        case 4:
            func_80020308(D_80167FC0[g_sys->stage_wave_base + 1].data);
            D_8006D324[0]                     = TASK_STATUS_MENU_UPDATE | TASK_STATUS_MENU_DRAW;
            g_sys_real.disable_graphics_tasks = 0;
            if (g_sys_real.pause_show_map == 0 ||
                (g_sys_real.intended_stage_group == 0 && D_8015C608.has_area_map[g_sys_real.map_area] == 0) ||
                ((g_sys_real.intended_stage_group == 1 || g_sys_real.intended_stage_group == 2) &&
                    D_8015C608.has_stage_map == 0)) {
                g_sys_real.pause_show_map = 0;
                func_800101AC();
                func_8021433C_6732EC(g_sys_real.menu_tasks[1]);
            } else if (g_sys->intended_stage_group == 0) {
                func_800101AC();
                func_802160A0_675050(g_sys_real.menu_tasks[1], D_8015C5D8.character, 0, 0, 0, g_sys->map_area, g_sys->map_floor,
                    g_sys->map_cell, D_8015C608.area_map_flags[g_sys->map_area]);
            } else {
                for (count = 0; D_8015C608.map_point_reached[count] != 0; count++) {
                }
                func_8020F170_66E120(g_sys_real.menu_tasks[1], 0, count, D_8015C5D8.character, g_sys->intended_stage_id, D_801FC60C_5B851C->tx,
                    D_801FC60C_5B851C->tz);
            }
            g_sys_real.wait_frames = 3;
            g_sys_real.pause_state++;
            break;
        case 5:
            if (g_sys->wait_frames-- == 0) {
                osViBlack(0);
            }
            if ((g_sys_real.intended_stage_group == 0 && D_8015C608.has_area_map[g_sys_real.map_area] != 0) ||
                ((g_sys_real.intended_stage_group == 1 || g_sys_real.intended_stage_group == 2) &&
                    D_8015C608.has_stage_map != 0)) {
                if (g_sys->controller[0].button_pressed & Z_TRIG) {
                    g_sys_real.pause_show_map    = (g_sys->pause_show_map & 1) ^ 1;
                    g_sys_real.pause_close_state = 1;
                    g_sys_real.pause_state++;
                }
            }
            if (g_sys->controller[0].button_pressed & START_BUTTON) {
                if (g_sys->pause_close_state != 1) {
                    g_sys_real.pause_close_state = 1;
                    g_sys_real.pause_state       = 8;
                }
            }
            break;
        case 6:
            if (g_sys->pause_close_state == 2) {
                g_sys_real.disable_graphics_tasks = 1;
                g_sys_real.wait_frames            = 5;
                osViBlack(1);
                g_sys_real.pause_state++;
            }
            break;
        case 7:
            if (D_800548D8 == 0) {
                func_80034EF8(g_sys_real.menu_tasks[1]);
                g_sys_real.menu_tasks[1] = func_80034E08(g_sys_real.menu_tasks[0], func_80020724, 0);
                func_80020364();
                D_80167FC0[g_sys_real.temp_wave_slot].wave_no = 0;
                g_sys->pause_state                            = 4;
                g_sys->pause_close_state                      = 0;
            }
            break;
        case 8:
            if (g_sys->pause_close_state == 2) {
                g_sys_real.disable_graphics_tasks = 1;
                g_sys_real.wait_frames            = 5;
                osViBlack(1);
                g_sys_real.pause_state++;
            }
            break;
        case 9:
            if (D_800548D8 == 0) {
                func_80034EF8(g_sys_real.menu_tasks[1]);
                g_sys_real.wait_frames            = 4;
                g_sys_real.disable_graphics_tasks = 0;
                g_sys_real.pause_state++;
            }
            break;
        case 10:
            func_80001C00(FILE_12, D_8020D2A0);
            PRINTF(("DOUTHYU RAM %08x\n", D_8020D2A0));

            delay = 0x7FFF;
        wait:
            if (delay != 0) {
                delay--;
                goto wait;
            }
            func_801F9230_5B5140();
            func_80020364();
            g_sys_real.pause_state++;
            break;
        case 11:
            g_sys_real.pause_wave_reload_index            = 1;
            D_80167FC0[g_sys_real.temp_wave_slot].wave_no = 0;
            D_80167FC0[g_sys_real.temp_wave_slot].data    = g_sys_real.temp_wave_slot_addr;
            g_sys_real.pause_state++;
            break;
        case 12:
            PRINTF(("WAVE_WRITE %d,%d \n", g_sys->stage_wave_base, g_sys->pause_wave_reload_index));
            func_80013C0C(g_sys->stage_wave_base + g_sys_real.pause_wave_reload_index);
            g_sys_real.pause_wave_reload_index++;
            entry = &D_80167FC0[g_sys->stage_wave_base + g_sys_real.pause_wave_reload_index];
            PRINTF(("WRITE %p,%p,%d,%d \n", entry->data, g_sys->pause_wave_clobber_end, g_sys->pause_wave_reload_index, entry->wave_no));
            if ((entry->data & ~WAVE_DATA_TLB) >= g_sys_real.pause_wave_clobber_end || entry->wave_no == 0) {
                func_800369B4(g_task_list.head);
                g_sys_real.task_disabled_status = TASK_STATUS_SUSPEND_UPDATE | TASK_STATUS_SUSPEND_DRAW | TASK_STATUS_FIELD_UPDATE;
                g_sys_real.pause_state++;
            }
            break;
        case 13:
            if (func_80036840(g_task_list.head) == 0) {
                PRINTF(("PAUSE OFF\n"));
                g_sys_real.paused               = 0;
                g_sys_real.task_disabled_status = TASK_STATUS_SUSPEND_UPDATE | TASK_STATUS_SUSPEND_DRAW;
                g_sys_real.wait_frames          = 0;
                g_sys->retraces_per_game_step   = 2;
                func_80038BC8(4);
            }
            break;
    }
}

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
    PRINTF(("WAVE MEN1 %d,%p \n", i, data));
}

void func_80020364(void)
{
    unsigned short i;

    i = 0;
    while (D_80167FC0[i].wave_no != 0) {
        i++;
    }
    PRINTF(("WAVE MEN2 %d,%p \n", i, D_80167FC0[i].data));
    if (g_sys->pause_wave_clobber_end < D_80167FC0[i].data) {
        PRINTF(("CRASH WAVE %i %p \n", i, D_80167FC0[i].data));
        g_sys->pause_wave_clobber_end = D_80167FC0[i].data;
    }
}

void func_800203D4(unsigned short file_0, unsigned short file_1)
{
    unsigned short i;

    if (file_0 != 0) {
        func_80001C00(file_0, func_801CB460);
        PRINTF(("CODE MAX1 %08x \n"));
    }
    if (file_1 != 0) {
        func_80001C00(file_1, D_8020D2A0);
        PRINTF(("CODE MAX2 %08x \n2"));
    }
    i = 0xFFFF;
    while (1) {
        if (i == 0) {
            break;
        }
        i--;
    }
}

void func_80020440(void)
{
    // clang-format off
    // Two per stage group.
    unsigned short overlays[27] = {
        FILE_11, FILE_12, // 0
        FILE_11, FILE_12, // 1
        FILE_11, FILE_12, // 2
        FILE_11, FILE_12, // 3
        FILE_14, 0,       // 4
        FILE_13, 0,       // 5
        0,       FILE_17, // 6
        FILE_11, FILE_18, // 7
        FILE_11, FILE_19, // 8
        FILE_13, 0,       // 9
        FILE_15, 0,       // 10
        FILE_11, FILE_12, // 11
        FILE_16, 0,       // 12
        0,
    };
    // clang-format on
    unsigned short count;

    g_sys->task_disabled_status = TASK_STATUS_SUSPEND_UPDATE | TASK_STATUS_SUSPEND_DRAW;
    func_800203D4(overlays[g_sys_real.intended_stage_group * 2], overlays[g_sys_real.intended_stage_group * 2 + 1]);
    g_sys->mode_frame_count = 0;
    switch (g_sys->intended_stage_group) {
        case 0:
        case 1:
        case 2:
        case 3:
            func_8003488C((void (*)(Task *, Obj *)) func_801F71D0_5B30E0);
            break;
        case 4:
            func_8003488C((void (*)(Task *, Obj *)) func_801CB5A0_63A3F0);
            break;
        case 5:
        case 9:
            if (g_sys->demo_mode != 2) {
                func_8003488C((void (*)(Task *, Obj *)) func_801CB6AC_5F6A8C);
            } else {
                func_8003488C((void (*)(Task *, Obj *)) func_801CB620_5F6A00);
            }
            break;
        case 6:
            if (g_sys_real.prev_stage_id == 0x1B8) {
                PRINTF(("ERAI\n"));
                func_8020F3B8(g_task_list.head, 1);
            } else if (g_sys_real.prev_stage_id == 0x1B9) {
                PRINTF(("OMATURI\n"));
                func_8020F3B8(g_task_list.head, 0);
            } else {
                for (count = 0; D_8015C608.map_point_reached[count] != 0; count++) {
                }
                func_8020F170(g_task_list.head, 1, count, D_8015C5D8.character, g_sys_real.prev_stage_id,
                    g_sys_real.next_entry.x, g_sys_real.next_entry.z);
            }
            break;
        case 7:
            func_8003488C((void (*)(Task *, Obj *)) func_80211EA0_67B880);
            break;
        case 8:
            func_8003488C((void (*)(Task *, Obj *)) func_8021373C_69B13C);
            break;
        case 10:
            func_8003488C((void (*)(Task *, Obj *)) D_801CCB7C);
            break;
        case 11:
            func_8003488C((void (*)(Task *, Obj *)) func_8021373C_69B13C);
            break;
        case 12:
            func_8003488C((void (*)(Task *, Obj *)) func_801CB460);
            break;
        default:
            func_8003488C((void (*)(Task *, Obj *)) func_801F71D0_5B30E0);
            break;
    }
}

void func_800206D4(void)
{
    g_sys->task_disabled_status |= TASK_STATUS_FIELD_UPDATE;
}

void func_800206FC(void)
{
    g_sys->task_disabled_status |= TASK_STATUS_FIELD_DRAW;
}

void func_80020724(Task *task, Obj *obj)
{
}
