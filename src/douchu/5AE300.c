#include "douchu/5AE300.h"
#include "common.h"
#include "structs.h"
#include "macros.h"
#include "douchu/5A12F0.h"
#include "douchu/5A4730.h"
#include "sys/sd_main.h"
#include "sys/gfx_util.h"
#include "douchu/5959C0.h"
#include "douchu/5A6F30.h"
#include "sys/task.h"
#include "sys/wave_uty.h"
#include "sys/gfx_data.h"
#include "sys/sd_location.h"
#include "sys/sys.h"
#include "douchu/587B50.h"
#include "douchu/5883D0.h"
#include "unk.h"

extern unsigned int         D_80205000_5C0F10[];
extern PlayerEffectTemplate D_80205078_5C0F88;
extern PlayerEffectTemplate D_80205084_5C0F94;
extern PlayerEffectTemplate D_80205090_5C0FA0;

void func_801F23F0_5AE300(Task *task, unsigned char kind)
{
    PlayerEffectTemplate *tmpl;
    Task                 *effect;
    ObjSolid             *solid;

    switch (kind) {
        case 0x20:
            tmpl = &D_80205078_5C0F88;
            break;
        case 0x29:
            tmpl = &D_80205084_5C0F94;
            break;
        case 0x2A:
            tmpl = &D_80205090_5C0FA0;
            break;
        default:
            return;
    }
    if (func_801E8C44_5A4B54(task, kind) != 0) {
        return;
    }
    effect = func_800358E8(task, tmpl->exec, (unsigned int) D_A000800 + 0x40000000, 0, D_801FC60C_5B851C->tx, (PLAYER_WORK(D_801FC604_5B8514)->physics->body_height - 0x28) * D_801FC60C_5B851C->sy + (D_801FC60C_5B851C->ty + PLAYER_WORK(D_801FC604_5B8514)->physics->water_height), D_801FC60C_5B851C->tz, 0, 0, 0, D_801FC60C_5B851C->sx, D_801FC60C_5B851C->sy, D_801FC60C_5B851C->sz, 0, 0x80);
    if (effect == NULL) {
        return;
    }
    solid = (ObjSolid *) effect->obj_head;
    if (solid == NULL) {
        return;
    }
    func_801EE4AC_5AA3BC(effect, task, kind);
    func_801DC554_598464(0, PLAYER_EFFECT_WORK(effect)->dl, D_8006DDE8, tmpl->prim_r, tmpl->prim_g, tmpl->prim_b, tmpl->env_r, tmpl->env_g, tmpl->env_b, tmpl->env_a);
    solid->init_glist         = (unsigned int) PLAYER_EFFECT_WORK(effect)->dl | 0x20000000;
    solid->SegWave[2].wave_no = 0x152;
    func_80014218(solid);
    func_801E8820_5A4730(solid, 0xA, D_80205000_5C0F10);
    solid->header.pri = 7;
    solid->disabled   = 0;
}

void func_801F25D8_5AE4E8(Task *task, ObjSolid *obj)
{
    PlayerPhysics *physics = PLAYER_WORK(D_801FC604_5B8514)->physics;
    int            pad;
    unsigned short rot[3];
    float          vec[3];
    float          scale;
    float          abs_y;
    float          zero = 0.0f;

    obj->tx = D_801FC60C_5B851C->tx;
    obj->tz = D_801FC60C_5B851C->tz;
    if (physics->water_height < zero) {
        abs_y = -physics->water_height;
    } else {
        abs_y = physics->water_height;
    }
    scale = (12.0f - abs_y) * (D_801FC60C_5B851C->sx * 0.1);
    if (scale < zero) {
        scale = zero;
    }
    if (D_801FC60C_5B851C->sx < scale) {
        scale = D_801FC60C_5B851C->sx;
    }
    obj->ty = (physics->body_height - 0x28) * D_801FC60C_5B851C->sy + (D_801FC60C_5B851C->ty + physics->water_height);
    if (func_801E7E40_5A3D50(D_801FC604_5B8514) != 0) {
        if (zero == obj->sx * scale && scale != obj->sx) {
            func_80038B98(0x287);
        }
    }
    obj->sz = scale;
    obj->sx = scale;
    rot[0]  = 0;
    rot[1]  = 0;
    rot[2]  = 0;
    vec[0]  = physics->water_normal[0];
    vec[1]  = physics->water_normal[1];
    vec[2]  = physics->water_normal[2];
    func_8001DB04(rot, vec, 0, 0, 0);
    obj->rx = rot[0];
    obj->ry = rot[1];
    obj->rz = rot[2];
    if (physics->water_result == 0) {
        PLAYER_EFFECT_WORK(task)->done = 1;
        obj->hidden                    = 1;
    } else {
        func_801E8858_5A4768(obj, 0xA);
    }
}

#ifdef NON_MATCHING
void func_801F27AC_5AE6BC(Task *task, unsigned char kind)
{
    PlayerPhysics    *physics = PLAYER_WORK(D_801FC604_5B8514)->physics;
    Task             *effect;
    ObjSolid         *solid;
    float             vec[3];
    unsigned short    rot[3];
    float             y;
    PlayerEffectAnim *anim;
    float             abs_a4;
    unsigned int      model;

    if (func_801E8C44_5A4B54(task, kind) != 0) {
        return;
    }
    y = D_8020CAC0_5C89D0[1] + D_801FC60C_5B851C->ty + physics->water_height + (physics->body_height - 0x28) * D_801FC60C_5B851C->sy;
    if (y > D_801FC60C_5B851C->ty + D_801FC60C_5B851C->sy * 300.0f || y < D_801FC60C_5B851C->ty - D_801FC60C_5B851C->sy * 100.0f) {
        return;
    }
    rot[0] = rot[1] = rot[2] = 0;
    vec[0]                   = physics->water_normal[0];
    vec[1]                   = physics->water_normal[1];
    vec[2]                   = physics->water_normal[2];
    func_8001DB04(rot, vec, 0, 0, 0);
    effect = func_800358E8(task, func_801F2B70_5AEA80, (unsigned int) (D_09000D70_F58A30 + 0x1E60) + 0x40000000, 0, D_8020CAC0_5C89D0[0] + D_801FC60C_5B851C->tx, y, D_8020CAC0_5C89D0[2] + D_801FC60C_5B851C->tz, rot[0], rot[1], rot[2], D_801FC60C_5B851C->sx, D_801FC60C_5B851C->sy, D_801FC60C_5B851C->sz, 0, 0x80);
    if (effect == NULL) {
        return;
    }
    solid = (ObjSolid *) effect->obj_head;
    if (solid == NULL) {
        return;
    }
    func_801EE4AC_5AA3BC(effect, task, kind);
    func_801DC554_598464(0, PLAYER_EFFECT_WORK(effect)->dl, D_802049C0_5C08D0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0x80);
    solid->init_glist         = (unsigned int) PLAYER_EFFECT_WORK(effect)->dl | 0x20000000;
    solid->SegWave[2].wave_no = 0x152;
    func_80014218(solid);
    solid->header.pri = 7;
    solid->disabled   = 0;
    model             = D_801FC628_5B8538->AModel & 0x8FFFFFFE;
    if (g_sys_real.wait_frames == 0) {
        if (PLAYER_WORK(D_801FC604_5B8514)->vertical_speed < 0.0f) {
            abs_a4 = -PLAYER_WORK(D_801FC604_5B8514)->vertical_speed;
        } else {
            abs_a4 = PLAYER_WORK(D_801FC604_5B8514)->vertical_speed;
        }
        if (abs_a4 < 7.0f) {
            func_8000FE1C(0x287, model, solid->tx, solid->ty, solid->tz, 600.0f);
        } else {
            func_8000FE1C(0x284, model, solid->tx, solid->ty, solid->tz, 600.0f);
        }
    }
    if (PLAYER_WORK(D_801FC604_5B8514)->vertical_speed < 0.0f) {
        abs_a4 = -PLAYER_WORK(D_801FC604_5B8514)->vertical_speed;
    } else {
        abs_a4 = PLAYER_WORK(D_801FC604_5B8514)->vertical_speed;
    }
    solid->sx = solid->sz = (abs_a4 * 0.5 / 6.0 + 0.5) * D_801FC60C_5B851C->sx;
    anim                  = &PLAYER_EFFECT_WORK(effect)->anim;
    if (PLAYER_WORK(D_801FC604_5B8514)->vertical_speed < 0.0f) {
        abs_a4 = -PLAYER_WORK(D_801FC604_5B8514)->vertical_speed;
    } else {
        abs_a4 = PLAYER_WORK(D_801FC604_5B8514)->vertical_speed;
    }
    anim->state   = 0;
    anim->counter = 0;
    anim->speed   = abs_a4 * 0.03 / 5.0;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5AE300/func_801F27AC_5AE6BC.s")
#endif

void func_801F2B70_5AEA80(Task *task, ObjSolid *obj)
{
    PlayerEffectAnim *anim = &PLAYER_EFFECT_WORK(task)->anim;

    switch (anim->state) {
        case 0:
            anim->state = 1;
            break;
        case 1:
            obj->sx += 0.005f;
            obj->sz += 0.005f;
            if (anim->counter < 4.5) {
                obj->sy += anim->speed;
            }
            if (anim->counter > 4.5) {
                obj->sy -= 0.02;
            }
            if (obj->sy <= 0.0) {
                obj->sy     = 0.0f;
                anim->state = 2;
            }
            break;
        case 2:
            if (D_8020CA6C_5C897C == 0) {
                PLAYER_EFFECT_WORK(task)->done = 1;
                return;
            }
            break;
    }
    anim->counter++;
}

void func_801F2CB4_5AEBC4(Task *task, ObjSolid *obj)
{
}

void func_801F2CC0_5AEBD0(Task *task, ObjSolid *obj)
{
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5AE300/D_8020BEE0_5C7DF0.s")
