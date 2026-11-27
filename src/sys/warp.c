#include "sys/warp.h"
#include "common.h"
#include "sys/stage.h"
#include "sys/step.h"
#include "sys/sys.h"
#include "douchu/5B6060.h"
#include "douchu/587B50.h"
#include "unk.h"

// clang-format off

// <<<<< data >>>>>
EntryPoint D_8006D410[16] = {
    { 350, -440, 0, 57, 512, 19 },
    { 300, 730, 222, 334, 135, 19 },
    { 358, 150, 171, -55, 512, 19 },
    { 359, 3, 0, 191, 512, 19 },
    { 312, 1033, 68, 52, 512, 19 },
    { 375, -227, 112, -54, 256, 19 },
    { 318, 5, 53, -153, 0, 19 },
    { 321, 89, 73, -273, 768, 19 },
    { 322, 150, 231, -493, 0, 19 },
    { 328, -993, 0, 569, 0, 19 },
    { 327, 967, -165, 68, 768, 19 },
    { 377, -372, 70, -129, 0, 19 },
    { 331, 602, 257, -730, 0, 19 },
    { 334, -231, 15, 724, 512, 19 },
    { 440, 0, -40, -75, 0, 19 },
    { 441, 0, -40, -75, 0, 19 },
};

// clang-format on

void func_80037000(void)
{
    if (g_sys->intended_stage_id >= 0x263) {
        g_sys->next_stage_id = 0x25F;
    } else {
        g_sys->next_stage_id = g_sys->intended_stage_id + 1;
    }
    func_80003728(GAME_STEP_WARP_NEXT);
}

void func_80037060(void)
{
    g_sys_real.stepw_end = 2;
}

void func_80037070(void)
{
    g_sys_real.stepw_end = 1;
}

void func_80037080(void)
{
    g_sys_real.stepw_end = 3;
}

void func_80037090(void)
{
    func_80003728(GAME_STEP_OPTIONS);
}

void func_800370B0(void)
{
    g_sys->next_stage_id = 0x260;
    func_80003728(GAME_STEP_WARP_NEXT);
}

void func_800370E8(void)
{
    g_sys->entry.x      = D_801FC60C_5B851C->tx;
    g_sys->entry.y      = D_801FC60C_5B851C->ty;
    g_sys->entry.z      = D_801FC60C_5B851C->tz;
    g_sys->entry.facing = PLAYER_WORK(D_801FC604_5B8514)->angle;
    func_801FA4FC_5B640C(0x1E0, 0, 25, 0, 0, 1);
}

void func_800371B4(void)
{
    g_sys->entry.x      = D_801FC60C_5B851C->tx;
    g_sys->entry.y      = D_801FC60C_5B851C->ty;
    g_sys->entry.z      = D_801FC60C_5B851C->tz;
    g_sys->entry.facing = PLAYER_WORK(D_801FC604_5B8514)->angle;
    func_801FA4FC_5B640C(0x1E2, -213, 0, -357, 0x60, 1);
}

int func_80037284(void)
{
    if (g_sys->intended_stage_group != 1 && g_sys->intended_stage_group != 2) {
        return 0;
    }
    g_sys->stage_change_flags = 0x80;
    g_sys->next_stage_id      = 0x226;
    return 1;
}

void func_800372E8(void)
{
    g_sys->stage_change_flags = 0x80;
    g_sys->next_stage_id      = 0x226;
}

void func_8003731C(unsigned char index)
{
    EntryPoint *params = &D_8006D410[index];

    g_sys->next_stage_id              = params->stage_id;
    g_sys->next_entry.x               = params->x;
    g_sys->next_entry.y               = params->y;
    g_sys->next_entry.z               = params->z;
    g_sys->next_entry.facing          = params->player_yaw;
    g_sys->next_entry.camera_yaw_step = params->camera_yaw;
    func_80003728(GAME_STEP_WARP_NEXT);
}

void func_800373DC(void)
{
    g_sys->next_stage_id = 0x240;
    func_80003728(GAME_STEP_WARP_NEXT);
}

void func_80037414(void)
{
    g_sys->stage_change_flags = 0x80;
    g_sys->next_stage_id      = 0x221;
}

void func_80037448(void)
{
    func_8000383C();
    func_80003728(GAME_STEP_KONAMI_LOGO);
}

void func_80037470(unsigned char index)
{
    g_sys->stage_change_flags = 0x80;
    g_sys->next_stage_id      = index + 0x239;
}

void func_800374AC(unsigned char index)
{
    g_sys->next_stage_id = index + 0x21C;
    func_80003728(GAME_STEP_WARP_NEXT);
}

void func_800374EC(void)
{
    if (func_8000B578() == 0) {
        func_80003728(GAME_STEP_GAME_OVER);
    } else {
        g_sys->next_stage_id = g_sys->intended_stage_id;
        func_80003728(GAME_STEP_WARP_NEXT);
    }
}

void func_80037548(void)
{
    func_80003728(GAME_STEP_WARP_NEXT);
    if (g_sys->intended_stage_group == 4) {
        D_8015C608.bomber_reached[g_sys->intended_stage_group_index] = 1;
        g_sys->next_stage_id                                         = g_sys->intended_stage_group_index + 0x221;
    } else {
        D_8015C608.stage_reached[g_sys->intended_stage_group_index] = 1;
        switch (g_sys->intended_stage_group_index) {
            case 0:
                break;
            case 1:
                g_sys_real.next_stage_id              = 0x132;
                g_sys_real.next_entry.camera_yaw_step = 0;
                g_sys_real.next_entry.x               = 0x6C4;
                g_sys_real.next_entry.y               = 0x1B2;
                g_sys_real.next_entry.z               = 5;
                g_sys_real.next_entry.facing          = ANGLE_HALF;
                break;
            case 2:
                g_sys_real.bgm                        = 0x49;
                g_sys_real.next_stage_id              = 0x14D;
                g_sys_real.next_entry.camera_yaw_step = 0;
                g_sys_real.next_entry.x               = 0xE1;
                g_sys_real.next_entry.y               = 0x202;
                g_sys_real.next_entry.z               = -0x1F3;
                g_sys_real.next_entry.facing          = ANGLE_HALF;
                break;
            case 3:
                break;
        }
    }
}

int func_8003767C(void)
{
    if (g_sys_real.prev_stage_id == g_sys_real.intended_stage_id) {
        return 1;
    }
    return 0;
}
