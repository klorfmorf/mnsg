// Player overlay (5AFA40).
#include "common.h"
#include "structs.h"
#include "macros.h"
#include "file_11.h"
#include "5A6F30.h"
#include "sys/task.h"
#include "sys/obj_alloc.h"
#include "sys/anime.h"
#include "sys/gfx_util.h"
#include "sys/gfx_data.h"
#include "sys/sys.h"
#include "unk.h"

int func_801F3FAC_5AFEBC(Task *task, ObjSolid *solid, Vtx *vtx, unsigned char n, ObjSolid *pose, unsigned char ja, unsigned char jb);

void func_801F3B30_5AFA40(Task *player, unsigned char kind)
{
    Task         *task;
    ObjSolid     *solid;
    unsigned char i;

    if (PLAYER_WORK(D_801FC604_5B8514)->physics->afterline == NULL) {
        task = func_80034E08(player, D_80204868_5C0778[kind], 0);
        if (task != NULL) {
            func_801EE4AC_5AA3BC(task, player, kind);
            solid = func_80035EEC(task, 2, 2);
            if (solid == NULL) {
                PLAYER_EFFECT_WORK(task)->done = 1;
            } else {
                for (i = 0; i < 6; i++) {
                    solid->SegWave[i] = D_801FC60C_5B851C->SegWave[i];
                }
                solid->AModel                                      = 0;
                PLAYER_WORK(D_801FC604_5B8514)->physics->afterline = task;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5AFA40/D_8020C150_5C8060.s")

void func_801F3C10_5AFB20(Task *task, ObjSolid *solid)
{
    ObjSolid      a;
    unsigned char i;
    int           pad[9];

    Task *effect = PLAYER_WORK(D_801FC604_5B8514)->physics->afterline;

    if (effect != NULL) {
        if (task != effect) {
            PLAYER_EFFECT_WORK(task)->done = 1;
            solid->hidden                  = 1;
            return;
        }
    }
    if (PLAYER_EFFECT_WORK(task)->unk_06) {
        if (PLAYER_EFFECT_WORK(task)->unk_06++ >= 4) {
            PLAYER_EFFECT_WORK(task)->done = 1;
            solid->hidden                  = 1;
            return;
        }
    } else {
        PLAYER_EFFECT_WORK(task)->angle = PLAYER_WORK(D_801FC604_5B8514)->angle;
        solid->time                     = D_801FC60C_5B851C->time;
    }
    PLAYER_EFFECT_WORK(task)->model = D_801FC60C_5B851C->AModel;
    for (i = 0; i < 6; i++) {
        solid->SegWave[i] = D_801FC60C_5B851C->SegWave[i];
    }
    a.tx = a.ty = a.tz = 0.0f;
    a.rx = a.ry = a.rz = 0;
    a.sx = a.sy = a.sz = 1.0f;
    for (i = 0; i < 6; i++) {
        a.SegWave[i] = D_801FC60C_5B851C->SegWave[i];
    }
    a.AModel = (PLAYER_EFFECT_WORK(task)->model & 0x8FFFFFFE) + 0x10000000;
    a.time   = solid->time;
    if (PLAYER_EFFECT_WORK(task)->unk_06 == 0) {
        if (!anime_locate_joint(NULL, &a, 0x0FFFFF40)) {
            if (func_801F3FAC_5AFEBC(task, solid, D_80205108_5C1018, 6, &a, 0, 2)) {
                PLAYER_WORK(D_801FC604_5B8514)->physics->afterline = NULL;
                PLAYER_EFFECT_WORK(task)->unk_06++;
            } else {
                PLAYER_EFFECT_WORK(task)->count++;
                if (PLAYER_EFFECT_WORK(task)->count >= 7) {
                    PLAYER_EFFECT_WORK(task)->count = 6;
                }
            }
            solid->AModel = (unsigned int) D_8006E170 + 0x40000000;
        } else {
            if (func_801F3FAC_5AFEBC(task, solid, D_80205108_5C1018, 6, &a, 0, 2) || func_801F3FAC_5AFEBC(task, solid, D_802051C8_5C10D8, 6, &a, 3, 5)) {
                PLAYER_WORK(D_801FC604_5B8514)->physics->afterline = NULL;
                PLAYER_EFFECT_WORK(task)->unk_06++;
            } else {
                PLAYER_EFFECT_WORK(task)->count++;
                if (PLAYER_EFFECT_WORK(task)->count >= 7) {
                    PLAYER_EFFECT_WORK(task)->count = 6;
                }
            }
            solid->AModel = (unsigned int) D_8006E1C8 + 0x40000000;
        }
    }
    if (PLAYER_EFFECT_WORK(task)->count == 0) {
        PLAYER_EFFECT_WORK(task)->done = 1;
        solid->hidden                  = 1;
    } else {
        solid->header.pri = 9;
        func_8001C970(solid, D_801FC60C_5B851C);
        solid->sx *= 0.2;
        solid->sy *= 0.2;
        solid->sz *= 0.2;
        func_8001DB04(&solid->rx, &PLAYER_WORK(D_801FC604_5B8514)->physics->unk_3c, 0, PLAYER_EFFECT_WORK(task)->angle, 0);
        solid->init_glist = (unsigned int) D_80205100_5C1010 | 0x20000000;
    }
}

#ifdef NON_MATCHING
int func_801F3FAC_5AFEBC(Task *task, ObjSolid *solid, Vtx *vtx, unsigned char n, ObjSolid *pose, unsigned char ja, unsigned char jb)
{
    AfterlineJoints joints = D_802052D0_5C11E0;
    ObjSolid        b;
    ObjSolid        a;
    unsigned char   kind;
    float           scale = 0.0f;
    signed char     i;
    unsigned char   idx;
    unsigned char   src;
    unsigned char   dst;
    Vtx            *s;
    unsigned char  *col;
    Vtx            *v;

    i   = n - 1;
    idx = n * 2 - 1;
    if (D_8015C5D8.unk_2c == 1) {
        if (D_8015C608.unk_a4[PLAYER_WORK(D_801FC604_5B8514)->character] == 0) {
            kind = PLAYER_WORK(D_801FC604_5B8514)->character;
        } else if (D_8015C608.unk_a4[PLAYER_WORK(D_801FC604_5B8514)->character] == 1) {
            kind = 4;
        } else if (D_8015C608.unk_a4[PLAYER_WORK(D_801FC604_5B8514)->character] == 2) {
            kind = 5;
        }
    } else if (D_8015C5D8.unk_2c == 2) {
        if (PLAYER_WORK(D_801FC604_5B8514)->character == 0) {
            kind = 6;
        }
        if (PLAYER_WORK(D_801FC604_5B8514)->character == 1) {
            kind = 7;
        }
    }

    for (; i >= 0; i--) {
        if (i == 0) {
            if (!anime_locate_joint(&a, pose, joints.target[ja])) {
                return 1;
            }
            if (a.sx < 0.2) {
                return 1;
            }
            if (!anime_locate_joint(&b, pose, joints.target[jb])) {
                return 1;
            }
            if (b.sx < 0.2) {
                return 1;
            }
            v             = &vtx[idx];
            v->v.ob[0]    = b.tx * 5.0f;
            v->v.ob[1]    = b.ty * 5.0f;
            v->v.ob[2]    = b.tz * 5.0f;
            v[-1].v.ob[0] = a.tx * 5.0f;
            v[-1].v.ob[1] = a.ty * 5.0f;
            v[-1].v.ob[2] = a.tz * 5.0f;
            col           = D_802052A0_5C11B0[kind];
        } else {
            col = D_802052A0_5C11B0[kind];
            if (PLAYER_EFFECT_WORK(task)->count < i) {
                src = PLAYER_EFFECT_WORK(task)->count;
            } else {
                src = idx - 2;
            }
            dst = idx;
            if (i != n - 1) {
                s             = &vtx[src];
                v             = &vtx[dst];
                v->v.ob[0]    = s->v.ob[0];
                v->v.ob[1]    = s->v.ob[1];
                v->v.ob[2]    = s->v.ob[2];
                v[-1].v.ob[0] = s[-1].v.ob[0];
                v[-1].v.ob[1] = s[-1].v.ob[1];
                v[-1].v.ob[2] = s[-1].v.ob[2];
            } else {
                v          = &vtx[dst];
                v->v.ob[0] = v[-1].v.ob[0] = ((float) v->v.ob[0] + v[-1].v.ob[0]) * 0.5;
                v->v.ob[2] = v[-1].v.ob[2] = v->v.ob[1] = v[-1].v.ob[1] = ((float) v[-1].v.ob[0] + v->v.ob[0]) * 0.5;
            }
        }
        v[-1].v.cn[0] = col[0];
        v[-1].v.cn[1] = col[1];
        v[-1].v.cn[2] = col[2];
        v->v.cn[0]    = col[3];
        v->v.cn[1]    = col[4];
        v->v.cn[2]    = col[5];
        v->v.cn[3] = v[-1].v.cn[3] = scale;
        scale += 200.0f / (n - 1);
        if (scale > 200.0f) {
            scale = 200.0f;
        }
        idx -= 2;
    }

    if (PLAYER_EFFECT_WORK(task)->count == 0) {
        solid->hidden = 1;
    } else {
        solid->hidden = 0;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/5AFA40/func_801F3FAC_5AFEBC.s")
#endif
