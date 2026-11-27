#include "douchu/587B50.h"
#include "common.h"
#include "douchu/file_11.h"
#include "sys/wave_uty.h"
#include "douchu/598540.h"
#include "sys/sys.h"
#include "douchu/5A12F0.h"
#include "douchu/5B20B0.h"
#include "sys/task.h"
#include "sys/gfx_util.h"
#include "douchu/5883D0.h"
#include "douchu/5959C0.h"
#include "douchu/5997A0.h"
#include "unk.h"

void func_801CC000_587F10(Task *task);
void func_801CBF0C_587E1C(Task *task);

extern unsigned short  D_801FC660_5B8570[4];
extern char            D_801FC680_5B8590[];
extern PlayerWaveList  D_801FC7B8_5B86C8;
extern PlayerByteTable D_801FC7BC_5B86CC;
extern float           D_8020A7D8_5C66E8;
extern float           D_8020A7DC_5C66EC;
extern float           D_8020A7E0_5C66F0;
extern float           D_8020A7E4_5C66F4;
extern float           D_8020A7E8_5C66F8;

void func_801CBC40_587B50(void)
{
    Task     *task = D_801FC604_5B8514;
    ObjSolid *solid;

    if (task != NULL) {
        task->wave.data = func_800141C4(task->wave.wave_no);
        solid           = task->obj_head;

        solid->SegWave[2].wave_no = g_sys->common_wave_no;
        solid->SegWave[1].wave_no = D_80204020_5BFF30[PLAYER_WORK(task)->character];
        solid->SegWave[1].data    = D_8020D220_5C9130[PLAYER_WORK(task)->controller];
        func_801DC9C8_5988D8(task, PLAYER_WORK(task)->character);
        func_801DCA64_598974(task, 0, D_8020D260_5C9170);
    }
}

void func_801CBCE4_587BF4(void)
{
    PlayerWaveList list = D_801FC7B8_5B86C8;

    func_80013AC4(list.wave);
}

void func_801CBD14_587C24(void)
{
    D_801FC600_5B8510[0]    = NULL;
    (&D_801FC604_5B8514)[1] = NULL;
    D_801FC604_5B8514       = NULL;
    (&D_801FC60C_5B851C)[1] = NULL;
    D_801FC60C_5B851C       = NULL;
    (&D_801FC614_5B8524)[1] = NULL;
    D_801FC614_5B8524       = NULL;
    (&D_801FC61C_5B852C)[1] = NULL;
    D_801FC61C_5B852C       = NULL;
    D_801FC624_5B8534       = NULL;
    D_801FC628_5B8538       = 0;
    func_801DC988_598898();
}

void func_801CBD88_587C98(void)
{
    Task *task = D_801FC604_5B8514;

    if (task != NULL) {
        func_801DC988_598898();
        func_801E7FB4_5A3EC4(task);
        D_801FC60C_5B851C->tx                = g_sys->next_entry.x;
        D_801FC60C_5B851C->ty                = g_sys->next_entry.y - 2;
        D_801FC60C_5B851C->tz                = g_sys->next_entry.z;
        PLAYER_WORK(task)->angle             = g_sys->next_entry.facing;
        PLAYER_WORK(task)->physics->swim_yaw = PLAYER_WORK(task)->angle << 6;
        if (PLAYER_WORK(task)->character != 1 || PLAYER_WORK(task)->physics->ability_timer != 0xFFFF) {
            D_801FC60C_5B851C->sz = D_8020A7D8_5C66E8;
            D_801FC60C_5B851C->sx = D_801FC60C_5B851C->sy = D_801FC60C_5B851C->sz;
        }
        func_801CBF0C_587E1C(task);
        D_801FC60C_5B851C->hidden = 0;
        D_801FC614_5B8524->tx = D_801FC61C_5B852C->tx = D_801FC60C_5B851C->tx;
        D_801FC614_5B8524->ty = D_801FC61C_5B852C->ty = D_801FC60C_5B851C->ty;
        D_801FC614_5B8524->tz = D_801FC61C_5B852C->tz = D_801FC60C_5B851C->tz;
    }
}

void func_801CBF0C_587E1C(Task *task)
{
    func_801CC000_587F10(task);
    func_801CBFCC_587EDC(task);
    func_801CC4C0_5883D0(task, PLAYER_WORK(task)->max_speed, PLAYER_WORK(task)->move_accel);
    func_801CD084_588F94(task);
    if (func_801E7E90_5A3DA0(task) != 0) {
        func_801F6FE8_5B2EF8(task);
        func_801DACDC_596BEC(task, 0xAE);
        return;
    }
    if (PLAYER_WORK(task)->character == 0) {
        if (PLAYER_WORK(task)->physics->ability_timer == 0) {
            PLAYER_WORK(task)->physics->model_swap = 2;
        }
    }
    if (func_801E7DE8_5A3CF8(task) != 0 || PLAYER_WORK(task)->physics->ability_timer == 0) {
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801CBFCC_587EDC(Task *task)
{
    PlayerByteTable table = D_801FC7BC_5B86CC;

    PLAYER_WORK(task)->physics->body_height = table.byte[PLAYER_WORK(task)->character];
}

void func_801CC000_587F10(Task *task)
{
    PLAYER_WORK(task)->movement_locked       = 0;
    PLAYER_WORK(task)->pushed                = 0;
    PLAYER_WORK(task)->kill_request          = 0;
    PLAYER_WORK(task)->camera                = D_801FC624_5B8534;
    PLAYER_WORK(task)->action_timer          = 0;
    PLAYER_WORK(task)->unk_26                = 0;
    PLAYER_WORK(task)->controller            = 0;
    PLAYER_WORK(task)->wall_group            = 0;
    PLAYER_WORK(task)->floor_group           = 1;
    PLAYER_WORK(task)->ceiling_hit           = 0;
    PLAYER_WORK(task)->wall_solid            = 0;
    PLAYER_WORK(task)->floor_solid           = 0;
    PLAYER_WORK(task)->interact_step         = 0;
    PLAYER_WORK(task)->facing_override       = 0;
    PLAYER_WORK(task)->invincible_frames     = 0;
    PLAYER_WORK(task)->interact_task         = 0;
    PLAYER_WORK(task)->unk_90                = 0;
    PLAYER_WORK(task)->unk_91                = 0;
    PLAYER_WORK(task)->idle_frames           = 0;
    PLAYER_WORK(task)->accel_z               = 0.0f;
    PLAYER_WORK(task)->accel_y               = 0.0f;
    PLAYER_WORK(task)->accel_x               = 0.0f;
    PLAYER_WORK(task)->vel_z                 = 0.0f;
    PLAYER_WORK(task)->vel_y                 = 0.0f;
    PLAYER_WORK(task)->vel_x                 = 0.0f;
    PLAYER_WORK(task)->ground_normal_z       = 0.0f;
    PLAYER_WORK(task)->ground_normal_x       = 0.0f;
    PLAYER_WORK(task)->vertical_speed        = 0.0f;
    PLAYER_WORK(task)->wall_normal_z         = 0.0f;
    PLAYER_WORK(task)->wall_normal_x         = 0.0f;
    PLAYER_WORK(task)->floor_normal_z        = 0.0f;
    PLAYER_WORK(task)->floor_normal_x        = 0.0f;
    PLAYER_WORK(task)->push_z                = 0.0f;
    PLAYER_WORK(task)->push_y                = 0.0f;
    PLAYER_WORK(task)->push_x                = 0.0f;
    PLAYER_WORK(task)->move_accel            = 0.0f;
    PLAYER_WORK(task)->max_speed             = 0.0f;
    PLAYER_WORK(task)->ground_normal_y       = 1.0f;
    PLAYER_WORK(task)->wall_normal_y         = 1.0f;
    PLAYER_WORK(task)->floor_normal_y        = 1.0f;
    PLAYER_WORK(task)->physics->forced_move  = 0;
    PLAYER_WORK(task)->physics->forced_angle = 0;
    PLAYER_WORK(task)->physics->forced_speed = 0.0f;
    PLAYER_WORK(task)->physics->input_angle  = 0;
    PLAYER_WORK(task)->physics->raw_vel_x = PLAYER_WORK(task)->physics->raw_vel_y = PLAYER_WORK(task)->physics->raw_vel_z = 0.0f;
    PLAYER_WORK(task)->physics->slide_flags                                                                               = 0;
    PLAYER_WORK(task)->physics->unk_19                                                                                    = 0;
    PLAYER_WORK(task)->physics->angle                                                                                     = 0;
    PLAYER_WORK(task)->physics->speed = PLAYER_WORK(task)->physics->speed_prev = PLAYER_WORK(task)->physics->speed_prev2 = 0.0f;
    PLAYER_WORK(task)->physics->state_step = PLAYER_WORK(task)->physics->input_frames = PLAYER_WORK(task)->physics->jump_cut = 0;
    PLAYER_WORK(task)->physics->up_mode                                                                                      = 0;
    PLAYER_WORK(task)->physics->state_timer                                                                                  = 0;
    PLAYER_WORK(task)->physics->jump_start_y                                                                                 = 0;
    PLAYER_WORK(task)->physics->aim_angle                                                                                    = 0;
    PLAYER_WORK(task)->physics->charge_frames                                                                                = 0;
    PLAYER_WORK(task)->physics->interact_solid                                                                               = 0;
    PLAYER_WORK(task)->physics->up_x = PLAYER_WORK(task)->physics->up_z = 0.0f;
    PLAYER_WORK(task)->physics->up_y                                    = 1.0f;
    PLAYER_WORK(task)->physics->gravity                                 = D_8020A7DC_5C66EC;
    PLAYER_WORK(task)->physics->water_task                              = 0;
    if (func_801E7E90_5A3DA0(task) != 0) {
        PLAYER_WORK(task)->physics->buoyancy = D_8020A7E0_5C66F0;
    } else {
        PLAYER_WORK(task)->physics->buoyancy = D_8020A7E4_5C66F4;
    }
    PLAYER_WORK(task)->physics->water_height = 0.0f;
    PLAYER_WORK(task)->physics->body_height  = 0;
    PLAYER_WORK(task)->physics->water_state  = 0;
    PLAYER_WORK(task)->physics->contact_x = PLAYER_WORK(task)->physics->contact_z = 0.0f;
    PLAYER_WORK(task)->physics->contact_y                                         = 1;
    PLAYER_WORK(task)->physics->charge_level                                      = 0;
    PLAYER_WORK(task)->physics->changing_character                                = 0;
    PLAYER_WORK(task)->physics->held_stick_angle                                  = 0;
    PLAYER_WORK(task)->physics->held_dir_x                                        = 0.0f;
    PLAYER_WORK(task)->physics->held_dir_x = PLAYER_WORK(task)->physics->held_dir_y = PLAYER_WORK(task)->physics->held_dir_z = 0.0f;
    PLAYER_WORK(task)->physics->held_dir_frames                                                                              = 0;
    PLAYER_WORK(task)->physics->wall_task                                                                                    = NULL;
    PLAYER_WORK(task)->physics->floor_task                                                                                   = 0;
    PLAYER_WORK(task)->physics->walk_frames                                                                                  = 0;
    PLAYER_WORK(task)->physics->target_task                                                                                  = 0;
    PLAYER_WORK(task)->physics->held_task                                                                                    = 0;
    PLAYER_WORK(task)->physics->push_task                                                                                    = 0;
    PLAYER_WORK(task)->physics->ladder_task                                                                                  = 0;
    PLAYER_WORK(task)->physics->effect_tasks[0] = PLAYER_WORK(task)->physics->effect_tasks[1] = PLAYER_WORK(task)->physics->effect_tasks[2] = 0;
    PLAYER_WORK(task)->physics->swim_pitch = PLAYER_WORK(task)->physics->swim_turn = 0;
    PLAYER_WORK(task)->physics->water_result                                       = 0;
    PLAYER_WORK(task)->physics->swim_speed = PLAYER_WORK(task)->physics->velocity_length = 0;
    PLAYER_WORK(task)->physics->afterline                                                = NULL;
    func_801CC454_588364(task);
}

void func_801CC30C_58821C(Task *task)
{
    ObjSolid *solid = task->obj_head;

    func_801CC454_588364(task);
    solid->init_glist                     = (unsigned int) D_801FC680_5B8590 | 0x40000000;
    solid->header.pri                     = 2;
    PLAYER_WORK(task)->probe_height       = 0xB9;
    PLAYER_WORK(task)->box_probe_height   = 0xB4;
    PLAYER_WORK(task)->physics->contact_x = solid->tx;
    PLAYER_WORK(task)->physics->contact_y = solid->ty;
    PLAYER_WORK(task)->physics->contact_z = solid->tz;
    PLAYER_WORK(task)->floor_normal_y     = 1.0f;
    PLAYER_WORK(task)->ground_normal_y    = 1.0f;
    PLAYER_WORK(task)->floor_normal_x     = 0.0f;
    PLAYER_WORK(task)->ground_normal_x    = 0.0f;
    PLAYER_WORK(task)->floor_normal_z     = 0.0f;
    PLAYER_WORK(task)->ground_normal_z    = 0.0f;
    PLAYER_WORK(task)->physics->gravity   = D_8020A7E8_5C66F8;
    func_8001D394((Vec3f *) &PLAYER_WORK(task)->floor_normal_x);
    func_80035214(task, (void (*)(Task *, Obj *)) func_801CB824_587734);
    func_80035244(task, (void (*)(Task *, Obj *)) func_801CBACC_5879DC);
    PLAYER_WORK(task)->state = 0xC;
    if (g_sys_real.player_event_mode == 1) {
        func_801DACDC_596BEC(task, 0xBC);
        return;
    }
    func_801DACDC_596BEC(task, 0);
}

void func_801CC424_588334(Task *task)
{
    PLAYER_WORK(task)->facing_override       = 0;
    PLAYER_WORK(task)->physics->forced_move  = 0;
    PLAYER_WORK(task)->physics->forced_angle = 0;
    PLAYER_WORK(task)->physics->forced_speed = 0.0f;
    PLAYER_WORK(task)->physics->aim_angle    = 0;
    PLAYER_WORK(task)->unk_90                = 0;
}

void func_801CC454_588364(Task *task)
{
    task->hit_flags       = 3;
    task->hit_by          = 0;
    task->hit             = 0;
    task->width           = D_801FC660_5B8570[PLAYER_WORK(task)->character];
    task->height          = D_801FC668_5B8578[PLAYER_WORK(task)->character];
    task->attack_offset_z = 0;
    task->offset_y        = 0;
    task->offset_z        = 0;
    task->hit_index       = 0;
    task->hit_ref         = 0;
    task->hit_kind        = 0x14;
    task->contact         = 0;
    task->anim_events     = 0;
    task->attack_offset_y = task->attack_offset_z;
    task->attack_radius   = task->attack_offset_z;
}
