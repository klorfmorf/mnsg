#include "sys/step.h"
#include "sys/sd_main.h"
#include "sys/joypad.h"
#include "sys/demo.h"
#include "sys/window.h"
#include "sys/fade.h"
#include "sys/obj_alloc.h"
#include "sys/stage_select.h"
#include "sys/controller_pak.h"
#include "sys/douchu.h"
#include "sys/save_file.h"
#include "sys/sched.h"
#include "sys/stage.h"
#include "sys/sys.h"
#include "sys/rom_trans.h"
#include "sys/rom_queue.h"
#include "sys/obj.h"
#include "sys/string.h"
#include "sys/wave_uty.h"
#include "sys/task.h"
#include "unk.h"
#include "sys/main.h"
#include "sys/pic.h"

void func_800020B8(void);
void func_80002138(void);
void func_8000236C(void);
void func_80002454(void);
void func_80002518(void);
void func_80002718(void);
void func_80002938(void);
void func_80002A98(void);
void func_80002AB8(void);
void func_80002C7C(void);
void func_80002D94(void);
void func_80002DE4(void);
void func_80002E70(void);
void func_80002EFC(void);
void func_80002F54(void);
void func_800030F0(void);
void func_80003328(void);
void func_80003358(void);
void func_80003678(void);
void func_8000378C(void);
void func_8000383C(void);
void func_80003880(void);
void func_800038E4(void);
void func_8000394C(void);

// clang-format off

// <<<<< data >>>>>
Gfx D_80058860[] = {
    gsSPEndDisplayList(),
};

int D_80058868[40] = {
    0x00000001, 0x20013001, 0x40015001, 0x60017001, 0x80019001, 0xA001B001, 0xC001D001, 0xE001FFFF,
    0x00801081, 0x20813081, 0x40815081, 0x60817081, 0x80819081, 0xA081B081, 0xC081D081, 0xE081F83F,
    0x01001101, 0x21013101, 0x41015101, 0x61017001, 0x81019101, 0xA101B101, 0xC101D101, 0xE10107C1,
    0x01801181, 0x21813181, 0x41815181, 0x61817181, 0x81819181, 0xA181B181, 0xC181D181, 0xE181FFC1,
    0x02001201, 0x22013201, 0x42015201, 0x62017201, 0x82019201, 0xA201B201, 0xC201D201, 0xE201003F,
};

GameStepTable D_80058908 = {
    {
        func_800020B8, func_80002138, func_8000236C, func_80002454,
        func_80002518, func_80002718, func_80002938, func_80002A98,
        func_80002AB8, func_80002C7C, func_80002D94, func_80002DE4,
        func_80002E70, func_80002EFC, func_80002F54, func_800030F0,
        func_80003328, func_80003358,
    },
};

// <<<<< rodata >>>>>
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/step/D_8007A7A0.s")

// clang-format on

void func_80002040(void)
{
    int           pad[2];
    GameStepTable table = D_80058908;

    table.funcs[g_sys->stepw]();
}

void func_800020B8(void)
{
    func_80004240();
    func_800148C0(g_sys->memory_blocks, D_802F7000, 0xA000);
    func_80005A20(&D_8006ADD0);
    g_sys->unk_cf7b0 = D_80058868;
    func_8000B880();
    func_8000A0F0();
    func_8000378C();
}

void func_80002138(void)
{
    unsigned short i;

    switch (g_sys->step_sub) {
        case 0:
            func_80001C00(FILE_23, func_801CB460);
            i = 0xFFFF;
            while (1) {
                if (i == 0) {
                    break;
                }
                i--;
            }
            do {
                g_sys_real.step_sub++;
            } while (0);
            return;
        case 1:
            func_80004240();
            func_80013940();
            if (g_sys->controller[0].button_held_down & START_BUTTON) {
                if (g_sys_real.is_controller_pak_connected == 0) {
                    if (func_801CB9C8() != 0) {
                        func_8000378C();
                        return;
                    }
                    func_80003678();
                    return;
                }
            }
            func_8000378C();
            return;
        case 2:
            g_sys_real.dont_process_draw_lists = 1;
            if (func_801CBB70(&D_8015C5CC, func_800141C4(2)) != 0) {
                func_80003678();
            }
            return;
        case 3:
            g_sys_real.disable_graphics_tasks      = 1;
            g_sys_real.dont_process_draw_lists     = 0;
            g_sys_real.is_controller_pak_connected = func_800231E0();
            if (g_sys_real.is_controller_pak_connected != 0 || func_800232EC() != 0 || func_80023410() != 0 ||
                func_80023480() != 0 || func_80023560(D_8015CC18) != 0) {
                int            j;
                unsigned char *p;
                p = D_8015CC18;
                j = 0;
                do {
                    *p++ = 0;
                } while (++j < 12);
            }
            i = 0xFFFF;
            while (1) {
                if (i == 0) {
                    break;
                }
                i--;
            }
            func_80003678();
            return;
        case 4:
            func_8000378C();
            break;
    }
}

void func_8000236C(void)
{
    unsigned short i;

    switch (g_sys->step_sub) {
        case 0:
            func_80001C00(FILE_15, func_801CB460);
            i = 0xFFFF;
            while (1) {
                if (i == 0) {
                    break;
                }
                i--;
            }
            g_sys_real.disable_graphics_tasks = 0;
        case 1:
            g_sys_real.step_sub++;
            return;
        case 2:
            if (func_801D1580() != 0) {
                g_sys_real.disable_graphics_tasks = 1;
                g_sys_real.step_sub++;
                return;
            }
            return;
        case 3:
            func_80003728(GAME_STEP_KONAMI_LOGO);
            break;
    }
}

void func_80002454(void)
{
    unsigned short i;

    if (g_sys->step_sub == 0) {
        func_80001C00(FILE_22, func_801CB460);
        i = 0xFFFF;
        while (1) {
            if (i == 0) {
                break;
            }
            i--;
        }
        g_sys_real.disable_graphics_tasks = 0;
    }
    func_801CB460();
    D_8015C5CC = func_801CB668(g_sys_real.current_graphics_pool, D_8015C5CC);
    if (g_sys->stepw != GAME_STEP_KONAMI_LOGO) {
        g_sys->retraces_per_game_step = 2;
        osViSetSpecialFeatures(OS_VI_GAMMA_OFF | OS_VI_GAMMA_DITHER_OFF | OS_VI_DIVOT_ON | OS_VI_DITHER_FILTER_ON);
    }
    g_sys_real.demo_no = 0x8000;
}

void func_80002518(void)
{
    unsigned short i;
    unsigned short input;

    switch (g_sys_real.step_sub) {
        case 0:
            g_sys->retraces_per_game_step = 1;
            func_80001C00(FILE_20, func_801CB460);
            i = 0x7FFF;
            while (1) {
                if (i == 0) {
                    break;
                }
                i--;
            }
            g_sys->step_sub++;
            return;
        case 1:
            func_8000383C();
            func_801CB6C0();
            g_sys->retraces_per_game_step = 0;
            func_800369B4(g_task_list.head);
            g_sys->step_sub++;
            return;
        case 2:
            g_sys->retraces_per_game_step = 0;
            func_80034734();
            if (func_80036840(g_task_list.head) == 0) {
                g_sys->step_sub++;
            }
            return;
        default:
            return;
        case 3:
            input = (g_sys->controller[0].button_pressed | g_sys->controller[1].button_pressed) & (A_BUTTON | B_BUTTON | START_BUTTON);
            if (input != 0) {
                g_sys_real.stepw_end = 2;
            }
            func_800038E4();
            return;
        case 4:
            func_8000394C();
            return;
        case 5:
            if (D_800548D8 == 0) {
                g_sys_real.disable_graphics_tasks = 0;
                func_8000383C();
                if (g_sys_real.stepw_end == 1) {
                    func_80003728(GAME_STEP_OPENING);
                } else {
                    func_80003728(GAME_STEP_TITLE);
                }
            }
            break;
    }
}

#ifdef NON_MATCHING
void func_80002718(void)
{
    unsigned int  step;
    unsigned char i;

    step = g_sys->step_sub;
    switch (step) {
        case 0:
            func_8000383C();
            func_80004910();
            if (g_sys->step_sub == 0) {
                func_80001C00(FILE_11, func_801CB460);
                func_80001C00(FILE_19, D_8020D2A0);
                do {
                    i = 0xFF;
                    while (1) {
                        if (i == 0) {
                            break;
                        }
                        i--;
                    }
                } while (0);
            }
        case 1:
            g_sys->step_sub++;
            return;
        case 2:
            g_sys->retraces_per_game_step     = 2;
            g_sys_real.demo_mode              = 0;
            g_sys_real.disable_graphics_tasks = 0;
            func_8003488C(D_8020D2A0);
            g_sys->step_sub++;
            return;
        case 3:
            func_800038E4();
            return;
        case 4:
            func_8000394C();
            return;
        case 5:
            g_sys->wait_frames--;
            if (g_sys->wait_frames == 0) {
                g_sys_real.disable_graphics_tasks = 0;
                func_8000383C();
                if (g_sys_real.stepw_end == 1) {
                    if (g_sys_real.demo_no & 0x8000) {
                        func_80003728(GAME_STEP_OPENING);
                    } else {
                        g_sys_real.demo_state = 0;
                        func_80003728(GAME_STEP_DEMO);
                    }
                }
                if (g_sys_real.stepw_end == 2) {
                    func_80003728(GAME_STEP_DIARY);
                }
                if (g_sys_real.stepw_end == 3) {
                    func_80003728(GAME_STEP_OPTIONS);
                }
            }
            return;
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/step/func_80002718.s")
#endif

void func_80002938(void)
{
    switch (g_sys->step_sub) {
        case 0:
            func_8000383C();
            g_sys->intended_room_id = 0x24C;
            func_8000B3E4();
            func_80020440();
            g_sys_real.disable_graphics_tasks = 0;
            g_sys->step_sub++;
            return;
        case 1:
            if (g_sys_real.disable_graphics_tasks == 0 &&
                ((g_sys->controller[0].button_pressed | g_sys->controller[1].button_pressed) & (A_BUTTON | B_BUTTON | START_BUTTON))) {
                g_sys->stepw_end++;
            }
            func_800038E4();
            return;
        case 2:
            func_8000394C();
            return;
        case 3:
            if (D_800548D8 == 0) {
                func_8000383C();
                g_sys_real.disable_graphics_tasks = 0;
                g_sys_real.demo_no &= 0x7FFF;
                func_80003728(GAME_STEP_TITLE);
            }
            return;
    }
}

void func_80002A98(void)
{
    func_80005B90();
}

#ifdef NON_MATCHING
void func_80002AB8(void)
{
    unsigned char i;

    i = g_sys->step_sub;
    switch (i) {
        case 0:
            func_8000383C();
            func_80001C00(FILE_15, func_801CB460);
            i = 0xFF;
            while (1) {
                if (i == 0) {
                    break;
                }
                i--;
            }
            g_sys->step_sub++;
            return;
        case 1:
            g_sys->intended_room_group_index = 0;
            func_8003488C(D_801CCB7C);
            g_sys->step_sub++;
            return;
        case 2:
            func_80034734();
            if (g_sys_real.stepw_end != 0) {
                func_80038BC8(7);
                g_sys->step_sub++;
            }
            return;
        case 3:
            if (g_sys_real.stepw_end != 0) {
                func_8000383C();
                if (g_sys_real.stepw_end == 1) {
                    g_sys_real.demo_no = 0x8000;
                    func_80003728(GAME_STEP_TITLE);
                }
                if (g_sys_real.stepw_end == 2) {
                    if (D_8015C608.room_id == 0x1D1) {
                        func_80003728(GAME_STEP_INTRO);
                    } else {
                        func_80003728(GAME_STEP_WARP_SAVE);
                    }
                }
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/step/func_80002AB8.s")
#endif

void func_80002C7C(void)
{
    switch (g_sys->step_sub) {
        case 0:
            func_8000383C();
            g_sys->intended_room_id = 0x231;
            func_8000B3E4();
            func_80020440();
            g_sys->step_sub++;
            return;
        case 1:
            if ((g_sys->controller[0].button_pressed | g_sys->controller[1].button_pressed) & START_BUTTON) {
                g_sys->stepw_end++;
            }
            func_800038E4();
            return;
        case 2:
            func_8000394C();
            return;
        case 3:
            if (D_800548D8 == 0) {
                func_8000383C();
                func_80003728(GAME_STEP_WARP_SAVE);
            }
            return;
    }
}

void func_80002D94(void)
{
    func_80020730();
    if (g_sys->stepw_end != 0) {
        g_sys->mode_frame_count = 0;
        func_80003728(3);
    }
}

void func_80002DE4(void)
{
    if (g_sys_real.step_sub == 0 && g_sys_real.disable_graphics_tasks == 0) {
        g_sys_real.disable_graphics_tasks = 1;
        g_sys_real.step_sub++;
        return;
    }
    if (D_800548D8 == 0) {
        func_8000B2A0();
        g_sys_real.step_sub = 1;
        func_8000383C();
        func_80003728(GAME_STEP_PLAY);
    }
}

void func_80002E70(void)
{
    if (g_sys_real.step_sub == 0 && g_sys_real.disable_graphics_tasks == 0) {
        g_sys_real.disable_graphics_tasks = 1;
        g_sys_real.step_sub++;
        return;
    }
    if (D_800548D8 == 0) {
        func_8000B364();
        g_sys_real.step_sub = 1;
        func_8000383C();
        func_80003728(GAME_STEP_PLAY);
    }
}

void func_80002EFC(void)
{
    func_8001F8B0();
    func_80034734();
    if (g_sys->mode_end != 0) {
        g_sys->mode_frame_count = 0;
        func_80003728(3);
    }
}

void func_80002F54(void)
{
    switch (g_sys->step_sub) {
        case 0:
            g_sys_real.disable_graphics_tasks = 1;
            g_sys_real.step_sub++;
            return;
        case 1:
            if (D_800548D8 == 0) {
                func_8000383C();
                g_sys->intended_room_group       = 12;
                g_sys->intended_room_group_index = 0;
                func_80020440();
                func_800369B4(g_task_list.head);
                g_sys->step_sub++;
                return;
            }
        default:
            return;
        case 2:
            g_sys_real.disable_graphics_tasks = 0;
            func_80036840(g_task_list.head);
            func_800038E4();
            return;
        case 3:
            func_8000394C();
            return;
        case 4:
            if (D_800548D8 == 0) {
                func_8000383C();
                if (g_sys_real.stepw_end == 1) {
                    func_8000B6E0();
                    g_sys_real.enter_voice_pending++;
                    func_80003728(GAME_STEP_WARP_SAVE);
                    return;
                }
                func_80003728(GAME_STEP_KONAMI_LOGO);
            }
            break;
    }
}

void func_800030F0(void)
{
    unsigned int   step;
    unsigned short i;

    step = g_sys_real.step_sub;
    switch (step) {
        case 0:
            g_sys_real.disable_graphics_tasks = 1;
            g_sys_real.step_sub++;
            g_sys_real.stepw_end = 0;
            return;
        case 1:
            if (D_800548D8 == 0) {
                func_8000383C();
                func_80001C00(FILE_15, func_801CB460);
                i = 0xFFFF;
                while (1) {
                    if (i == 0) {
                        break;
                    }
                    i--;
                }
                g_sys->step_sub++;
                return;
            }
        default:
            return;
        case 2:
            g_sys_real.disable_graphics_tasks = 0;
            g_sys->step_sub++;
            return;
        case 3:
            g_sys->intended_room_group_index = 3;
            func_8003488C(D_801CCB7C);
            g_sys->step_sub++;
            return;
        case 4:
            switch (g_sys_real.stepw_end) {
                case 0:
                    func_80034734();
                    return;
                case 1:
                    func_8000383C();
                    g_sys->intended_room_group_index = 3;
                    g_sys_real.stepw_end             = 0;
                    func_8003488C(D_801CCB7C);
                    return;
                case 2:
                    func_8000383C();
                    g_sys->intended_room_group_index = 1;
                    g_sys_real.stepw_end             = 0;
                    func_8003488C(D_801CCB7C);
                    return;
                case 3:
                    func_8000383C();
                    g_sys_real.demo_no = 0x8000;
                    func_80003728(GAME_STEP_TITLE);
                    break;
            }
            break;
    }
}

void func_80003328(void)
{
    func_8000B364();
    func_8000383C();
    func_80003728(0x11);
}

void func_80003358(void)
{
    func_8001F8B0();
    func_80034734();
}

void func_80003380(unsigned char mode)
{
    g_sys->pause_state       = mode;
    g_sys->pause_close_state = 0;
}

void func_800033B0(void)
{
    g_sys->pause_state++;
    g_sys->pause_close_state = 0;
}

void func_800033EC(void)
{
    g_sys->pause_state--;
    g_sys->pause_close_state = 0;
}

void func_80003428(unsigned char step)
{
    g_sys->mode     = step;
    g_sys->mode_end = 0;
    func_80003380(0);
}

void func_80003478(void)
{
    g_sys->mode++;
    g_sys->mode_end = 0;
    func_80003380(0);
}

void func_800034D0(void)
{
    g_sys->mode--;
    g_sys->mode_end = 0;
    func_80003380(0);
}

void func_80003528(unsigned char step)
{
    g_sys->step_sub2     = step;
    g_sys->step_sub2_end = 0;
    func_80003428(0);
}

void func_80003578(void)
{
    g_sys->step_sub2++;
    g_sys->step_sub2_end = 0;
    func_80003428(0);
}

void func_800035D0(void)
{
    g_sys->step_sub2--;
    g_sys->step_sub2_end = 0;
    func_80003428(0);
}

void func_80003628(unsigned char step)
{
    g_sys->step_sub     = step;
    g_sys->step_sub_end = 0;
    func_80003528(0);
}

void func_80003678(void)
{
    g_sys->step_sub++;
    g_sys->step_sub_end = 0;
    func_80003528(0);
}

void func_800036D0(void)
{
    g_sys->step_sub--;
    g_sys->step_sub_end = 0;
    func_80003528(0);
}

void func_80003728(unsigned char step)
{
    g_sys->stepw                  = step;
    g_sys->stepw_end              = 0;
    g_sys->retraces_per_game_step = 2;
    func_80003628(0);
}

void func_8000378C(void)
{
    g_sys->stepw++;
    g_sys->stepw_end = 0;
    func_80003628(0);
}

void func_800037E4(void)
{
    g_sys->stepw--;
    g_sys->stepw_end = 0;
    func_80003628(0);
}

void func_8000383C(void)
{
    func_80003880();
    func_800148C0(g_sys->memory_blocks, D_802F7000, 0xA000);
}

void func_80003880(void)
{
    func_80004240();
    func_8003488C(NULL);
    func_8000A0F0();
    func_80035B50();
    func_8000B880();
    func_8000B8A4(D_800627F0);
    g_sys_real.task_disabled_status = 0x14;
    func_80013940();
    osViBlack(FALSE);
}

void func_800038E4(void)
{
    func_80034734();
    if (g_sys_real.stepw_end != 0) {
        func_800369F0(g_task_list.head);
        g_sys->step_sub++;
        func_80038BC8(7);
    }
}

void func_8000394C(void)
{
    func_80034734();
    if (func_80036908(g_task_list.head) == 0) {
        g_sys_real.wait_frames            = 5;
        g_sys_real.disable_graphics_tasks = 1;
        func_80003880();
        g_sys->step_sub++;
    }
}
