#include "sys/task.h"
#include "sys/sys.h"
#include "sys/obj_alloc.h"
#include "unk.h"
#include "sys/wave_uty.h"

Task *func_80034A10(Task *task);
Task *func_80034B24(void (*exec)(Task *, Obj *), unsigned short priority);
Task *func_80034B58(Task *prev, void (*exec)(Task *, Obj *), unsigned short priority);
Task *func_80034C4C(void (*exec)(Task *, Obj *), unsigned short priority);
Task *func_80034C84(void (*exec)(Task *, Obj *), unsigned short priority);
Task *func_80034CBC(Task *prev, void (*exec)(Task *, Obj *), short kind, unsigned short priority);
Task *func_80034D24(Task *task);
void  func_80034F44(Task *task);
void  func_80035044(Task *task);
void  func_800350C4(Task *task);
void  func_80035194(Task *task, Obj *obj);
void  func_800351B4(Task *task);
void  func_80035314(Task *task, void (*exec)(Task *, Obj *));
void  func_800353F8(Task *task, void (*exec)(Task *, Obj *), short timer);
void  func_80035430(Task *task, Obj *obj);
void  func_80035490(Task *task);
void  func_800354B4(Task *task, Obj *obj);
Task *func_8003555C(Task *prev, void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1, unsigned short priority);
Task *func_80035690(Task *prev, void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1, unsigned short priority);
Task *func_800357BC(Task *prev, void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1);
Task *func_800358E8(Task *prev, void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1);
Task *func_80035964(Task *task, unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1);

extern Task D_80168FB0[80];

// clang-format off

// <<<<< data >>>>>
void *D_8006D320 = NULL;

unsigned short D_8006D324[2] = {
    0x0081, 0x0000,
};

TaskList g_task_list = {
    D_80168FB0, &D_80168FB0[79], D_80168FB0, 0, NULL,
};

TaskList g_task_list_init = {
    D_80168FB0, &D_80168FB0[79], D_80168FB0, 0, NULL,
};

// <<<<< bss >>>>>
Task           D_80168FB0[80];
unsigned short D_8016DAB0;
unsigned short D_8016DAB2;
Task          *D_8016DAB4;

// clang-format on

void func_80034680(ObjSolid *solid, unsigned int model, unsigned int glist, float sx, float sy, float sz,
    float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz,
    unsigned short wave0, unsigned short wave1, unsigned short wave2)
{
    solid->init_glist         = glist;
    solid->AModel             = model;
    solid->sx                 = sx;
    solid->sy                 = sy;
    solid->sz                 = sz;
    solid->tx                 = tx;
    solid->ty                 = ty;
    solid->tz                 = tz;
    solid->rx                 = rx;
    solid->ry                 = ry;
    solid->rz                 = rz;
    solid->SegWave[0].wave_no = wave0;
    solid->SegWave[1].wave_no = wave1;
    solid->SegWave[2].wave_no = wave2;
    solid->SegWave[3].wave_no = 0;
    solid->SegWave[4].wave_no = 0;
    solid->SegWave[5].wave_no = 0;
    func_80014218(solid);
}

void func_80034710(void)
{
    Task *task = g_task_list.head;

    if (task != NULL) {
        do {
            task = task->next;
        } while (task != NULL);
    }
}

void func_80034734(void)
{
    Task          *blocker = NULL;
    unsigned short i;

    D_8016DAB4 = g_task_list.head;

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

#ifdef NON_MATCHING
void func_8003488C(char *arg0)
{
    unsigned short i;

    g_task_list   = g_task_list_init;
    D_8016DAB4    = g_task_list.head;
    D_8006D324[0] = 0x81;

    func_80034A10(&D_80168FB0[0]);
    g_task_list.free  = func_80034A10(&D_80168FB0[1]);
    g_task_list.count = 0;

    for (i = 1; i < 0x4F; i++) {
        D_80168FB0[i].next = func_80034A10(&D_80168FB0[i + 1]);
    }

    D_80168FB0[0].priority = 0;
    D_80168FB0[0].next     = NULL;
    D_80168FB0[0].prev     = &D_80168FB0[0];
    D_80168FB0[0].exec[0]  = NULL;
    D_80168FB0[0].exec[2]  = NULL;
    D_80168FB0[0].status   = 0;
    D_80168FB0[0].obj_head = NULL;
    D_80168FB0[0].obj_tail = NULL;

    D_80168FB0[79].priority = 0;
    D_80168FB0[79].next     = NULL;

    D_80168FB0[0].unk_48  = 0;
    D_80168FB0[0].unk_3c  = 0;
    D_80168FB0[0].unk_3e  = 0;
    D_80168FB0[0].unk_40  = 0;
    D_80168FB0[0].unk_42  = 0;
    D_80168FB0[0].unk_44  = 0;
    D_80168FB0[0].unk_34  = 0;
    D_80168FB0[0].unk_38  = 0;
    D_80168FB0[0].unk_30  = 0;
    D_80168FB0[0].unk_4c  = 0;
    D_80168FB0[0].unk_4e  = 0;
    D_80168FB0[0].unk_50  = 0;
    D_80168FB0[0].unk_52  = 0;
    D_80168FB0[0].unk_54  = 0;
    D_80168FB0[0].unk_58  = 0;
    D_80168FB0[0].exec[1] = (void (*)(Task *, Obj *)) arg0;

    D_8006D320 = NULL;
    D_8016DAB2 = D_8016DAB0 = 0;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/task/func_8003488C.s")
#endif

Task *func_80034A10(Task *task)
{
    int i;

    task->timer        = 0;
    task->status       = task->timer;
    task->prev         = NULL;
    task->next         = NULL;
    task->prev_exec    = NULL;
    task->exec[2]      = NULL;
    task->exec[1]      = NULL;
    task->exec[0]      = NULL;
    task->obj_head     = NULL;
    task->obj_tail     = NULL;
    task->priority     = 0;
    task->wave.wave_no = 0;
    task->wave.data    = 0;
    task->unk_48       = 0;
    task->unk_3c       = 0;
    task->unk_3e       = 0;
    task->unk_40       = 0;
    task->unk_42       = 0;
    task->unk_44       = 0;
    task->unk_34       = 0;
    task->unk_38       = 0;
    task->unk_30       = 0;
    task->unk_4c       = 0;
    task->unk_4e       = 0;
    task->unk_50       = 0;
    task->unk_52       = 0;
    task->unk_54       = 0;
    task->unk_58       = 0;

    i = 0;
    do {
        task->work[i] = 0;
        i++;
    } while (i < 0x25);

    return task;
}

Task *func_80034AB8(Task *prev, void (*exec)(Task *, Obj *), unsigned char count)
{
    Task *task = func_80034B58(prev, exec, 0);

    if (task == NULL) {
        return NULL;
    }

    if (task != NULL) {
        if (func_80035DFC(task, 2, count) == NULL) {
            func_80035044(task);
            return NULL;
        }
    }

    D_8006D320 = task;
    return task;
}

Task *func_80034B24(void (*exec)(Task *, Obj *), unsigned short priority) { return func_80034B58(D_8016DAB4, exec, priority); }

#ifdef NON_MATCHING
Task *func_80034B58(Task *prev, void (*exec)(Task *, Obj *), unsigned short priority)
{
    Task *next;
    Task *after;

    if (g_task_list.free != NULL) {
        g_task_list.count++;
        next = prev->next;
        if (prev->next != NULL) {
            after = prev->next;
        } else {
            after = g_task_list.head;
        }

        prev->next       = g_task_list.free;
        g_task_list.free = g_task_list.free->next;

        func_80034A10(prev->next);
        prev->next->next = next;
        prev->next->prev = prev;
        after->prev      = prev->next;

        prev->next->priority = prev->priority + 1;
        prev->next->exec[1]  = exec;

        prev->next->wave.wave_no = priority;
        prev->next->wave.data    = func_800141C4(priority);
        prev->next->status       = D_8006D324[0];

        return prev->next;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/task/func_80034B58.s")
#endif

Task *func_80034C4C(void (*exec)(Task *, Obj *), unsigned short priority)
{
    return func_80034CBC(D_8016DAB4, exec, 1, priority);
}

Task *func_80034C84(void (*exec)(Task *, Obj *), unsigned short priority)
{
    return func_80034CBC(D_8016DAB4, exec, 2, priority);
}

Task *func_80034CBC(Task *prev, void (*exec)(Task *, Obj *), short kind, unsigned short priority)
{
    Task *task = func_80034B58(prev, exec, priority);

    if (task == NULL) {
        return NULL;
    }

    if (task != NULL) {
        if (func_80035DFC(task, kind, 1) == NULL) {
            func_80035044(task);
            return NULL;
        }
    }

    return task;
}

#ifdef NON_MATCHING
Task *func_80034D24(Task *task)
{
    Task          *before;
    Task          *last;
    Task          *first = NULL;
    Task          *next;
    unsigned short pri;
    Task          *old_prev;

    if (task == NULL) {
        return NULL;
    }

    next = task->next;
    if (next != NULL) {
        pri = next->priority;
        if (pri >= task->priority) {
            do {
                last = next;
                if (first == NULL && pri == task->priority) {
                    first  = next;
                    before = next->prev;
                }
                next = next->next;
                if (next == NULL) {
                    break;
                }
                pri = next->priority;
            } while (pri >= task->priority);

            if (first != NULL) {
                old_prev     = task->prev;
                last->next   = task;
                task->prev   = last;
                before->next = next;
                if (next != NULL) {
                    next->prev = before;
                }
                if (old_prev == task) {
                    g_task_list.head = first;
                    first->prev      = first;
                } else {
                    old_prev->next = first;
                    first->prev    = old_prev;
                }
            }
        }
    }
    return task;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/task/func_80034D24.s")
#endif

Task *func_80034DD8(void (*exec)(Task *, Obj *), unsigned short priority)
{
    return func_80034D24(func_80034B24(exec, priority));
}

Task *func_80034E08(Task *prev, void (*exec)(Task *, Obj *), unsigned short priority)
{
    return func_80034D24(func_80034B58(prev, exec, priority));
}

Task *func_80034E38(void (*exec)(Task *, Obj *), unsigned short priority)
{
    return func_80034D24(func_80034C4C(exec, priority));
}

Task *func_80034E68(void (*exec)(Task *, Obj *), unsigned short priority)
{
    return func_80034D24(func_80034C84(exec, priority));
}

Task *func_80034E98(Task *prev, void (*exec)(Task *, Obj *), short kind, unsigned short priority)
{
    return func_80034D24(func_80034CBC(prev, exec, kind, priority));
}

void func_80034ED4(void)
{
    func_80034EF8(D_8016DAB4);
}

void func_80034EF8(Task *task)
{
    func_80034F44(task);
    func_80035044(task);
}

void func_80034F20(void)
{
    func_80034F44(D_8016DAB4);
}

#ifdef NON_MATCHING
void func_80034F44(Task *task)
{
    Task          *cur;
    Task          *first;
    Task          *after;
    unsigned short pri;

    if (task->next != NULL) {
        first = task->next;
        pri   = task->priority;
        cur   = task;
        if (pri < task->next->priority) {
            do {
                g_task_list.count--;
                cur = cur->next;
                func_800351B4(cur);
                cur->exec[0] = NULL;
                cur->exec[1] = func_800354B4;
                cur->exec[2] = NULL;
                cur->prev    = NULL;
                if (cur->next != NULL) {
                    after = cur->next;
                } else {
                    after = g_task_list.head;
                }
            } while (pri < after->priority);

            after->prev      = task;
            task->next       = cur->next;
            cur->next        = g_task_list.free;
            g_task_list.free = first;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/task/func_80034F44.s")
#endif

void func_80035020(void)
{
    func_80035044(D_8016DAB4);
}

void func_80035044(Task *task)
{
    func_800350C4(task);
}

void func_80035064(void)
{
    func_800362DC(D_8016DAB4);
    func_80035044(D_8016DAB4);
}

void func_80035094(Task *task)
{
    func_800362DC(D_8016DAB4);
    func_800350C4(task);
}

#ifdef NON_MATCHING
void func_800350C4(Task *task)
{
    Task *after;

    if (task->next != NULL) {
        after = task->next;
    } else {
        after = g_task_list.head;
    }

    if (task->priority >= after->priority) {
        func_800351B4(task);
        task->exec[0]    = NULL;
        task->exec[1]    = func_800354B4;
        task->exec[2]    = NULL;
        after->prev      = task->prev;
        task->prev->next = task->next;
        task->next       = g_task_list.free;
        g_task_list.free = task;
        g_task_list.count--;
        if (task == D_8016DAB4) {
            D_8016DAB4 = task->prev;
        }
        task->prev = NULL;
    } else {
        task->exec[1] = func_80035194;
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/task/func_800350C4.s")
#endif

void func_80035194(Task *task, Obj *obj)
{
    func_800350C4(task);
}

void func_800351B4(Task *task)
{
    short i;

    func_80036260(task);
    task->status = 1;

    for (i = 0; i < 0x25; i++) {
        task->work[i] = 0;
    }
}

void func_80035204(void (*exec)(Task *, Obj *))
{
    D_8016DAB4->exec[0] = exec;
}

void func_80035214(Task *task, void (*exec)(Task *, Obj *))
{
    task->exec[0] = exec;
}

void func_8003521C(void (*exec)(Task *, Obj *))
{
    D_8016DAB4->exec[1] = exec;
}

void func_8003522C(Task *task, void (*exec)(Task *, Obj *))
{
    task->exec[1] = exec;
}

void func_80035234(void (*exec)(Task *, Obj *))
{
    D_8016DAB4->exec[2] = exec;
}

void func_80035244(Task *task, void (*exec)(Task *, Obj *))
{
    task->exec[2] = exec;
}

void func_8003524C(void (*exec)(Task *, Obj *))
{
    D_8016DAB4->prev_exec = D_8016DAB4->exec[1];
    D_8016DAB4->exec[1]   = exec;
    D_8016DAB4->exec[1](D_8016DAB4, D_8016DAB4->obj_head);
    D_8016DAB4->exec[1] = D_8016DAB4->prev_exec;
}

void func_800352AC(Task *task, void (*exec)(Task *, Obj *))
{
    task->prev_exec = task->exec[1];
    task->exec[1]   = exec;
    exec(task, task->obj_head);
    task->exec[1] = task->prev_exec;
}

void func_800352EC(void (*exec)(Task *, Obj *))
{
    func_80035314(D_8016DAB4, exec);
}

void func_80035314(Task *task, void (*exec)(Task *, Obj *))
{
    task->exec[1] = exec;
    exec(task, D_8016DAB4->obj_head);
}

void func_80035344(void)
{
    D_8016DAB4->exec[1] = D_8016DAB4->prev_exec;
    D_8016DAB4->exec[1](D_8016DAB4, D_8016DAB4->obj_head);
}

void func_80035384(void)
{
    D_8016DAB4->exec[1] = D_8016DAB4->prev_exec;
}

void func_80035398(Task *task)
{
    task->exec[1] = task->prev_exec;
}

void func_800353A4(void (*exec)(Task *, Obj *))
{
    D_8016DAB4->prev_exec = exec;
}

void func_800353B4(Task *task, void (*exec)(Task *, Obj *))
{
    task->prev_exec = exec;
}

void func_800353BC(void (*exec)(Task *, Obj *), short timer)
{
    func_800353F8(D_8016DAB4, exec, timer);
}

void func_800353F8(Task *task, void (*exec)(Task *, Obj *), short timer)
{
    task->timer = timer;
    func_800353B4(task, exec);
    func_8003522C(task, func_80035430);
}

void func_80035430(Task *task, Obj *obj)
{
    task->timer--;

    if (task->timer <= 0) {
        func_80035384();
    }
}

void func_8003546C(void)
{
    func_80035490(D_8016DAB4);
}

void func_80035490(Task *task)
{
    func_8003522C(task, func_800354B4);
}

void func_800354B4(Task *task, Obj *obj)
{
}

Task *func_800354C0(void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1, unsigned short priority)
{
    return func_8003555C(D_8016DAB4, exec, model, glist, tx, ty, tz, rx, ry, rz, sx, sy, sz, wave0, wave1, priority);
}

Task *func_8003555C(Task *prev, void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1, unsigned short priority)
{
    Task *task = func_80034E98(prev, exec, 2, priority);

    func_80035964(task, model, glist, tx, ty, tz, rx, ry, rz, sx, sy, sz, wave0, wave1);
    return task;
}

Task *func_800355F4(void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1, unsigned short priority)
{
    return func_80035690(D_8016DAB4, exec, model, glist, tx, ty, tz, rx, ry, rz, sx, sy, sz, wave0, wave1, priority);
}

Task *func_80035690(Task *prev, void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1, unsigned short priority)
{
    Task *task = func_80034CBC(prev, exec, 2, priority);

    func_80035964(task, model, glist, tx, ty, tz, rx, ry, rz, sx, sy, sz, wave0, wave1);
    return task;
}

Task *func_80035728(void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1)
{
    return func_800357BC(D_8016DAB4, exec, model, glist, tx, ty, tz, rx, ry, rz, sx, sy, sz, wave0, wave1);
}

Task *func_800357BC(Task *prev, void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1)
{
    Task *task = func_80034CBC(prev, exec, 2, wave0);

    func_80035964(task, model, glist, tx, ty, tz, rx, ry, rz, sx, sy, sz, wave0, wave1);
    return task;
}

Task *func_80035854(void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1)
{
    return func_800358E8(D_8016DAB4, exec, model, glist, tx, ty, tz, rx, ry, rz, sx, sy, sz, wave0, wave1);
}

Task *func_800358E8(Task *prev, void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1)
{
    return func_80034D24(func_800357BC(prev, exec, model, glist, tx, ty, tz, rx, ry, rz, sx, sy, sz, wave0, wave1));
}

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
