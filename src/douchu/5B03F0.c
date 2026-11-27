#include "douchu/5B03F0.h"
#include "common.h"
#include "douchu/5A12F0.h"
#include "sys/anime.h"
#include "sys/solid_atari.h"
#include "sys/vram.h"
#include "douchu/5959C0.h"
#include "douchu/59D4E0.h"
#include "douchu/5A4730.h"
#include "sys/sd_main.h"
#include "sys/sys.h"
#include "douchu/5995F0.h"
#include "unk.h"

void func_801F5420_5B1330(Task *task);
int  func_801F4D94_5B0CA4(ObjSolid *solid);
int  func_801F4984_5B0894(Task *task, unsigned char state);
void func_801F4AA4_5B09B4(Task *task, unsigned char state_a, unsigned char state_b);
void func_801F4B6C_5B0A7C(Task *task, unsigned char state_a, unsigned char state_b);
void func_801F4C20_5B0B30(Task *task, unsigned char state);
void func_801F4E38_5B0D48(Task *task, unsigned char state);

void func_801F44E0_5B03F0(Task *task, ObjSolid *obj)
{
    if (func_801F4984_5B0894(task, 0x71) != 0) {
        func_801E3B9C_59FAAC(task, -0.6f);
        func_801E3D04_59FC14(task, 0x10);
    }
}

void func_801F4528_5B0438(Task *task, ObjSolid *obj)
{
    func_801F4AA4_5B09B4(task, 0x72, 0x73);
}

void func_801F4550_5B0460(Task *task, ObjSolid *obj)
{
    func_801F4B6C_5B0A7C(task, 0, 0);
}

void func_801F4578_5B0488(Task *task, ObjSolid *obj)
{
    func_801F4C20_5B0B30(task, 0x74);
}

void func_801F459C_5B04AC(Task *task, ObjSolid *obj)
{
    func_801F4E38_5B0D48(task, 0);
}

void func_801F45C0_5B04D0(Task *task, ObjSolid *obj)
{
    func_801F4984_5B0894(task, 0x78);
}

void func_801F45E4_5B04F4(Task *task, ObjSolid *obj)
{
    func_801F4AA4_5B09B4(task, 0x79, 0x7A);
}

void func_801F460C_5B051C(Task *task, ObjSolid *obj)
{
    func_801F4B6C_5B0A7C(task, 2, 0x14);
}

void func_801F4634_5B0544(Task *task, ObjSolid *obj)
{
    func_801F4C20_5B0B30(task, 0x7B);
}

void func_801F4658_5B0568(Task *task, ObjSolid *obj)
{
    func_801E84A4_5A43B4(task);
    func_801F4E38_5B0D48(task, 0);
}

void func_801F4688_5B0598(Task *task, ObjSolid *obj)
{
    func_801E1C90_59DBA0(task);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        if (PLAYER_WORK(task)->floor_group != 0) {
            PLAYER_WORK(task)->max_speed  = 0.0f;
            PLAYER_WORK(task)->move_accel = 0.0f;
            PLAYER_WORK(task)->vel_z      = 0.0f;
            PLAYER_WORK(task)->vel_y      = 0.0f;
            PLAYER_WORK(task)->vel_x      = 0.0f;
            func_801DACDC_596BEC(task, 0x71);
        } else {
            PLAYER_WORK(task)->physics->aim_angle = PLAYER_WORK(task)->physics->angle;
            func_801DACDC_596BEC(task, 0x76);
        }
        func_801E8964_5A4874(task, 2);
        func_80038BC8(0x205);
        func_80038BC8(0x20B);
    }
}

void func_801F4754_5B0664(Task *task, ObjSolid *obj)
{
    int       result = func_801E8C98_5A4BA8(task, 2);
    Task     *target;
    ObjSolid *target_solid;

    if (result < 0) {
        func_801DACDC_596BEC(task, 0);
        return;
    }
    if (result == 3) {
        PLAYER_WORK(task)->physics->aim_angle = 0;
        PLAYER_WORK(task)->facing_override    = 0;
        func_80038BC8(0x206);
        if (PLAYER_WORK(task)->floor_group != 0) {
            func_801DACDC_596BEC(task, 0x72);
            return;
        }
        if (PLAYER_WORK(task)->vertical_speed <= 0.0f) {
            func_801E3324_59F234(task);
            func_801DAC7C_596B8C(task, 0x1A, 0.0f, PLAYER_WORK(task)->anime_mode);
            return;
        }
        func_801DACDC_596BEC(task, 0x17);
        return;
    }
    PLAYER_WORK(task)->physics->target_task = func_801DB494_5973A4(task, ENEMY_MGR->parents[1], 0x196, 0x80, 115.0f);
    target                                  = PLAYER_WORK(task)->physics->target_task;
    target_solid                            = target != NULL ? (ObjSolid *) target->obj_head : NULL;
    if (target_solid != NULL && obj->ty - target_solid->ty <= 8.0f) {
        PLAYER_WORK(task)->max_speed  = 0.0f;
        PLAYER_WORK(task)->move_accel = 0.0f;
        PLAYER_WORK(task)->vel_z      = 0.0f;
        PLAYER_WORK(task)->vel_y      = 0.0f;
        PLAYER_WORK(task)->vel_x      = 0.0f;
        func_801DB3A0_5972B0(task, target_solid->tx, target_solid->ty, target_solid->tz, 0x80);
        func_801EA5E4_5A64F4(func_801E8D30_5A4C40(task, 2), task, PLAYER_WORK(task)->physics->target_task);
        func_80038BC8(0x21C);
        PLAYER_WORK(task)->physics->gravity = 0;
        PLAYER_WORK(task)->vertical_speed   = 0.0f;
        task->hit_flags &= 0xFFFE;
        PLAYER_WORK(task)->physics->aim_angle = 0;
        PLAYER_WORK(task)->facing_override    = 0;
        func_801DACDC_596BEC(task, 0x73);
        return;
    }
    if (PLAYER_WORK(task)->floor_group != 0) {
        PLAYER_WORK(task)->facing_override = 0;
        PLAYER_WORK(task)->max_speed       = 0.0f;
        PLAYER_WORK(task)->move_accel      = 0.0f;
        PLAYER_WORK(task)->vel_z           = 0.0f;
        PLAYER_WORK(task)->vel_y           = 0.0f;
        PLAYER_WORK(task)->vel_x           = 0.0f;
    } else {
        func_801E1C90_59DBA0(task);
        PLAYER_WORK(task)->facing_override = PLAYER_WORK(task)->physics->aim_angle | 0x8000;
    }
}

int func_801F4984_5B0894(Task *task, unsigned char state)
{
    ObjSolid *solid  = (ObjSolid *) task->obj_head;
    Task     *target = PLAYER_WORK(task)->physics->target_task;
    ObjSolid *target_solid;

    if (target != NULL) {
        target_solid = (ObjSolid *) target->obj_head;
        func_801DB3A0_5972B0(task, target_solid->tx, target_solid->ty, target_solid->tz, 0x20);
        if ((*anime_frame_count)(solid) -1.0f <= solid->time) {
            func_801E8964_5A4874(task, 2);
            func_80038BC8(0x205);
            func_80038BC8(0x20B);
            PLAYER_WORK(task)->physics->state_timer = 0;
            func_801DACDC_596BEC(task, state);
        }
        return 0;
    }
    if ((*anime_frame_count)(solid) -1.0f <= solid->time) {
        func_801E8964_5A4874(task, 2);
        func_80038BC8(0x205);
        func_80038BC8(0x20B);
        func_801DACDC_596BEC(task, state);
    }
    return 1;
}

void func_801F4AA4_5B09B4(Task *task, unsigned char state_a, unsigned char state_b)
{
    int result = func_801E8C98_5A4BA8(task, 2);

    if (result < 0) {
        PLAYER_WORK(task)->physics->forced_speed = 0.0f;
        PLAYER_WORK(task)->vel_x                 = 0.0f;
        PLAYER_WORK(task)->vel_y                 = 0.0f;
        PLAYER_WORK(task)->vel_z                 = 0.0f;
        PLAYER_WORK(task)->ground_normal_x       = 0.0f;
        PLAYER_WORK(task)->ground_normal_z       = 0.0f;
        PLAYER_WORK(task)->ground_normal_y       = 1.0f;
        func_801DACDC_596BEC(task, state_a);
    } else if (result == 3) {
        func_801DACDC_596BEC(task, state_a);
        func_80038BC8(0x206);
    } else if (PLAYER_WORK(task)->physics->target_task != NULL) {
        PLAYER_WORK(task)->physics->state_timer = 0;
        task->hit_flags &= 0xFFFE;
        PLAYER_WORK(task)->physics->gravity = 0;
        func_801DACDC_596BEC(task, state_b);
    }
}

void func_801F4B6C_5B0A7C(Task *task, unsigned char state_a, unsigned char state_b)
{
    ObjSolid *solid = (ObjSolid *) task->obj_head;

    if (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & 0x4000) {
        func_801E4624_5A0534(task, state_a);
    }
    if ((*anime_frame_count)(solid) -1.0f <= solid->time) {
        PLAYER_WORK(task)->physics->forced_move = 0;
        func_801DACDC_596BEC(task, state_b);
    }
}

void func_801F4C20_5B0B30(Task *task, unsigned char state)
{
    ObjSolid *solid  = (ObjSolid *) task->obj_head;
    int       result = func_801E8C98_5A4BA8(task, 2);
    Task     *effect;

    func_801F4D94_5B0CA4(solid);
    task->hit_flags &= 0xFFFE;
    if (result < 0) {
        PLAYER_WORK(task)->physics->forced_speed = 0.0f;
        PLAYER_WORK(task)->vel_x                 = 0.0f;
        PLAYER_WORK(task)->vel_y                 = 0.0f;
        PLAYER_WORK(task)->vel_z                 = 0.0f;
        PLAYER_WORK(task)->ground_normal_x       = 0.0f;
        PLAYER_WORK(task)->ground_normal_z       = 0.0f;
        PLAYER_WORK(task)->ground_normal_y       = 1.0f;
        func_801DACDC_596BEC(task, state);
        return;
    }
    if (result == 3 || PLAYER_WORK(task)->wall_group != 0 || func_801F4D94_5B0CA4(solid) != 0) {
        effect = func_801E8D30_5A4C40(task, 2);
        if (effect != NULL) {
            PLAYER_EFFECT_WORK(effect)->done = 1;
        }
        func_80038BC8(0x206);
        PLAYER_WORK(task)->physics->state_timer  = 0;
        PLAYER_WORK(task)->physics->forced_speed = 0.0f;
        PLAYER_WORK(task)->vel_x                 = 0.0f;
        PLAYER_WORK(task)->vel_y                 = 0.0f;
        PLAYER_WORK(task)->vel_z                 = 0.0f;
        PLAYER_WORK(task)->ground_normal_x       = 0.0f;
        PLAYER_WORK(task)->ground_normal_z       = 0.0f;
        PLAYER_WORK(task)->ground_normal_y       = 1.0f;
        func_801DACDC_596BEC(task, state);
        return;
    }
    if (PLAYER_WORK(task)->physics->state_timer++ == 0) {
        PLAYER_WORK(task)->vertical_speed   = 0.0f;
        PLAYER_WORK(task)->physics->gravity = 0.0f;
        func_801EA5E4_5A64F4(func_801E8D30_5A4C40(task, 2), task, PLAYER_WORK(task)->physics->target_task);
        func_80038BC8(0x21C);
    }
}

int func_801F4D94_5B0CA4(ObjSolid *solid)
{
    float z;
    float y;
    float x;

    x = 0.0f;
    y = 4.0f;
    z = 14.0f;
    func_80033898(solid->rx, solid->ry, solid->rz, &x, &y, &z);
    x += solid->tx;
    y += solid->ty;
    z += solid->tz;
    return func_80029E08(x, y, z) == 0x7FFF;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B03F0/D_8020C200_5C8110.s")

void func_801F4E38_5B0D48(Task *task, unsigned char state)
{
    ObjSolid *solid = (ObjSolid *) task->obj_head;

    task->hit_flags &= 0xFFFE;
    if (PLAYER_WORK(task)->physics->state_timer++ == 0) {
        PLAYER_WORK(task)->vertical_speed   = 0.0f;
        PLAYER_WORK(task)->physics->gravity = -0.6666666f;
    }
    if (PLAYER_WORK(task)->floor_group == 0) {
        if ((int) (solid->time / PLAYER_WORK(task)->anime_speed) >= (int) ((*anime_frame_count)(solid) / PLAYER_WORK(task)->anime_speed / 2)) {
            task->hit_flags |= 1;
            PLAYER_WORK(task)->physics->forced_move = 0;
            func_801E3324_59F234(task);
            func_801DAC7C_596B8C(task, 0x1A, 0, PLAYER_WORK(task)->anime_mode);
            return;
        }
    }
    if ((*anime_frame_count)(solid) -1.0f <= solid->time) {
        task->hit_flags |= 1;
        PLAYER_WORK(task)->physics->forced_move = 0;
        PLAYER_WORK(task)->move_accel           = 0.0f;
        PLAYER_WORK(task)->max_speed            = 0.0f;
        PLAYER_WORK(task)->physics->up_mode     = 0;
        func_801DACDC_596BEC(task, state);
    }
}

void func_801F4FA4_5B0EB4(Task *task, ObjSolid *obj)
{
    func_801F50A4_5B0FB4(task, 1, 0, 4.5f);
}

void func_801F4FD0_5B0EE0(Task *task, ObjSolid *obj)
{
    func_801F50A4_5B0FB4(task, 1, 0x14, 4.5f);
}

void func_801F4FFC_5B0F0C(Task *task, ObjSolid *obj)
{
    func_801F519C_5B10AC(task, 1, 4.5f);
}

void func_801F5024_5B0F34(Task *task, ObjSolid *obj)
{
    func_801F50A4_5B0FB4(task, 0x12, 0, 4.5f);
}

void func_801F5050_5B0F60(Task *task, ObjSolid *obj)
{
    func_801F50A4_5B0FB4(task, 0x12, 0x14, 4.5f);
}

void func_801F507C_5B0F8C(Task *task, ObjSolid *obj)
{
    func_801F519C_5B10AC(task, 0x12, 4.5f);
}

void func_801F50A4_5B0FB4(Task *task, unsigned char state_a, unsigned char state_b, float time)
{
    ObjSolid *solid = (ObjSolid *) task->obj_head;

    if (time <= solid->time) {
        if (PLAYER_WORK(task)->physics->state_step == 0) {
            PLAYER_WORK(task)->physics->state_step++;
            func_801E8964_5A4874(task, state_a);
            func_801DD830_599740(task, 6);
            if (state_a == 0x12) {
                func_80038BC8(0x15A);
            } else if (state_a == 0x1A || state_a == 0x1B) {
                func_80038BC8(0x103);
            }
        }
    }
    if ((*anime_frame_count)(solid) -1.0f <= solid->time) {
        PLAYER_WORK(task)->physics->forced_move = 0;
        func_801DACDC_596BEC(task, state_b);
    }
}

void func_801F519C_5B10AC(Task *task, unsigned char state, float time)
{
    ObjSolid *solid = (ObjSolid *) task->obj_head;

    func_801E1C90_59DBA0(task);
    if (time <= solid->time) {
        if (PLAYER_WORK(task)->physics->state_step == 0) {
            PLAYER_WORK(task)->physics->state_step++;
            func_801E8964_5A4874(task, state);
            func_801DD830_599740(task, 6);
            if (state == 0x12) {
                func_80038BC8(0x15A);
            } else if (state == 0x1A || state == 0x1B) {
                func_80038BC8(0x103);
            }
        }
    }
    if (PLAYER_WORK(task)->floor_group != 0) {
        if (PLAYER_WORK(task)->vel_y > -7.0f) {
            func_801E2264_59E174(task);
            func_801DACDC_596BEC(task, 0x1C);
            return;
        }
        func_801E2344_59E254(task);
        func_801DACDC_596BEC(task, 0x1B);
        return;
    }
    if ((*anime_frame_count)(solid) -1.0f <= solid->time) {
        PLAYER_WORK(task)->vel_y          = 0.0f;
        PLAYER_WORK(task)->vertical_speed = 0.0f;
        func_801E3324_59F234(task);
        func_801DAC7C_596B8C(task, 0x1A, 0, PLAYER_WORK(task)->anime_mode);
    }
}

void func_801F5314_5B1224(Task *task, ObjSolid *obj)
{
    task->hit_flags &= 0xFFFE;
    if (obj->time >= 4.0f) {
        func_801E8964_5A4874(task, 0x23);
    }
    if (obj->time >= 10.0f) {
        if (PLAYER_WORK(task)->physics->state_timer == 0) {
            PLAYER_WORK(task)->physics->model_swap = 1;
            PLAYER_WORK(task)->physics->state_timer++;
        }
    }
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801DACDC_596BEC(task, 0x83);
    }
}

void func_801F5400_5B1310(Task *task, ObjSolid *obj)
{
    func_801F5420_5B1330(task);
}

void func_801F5420_5B1330(Task *task)
{
    ObjSolid *solid = (ObjSolid *) task->obj_head;

    task->hit_flags &= 0xFFFE;
    if ((*anime_frame_count)(solid) -1.0f <= solid->time) {
        task->hit_flags |= 1;
        func_801DACDC_596BEC(task, 0);
        func_801E8178_5A4088();
        PLAYER_WORK(task)->physics->gravity = -0.6666666f;
    }
}
