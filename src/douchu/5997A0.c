#include "douchu/5997A0.h"
#include "common.h"
#include "douchu/587B50.h"
#include "douchu/5959C0.h"
#include "douchu/598540.h"
#include "douchu/5995F0.h"
#include "douchu/59D4E0.h"
#include "douchu/5A12F0.h"
#include "douchu/5A4730.h"
#include "douchu/5B17D0.h"
#include "sys/anime.h"
#include "sys/sys.h"
#include "sys/task.h"
#include "douchu/5883D0.h"
#include "douchu/58B870.h"
#include "unk.h"

#pragma intrinsic(sqrtf)


extern unsigned int  D_80204340_5C0250[];
extern unsigned int  D_80204350_5C0260[];
extern unsigned int  D_80204360_5C0270[];
extern unsigned int  D_80204370_5C0280[];
extern unsigned int  D_80204380_5C0290[];
extern unsigned int  D_80204390_5C02A0[];
extern unsigned char D_802043A0_5C02B0[4][4];
extern short         D_8020D262_5C9172[];

int func_801DF858_59B768(Task *task);
int func_801DF8B8_59B7C8(Task *task);
#ifndef JAPAN_0
int func_801E0158_59C068(Task *task);
#endif
void func_801E1150_59D060(Task *task);

void func_801DD890_5997A0(Task *task, ObjSolid *obj)
{
    Task         *target;
    ObjSolid     *head;
    float         size;
    unsigned char act = 0;

    if (task->hit_by == NULL) {
        task->hit = task->hit_by         = NULL;
        PLAYER_WORK(task)->interact_step = 0;
        g_sys_real.player_input_locked   = 0;
        func_801DACDC_596BEC(task, act);
    } else {
        target = task->hit_by;
        head   = (ObjSolid *) target->obj_head;
        if (func_801DB3A0_5972B0(task, head->tx, head->ty, head->tz, 16)) {
            task->hit = task->hit_by         = NULL;
            PLAYER_WORK(task)->interact_step = 3;
            size                             = ENEMY_WORK(target)->col_height;
            if (size <= 5.0f) {
                act = 0x57;
            } else if (15.0f <= size) {
                act = 0x55;
            } else {
                act = 0x56;
            }
            func_801DACDC_596BEC(task, act);
        }
    }
}

void func_801DD988_599898(Task *task, ObjSolid *obj)
{
    ObjSolid *target = PLAYER_WORK(task)->physics->interact_solid;

    if (target == NULL) {
        PLAYER_WORK(task)->interact_step = 0;
        g_sys_real.player_input_locked   = 0;
        func_801DACDC_596BEC(task, 0);
    } else if (func_801DB3E4_5972F4(task, (target->ry + 0x200) & 0x3FF, 16)) {
        task->hit = task->hit_by         = NULL;
        PLAYER_WORK(task)->interact_step = 3;
        func_801DACDC_596BEC(task, 0x56);
    }
}

void func_801DDA08_599918(Task *task, ObjSolid *obj)
{
    func_801E1B60_59DA70(task);
}

void func_801DDA28_599938(Task *task, ObjSolid *obj)
{
    func_801E1B60_59DA70(task);
}

void func_801DDA48_599958(Task *task, ObjSolid *obj)
{
    func_801E1B60_59DA70(task);
}

void func_801DDA68_599978(Task *task, ObjSolid *obj)
{
    func_801E7CC4_5A3BD4(task);
}

void func_801DDA88_599998(Task *task, ObjSolid *obj)
{
    func_801E7CC4_5A3BD4(task);
}

void func_801DDAA8_5999B8(Task *task, ObjSolid *obj)
{
    func_801E15D0_59D4E0(task);
}

void func_801DDAC8_5999D8(Task *task, ObjSolid *obj)
{
    func_801E15D0_59D4E0(task);
}

void func_801DDAE8_5999F8(Task *task, ObjSolid *obj)
{
    func_801E15D0_59D4E0(task);
}

void func_801DDB08_599A18(Task *task, ObjSolid *obj)
{
    func_801E15D0_59D4E0(task);
}

void func_801DDB28_599A38(Task *task, ObjSolid *obj)
{
    task->hit_flags &= ~1;
    D_801FC61C_5B852C->hidden = 1;
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801E3358_59F268(task);
        func_801DACDC_596BEC(task, 0x3B);
    }
}

void func_801DDBB0_599AC0(Task *task, ObjSolid *obj)
{
    task->hit_flags &= ~1;
    D_801FC61C_5B852C->hidden = 1;
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801CC454_588364(task);
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801DDC38_599B48(Task *task, ObjSolid *obj)
{
    D_801FC61C_5B852C->hidden = 1;
#ifdef JAPAN_0
    if (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & Z_TRIG) {
#else
    if ((g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & Z_TRIG) || PLAYER_WORK(task)->floor_group == 0) {
#endif
        D_801FC7C4_5B86D4 = 0;
        func_801E8724_5A4634(task);
        func_801E3324_59F234(task);
        func_801DAC7C_596B8C(task, 0x1A, 0.0f, PLAYER_WORK(task)->anime_mode);
        func_801CC454_588364(task);
        return;
    }
    if (func_801E3C34_59FB44(PLAYER_WORK(task)->physics->input_angle, PLAYER_WORK(task)->angle, 0x8080) ||
        (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & A_BUTTON)) {
        PLAYER_WORK(task)->physics->forced_move = 0;
        PLAYER_WORK(task)->move_accel = PLAYER_WORK(task)->max_speed = 0.0f;
        func_801DACDC_596BEC(task, 0x3C);
        func_801DD6E0_5995F0(task, 0x16);
        task->hit_flags &= ~1;
    }
}

void func_801DDD5C_599C6C(Task *task, ObjSolid *obj)
{
    func_801E3400_59F310(task);
}

void func_801DDD7C_599C8C(Task *task, ObjSolid *obj)
{
    func_801E3400_59F310(task);
}

void func_801DDD9C_599CAC(Task *task, ObjSolid *obj)
{
    func_801E3400_59F310(task);
}

void func_801DDDBC_599CCC(Task *task, ObjSolid *obj)
{
    func_801E3400_59F310(task);
    func_801E8964_5A4874(task, 0x24);
}

void func_801DDDEC_599CFC(Task *task, ObjSolid *obj)
{
    int pad;

    PLAYER_WORK(task)->physics->input_frames += func_801E2740_59E650(task);
    if ((g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & B_BUTTON) || PLAYER_WORK(task)->physics->charge_level == 3) {
        func_801E4624_5A0534(task, 0);
    } else if (!func_801E79F4_5A3904(task)) {
        if (func_801E5328_5A1238(task)) {
            PLAYER_WORK(task)->physics->forced_move = 0;
            func_801E20A0_59DFB0(task);
            func_801DACDC_596BEC(task, 0x17);
#ifndef JAPAN_0
        } else if (PLAYER_WORK(task)->floor_group == 0) {
            func_801E3324_59F234(task);
            func_801DAC7C_596B8C(task, 0x1A, 0, PLAYER_WORK(task)->anime_mode);
#endif
        } else if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
            if (PLAYER_WORK(task)->physics->input_frames >= (int) ((*anime_frame_count)(obj) / PLAYER_WORK(task)->anime_speed) / 2) {
                func_801DACDC_596BEC(task, 0x12);
            } else {
                PLAYER_WORK(task)->move_accel = 0.0f;
                func_801DACDC_596BEC(task, 0x11);
            }
        }
    }
    func_801E3B9C_59FAAC(task, -0.6f);
    func_801E8964_5A4874(task, 0x25);
}

void func_801DDFA8_599EB8(Task *task, ObjSolid *obj)
{
    unsigned char act;

    if ((g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & B_BUTTON) || PLAYER_WORK(task)->physics->charge_level == 3) {
        func_801E4624_5A0534(task, 0);
    } else if (!func_801E79F4_5A3904(task)) {
        if (func_801E5328_5A1238(task)) {
            PLAYER_WORK(task)->physics->forced_move = 0;
            func_801E20A0_59DFB0(task);
            func_801DACDC_596BEC(task, 0x17);
        } else if ((act = func_801E1C90_59DBA0(task)) != 0) {
            PLAYER_WORK(task)->physics->forced_move = 0;
            func_801DACDC_596BEC(task, act);
#ifndef JAPAN_0
        } else if (PLAYER_WORK(task)->floor_group == 0) {
            func_801E3324_59F234(task);
            func_801DAC7C_596B8C(task, 0x1A, 0, PLAYER_WORK(task)->anime_mode);
#endif
        } else if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
            PLAYER_WORK(task)->physics->forced_move = 0;
            func_801DACDC_596BEC(task, 0);
        }
    }
}

void func_801DE104_59A014(Task *task, ObjSolid *obj)
{
    if (func_801E5328_5A1238(task)) {
        PLAYER_WORK(task)->physics->forced_move = 0;
        func_801E20A0_59DFB0(task);
        func_801DACDC_596BEC(task, 0x17);
#ifndef JAPAN_0
    } else if (PLAYER_WORK(task)->floor_group == 0) {
        func_801E3324_59F234(task);
        func_801DAC7C_596B8C(task, 0x1A, 0, PLAYER_WORK(task)->anime_mode);
#endif
    } else if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        PLAYER_WORK(task)->physics->forced_move = 0;
        PLAYER_WORK(task)->angle                = (PLAYER_WORK(task)->angle + 0x200) & 0x3FF;
        func_801DACDC_596BEC(task, 0);
    }
    func_801E3B9C_59FAAC(task, -0.6f);
}

void func_801DE1F4_59A104(Task *task, ObjSolid *obj)
{
    func_801E4078_59FF88(task, 1, 89, 91);
}

void func_801DE220_59A130(Task *task, ObjSolid *obj)
{
    func_801E4078_59FF88(task, 2, 90, 92);
}

void func_801DE24C_59A15C(Task *task, ObjSolid *obj)
{
    func_801E4260_5A0170(task, 93);
}

void func_801DE270_59A180(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->character == 2) {
        func_801F5B04_5B1A14(task, 6, 0x61, 0x63, 0, 5);
    } else {
        func_801E4078_59FF88(task, 6, 0x61, 0x63);
    }
}

void func_801DE2CC_59A1DC(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->character == 2) {
        func_801F5B04_5B1A14(task, 7, 0x62, 0x64, 1, 6);
    } else {
        func_801E4078_59FF88(task, 7, 0x62, 0x64);
    }
}

void func_801DE32C_59A23C(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->character == 2) {
        func_801F5B9C_5B1AAC(task, 0x65, 2);
    } else {
        func_801E4260_5A0170(task, 0x65);
    }
}

void func_801DE374_59A284(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->character == 2) {
        func_801F5B04_5B1A14(task, 11, 0x69, 0x6B, 4, 9);
    } else {
        func_801E4078_59FF88(task, 11, 0x69, 0x6B);
    }
}

void func_801DE3D4_59A2E4(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->character == 2) {
        func_801F5B04_5B1A14(task, 12, 0x6A, 0x6C, 5, 10);
    } else {
        func_801E4078_59FF88(task, 12, 0x6A, 0x6C);
    }
}

void func_801DE434_59A344(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->character == 2) {
        func_801F5B9C_5B1AAC(task, 0x6D, 6);
    } else {
        func_801E4260_5A0170(task, 0x6D);
    }
}

void func_801DE47C_59A38C(Task *task, ObjSolid *obj)
{
    func_801E3AC0_59F9D0(task);
}

void func_801DE49C_59A3AC(Task *task, ObjSolid *obj)
{
    func_801E3AC0_59F9D0(task);
}

void func_801DE4BC_59A3CC(Task *task, ObjSolid *obj)
{
    func_801E3AC0_59F9D0(task);
}

void func_801DE4DC_59A3EC(Task *task, ObjSolid *obj)
{
    func_801E3AC0_59F9D0(task);
}

void func_801DE4FC_59A40C(Task *task, ObjSolid *obj)
{
    func_801E3AC0_59F9D0(task);
}

void func_801DE51C_59A42C(Task *task, ObjSolid *obj)
{
    func_801E3AC0_59F9D0(task);
}

void func_801DE53C_59A44C(Task *task, ObjSolid *obj)
{
    func_801E3AC0_59F9D0(task);
}

void func_801DE55C_59A46C(Task *task, ObjSolid *obj)
{
    func_801E3AC0_59F9D0(task);
}

void func_801DE57C_59A48C(Task *task, ObjSolid *obj)
{
    func_801E3AC0_59F9D0(task);
}

void func_801DE59C_59A4AC(Task *task, ObjSolid *obj)
{
    func_801E43B0_5A02C0(task);
}

void func_801DE5BC_59A4CC(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->character == 2) {
        func_801F5BF0_5B1B00(task, 3);
    } else {
        func_801E43B0_5A02C0(task);
    }
}

void func_801DE600_59A510(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->character == 2) {
        func_801F5BF0_5B1B00(task, 7);
    } else {
        func_801E43B0_5A02C0(task);
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5997A0/D_8020B060_5C6F70.s")

void func_801DE644_59A554(Task *task, ObjSolid *obj)
{
    func_801E3EBC_59FDCC(task, 0x1E, func_801E7DE8_5A3CF8(task) ? 0.8f : 2.0f);
}

void func_801DE694_59A5A4(Task *task, ObjSolid *obj)
{
    func_801E3EBC_59FDCC(task, 0x1F, func_801E7DE8_5A3CF8(task) ? 0.4f : 1.0f);
}

void func_801DE6E4_59A5F4(Task *task, ObjSolid *obj)
{
    func_801E3EBC_59FDCC(task, 0, 0.0f);
}

void func_801DE70C_59A61C(Task *task, ObjSolid *obj)
{
    func_801E3EBC_59FDCC(task, 0x21, func_801E7DE8_5A3CF8(task) ? 1.6f : 4.0f);
}

void func_801DE75C_59A66C(Task *task, ObjSolid *obj)
{
    func_801E3EBC_59FDCC(task, 0x22, func_801E7DE8_5A3CF8(task) ? 0.8f : 2.0f);
}

void func_801DE7AC_59A6BC(Task *task, ObjSolid *obj)
{
    func_801E3EBC_59FDCC(task, 0, 0.0f);
}

void func_801DE7D4_59A6E4(Task *task, ObjSolid *obj)
{
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        task->hit_ref                        = 0;
        PLAYER_WORK(task)->physics->buoyancy = PLAYER_WORK(task)->physics->gravity * -1.3f;
        func_801DACDC_596BEC(task, 0x42);
    }
}

void func_801DE858_59A768(Task *task, ObjSolid *obj)
{
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        if (D_8015C5D8.health <= 0) {
            func_801E3098_59EFA8(task);
            func_801DACDC_596BEC(task, 0x2C);
        } else {
            func_801E3134_59F044(task);
            func_801DACDC_596BEC(task, 0x2A);
        }
    } else if ((*anime_frame_count)(obj) / 4 <= obj->time) {
        func_801E3B9C_59FAAC(task, -0.4f);
    }
}

void func_801DE940_59A850(Task *task, ObjSolid *obj)
{
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        if (D_8015C5D8.health <= 0) {
            func_801E3098_59EFA8(task);
            func_801DACDC_596BEC(task, 0x2C);
        } else {
            func_801E3134_59F044(task);
            func_801DACDC_596BEC(task, 0x28);
        }
    } else if ((*anime_frame_count)(obj) / 4 <= obj->time) {
        func_801E3B9C_59FAAC(task, -0.4f);
    }
}

void func_801DEA28_59A938(Task *task, ObjSolid *obj)
{
    PLAYER_STOP(task);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        PLAYER_WORK(task)->physics->forced_move = 0;
        func_801DACDC_596BEC(task, 0);
    }
    func_801E84A4_5A43B4(task);
}

void func_801DEABC_59A9CC(Task *task, ObjSolid *obj)
{
    PLAYER_STOP(task);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        PLAYER_WORK(task)->physics->forced_move = 0;
        func_801DACDC_596BEC(task, 0);
    }
    func_801E84A4_5A43B4(task);
}

void func_801DEB50_59AA60(Task *task, ObjSolid *obj)
{
    func_801DD720_599630(task, 12);
    func_801E50C0_5A0FD0(task);
}

void func_801DEB80_59AA90(Task *task, ObjSolid *obj)
{
    func_801E5154_5A1064(task);
}

void func_801DEBA0_59AAB0(Task *task, ObjSolid *obj)
{
    func_801E5208_5A1118(task);
}

void func_801DEBC0_59AAD0(Task *task, ObjSolid *obj)
{
    func_801E5090_5A0FA0(task);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801DACDC_596BEC(task, 0x30);
    }
}

void func_801DEC24_59AB34(Task *task, ObjSolid *obj)
{
    func_801E50C0_5A0FD0(task);
}

void func_801DEC44_59AB54(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->floor_group == 0) {
        func_801E3324_59F234(task);
        func_801DAC7C_596B8C(task, 0x1A, 0.0f, PLAYER_WORK(task)->anime_mode);
    } else if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801DACDC_596BEC(task, 0x14);
    }
    func_801E83F8_5A4308(task);
}

void func_801DECE0_59ABF0(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->floor_group == 0) {
        func_801E3324_59F234(task);
        func_801DAC7C_596B8C(task, 0x1A, 0, PLAYER_WORK(task)->anime_mode);
    } else if (!(g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_held_down & Z_TRIG)) {
        func_801E3178_59F088(task);
        func_801DACDC_596BEC(task, 0x16);
    } else if ((g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & B_BUTTON) || PLAYER_WORK(task)->physics->charge_level == 3) {
        func_801E4624_5A0534(task, 2);
    } else if (!((g_sys_real.player_controller[PLAYER_WORK(task)->controller].stick_magnitude < 0.0f
                         ? -g_sys_real.player_controller[PLAYER_WORK(task)->controller].stick_magnitude
                         : g_sys_real.player_controller[PLAYER_WORK(task)->controller].stick_magnitude) < 1e-5)) {
        func_801E31A8_59F0B8(task);
        func_801DACDC_596BEC(task, 0x15);
    }
}

void func_801DEE08_59AD18(Task *task, ObjSolid *obj)
{
#ifndef JAPAN_0
    if (D_8020CA6C_5C897C != 0) {
        func_801DD720_599630(task, 0xE);
    }
#endif
    if (PLAYER_WORK(task)->floor_group == 0) {
        func_801E3324_59F234(task);
        func_801DAC7C_596B8C(task, 0x1A, 0.0f, PLAYER_WORK(task)->anime_mode);
    } else if (!(g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_held_down & Z_TRIG)) {
        func_801E3178_59F088(task);
        func_801DACDC_596BEC(task, 0x16);
    } else if ((g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & B_BUTTON) || PLAYER_WORK(task)->physics->charge_level == 3) {
        func_801E4624_5A0534(task, 2);
    } else if (!func_801E1E10_59DD20(task)) {
        func_801DACDC_596BEC(task, 0x14);
    }
}

void func_801DEF18_59AE28(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->floor_group == 0) {
        func_801E3324_59F234(task);
        func_801DAC7C_596B8C(task, 0x1A, 0.0f, PLAYER_WORK(task)->anime_mode);
    } else {
        if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
            PLAYER_WORK(task)->physics->forced_move = 0;
            func_801DACDC_596BEC(task, 0);
        }
        func_801E3D04_59FC14(task, 0x20);
    }
    func_801E84A4_5A43B4(task);
}

void func_801DEFC8_59AED8(Task *task, ObjSolid *obj)
{
    func_801E4530_5A0440(task);
}

void func_801DEFE8_59AEF8(Task *task, ObjSolid *obj)
{
    func_801E4530_5A0440(task);
}

void func_801DF008_59AF18(Task *task, ObjSolid *obj)
{
    func_801E4530_5A0440(task);
}

void func_801DF028_59AF38(Task *task, ObjSolid *obj)
{
    float first  = func_801E7DE8_5A3CF8(task) ? 4.0f : 10.0f;
    float second = func_801E7DE8_5A3CF8(task) ? 1.0f : 3.0f;

    func_801E8194_5A40A4(task, first, second, 0);
}

void func_801DF0B0_59AFC0(Task *task, ObjSolid *obj)
{
    float speed = sqrtf(func_801E7DE8_5A3CF8(task) ? 2.0f * PLAYER_GRAVITY * 14.4f : 2.0f * PLAYER_GRAVITY * 90.0f);

    func_801E8194_5A40A4(task, -1.0f * speed / -PLAYER_GRAVITY, 0.0f, 1);
}

void func_801DF120_59B030(Task *task, ObjSolid *obj)
{
#ifndef JAPAN_0
    PLAYER_WORK(task)->physics->state_timer++;
#endif
    func_801E1C90_59DBA0(task);
    if (PLAYER_WORK(task)->ceiling_hit != 0) {
        func_801E3358_59F268(task);
        func_801DACDC_596BEC(task, 0x3B);
    } else if ((g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & B_BUTTON) || PLAYER_WORK(task)->physics->charge_level == 3) {
        func_801E4624_5A0534(task, 1);
    } else if (PLAYER_WORK(task)->floor_group != 0) {
#ifdef JAPAN_0
        if (-7.0f < PLAYER_WORK(task)->vel_y) {
            func_801E2264_59E174(task);
            func_801DACDC_596BEC(task, 0x1C);
        } else {
            func_801E2344_59E254(task);
            func_801DACDC_596BEC(task, 0x1B);
        }
#else
        if (!func_801E8390_5A42A0(task)) {
            if (PLAYER_WORK(task)->physics->state_timer < 15) {
                func_801E2264_59E174(task);
                func_801DACDC_596BEC(task, 0x1C);
            } else {
                func_801E2344_59E254(task);
                func_801DACDC_596BEC(task, 0x1B);
            }
        }
#endif
    }
}

void func_801DF234_59B144(Task *task, ObjSolid *obj)
{
    float wait = func_801E7DE8_5A3CF8(task) ? 1.0f : 3.0f;

    func_801E1C90_59DBA0(task);
    if (PLAYER_WORK(task)->ceiling_hit != 0) {
        func_801E3358_59F268(task);
        func_801DACDC_596BEC(task, 0x3B);
        return;
    }
    if ((g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & B_BUTTON) || PLAYER_WORK(task)->physics->charge_level == 3) {
        func_801E4624_5A0534(task, 1);
        return;
    }
    if (PLAYER_WORK(task)->floor_group != 0) {
#ifdef JAPAN_0
        if (-7.0f < PLAYER_WORK(task)->vel_y) {
            func_801E2264_59E174(task);
            func_801DACDC_596BEC(task, 0x1C);
        } else {
            func_801E2344_59E254(task);
            func_801DACDC_596BEC(task, 0x1B);
        }
#else
        if (!func_801E8390_5A42A0(task)) {
            if (PLAYER_WORK(task)->physics->state_timer < 15) {
                func_801E2264_59E174(task);
                func_801DACDC_596BEC(task, 0x1C);
            } else {
                func_801E2344_59E254(task);
                func_801DACDC_596BEC(task, 0x1B);
            }
        }
#endif
        return;
    }
    PLAYER_WORK(task)->physics->state_timer++;
    if (wait * 2 < PLAYER_WORK(task)->physics->state_timer) {
        func_801E3324_59F234(task);
        func_801DAC7C_596B8C(task, 0x1A, 0.0f, PLAYER_WORK(task)->anime_mode);
    }
}

void func_801DF3D8_59B2E8(Task *task, ObjSolid *obj)
{
    if (func_801E8390_5A42A0(task)) {
        return;
    }
    if (func_801E5328_5A1238(task)) {
        func_801E20A0_59DFB0(task);
        func_801DACDC_596BEC(task, 0x17);
    } else if ((g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & B_BUTTON) || PLAYER_WORK(task)->physics->charge_level == 3) {
        func_801E4624_5A0534(task, 0);
    } else if (!func_801E79F4_5A3904(task)) {
        if (!(ABS(g_sys_real.player_controller[PLAYER_WORK(task)->controller].stick_magnitude) < 0.00001)) {
            PLAYER_WORK(task)->move_accel = 0.7f;
            func_801DACDC_596BEC(task, 0xD);
        } else if ((g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & Z_TRIG) ||
                   (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_held_down & Z_TRIG)) {
            PLAYER_WORK(task)->move_accel = 0;
            func_801DACDC_596BEC(task, 0x13);
        } else if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
            func_801DACDC_596BEC(task, 0);
        } else {
            PLAYER_WORK(task)->move_accel = 0;
        }
    }
}

void func_801DF5A4_59B4B4(Task *task, ObjSolid *obj)
{
    PLAYER_WORK(task)->move_accel = 0.0f;
#ifndef JAPAN_0
    func_801E307C_59EF8C(task);
#endif
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801DF610_59B520(Task *task, ObjSolid *obj)
{
    float magnitude;

    PLAYER_WORK(task)->physics->buoyancy = 0.86666656f;
    func_801E7F50_5A3E60(task);
    if (!func_801DF858_59B768(task) && !func_801DF8B8_59B7C8(task)) {
        magnitude = g_sys_real.player_controller[PLAYER_WORK(task)->controller].stick_magnitude;
        if (!((magnitude < 0.0f ? -magnitude : magnitude) < 1e-05)) {
            func_801DACDC_596BEC(task, 0x44);
        }
    }
}

void func_801DF6D0_59B5E0(Task *task, ObjSolid *obj)
{
    func_801E7F50_5A3E60(task);
    func_801DD720_599630(task, 15);
    func_801E31DC_59F0EC(task);
    if (!func_801DF858_59B768(task) && !func_801DF8B8_59B7C8(task) && !func_801E1E70_59DD80(task)) {
        func_801DAD08_596C18(task, 0x45);
    }
}

void func_801DF748_59B658(Task *task, ObjSolid *obj)
{
    func_801E7F50_5A3E60(task);
    func_801E31DC_59F0EC(task);
    func_801E1E70_59DD80(task);
    if (!func_801DF858_59B768(task)) {
        if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
            func_801DACDC_596BEC(task, 0x43);
        } else {
            func_801DF8B8_59B7C8(task);
        }
    }
}

void func_801DF7E0_59B6F0(Task *task, ObjSolid *obj)
{
    func_801E7F50_5A3E60(task);
    func_801E1E70_59DD80(task);
    if (!func_801DF858_59B768(task)) {
        if (obj->time <= 0.0f) {
            func_801DACDC_596BEC(task, 0x42);
        } else {
            func_801DF8B8_59B7C8(task);
        }
    }
}

int func_801DF858_59B768(Task *task)
{
    if (PLAYER_WORK(task)->physics->water_state == 0 && PLAYER_WORK(task)->floor_group != 0) {
        PLAYER_WORK(task)->physics->buoyancy    = 0.0f;
        PLAYER_WORK(task)->physics->forced_move = 0;
        PLAYER_WORK(task)->max_speed            = 0.0f;
        PLAYER_WORK(task)->move_accel           = 0.0f;
        func_801DACDC_596BEC(task, 0);
        return 1;
    }
    return 0;
}

int func_801DF8B8_59B7C8(Task *task)
{
    if ((g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & A_BUTTON) && (PLAYER_WORK(task)->physics->water_state & 0x80) &&
        !(PLAYER_WORK(task)->physics->slide_flags & 1)) {
        PLAYER_WORK(task)->physics->buoyancy    = 0.0f;
        PLAYER_WORK(task)->physics->forced_move = 0;
        func_801E20A0_59DFB0(task);
        func_801DACDC_596BEC(task, 0x17);
        return 1;
    }
    return 0;
}

void func_801DF950_59B860(Task *task, ObjSolid *obj)
{
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801DACDC_596BEC(task, 0x4F);
        func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204360_5C0270[PLAYER_WORK(task)->character]);
    } else {
        func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204350_5C0260[PLAYER_WORK(task)->character]);
    }
}

void func_801DFA1C_59B92C(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->floor_group == 0) {
        func_801E55D4_5A14E4(task, 0.0f, 2.0f, 0.0f);
        func_801E3324_59F234(task);
        func_801DAC7C_596B8C(task, 0x1A, 0, PLAYER_WORK(task)->anime_mode);
    } else if (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & B_BUTTON) {
        func_801E307C_59EF8C(task);
        PLAYER_WORK(task)->move_accel = 0.0f;
        func_801DACDC_596BEC(task, 0x50);
        func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204370_5C0280[PLAYER_WORK(task)->character]);
    } else if (!(ABS(g_sys_real.player_controller[PLAYER_WORK(task)->controller].stick_magnitude) < 0.00001)) {
        func_801E3244_59F154(task);
        func_801DACDC_596BEC(task, 0x52);
        func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204380_5C0290[PLAYER_WORK(task)->character]);
    } else {
        func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204360_5C0270[PLAYER_WORK(task)->character]);
    }
}

void func_801DFBC4_59BAD4(Task *task, ObjSolid *obj)
{
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801E55D4_5A14E4(task, 0.0f, 2.0f, 0.0f);
        func_801DACDC_596BEC(task, 0x51);
    } else {
        func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204370_5C0280[PLAYER_WORK(task)->character]);
    }
}

void func_801DFC70_59BB80(Task *task, ObjSolid *obj)
{
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        PLAYER_WORK(task)->physics->forced_move = 0;
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801DFCD8_59BBE8(Task *task, ObjSolid *obj)
{
#ifndef JAPAN_0
    func_801DD720_599630(task, 1);
#endif
    if (PLAYER_WORK(task)->floor_group == 0) {
        func_801E55D4_5A14E4(task, 0.0f, 2.0f, 0.0f);
        func_801E3324_59F234(task);
        func_801DAC7C_596B8C(task, 0x1A, 0, PLAYER_WORK(task)->anime_mode);
        return;
    }
    if (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & B_BUTTON) {
        func_801E307C_59EF8C(task);
        PLAYER_WORK(task)->move_accel = 0.0f;
        func_801DACDC_596BEC(task, 0x50);
        func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204370_5C0280[PLAYER_WORK(task)->character]);
        return;
    }
    if (!func_801E1ED0_59DDE0(task)) {
        func_801DACDC_596BEC(task, 0x4F);
        func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204360_5C0270[PLAYER_WORK(task)->character]);
        return;
    }
    func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204380_5C0290[PLAYER_WORK(task)->character]);
}

void func_801DFE44_59BD54(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->physics->state_timer++ == 0) {
        PLAYER_WORK(task)->max_speed  = 2.8f;
        PLAYER_WORK(task)->move_accel = 0.7f;
        return;
    }
    PLAYER_WORK(task)->max_speed  = 0.0f;
    PLAYER_WORK(task)->move_accel = 1.0f;
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801DD6E0_5995F0(task, 0x16);
        PLAYER_WORK(task)->physics->state_timer = 0;
        if (func_801E3C34_59FB44(PLAYER_WORK(task)->physics->input_angle, PLAYER_WORK(task)->angle, 0x100) &&
            (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_held_down & B_BUTTON)) {
            PLAYER_WORK(task)->physics->forced_angle = (PLAYER_WORK(task)->physics->forced_angle + 0x200) & 0x3FF;
            func_801DACDC_596BEC(task, 0x4A);
        } else {
            func_801DACDC_596BEC(task, 0x47);
        }
    }
}

void func_801DFF70_59BE80(Task *task, ObjSolid *obj)
{
#ifndef JAPAN_0
    if (func_801E0158_59C068(task)) {
        func_801DAD08_596C18(task, 0x48);
        return;
    }
#endif
    switch (PLAYER_WORK(task)->physics->state_timer) {
        case 0:
            if (func_801E3C34_59FB44(PLAYER_WORK(task)->physics->input_angle, PLAYER_WORK(task)->angle, 0x100) &&
                (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_held_down & B_BUTTON)) {
                PLAYER_WORK(task)->max_speed            = 0.0f;
                PLAYER_WORK(task)->move_accel           = 1.0f;
                PLAYER_WORK(task)->physics->state_timer = 0;
                func_801DACDC_596BEC(task, 0x4C);
            } else if (PLAYER_WORK(task)->floor_group == 0) {
                func_801E62D0_5A21E0(task);
                func_801E3324_59F234(task);
                func_801DAC7C_596B8C(task, 0x1A, 0, PLAYER_WORK(task)->anime_mode);
            } else if (!func_801E5D2C_5A1C3C(task, PLAYER_WORK(task)->physics->push_task, 0)) {
                PLAYER_WORK(task)->action_timer = 0;
                PLAYER_WORK(task)->max_speed    = 0.0f;
                PLAYER_WORK(task)->move_accel   = 1.0f;
                PLAYER_WORK(task)->physics->state_timer++;
            }
            break;
        case 1:
            if (++PLAYER_WORK(task)->action_timer >= 6) {
                if (func_801E3C34_59FB44(PLAYER_WORK(task)->physics->input_angle, PLAYER_WORK(task)->angle, 0x100) &&
                    (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_held_down & B_BUTTON)) {
                    PLAYER_WORK(task)->max_speed            = 0.0f;
                    PLAYER_WORK(task)->move_accel           = 1.0f;
                    PLAYER_WORK(task)->physics->state_timer = 0;
                    func_801DACDC_596BEC(task, 0x4C);
                } else {
                    func_801DAD08_596C18(task, 0x48);
                }
            }
            break;
    }
}

#ifndef JAPAN_0
// Whether player character 0, without the power-up, is on an object of kind 0x245.
int func_801E0158_59C068(Task *task)
{
    if (PLAYER_WORK(task)->character == 0) {
        if (PLAYER_WORK(task)->physics->push_task != NULL) {
            if (*(unsigned short *) PLAYER_WORK(task)->physics->push_task->work == 0x245) {
                return PLAYER_WORK(task)->physics->ability_timer == 0;
            }
        }
    }
    return 0;
}
#endif

void func_801E01A0_59C0B0(Task *task, ObjSolid *obj)
{
    if (obj->time <= 0.0) {
        func_801E62D0_5A21E0(task);
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801E01F0_59C100(Task *task, ObjSolid *obj)
{
    PLAYER_STOP(task);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801DACDC_596BEC(task, 0x4A);
    }
}

void func_801E026C_59C17C(Task *task, ObjSolid *obj)
{
#ifndef JAPAN_0
    if (func_801E0158_59C068(task)) {
        func_801DAD08_596C18(task, 0x4B);
        return;
    }
#endif
    switch (PLAYER_WORK(task)->physics->state_timer) {
        case 0:
            if (func_801E3C34_59FB44(PLAYER_WORK(task)->physics->input_angle, PLAYER_WORK(task)->angle, 0x100) &&
                (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_held_down & B_BUTTON)) {
                PLAYER_WORK(task)->max_speed             = 0.0f;
                PLAYER_WORK(task)->move_accel            = 1.0f;
                PLAYER_WORK(task)->physics->state_timer  = 0;
                PLAYER_WORK(task)->physics->forced_angle = (PLAYER_WORK(task)->physics->forced_angle + 0x200) & 0x3FF;
                func_801DAD08_596C18(task, 0x4D);
            } else if (PLAYER_WORK(task)->floor_group == 0) {
                func_801E62D0_5A21E0(task);
                func_801E3324_59F234(task);
                func_801DAC7C_596B8C(task, 0x1A, 0, PLAYER_WORK(task)->anime_mode);
            } else if (!func_801E5D2C_5A1C3C(task, PLAYER_WORK(task)->physics->push_task, 1)) {
                PLAYER_WORK(task)->max_speed  = 0.0f;
                PLAYER_WORK(task)->move_accel = 1.0f;
                PLAYER_WORK(task)->physics->state_timer++;
                PLAYER_WORK(task)->action_timer = 0;
            } else if (!(g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_held_down & B_BUTTON)) {
                PLAYER_WORK(task)->max_speed  = 0.0f;
                PLAYER_WORK(task)->move_accel = 1.0f;
                PLAYER_WORK(task)->physics->state_timer++;
                PLAYER_WORK(task)->action_timer = 0;
            }
            break;
        case 1:
            if (++PLAYER_WORK(task)->action_timer >= 6) {
                if (func_801E3C34_59FB44(PLAYER_WORK(task)->physics->input_angle, PLAYER_WORK(task)->angle, 0x100) &&
                    (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_held_down & B_BUTTON)) {
                    PLAYER_WORK(task)->max_speed             = 0.0f;
                    PLAYER_WORK(task)->move_accel            = 1.0f;
                    PLAYER_WORK(task)->physics->state_timer  = 0;
                    PLAYER_WORK(task)->physics->forced_angle = (PLAYER_WORK(task)->physics->forced_angle + 0x200) & 0x3FF;
                    func_801DAD08_596C18(task, 0x4D);
                } else {
                    func_801DAD08_596C18(task, 0x4B);
                }
            }
            break;
    }
}

void func_801E04D0_59C3E0(Task *task, ObjSolid *obj)
{
    PLAYER_STOP(task);
    if (obj->time <= 0.0) {
        PLAYER_WORK(task)->angle = (PLAYER_WORK(task)->physics->forced_angle + 0x200) & 0x3FF;
        func_801E62D0_5A21E0(task);
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801E0544_59C454(Task *task, ObjSolid *obj)
{
    PLAYER_STOP(task);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        PLAYER_WORK(task)->physics->forced_angle = (PLAYER_WORK(task)->physics->forced_angle + 0x200) & 0x3FF;
        func_801DACDC_596BEC(task, 0x4A);
    }
}

void func_801E05D4_59C4E4(Task *task, ObjSolid *obj)
{
    PLAYER_STOP(task);
    if (obj->time <= 0.0) {
        func_801DACDC_596BEC(task, 0x47);
    }
}

void func_801E0628_59C538(Task *task, ObjSolid *obj)
{
    D_801FC7C4_5B86D4 = 0;
    if (func_801E7338_5A3248(task)) {
        func_801DAD08_596C18(task, 0x3A);
    }
}

void func_801E0664_59C574(Task *task, ObjSolid *obj)
{
    D_801FC7C4_5B86D4 = 0;
    func_801E708C_5A2F9C(task, 0);
}

void func_801E0690_59C5A0(Task *task, ObjSolid *obj)
{
    D_801FC7C4_5B86D4 = 0;
    func_801DD720_599630(task, 5);
    func_801E708C_5A2F9C(task, 1);
}

void func_801E06CC_59C5DC(Task *task, ObjSolid *obj)
{
    D_801FC7C4_5B86D4 = 0;
    func_801DD720_599630(task, 5);
    func_801E708C_5A2F9C(task, 2);
}

void func_801E0708_59C618(Task *task, ObjSolid *obj)
{
#ifndef JAPAN_0
    D_801FC61C_5B852C->hidden = 1;
#endif
    D_801FC7C4_5B86D4 = 0;
    func_801DD720_599630(task, 5);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801E6F00_5A2E10(task);
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801E0794_59C6A4(Task *task, ObjSolid *obj)
{
#ifndef JAPAN_0
    D_801FC61C_5B852C->hidden = 1;
#endif
    D_801FC7C4_5B86D4 = 0;
    func_801DD720_599630(task, 5);
    if (obj->time <= 0.0) {
        func_801E6E98_5A2DA8(task);
        func_801DACDC_596BEC(task, 0x38);
    }
}

void func_801E0810_59C720(Task *task, ObjSolid *obj)
{
}

void func_801E081C_59C72C(Task *task, ObjSolid *obj)
{
    func_801E74EC_5A33FC(task);
    if (
#ifndef JAPAN_0
        PLAYER_WORK(task)->physics->slide_flags == 0 ||
#endif
        (PLAYER_WORK(task)->physics->slide_flags & 8) ||
        ((PLAYER_WORK(task)->physics->slide_flags & 4) && (g_sys_real.player_controller[PLAYER_WORK(task)->controller].button_pressed & A_BUTTON))) {
        func_801E7544_5A3454(task);
        func_801DACDC_596BEC(task, 0x34);
    }
    func_801E8964_5A4874(task, 0x26);
}

void func_801E08B0_59C7C0(Task *task, ObjSolid *obj)
{
}

void func_801E08BC_59C7CC(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->physics->slide_flags & 1) {
        PLAYER_WORK(task)->physics->slide_flags |= 8;
    }
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801E759C_5A34AC(task);
        func_801DACDC_596BEC(task, 0);
    }
    func_801E84A4_5A43B4(task);
}

void func_801E0944_59C854(Task *task, ObjSolid *obj)
{
    task->hit_flags &= ~1;
    switch (PLAYER_WORK(task)->physics->state_timer) {
        case 0:
            if (++PLAYER_WORK(task)->action_timer >= 5) {
                obj->AModel                                      = 0;
                D_801FC61C_5B852C->AModel                        = 0;
                D_8020D262_5C9172[PLAYER_WORK(task)->controller] = g_sys_real.current_graphics_pool;
                PLAYER_WORK(task)->action_timer                  = 0;
                PLAYER_WORK(task)->physics->state_timer++;
            }
            break;
        case 1:
            if (D_8020D262_5C9172[PLAYER_WORK(task)->controller] != g_sys_real.current_graphics_pool) {
                PLAYER_WORK(task)->action_timer++;
                PLAYER_WORK(task)->physics->state_timer++;
            }
            break;
        case 2:
            func_801DC9C8_5988D8(task, PLAYER_WORK(task)->character);
            D_8020D260_5C9170[PLAYER_WORK(task)->controller] = 0;
            PLAYER_WORK(task)->action_timer++;
            PLAYER_WORK(task)->physics->state_timer++;
            break;
        case 3:
            PLAYER_WORK(task)->action_timer++;
            if (func_801DCA64_598974(task, 2, &D_8020D260_5C9170[PLAYER_WORK(task)->controller])) {
                PLAYER_WORK(task)->physics->state_timer++;
            }
            break;
        case 4:
            PLAYER_WORK(task)->physics->changing_character = 0;
            PLAYER_WORK(task)->physics->model_swap         = 2;
            if (PLAYER_WORK(task)->physics->water_state) {
                func_801DACDC_596BEC(task, 0x42);
            } else {
                func_801DACDC_596BEC(task, 0);
            }
            PLAYER_WORK(task)->state = 0xBA;
            func_8003521C((void (*)(Task *, Obj *)) func_801E0944_59C854);
            PLAYER_WORK(task)->physics->model_swap = 0;
            PLAYER_WORK(task)->action_timer++;
            PLAYER_WORK(task)->physics->state_timer++;
            if (!g_sys_real.event_input_locked) {
                func_801DD830_599740(task, 3);
            }
            func_801CBFCC_587EDC(task);
            break;
        case 5:
            if (++PLAYER_WORK(task)->action_timer >= 24) {
                func_801CC454_588364(task);
                PLAYER_WORK(task)->physics->forced_move = 0;
                if (PLAYER_WORK(task)->physics->water_state) {
                    PLAYER_SET_ACTION(task, 0x42, func_801DF610_59B520);
                } else if (D_8015C5D8.max_health >= D_8015C5D8.health * 4) {
                    PLAYER_SET_ACTION(task, 1, func_801DDA88_599998);
                } else {
                    PLAYER_SET_ACTION(task, 0, func_801DDA68_599978);
                }
            }
            break;
    }
}

void func_801E0BF8_59CB08(Task *task, ObjSolid *obj)
{
    switch (PLAYER_WORK(task)->physics->state_timer) {
        case 0:
            func_801DC9C8_5988D8(task, PLAYER_WORK(task)->character);
            D_8020D260_5C9170[PLAYER_WORK(task)->controller] = 0;
            PLAYER_WORK(task)->physics->state_timer++;
            break;
        case 1:
            func_801DCA64_598974(task, 0, &D_8020D260_5C9170[PLAYER_WORK(task)->controller]);
            PLAYER_WORK(task)->physics->state_timer++;
            break;
        case 2:
            PLAYER_WORK(task)->physics->changing_character = 0;
            PLAYER_WORK(task)->physics->model_swap         = 2;
            task->hit_flags |= 1;
            PLAYER_WORK(task)->physics->forced_move = 0;
            func_801DACDC_596BEC(task, 0);
            PLAYER_WORK(task)->physics->model_swap = 0;
            break;
    }
}

void func_801E0CE4_59CBF4(Task *task, ObjSolid *obj)
{
    func_801DD720_599630(task, 6);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        task->hit_flags |= 1;
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801E0D5C_59CC6C(Task *task, ObjSolid *obj)
{
    func_801DD720_599630(task, 7);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        if (PLAYER_WORK(task)->character == 1) {
            func_801DACDC_596BEC(task, 0xD0);
        } else {
            task->hit_flags |= 1;
            func_801DACDC_596BEC(task, 0);
        }
    }
}

void func_801E0DF8_59CD08(Task *task, ObjSolid *obj)
{
    func_801DD720_599630(task, 8);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801DACDC_596BEC(task, 0xD1);
    }
}

void func_801E0E60_59CD70(Task *task, ObjSolid *obj)
{
    func_801DD720_599630(task, 9);
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        task->hit_flags |= 1;
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801E0ED8_59CDE8(Task *task, ObjSolid *obj)
{
    func_801E7B24_5A3A34(task, 0, 0);
}

void func_801E0F00_59CE10(Task *task, ObjSolid *obj)
{
    func_801E7B24_5A3A34(task, 1, 0);
}

void func_801E0F28_59CE38(Task *task, ObjSolid *obj)
{
    func_801E7B24_5A3A34(task, 2, D_802043A0_5C02B0[PLAYER_WORK(task)->character][0]);
    if (PLAYER_WORK(task)->character == 1 || PLAYER_WORK(task)->character == 2) {
        func_801E83F8_5A4308(task);
    }
}

void func_801E0F88_59CE98(Task *task, ObjSolid *obj)
{
    func_801E7B24_5A3A34(task, 2, D_802043A0_5C02B0[PLAYER_WORK(task)->character][1]);
}

void func_801E0FC0_59CED0(Task *task, ObjSolid *obj)
{
    func_801E7B24_5A3A34(task, 2, D_802043A0_5C02B0[PLAYER_WORK(task)->character][2]);
}

void func_801E0FF8_59CF08(Task *task, ObjSolid *obj)
{
    func_801E7B24_5A3A34(task, 2, D_802043A0_5C02B0[PLAYER_WORK(task)->character][3]);
}

void func_801E1030_59CF40(Task *task, ObjSolid *obj)
{
    func_801E1150_59D060(task);
    if (PLAYER_WORK(task)->character == 1 || PLAYER_WORK(task)->character == 2) {
        func_801E84A4_5A43B4(task);
    }
}

void func_801E1078_59CF88(Task *task, ObjSolid *obj)
{
    func_801E1150_59D060(task);
    if (PLAYER_WORK(task)->character == 1 || PLAYER_WORK(task)->character == 2) {
        func_801E84A4_5A43B4(task);
    }
}

void func_801E10C0_59CFD0(Task *task, ObjSolid *obj)
{
    func_801E1150_59D060(task);
    if (PLAYER_WORK(task)->character == 1 || PLAYER_WORK(task)->character == 2) {
        func_801E84A4_5A43B4(task);
    }
}

void func_801E1108_59D018(Task *task, ObjSolid *obj)
{
    func_801E1150_59D060(task);
    if (PLAYER_WORK(task)->character == 1 || PLAYER_WORK(task)->character == 2) {
        func_801E84A4_5A43B4(task);
    }
}

void func_801E1150_59D060(Task *task)
{
    ObjSolid *solid = (ObjSolid *) task->obj_head;

    if ((*anime_frame_count)(solid) -1.0f <= solid->time) {
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801E11B0_59D0C0(Task *task, ObjSolid *obj)
{
}

void func_801E11BC_59D0CC(Task *task, ObjSolid *obj)
{
}

void func_801E11C8_59D0D8(Task *task, ObjSolid *obj)
{
}

void func_801E11D4_59D0E4(Task *task, ObjSolid *obj)
{
}

void func_801E11E0_59D0F0(Task *task, ObjSolid *obj)
{
}

void func_801E11EC_59D0FC(Task *task, ObjSolid *obj)
{
}

void func_801E11F8_59D108(Task *task, ObjSolid *obj)
{
}

void func_801E1204_59D114(Task *task, ObjSolid *obj)
{
}

void func_801E1210_59D120(Task *task, ObjSolid *obj)
{
}

void func_801E121C_59D12C(Task *task, ObjSolid *obj)
{
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801DACDC_596BEC(task, 0xC6);
        func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204360_5C0270[PLAYER_WORK(task)->character]);
    } else {
        func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204350_5C0260[PLAYER_WORK(task)->character]);
    }
}

void func_801E12E8_59D1F8(Task *task, ObjSolid *obj)
{
    func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204360_5C0270[PLAYER_WORK(task)->character]);
}

void func_801E132C_59D23C(Task *task, ObjSolid *obj)
{
    func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204370_5C0280[PLAYER_WORK(task)->character]);
}

void func_801E1370_59D280(Task *task, ObjSolid *obj)
{
    if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
        func_801DACDC_596BEC(task, 0xC4);
    }
}

void func_801E13D0_59D2E0(Task *task, ObjSolid *obj)
{
    func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204350_5C0260[PLAYER_WORK(task)->character]);
}

void func_801E1414_59D324(Task *task, ObjSolid *obj)
{
    func_801E54E0_5A13F0(task, D_80204340_5C0250[PLAYER_WORK(task)->character], D_80204390_5C02A0[PLAYER_WORK(task)->character]);
}

void func_801E1458_59D368(Task *task, ObjSolid *obj)
{
    func_801DD720_599630(task, 1);
}

void func_801E147C_59D38C(Task *task, ObjSolid *obj)
{
}

void func_801E1488_59D398(Task *task, ObjSolid *obj)
{
}

void func_801E1494_59D3A4(Task *task, ObjSolid *obj)
{
}

void func_801E14A0_59D3B0(Task *task, ObjSolid *obj)
{
}

void func_801E14AC_59D3BC(Task *task, ObjSolid *obj)
{
}

void func_801E14B8_59D3C8(Task *task, ObjSolid *obj)
{
}

void func_801E14C4_59D3D4(Task *task, ObjSolid *obj)
{
}

void func_801E14D0_59D3E0(Task *task, ObjSolid *obj)
{
}

void func_801E14DC_59D3EC(Task *task, ObjSolid *obj)
{
}

void func_801E14E8_59D3F8(Task *task, ObjSolid *obj)
{
}

void func_801E14F4_59D404(Task *task, ObjSolid *obj)
{
}

void func_801E1500_59D410(Task *task, ObjSolid *obj)
{
}

void func_801E150C_59D41C(Task *task, ObjSolid *obj)
{
}

void func_801E1518_59D428(Task *task, ObjSolid *obj)
{
}

void func_801E1524_59D434(Task *task, ObjSolid *obj)
{
}

void func_801E1530_59D440(Task *task, ObjSolid *obj)
{
}

void func_801E153C_59D44C(Task *task, ObjSolid *obj)
{
}

void func_801E1548_59D458(Task *task, ObjSolid *obj)
{
}

void func_801E1554_59D464(Task *task, ObjSolid *obj)
{
}

void func_801E1560_59D470(Task *task, ObjSolid *obj)
{
}

void func_801E156C_59D47C(Task *task, ObjSolid *obj)
{
}

void func_801E1578_59D488(Task *task, ObjSolid *obj)
{
}

void func_801E1584_59D494(Task *task, ObjSolid *obj)
{
}

void func_801E1590_59D4A0(Task *task, ObjSolid *obj)
{
}

void func_801E159C_59D4AC(Task *task, ObjSolid *obj)
{
}

void func_801E15A8_59D4B8(Task *task, ObjSolid *obj)
{
}

void func_801E15B4_59D4C4(Task *task, ObjSolid *obj)
{
}

void func_801E15C0_59D4D0(Task *task, ObjSolid *obj)
{
}
