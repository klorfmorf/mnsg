#include "sys/demo.h"
#include "common.h"
#include "sys/fade.h"
#include "sys/gfx_util.h"
#include "sys/joypad.h"
#include "sys/rom_trans.h"
#include "sys/save_file.h"
#include "sys/sd_main.h"
#include "sys/stage.h"
#include "sys/step.h"
#include "sys/string.h"
#include "sys/sys.h"
#include "sys/task.h"
#include "sys/wave_uty.h"
#include "segments.h"

void func_80005EDC(void);
void func_80005FDC(void);
void func_80006274(unsigned short keys_file, int keys_addr);
void func_8000607C(unsigned short stage, short x, short y, short z, unsigned short angle, unsigned short posi_extra, unsigned short keys_file, int keys_addr);

// clang-format off

// <<<<< data >>>>>
DemoStart D_8005B1E0[4] = {
    {   325,         0, -560, -20, -790, 0x049,      570, FILE_1293, FILE_RAM_START(file_1293) },
    {   312,         0, -197, 125, -471, 0x300,      960, FILE_1294, FILE_RAM_START(file_1294) },
    {     9,         0, -420, 105,  -40, 0x000,     1600, FILE_1295, FILE_RAM_START(file_1295) },
    {   545,         0,    0,   0,    0, 0x000,     3240, 0,         0                         },
};

// clang-format on

void func_80005B90(void)
{
    switch (g_sys_real.demo_state) {
        case 0:
            if (g_sys_real.demo_no >= 4) {
                g_sys_real.demo_no = 0;
            }
            func_80005EDC();
            if (g_sys->controller[1].button_held_down & A_BUTTON) {
                g_sys_real.demo_wave = 0xFFFF;
            }
            g_sys_real.attrack_demo_frames_elapsed = 0;
            g_sys_real.demo_state++;
            break;
        case 1:
            func_80005FDC();
            if (g_sys_real.demo_wave != 0xFFFF && g_sys_real.disable_graphics_tasks == 0) {
                if ((D_801671B8 & (A_BUTTON | B_BUTTON | START_BUTTON)) ||
                    D_8005B1E0[g_sys_real.demo_no].end_frame < g_sys_real.attrack_demo_frames_elapsed) {
                    func_80038BC8(7);
                    func_800369F0(g_task_list.head);
                    g_sys_real.demo_state++;
                    if (D_8005B1E0[g_sys_real.demo_no].end_frame < g_sys_real.attrack_demo_frames_elapsed) {
                        g_sys->attrack_demo_frames_elapsed = 0xF000;
                    }
                }
            }
            g_sys->attrack_demo_frames_elapsed = g_sys->attrack_demo_frames_elapsed + 1;
            break;
        case 2:
            if (func_80036908(g_task_list.head) == 0) {
                func_80004910();
                D_801671BC         = 0;
                g_sys->wait_frames = 4;
                func_80003880();
                g_sys_real.demo_state++;
            }
            break;
        case 3:
            g_sys->wait_frames = g_sys->wait_frames - 1;
            if (g_sys->wait_frames == 0) {
                func_8000383C();
                g_sys_real.demo_no++;
                if (g_sys_real.demo_no >= 4 && g_sys->attrack_demo_frames_elapsed > 0xE000) {
                    g_sys_real.demo_no   = 0;
                    g_sys_real.demo_mode = 0;
                    func_80003728(GAME_STEP_KONAMI_LOGO);
                    break;
                }
                if (g_sys_real.demo_no >= 4) {
                    g_sys_real.demo_no = 0;
                }
                func_80004910();
                g_sys_real.demo_no |= 0x8000;
                g_sys_real.demo_mode = 0;
                func_80003728(GAME_STEP_TITLE);
            }
            break;
    }
}

void func_80005EDC(void)
{
    unsigned char stepw     = g_sys_real.stepw;
    unsigned char stepw_sub = g_sys_real.step_sub;

    g_sys_real.game_loops_count = 0;
    g_sys_real.mode_frame_count = 0;
    D_801689F8                  = 0;
    D_8015CC30[18]              = 0;
    ENEMY_MGR->frame            = 0;
    func_8000B640();
    func_8000B5D0();
    func_8000607C(D_8005B1E0[g_sys_real.demo_no].stage, D_8005B1E0[g_sys_real.demo_no].x,
        D_8005B1E0[g_sys_real.demo_no].y, D_8005B1E0[g_sys_real.demo_no].z,
        D_8005B1E0[g_sys_real.demo_no].angle, D_8005B1E0[g_sys_real.demo_no].posi_extra,
        D_8005B1E0[g_sys_real.demo_no].keys_file, D_8005B1E0[g_sys_real.demo_no].keys_addr);
    g_sys_real.demo_mode = 1;
    func_80004240();
    func_8000B364();
    func_8000383C();
    g_sys_real.stepw    = stepw;
    g_sys_real.step_sub = stepw_sub;
    func_80003728(GAME_STEP_DEMO);
}

void func_80005FDC(void)
{
    func_80002EFC();
}

void func_80005FFC(unsigned short stage, short x, short y, short z, unsigned short angle, unsigned short posi_extra, unsigned short keys_file, int keys_addr)
{
    func_8000607C(stage, x, y, z, angle, posi_extra, keys_file, keys_addr);
    g_sys_real.demo_mode = 2;
    func_80003728(GAME_STEP_STAFF_ROLL_START);
}

void func_8000607C(unsigned short stage, short x, short y, short z, unsigned short angle, unsigned short posi_extra, unsigned short keys_file, int keys_addr)
{
    g_sys_real.next_stage_id              = stage;
    g_sys_real.next_entry.camera_yaw_step = posi_extra;
    g_sys_real.next_entry.x               = x;
    g_sys_real.next_entry.y               = y;
    g_sys_real.next_entry.z               = z;
    g_sys_real.next_entry.facing          = angle;
    g_sys_real.demo_wave                  = keys_file;
    g_sys_real.demo_offset                = keys_addr;
    g_sys_real.stage_change_flags         = 1;
}

void func_800060D4(unsigned short stage, short x, short y, short z, unsigned short angle, unsigned short posi_extra, unsigned short keys_file, int keys_addr)
{
    func_8000607C(stage, x, y, z, angle, posi_extra, keys_file, keys_addr);
}

void func_80006140(unsigned char index, unsigned short keys_file, int keys_addr)
{
    g_sys_real.disable_graphics_tasks = 1;
    func_80006274(keys_file, keys_addr);
    g_sys->stage_change_flags = 0x80;
    g_sys->next_stage_id      = index + 0x21C;
}

void func_800061B0(unsigned char index, unsigned short keys_file, int keys_addr)
{
    g_sys_real.disable_graphics_tasks = 1;
    func_80006274(keys_file, keys_addr);
    g_sys->stage_change_flags = 0x80;
    g_sys->next_stage_id      = index + 0x220;
}

void func_80006220(unsigned char index, unsigned short keys_file, int keys_addr)
{
    func_80006274(keys_file, keys_addr);
    g_sys->next_stage_id = index + 0x220;
    func_80003728(GAME_STEP_WARP_NEXT);
}

void func_80006274(unsigned short keys_file, int keys_addr)
{
    g_sys_real.disable_graphics_tasks = 1;
    g_sys_real.demo_wave              = keys_file;
    g_sys_real.demo_offset            = keys_addr;
}

void func_80006298(void)
{
    int bank;
    int offset;

    if (g_sys_real.demo_wave != 0 && g_sys_real.demo_offset != 0) {
        func_80013B14(g_sys_real.demo_wave);
        bank   = func_80001E50(g_sys_real.demo_wave);
        offset = func_800141C4(g_sys_real.demo_wave);
        func_80004964(0, (DemoKey *) (g_sys_real.demo_offset + offset - (bank << 24)));
    }
}

int func_8000631C(void)
{
    if (g_sys_real.demo_mode == 2) {
        return 1;
    }

    return 0;
}
