#include "douchu/file_11.h"
#include "common.h"
#include "sys/task.h"
#include "sys/string.h"
#include "sys/sys.h"
#include "sys/step.h"
#include "sys/obj.h"
#include "sys/obj_alloc.h"
#include "sys/anime.h"
#include "sys/gfx_util.h"
#include "douchu/59D4E0.h"
#include "douchu/587B50.h"
#include "douchu/5883D0.h"
#include "douchu/5944C0.h"
#include "douchu/5959C0.h"
#include "douchu/598540.h"
#include "douchu/5A12F0.h"
#include "douchu/5A4730.h"
#include "douchu/5B6060.h"
#include "douchu/58E2D0.h"
#include "unk.h"

void func_801CB7D4_5876E4(Task *task, ObjSolid *obj);
void func_801CBAF8_587A08(Task *task, ObjSolid *obj);
void func_801CBBE8_587AF8(Task *task);
void func_801CB5C4_5874D4(Task *task, ObjSolid *obj);
void func_801CB800_587710(Task *task, ObjSolid *obj);

extern PlayerModeTable D_801FC5F0_5B8500;
extern PlayerPhysics   D_8020C860_5C8770;

void func_801CB460_587370(void)
{
    PlayerModeTable table = D_801FC5F0_5B8500;
    int             pad;

    table.funcs[g_sys->mode]();
}

void func_801CB4C4_5873D4(void)
{
    func_80004240();
    g_sys->mode_frame_count = 0;
    func_80003478();
    func_8000A0F0();
    func_8003488C((void (*)(Task *, Obj *)) func_801CB5C4_5874D4);
    func_80035B50();
}

void func_801CB518_587428(void)
{
    func_80034734();
    if (g_sys->player_controller[0].button_pressed & 0x1000) {
        func_80003478();
    }
    g_sys->mode_frame_count++;
}

void func_801CB58C_58749C(void)
{
    func_80004240();
    g_sys->mode_end = 1;
}

void func_801CB5C4_5874D4(Task *task, ObjSolid *obj)
{
}

#ifdef NON_MATCHING
void func_801CB5D0_5874E0(Task *parent, ObjSolid *obj)
{
    int i;

    D_801FC604_5B8514                       = func_800358E8(parent, func_801CB7D4_5876E4, 0, 0, g_sys->next_entry.x, g_sys->next_entry.y, g_sys->next_entry.z, 0, g_sys->next_entry.facing, 0, 0.1f, 0.1f, 0.1f, 0, 0);
    PLAYER_WORK(D_801FC604_5B8514)->physics = &D_8020C860_5C8770;
    D_8020C860_5C8770.flags                 = 0;
    for (i = 1; i < 0x31; i++) {
    }
    D_801FC60C_5B851C = D_801FC604_5B8514->obj_head;
    D_801FC614_5B8524 = func_80035EEC(D_801FC604_5B8514, 2, 1);
    D_801FC61C_5B852C = func_80035EEC(D_801FC604_5B8514, 2, 1);
    func_8001C9BC(D_801FC614_5B8524, D_801FC60C_5B851C);
    func_8001C9BC(D_801FC61C_5B852C, D_801FC60C_5B851C);
    PLAYER_WORK(D_801FC604_5B8514)->character = D_8015C5D8.character;
    func_801D9B78_595A88(D_801FC61C_5B852C);
    D_801FC604_5B8514->contact = D_801FC640_5B8550;
    func_801CBC40_587B50();
    func_801D23D4_58E2E4();
    PLAYER_WORK(D_801FC604_5B8514)->camera     = D_801FC624_5B8534;
    PLAYER_WORK(D_801FC604_5B8514)->controller = 0;
    D_801FC638_5B8548                          = func_80034E08(parent, func_801E8EC4_5A4DD4, 0);
    PLAYER_WORK(D_801FC604_5B8514)->fx_mgr     = D_801FC638_5B8548;
    PLAYER_FX_WORK(D_801FC638_5B8548)->player  = D_801FC604_5B8514;
    func_8003521C(func_801CB800_587710);
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/file_11/func_801CB5D0_5874E0.s")
#endif

void func_801CB7A8_5876B8(Task *task, ObjSolid *obj)
{
    func_8003521C((void (*)(Task *, Obj *)) func_801CB7D4_5876E4);
}

void func_801CB7D4_5876E4(Task *task, ObjSolid *obj)
{
    func_801CC30C_58821C(task);
}

void func_801CB7F4_587704(Task *task, ObjSolid *obj)
{
}

void func_801CB800_587710(Task *task, ObjSolid *obj)
{
    func_801D98E0_5957F0();
}

void func_801CB824_587734(Task *task, ObjSolid *obj)
{
    PlayerPhysics *physics = PLAYER_WORK(task)->physics;

    if (physics->changing_character != 0) {
        return;
    }
    if (obj->blend == 0.0f && (PLAYER_WORK(task)->anime_mode & 0x80) != 0x80) {
        obj->time += PLAYER_WORK(task)->anime_speed + physics->extra_anime_speed;
        if (PLAYER_WORK(task)->anime_mode != 0) {
            if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
                obj->time = (*anime_frame_count)(obj) -1.0f;
            }
        } else {
            if ((*anime_frame_count)(obj) -1.0f <= obj->time) {
                obj->time -= (*anime_frame_count)(obj) -1.0f;
            }
        }
    }
    PLAYER_WORK(task)->physics->charge_level = func_801DC27C_59818C(task, obj);
    if (g_sys_real.player_event_mode & 1) {
        return;
    }
    if (g_sys_real.player_event_mode & 2) {
        return;
    }
    if (func_801DCE10_598D20(task) == 4) {
        func_801E8D90_5A4CA0(task, 1);
        return;
    }
    if (PLAYER_WORK(task)->physics->changing_character != 0) {
        return;
    }
    func_801D9CE8_595BF8(task);
    func_801E78DC_5A37EC(task);
    if (g_sys_real.player_input_locked == 0 && g_sys_real.event_input_locked == 0) {
        if (g_sys_real.player_event_mode == 0 || g_sys_real.player_event_mode == 4) {
            if (func_801D9E9C_595DAC(task)) {
                func_801E8E24_5A4D34(task, 1);
            }
        }
    }
    if (func_801DC120_598030(task)) {
        func_801E8E24_5A4D34(task, 1);
    }
    if (func_801E630C_5A221C(task, 0x322)) {
        func_801E8E24_5A4D34(task, 1);
    }
    if (func_801E630C_5A221C(task, 0x33B)) {
        func_801E8E24_5A4D34(task, 1);
    }
    if (func_801E630C_5A221C(task, 0x33C)) {
        func_801E8E24_5A4D34(task, 1);
    }
    if (func_801E73BC_5A32CC(task)) {
        func_801E8E24_5A4D34(task, 1);
    }
    D_801FC61C_5B852C->hidden = 0;
}

void func_801CBACC_5879DC(Task *task, ObjSolid *obj)
{
    func_80035234((void (*)(Task *, Obj *)) func_801CBAF8_587A08);
}

void func_801CBAF8_587A08(Task *task, ObjSolid *obj)
{
    if (PLAYER_WORK(task)->physics->changing_character == 0) {
        func_801DABDC_596AEC(task);
    }
    if ((g_sys_real.player_event_mode & 3) == 0) {
        func_801CC4C0_5883D0(task, PLAYER_WORK(task)->max_speed, PLAYER_WORK(task)->move_accel);
        if (PLAYER_WORK(task)->facing_override & 0x8000) {
            PLAYER_WORK(task)->angle = PLAYER_WORK(task)->facing_override & 0x3FF;
        }
        func_801CD084_588F94(task);
        func_801CBBE8_587AF8(task);
    }
    func_801D9C54_595B64(task);
    func_801FB1C0_5B70D0(PLAYER_WORK(task)->wall_group, PLAYER_WORK(task)->physics->wall_task);
    task->hit_by                            = 0;
    task->hit                               = 0;
    PLAYER_WORK(task)->physics->angle       = PLAYER_WORK(task)->angle;
    PLAYER_WORK(task)->physics->speed_prev2 = PLAYER_WORK(task)->physics->speed_prev;
    PLAYER_WORK(task)->physics->speed_prev  = PLAYER_WORK(task)->physics->speed;
    PLAYER_WORK(task)->physics->speed       = g_sys_real.player_controller[PLAYER_WORK(task)->controller].stick_magnitude;
}

void func_801CBBE8_587AF8(Task *task)
{
    if (PLAYER_WORK(task)->ceiling_hit != 0 && PLAYER_WORK(task)->state >= 0x17 && PLAYER_WORK(task)->state < 0x1B) {
        func_801E3358_59F268(task);
        func_801DACDC_596BEC(task, 0x3B);
    }
}
