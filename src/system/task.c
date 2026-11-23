#include "system/task.h"
#include "system/sys.h"
#include "unk.h"
#include "system/wave_uty.h"

extern Task D_80168FB0[80];

// clang-format off

// <<<<< data >>>>>
void *D_8006D320 = NULL;

unsigned short D_8006D324[2] = {
    0x0081, 0x0000,
};

Task *D_8006D328 = D_80168FB0;

void *D_8006D32C = &D_80168FB0[79];

void *D_8006D330 = D_80168FB0;

void *D_8006D334 = NULL;

void *D_8006D338 = NULL;

void *D_8006D33C = D_80168FB0;

void *D_8006D340 = &D_80168FB0[79];

void *D_8006D344 = D_80168FB0;

void *D_8006D348 = NULL;

void *D_8006D34C = NULL;

// <<<<< bss >>>>>
Task           D_80168FB0[80];
unsigned short D_8016DAB0;
short          D_8016DAB2;
Task          *D_8016DAB4;
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034680.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034710.s")

void func_80034734(void)
{
    Task          *blocker = NULL;
    unsigned short i;

    D_8016DAB4 = D_8006D328;

    // fake?
    if (D_8016DAB4 == NULL) {
    }

    do {
        if (blocker != NULL) {
            if (blocker->priority < D_8016DAB4->priority) {
                continue;
            }
            blocker = NULL;
        }

        if ((D_8016DAB4->status & g_sys_real.task_disabled_status) & TASK_STATUS_UPDATE_MASK) {
            blocker = D_8016DAB4;
            continue;
        }

        // fake?
        i = D_8016DAB4->priority;
        while (i-- > 0) {
        }

        // fake?    
        if (D_8016DAB4->priority == 5) {
        }

        // fake?
        if (D_8016DAB4->priority == 6) {
        }

        func_8001481C(D_8016DAB4);

        if (D_8016DAB4->exec[0] != NULL && !((unsigned int) D_8016DAB4->exec[0] & 0x800000)) {
            (*D_8016DAB4->exec[0])(D_8016DAB4, D_8016DAB4->obj_head);
        }

        if (D_8016DAB4->exec[1] != NULL && !((unsigned int) D_8016DAB4->exec[1] & 0x800000)) {
            (*D_8016DAB4->exec[1])(D_8016DAB4, D_8016DAB4->obj_head);
        }

        if (D_8016DAB4->exec[2] != NULL && !((unsigned int) D_8016DAB4->exec[2] & 0x800000)) {
            (*D_8016DAB4->exec[2])(D_8016DAB4, D_8016DAB4->obj_head);
        }
    } while ((D_8016DAB4 = D_8016DAB4->next) != NULL);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_8003488C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034A10.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034AB8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034B24.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034B58.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034C4C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034C84.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034CBC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034D24.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034DD8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034E08.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034E38.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034E68.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034E98.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034ED4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034EF8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034F20.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80034F44.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035020.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035044.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035064.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035094.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800350C4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035194.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800351B4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035204.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035214.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_8003521C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_8003522C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035234.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035244.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_8003524C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800352AC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800352EC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035314.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035344.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035384.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035398.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800353A4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800353B4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800353BC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800353F8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035430.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_8003546C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035490.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800354B4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800354C0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_8003555C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800355F4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035690.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035728.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800357BC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_80035854.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/task/func_800358E8.s")

Task *func_80035964(Task *task, unsigned int model, unsigned int glist, float tx, float ty, float tz,
    unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz,
    unsigned short wave0, unsigned short wave1)
{
    ObjSolid *solid;

    if (task != NULL) {
        solid = (ObjSolid *) task->obj_tail;

        if (solid != NULL) {
            solid->AModel             = model;
            solid->init_glist         = glist;
            solid->tx                 = tx;
            solid->ty                 = ty;
            solid->tz                 = tz;
            solid->rx                 = rx;
            solid->ry                 = ry;
            solid->rz                 = rz;
            solid->sx                 = sx;
            solid->sy                 = sy;
            solid->sz                 = sz;
            solid->SegWave[0].wave_no = wave0;
            solid->SegWave[1].wave_no = wave1;
            solid->SegWave[2].wave_no = g_sys->unk_c2d90;
            solid->SegWave[3].wave_no = 0;
            solid->SegWave[4].wave_no = 0;
            solid->SegWave[5].wave_no = 0;
            func_80014218(solid);
            solid->hidden       = 0;
            solid->disabled     = 0;
            solid->sibling      = NULL;
            solid->child        = NULL;
            solid->param        = 0;
            solid->param_fx8    = 0;
            solid->time         = 0.0f;
            solid->scratch_f[0] = 0.0f;
            solid->scratch_f[1] = 0.0f;
            solid->blend        = 0.0f;
        }
    }

    return task;
}

Task *func_80035A5C(Task *task, unsigned int model, unsigned int glist, float tx, float ty, float tz,
    unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz,
    unsigned short wave0, unsigned short wave2, unsigned short wave1)
{
    ObjSolid *solid;

    if (task != NULL) {
        solid = (ObjSolid *) task->obj_tail;

        if (solid != NULL) {
            solid->AModel             = model;
            solid->init_glist         = glist;
            solid->tx                 = tx;
            solid->ty                 = ty;
            solid->tz                 = tz;
            solid->rx                 = rx;
            solid->ry                 = ry;
            solid->rz                 = rz;
            solid->sx                 = sx;
            solid->sy                 = sy;
            solid->sz                 = sz;
            solid->SegWave[0].wave_no = wave0;
            solid->SegWave[1].wave_no = wave1;
            solid->SegWave[2].wave_no = wave2;
            solid->SegWave[3].wave_no = 0;
            solid->SegWave[4].wave_no = 0;
            solid->SegWave[5].wave_no = 0;
            func_80014218(solid);
            solid->hidden       = 0;
            solid->disabled     = 0;
            solid->sibling      = NULL;
            solid->child        = NULL;
            solid->param        = 0;
            solid->param_fx8    = 0;
            solid->time         = 0.0f;
            solid->scratch_f[0] = 0.0f;
            solid->scratch_f[1] = 0.0f;
            solid->blend        = 0.0f;
        }
    }

    return task;
}
