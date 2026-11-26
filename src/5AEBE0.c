// Player overlay (5AEBE0).
#include "common.h"
#include "structs.h"
#include "macros.h"
#include "file_11.h"
#include "5A4730.h"
#include "5A6F30.h"
#include "sys/task.h"
#include "5944C0.h"
#include "sys/obj_alloc.h"
#include "unk.h"

void func_801F3A9C_5AF9AC(Task *task, ObjSolid *obj);
void func_801F2ED0_5AEDE0(Task *task, ObjSolid *obj);
Task *func_801F2CD0_5AEBE0(Task *parent, unsigned char arg1, float x, float y, float z, float scale, float growth, int life, float life_div);
int   func_801F3AF0_5AFA00(Task *task);
void func_801F3AD0_5AF9E0(Task *task, float x, float y, float z);

Task *func_801F2CD0_5AEBE0(Task *parent, unsigned char arg1, float x, float y, float z, float scale, float growth, int life, float life_div)
{
    Task         *task;
    ObjSolid     *solid;
    unsigned int  model;
    unsigned int *dl;

    task = func_80034E08(parent, func_801F2ED0_5AEDE0, 0);
    if (task == NULL) {
        return NULL;
    }
    solid = func_80035EEC(task, 2, 1);
    if (solid == NULL) {
        PLAYER_EFFECT_WORK(task)->done = 1;
        return NULL;
    }
    func_801EE4AC_5AA3BC(task, parent, 0);
    PLAYER_EFFECT_WORK(task)->unk_0c = 1;
    func_801EE4AC_5AA3BC(task, parent, 0);
    PLAYER_EFFECT_WORK(task)->vel[0] = 0.0f;
    PLAYER_EFFECT_WORK(task)->vel[1] = 0.0f;
    PLAYER_EFFECT_WORK(task)->vel[2] = 0.0f;
    PLAYER_EFFECT_WORK(task)->step   = life / life_div;
    PLAYER_EFFECT_WORK(task)->life   = life;
    PLAYER_EFFECT_WORK(task)->growth = growth;
    dl                               = solid->work_w;
    if (arg1 == 0) {
        model = (unsigned int) D_A000640 + 0x40000000;
    } else {
        model = (unsigned int) (D_09000D70_F58A30 + 0x1940) + 0x40000000;
    }
    func_80034680(solid, model, (unsigned int) dl | 0x40000000 | 0x20000000, scale, scale, scale, x, y, z, 0x8000, 0x8000, 0x8000, 0, 0x80, 0x152);
    solid->header.pri = 0xA;
    func_801DC554_598464(0, dl, D_802049C0_5C08D0, 0, 0, 0, 0xE0, 0xD0, 0xB0, PLAYER_EFFECT_WORK(task)->life);
    PLAYER_EFFECT_WORK(task)->seq.tbl   = D_80204AD0_5C09E0;
    PLAYER_EFFECT_WORK(task)->seq.idx   = 0;
    PLAYER_EFFECT_WORK(task)->seq.timer = -1;
    func_801E8890_5A47A0(solid, 0xA, D_80204AD0_5C09E0, &PLAYER_EFFECT_WORK(task)->seq.idx, &PLAYER_EFFECT_WORK(task)->seq.timer);
    return task;
}

void func_801F2ED0_5AEDE0(Task *task, ObjSolid *obj)
{
    PlayerEffectSeq *seq = &PLAYER_EFFECT_WORK(task)->seq;

    PLAYER_EFFECT_WORK(task)->life -= PLAYER_EFFECT_WORK(task)->step;
    if (PLAYER_EFFECT_WORK(task)->life <= 0.0f) {
        func_80034ED4();
        return;
    }
    func_801F3A9C_5AF9AC(task, obj);
    func_801E8890_5A47A0(obj, 0xA, seq->tbl, &seq->idx, &seq->timer);
    func_801DC554_598464(0, obj->work_w, D_802049C0_5C08D0, 0, 0, 0, 0xE0, 0xD0, 0xB0, (unsigned char) PLAYER_EFFECT_WORK(task)->life);
    obj->sx += PLAYER_EFFECT_WORK(task)->growth;
    if (obj->sx < 0.0f) {
        obj->sx = 0.0f;
    }
    obj->sy += PLAYER_EFFECT_WORK(task)->growth;
    if (obj->sy < 0.0f) {
        obj->sy = 0.0f;
    }
    obj->sz += PLAYER_EFFECT_WORK(task)->growth;
    if (obj->sz < 0.0f) {
        obj->sz = 0.0f;
    }
}

void func_801F309C_5AEFAC(Task *parent, unsigned char kind)
{
    Task *effect;

    if (func_801E8C44_5A4B54(parent, kind) == 0 && D_8020CA6C_5C897C == 0) {
        effect = func_80034E08(parent, D_80204868_5C0778[kind], 0);
        if (effect != NULL) {
            func_801EE4AC_5AA3BC(effect, parent, kind);
            PLAYER_EFFECT_WORK(effect)->dir    = 0;
            PLAYER_EFFECT_WORK(effect)->frames = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5AEBE0/D_8020BF80_5C7E90.s")

void func_801F3118_5AF028(Task *task, Obj *obj)
{
    Task     *player = PLAYER_EFFECT_WORK(task)->player_task;
    ObjSolid *model  = (ObjSolid *) player->obj_head;
    Task     *effect;

    switch (PLAYER_EFFECT_WORK(task)->state) {
        case 0:
            if (PLAYER_EFFECT_WORK(task)->frames < 0x14) {
                PLAYER_EFFECT_WORK(task)->frames++;
                if (PLAYER_EFFECT_WORK(task)->dir >= 0) {
                    PLAYER_EFFECT_WORK(task)->dir = -0x19;
                } else {
                    PLAYER_EFFECT_WORK(task)->dir = 0x19;
                }
                effect = func_801F2CD0_5AEBE0(task, 0, 0.0f, 0.0f, 0.0f, model->sx * 0.05 / 0.1f, model->sx * 0.002 / 0.1f, 0x82, 4.0f);
                if (effect != NULL) {
                    func_801EE530_5AA440(model, (ObjSolid *) effect->obj_head, PLAYER_EFFECT_WORK(task)->dir, 0.0f, -45.0f);
                }
            }
            if (PLAYER_WORK(player)->state != 0xF || D_8020CA6C_5C897C != 0) {
                PLAYER_EFFECT_WORK(task)->state++;
            }
            break;
        case 1:
            if (func_801F3AF0_5AFA00(task) == 0) {
                PLAYER_EFFECT_WORK(task)->done = 1;
            }
            break;
    }
}

void func_801F3298_5AF1A8(Task *parent, unsigned char kind)
{
    Task *effect;

    if (func_801E8C44_5A4B54(parent, kind) == 0 && D_8020CA6C_5C897C == 0) {
        effect = func_80034E08(parent, D_80204868_5C0778[kind], 0);
        if (effect != NULL) {
            func_801EE4AC_5AA3BC(effect, parent, kind);
            PLAYER_EFFECT_WORK(effect)->dir    = 0;
            PLAYER_EFFECT_WORK(effect)->frames = 0;
        }
    }
}

void func_801F3314_5AF224(Task *task, Obj *obj)
{
    Task     *player = PLAYER_EFFECT_WORK(task)->player_task;
    ObjSolid *model  = (ObjSolid *) player->obj_head;
    Task     *effect;

    switch (PLAYER_EFFECT_WORK(task)->state) {
        case 0:
            if (PLAYER_EFFECT_WORK(task)->frames < 0x5) {
                PLAYER_EFFECT_WORK(task)->frames++;
                if (PLAYER_EFFECT_WORK(task)->dir >= 0) {
                    PLAYER_EFFECT_WORK(task)->dir = -0x1E;
                } else {
                    PLAYER_EFFECT_WORK(task)->dir = 0x1E;
                }
                effect = func_801F2CD0_5AEBE0(task, 0, 0.0f, 0.0f, 0.0f, model->sx * 0.03 / 0.1f, model->sx * 0.004 / 0.1f, 0xC8, 7.0f);
                if (effect != NULL) {
                    func_801EE530_5AA440(model, (ObjSolid *) effect->obj_head, PLAYER_EFFECT_WORK(task)->dir, 0.0f, 20.0f);
                }
            }
            if (PLAYER_WORK(player)->state != 0x10 || D_8020CA6C_5C897C != 0) {
                PLAYER_EFFECT_WORK(task)->state++;
            }
            break;
        case 1:
            if (func_801F3AF0_5AFA00(task) == 0) {
                PLAYER_EFFECT_WORK(task)->done = 1;
            }
            break;
    }
}

void func_801F3494_5AF3A4(Task *parent, unsigned char kind)
{
    Task *effect;

    if (func_801E8C44_5A4B54(parent, kind) == 0 && D_8020CA6C_5C897C == 0) {
        effect = func_80034E08(parent, D_80204868_5C0778[kind], 0);
        if (effect != NULL) {
            func_801EE4AC_5AA3BC(effect, parent, kind);
            PLAYER_EFFECT_WORK(effect)->unk_0c = 1;
        }
    }
}

void func_801F3510_5AF420(Task *task, Obj *obj)
{
    Task     *player = PLAYER_EFFECT_WORK(task)->player_task;
    ObjSolid *model  = (ObjSolid *) player->obj_head;
    Task     *effect;

    switch (PLAYER_EFFECT_WORK(task)->state) {
        case 0:
            if (--PLAYER_EFFECT_WORK(task)->unk_0c == 0) {
                PLAYER_EFFECT_WORK(task)->unk_0c = 2;
                effect                           = func_801F2CD0_5AEBE0(task, 0, 0.0f, 0.0f, 0.0f, model->sx * 0.08 / 0.1f, model->sx * 0.0 / 0.1f, 0x96, 6.0f);
                if (effect != NULL) {
                    func_801EE530_5AA440(model, (ObjSolid *) effect->obj_head, 0.0f, 0.0f, 0.0f);
                }
            }
            if (PLAYER_WORK(player)->state != 0x33 || D_8020CA6C_5C897C != 0) {
                PLAYER_EFFECT_WORK(task)->state++;
            }
            break;
        case 1:
            if (func_801F3AF0_5AFA00(task) == 0) {
                PLAYER_EFFECT_WORK(task)->done = 1;
            }
            break;
    }
}

void func_801F365C_5AF56C(Task *parent, unsigned char kind)
{
    Task *effect;

    if (func_801E8C44_5A4B54(parent, kind) == 0 && D_8020CA6C_5C897C == 0) {
        effect = func_80034E08(parent, D_80204868_5C0778[kind], 0);
        if (effect != NULL) {
            func_801EE4AC_5AA3BC(effect, parent, kind);
        }
    }
}

void func_801F36C8_5AF5D8(Task *task, Obj *obj)
{
    Task     *player = PLAYER_EFFECT_WORK(task)->player_task;
    ObjSolid *model  = (ObjSolid *) player->obj_head;
    Task     *effect;
    ObjSolid *solid;
    int       i;

    switch (PLAYER_EFFECT_WORK(task)->state) {
        case 0:
            for (i = 0; i < 6; i++) {
                effect = func_801F2CD0_5AEBE0(task, 0, 0.0f, 0.0f, 0.0f, model->sx * 0.02 / 0.1f, model->sx * 0.002 / 0.1f, 0x96, 8.0f);
                if (effect != NULL) {
                    solid = (ObjSolid *) effect->obj_head;
                    func_801EE530_5AA440(model, solid, 0.0f, 0.0f, 0.0f);
                    func_801F3AD0_5AF9E0(effect, D_802050A0_5C0FB0[i][0] * model->sx / 0.1f, 0.0f, D_802050A0_5C0FB0[i][1] * model->sx / 0.1f);
                }
            }
            PLAYER_EFFECT_WORK(task)->state++;
            break;
        case 1:
            if (func_801F3AF0_5AFA00(task) == 0) {
                PLAYER_EFFECT_WORK(task)->done = 1;
            }
            break;
    }
}

void func_801F387C_5AF78C(Task *parent, unsigned char kind)
{
    Task *effect;

    if (func_801E8C44_5A4B54(parent, kind) == 0 && D_8020CA6C_5C897C == 0) {
        effect = func_80034E08(parent, D_80204868_5C0778[kind], 0);
        if (effect != NULL) {
            func_801EE4AC_5AA3BC(effect, parent, kind);
        }
    }
}

void func_801F38E8_5AF7F8(Task *task, Obj *obj)
{
    Task     *player = PLAYER_EFFECT_WORK(task)->player_task;
    ObjSolid *model  = (ObjSolid *) player->obj_head;
    Task     *effect;
    ObjSolid *solid;
    int       i;

    switch (PLAYER_EFFECT_WORK(task)->state) {
        case 0:
            for (i = 6; i < 12; i++) {
                effect = func_801F2CD0_5AEBE0(task, 0, 0.0f, 0.0f, 0.0f, model->sx * 0.04 / 0.1f, model->sx * 0.004 / 0.1f, 0x96, 16.0f);
                if (effect != NULL) {
                    solid = (ObjSolid *) effect->obj_head;
                    func_801EE530_5AA440(model, solid, 0.0f, 0.0f, 0.0f);
                    func_801F3AD0_5AF9E0(effect, D_802050A0_5C0FB0[i][0] * model->sx / 0.1f, 0.0f, D_802050A0_5C0FB0[i][1] * model->sx / 0.1f);
                }
            }
            PLAYER_EFFECT_WORK(task)->state++;
            break;
        case 1:
            if (func_801F3AF0_5AFA00(task) == 0) {
                PLAYER_EFFECT_WORK(task)->done = 1;
            }
            break;
    }
}

void func_801F3A9C_5AF9AC(Task *task, ObjSolid *obj)
{
    obj->tx += PLAYER_EFFECT_WORK(task)->vel[0];
    obj->ty += PLAYER_EFFECT_WORK(task)->vel[1];
    obj->tz += PLAYER_EFFECT_WORK(task)->vel[2];
}

void func_801F3AD0_5AF9E0(Task *task, float x, float y, float z)
{
    PLAYER_EFFECT_WORK(task)->vel[0] = x;
    PLAYER_EFFECT_WORK(task)->vel[1] = y;
    PLAYER_EFFECT_WORK(task)->vel[2] = z;
}

int func_801F3AF0_5AFA00(Task *task)
{
    int   count = 0;
    Task *next  = task->next;

    while (next != NULL) {
        if (task->priority >= next->priority) {
            break;
        }
        next = next->next;
        count++;
    }
    return count;
}
