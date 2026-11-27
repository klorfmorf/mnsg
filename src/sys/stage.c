#include "sys/stage.h"
#include "common.h"
#include "sys/sys.h"
#include "sys/stage_select.h"
#include "sys/vibration_pak.h"
#include "douchu/587B50.h"
#include "unk.h"

void func_8000B5BC(void);
int  func_8000B51C(void);
void func_8000B4A0(void);

// clang-format off

// <<<<< data >>>>>
unsigned short D_8005BA10[16] = {
    0x0000, 0x012C, 0x015E, 0x0190, 0x021C, 0x0220, 0x0225, 0x0231, 0x024C, 0x025F, 0x0265, 0x026A,
    0x026B, 0x026C, 0x0000, 0x0000,
};

// clang-format on

void func_8000B2A0(void)
{
    g_sys_real.disable_graphics_tasks     = 1;
    g_sys->next_stage_id                  = D_8015C608.stage_id;
    g_sys_real.intended_stage_id          = g_sys->next_stage_id;
    g_sys_real.next_entry.camera_yaw_step = D_8015C608.camera_yaw;
    g_sys_real.next_entry.x               = D_8015C608.x;
    g_sys_real.next_entry.y               = D_8015C608.y;
    g_sys_real.next_entry.z               = D_8015C608.z;
    g_sys_real.next_entry.facing          = D_8015C608.player_yaw;
    PRINTF(("STAGE_NO & GAME_KIND %d,%d \n", g_sys->next_stage_id, g_sys->mode));
    func_8000B3E4();
    g_sys->task_disabled_status = TASK_STATUS_SUSPEND_UPDATE | TASK_STATUS_SUSPEND_DRAW;
    func_8000B4A0();
    PRINTF(("GAME_INIT2_SYORI \n"));
    g_sys_real.pause_disabled = 1;
    func_80037B10(0);
}

void func_8000B364(void)
{
    g_sys_real.disable_graphics_tasks = 1;
    g_sys_real.prev_stage_id          = g_sys_real.intended_stage_id;
    g_sys_real.intended_stage_id      = g_sys_real.next_stage_id;
    func_8000B3E4();
    g_sys_real.task_disabled_status = TASK_STATUS_SUSPEND_UPDATE | TASK_STATUS_SUSPEND_DRAW;
    g_sys_real.enter_voice_pending  = 0;
    func_800214E4();
    func_8000B4A0();
    g_sys_real.pause_disabled = 1;
    func_80037B10(0);
}

void func_8000B3E4(void)
{
    unsigned short i;

    g_sys->intended_stage_group       = 0;
    g_sys->intended_stage_group_index = 0;
    for (i = 1; i < 14; i++) {
        if (g_sys->intended_stage_id < D_8005BA10[i]) {
            g_sys->intended_stage_group       = i - 1;
            g_sys->intended_stage_group_index = g_sys->intended_stage_id - D_8005BA10[g_sys->intended_stage_group];
            return;
        }
    }
}

void func_8000B4A0(void)
{
    g_sys->player_input_locked = 0;
    g_sys->event_input_locked  = 0;
    g_sys->player_event_mode   = 0;
}

int func_8000B4DC(void)
{
    if (g_sys_real.player_dead == 0x80) {
        return func_8000B51C();
    }
    return func_8000B578();
}

int func_8000B51C(void)
{
    if (D_8015C5D8.health == 0 || --D_8015C5D8.health == 0) {
        if (func_801E5274(D_801FC604_5B8514) == 0) {
            return func_8000B578();
        }
    }
    return 2;
}

int func_8000B578(void)
{
    if (--D_8015C5D8.lives != 0) {
        func_8000B5BC();
        return 1;
    }
    return 0;
}

void func_8000B5BC(void)
{
    D_8015C5D8.health = D_8015C5D8.max_health;
}
