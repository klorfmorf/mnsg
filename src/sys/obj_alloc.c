#include "sys/obj_alloc.h"
#include "sys/task.h"
#include "sys/sys.h"
#include "sys/obj.h"
#include "sys/pal.h"

Obj *func_80035FDC(ObjSolid *solid);
void func_80036308(Obj *obj);
void func_800367E4(ObjSolid *solid);
Obj *func_80035D8C(short kind);
Obj *func_80036058(Task *task, unsigned char count);
void func_80035B88(void);
void func_80035BF8(void);
void func_80035C7C(void);
void func_80035D00(void);

// clang-format off

// <<<<< data >>>>>

// Capacity of each object kind, indexed by kind.
unsigned short D_8006D350[8] = {
    0, 24, 192, 2, 64, 2, 0, 0,
};

// <<<<< bss >>>>>
Obj  *D_8016DAC0[6];
short D_8016DAD8[6];

// clang-format on

void func_80035B50(void)
{
    func_80035B88();
    func_80035BF8();
    func_80035C7C();
    func_80035D00();
}

void func_80035B88(void)
{
    unsigned short i;

    D_8016DAC0[1] = &g_sys_real.sprites[0].header;
    for (i = 0; i < 24; i++) {
        g_sys_real.sprites[i].header.next = &g_sys_real.sprites[i + 1].header;
    }
    D_8016DAD8[1]                      = 0;
    g_sys_real.sprites[23].header.next = NULL;
}

void func_80035BF8(void)
{
    unsigned short i;

    D_8016DAC0[2] = &g_sys_real.solids[0].header;
    for (i = 0; i < 192; i++) {
        g_sys_real.solids[i].header.next = &g_sys_real.solids[i + 1].header;
    }
    D_8016DAD8[2]                      = 0;
    g_sys_real.solids[191].header.next = NULL;
}

void func_80035C7C(void)
{
    unsigned short i;

    D_8016DAC0[3] = &g_sys_real.mojis[0].header;
    for (i = 0; i < 2; i++) {
        g_sys_real.mojis[i].header.next = &g_sys_real.mojis[i + 1].header;
    }
    D_8016DAD8[3]                   = 0;
    g_sys_real.mojis[1].header.next = NULL;
}

void func_80035D00(void)
{
    unsigned short i;

    D_8016DAC0[5] = &g_sys_real.gbgs[0].header;
    for (i = 0; i < 2; i++) {
        g_sys_real.gbgs[i].header.next = &g_sys_real.gbgs[i + 1].header;
    }
    D_8016DAD8[5] = 0;
    // The original clears the last moji link here, not the last gbg link.
    g_sys_real.mojis[1].header.next = NULL;
}

void func_80035D84(void)
{
}

#ifdef NON_MATCHING
Obj *func_80035D8C(short kind)
{
    Obj  *obj;
    Obj **head = &D_8016DAC0[kind];

    obj = *head;
    if (obj != NULL) {
        *head     = obj->next;
        obj->next = NULL;
        obj->kind &= 0x7F;
        D_8016DAD8[kind]++;
        return obj;
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80035D8C.s")
#endif

void *func_80035DFC(Task *task, short kind, unsigned char count)
{
    Obj           *first = NULL;
    Obj           *obj;
    Obj           *head;
    unsigned short i;

    if (D_8006D350[kind] - D_8016DAD8[kind] < count) {
        return NULL;
    }
    for (i = 0; i < count; i++) {
        obj = func_80035D8C(kind);
        if (obj == NULL) {
            return NULL;
        }
        if (first == NULL) {
            first = obj;
        }
        head = task->obj_head;
        if (task->obj_head == NULL) {
            task->obj_tail = obj;
            task->obj_head = obj;
        } else {
            task->obj_head = obj;
            obj->next      = head;
        }
    }
    return first;
}

void *func_80035EEC(Task *task, short kind, unsigned char count)
{
    Obj           *first = NULL;
    Obj           *obj;
    unsigned short i;

    if (D_8006D350[kind] - D_8016DAD8[kind] < count) {
        return NULL;
    }
    for (i = 0; i < count; i++) {
        obj = func_80035D8C(kind);
        if (obj == NULL) {
            return NULL;
        }
        if (first == NULL) {
            first = obj;
        }
        if (task->obj_head == NULL) {
            task->obj_head = obj;
        } else {
            task->obj_tail->next = obj;
        }
        task->obj_tail = obj;
    }
    return first;
}

Obj *func_80035FDC(ObjSolid *solid)
{
    Obj  *old;
    short kind = solid->header.kind & 0x7F;

    old                = solid->header.next;
    solid->header.next = D_8016DAC0[kind];
    D_8016DAC0[kind]   = &solid->header;
    D_8016DAD8[kind]--;
    if (kind == 2) {
        func_800364FC(solid);
    }
    return old;
}

#ifdef NON_MATCHING
Obj *func_80036058(Task *task, unsigned char count)
{
    Obj           *obj;
    unsigned short i;

    if (task->obj_head == NULL) {
        return NULL;
    }
    obj = task->obj_head;
    if (obj == NULL) {
        return NULL;
    }
    task->obj_head = func_80035FDC(obj);
    if (task->obj_head == NULL) {
        task->obj_tail = NULL;
        func_80036308(obj);
        if (count != 1) {
            return NULL;
        }
        return obj;
    }
    func_80036308(obj);
    for (i = 1; i < count; i++) {
        obj            = task->obj_head;
        task->obj_head = func_80035FDC(obj);
        if (task->obj_head == NULL) {
            task->obj_tail = NULL;
            func_80036308(obj);
            return NULL;
        }
        func_80036308(obj);
    }
    return obj;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80036058.s")
#endif

#ifdef NON_MATCHING
Obj *func_80036158(Task *task, Obj *target, unsigned char count)
{
    Obj *prev = task->obj_head;
    Obj *next;
    Obj *obj;

    if (prev == NULL) {
        return NULL;
    }
    if (prev != target) {
        while (prev != NULL && prev->next != target) {
            prev = prev->next;
        }
        if (prev == NULL) {
            return NULL;
        }
    } else {
        prev = NULL;
    }
    obj = target;
    while (count--) {
        next = func_80035FDC(obj);
        func_80036308(obj);
        obj = next;
        if (prev != NULL) {
            prev->next = next;
        } else {
            task->obj_head = next;
        }
        if (next == NULL) {
            task->obj_tail = prev;
            if (count != 0) {
                return NULL;
            }
        }
    }
    return obj;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_80036158.s")
#endif

int func_80036260(Task *task)
{
    Obj *obj;

    if (task->obj_head == NULL) {
        return 0;
    }
    obj = task->obj_head;
    while (obj != NULL) {
        task->obj_head = func_80035FDC(obj);
        if (task->obj_head == NULL) {
            task->obj_tail = NULL;
            func_80036308(obj);
            return 0;
        }
        func_80036308(obj);
        obj = task->obj_head;
    }
}

Obj *func_800362DC(Task *task)
{
    Obj *obj;

    for (obj = task->obj_head; obj != NULL; obj = obj->next) {
        obj->kind |= 0x80;
    }
    return obj;
}

void func_80036308(Obj *obj)
{
    if (obj != NULL) {
        switch (obj->kind & 0x7F) {
            case 1:
                func_80007C90(obj);
                func_8000A228(obj);
                break;
            case 2:
                func_8000A5C4(obj);
                break;
            case 3:
                func_8000A394(obj);
                break;
            case 4:
                break;
        }
    }
}

int func_80036388(ObjSolid *solid, ObjSolid *node)
{
    ObjSolid *prev;
    ObjSolid *cur;

    if (solid == NULL || node == NULL) {
        return 0;
    }
    prev = cur = solid->child;
    cur        = cur->sibling;
    while (cur != node) {
        prev = cur;
        cur  = cur->sibling;
    }
    if (cur == NULL) {
        return 0;
    }
    prev->sibling = node->sibling;
    node->sibling = solid->child;
    solid->child  = node;
    return 1;
}

int func_800363F4(ObjSolid *solid, ObjSolid *node)
{
    ObjSolid *prev;
    ObjSolid *cur;

    if (solid == NULL || node == NULL) {
        return 0;
    }
    prev = cur = solid->sibling;
    while (cur != node) {
        prev = cur;
        cur  = cur->sibling;
    }
    prev->sibling  = node->sibling;
    node->sibling  = solid->sibling;
    solid->sibling = node;
    return 1;
}

ObjSolid *func_80036448(ObjSolid *solid)
{
    ObjSolid *obj;

    D_8016DAB0++;
    if (D_8016DAB2 < D_8016DAB0) {
        D_8016DAB2 = D_8016DAB0;
    }
    if (D_8006D320 != NULL) {
        if (func_80036058(D_8006D320, 1) == NULL) {
            // A stripped debug message was probably here.
        }
    } else if (D_8006D350[2] - D_8016DAD8[2] <= 0) {
        return NULL;
    }
    obj = func_80035D8C(2);
    if (obj != NULL) {
        return obj;
    }
    return NULL;
}

#ifdef NON_MATCHING
int func_800364FC(ObjSolid *solid)
{
    ObjSolid      *cur = solid;
    ObjSolid      *old;
    unsigned short depth = 0;
    int            i;
    ObjSolid      *stack[32];

    if (solid == NULL) {
        return 0;
    }
    i = 0;
    while (i < 32) {
        stack[i] = NULL;
        i++;
    }
    while (cur != NULL) {
        if (depth < 0 || depth >= 32) {
            return 0;
        }
        if (cur->child == NULL && cur->sibling == NULL) {
            if (cur == solid) {
                break;
            }
            func_800367E4(cur);
            old = cur;
            cur = stack[--depth];
            if (old == cur->child) {
                cur->child = NULL;
            }
            if (old == cur->sibling) {
                cur->sibling = NULL;
            }
        } else if (cur->sibling == NULL) {
            stack[depth++] = cur;
            cur            = cur->child;
        } else if (cur->child == NULL) {
            stack[depth++] = cur;
            cur            = cur->sibling;
        } else {
            stack[depth++] = cur;
            cur            = cur->child;
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_alloc/func_800364FC.s")
#endif

void func_80036660(ObjSolid *solid)
{
    Obj  *obj = solid->header.next;
    short kind;

    while (obj != NULL) {
        solid->header.next = obj->next;
        kind               = obj->kind & 0x7F;
        obj->next          = D_8016DAC0[kind];
        D_8016DAC0[kind]   = obj;
        D_8016DAD8[kind]--;
        func_80036308(obj);
        obj = solid->header.next;
    }
    kind               = solid->header.kind & 0x7F;
    solid->header.next = D_8016DAC0[kind];
    D_8016DAC0[kind]   = &solid->header;
    D_8016DAD8[2]--;
    func_80036308(&solid->header);
}

int func_8003674C(ObjSolid *solid)
{
    ObjSolid *child = solid->child;

    solid->child = NULL;
    if (child != NULL) {
        if (func_800364FC(child) == 0) {
            return 0;
        }
        func_800367E4(child);
    }
    return 1;
}

int func_80036798(ObjSolid *solid)
{
    ObjSolid *sibling = solid->sibling;

    solid->sibling = NULL;
    if (sibling != NULL) {
        if (func_800364FC(sibling) == 0) {
            return 0;
        }
        func_800367E4(sibling);
    }
    return 1;
}

void func_800367E4(ObjSolid *solid)
{
    if (solid != NULL) {
        func_80036660(solid);
        D_8016DAB0--;
        if (D_8006D320 != NULL) {
            func_80035DFC(D_8006D320, 2, 1);
        }
    }
}
