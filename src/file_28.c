#include "enemy/5D1B10.h"
#include "common.h"
#include "enemy/file_12.h"
#include "sys/sd_location.h"
#include "sys/task.h"
#include "douchu/58E2D0.h"
#include "unk.h"

void func_08000150_6B30F0(Task *task, ObjSolid *obj);
void func_0800011C_6B30BC(Task *task, ObjSolid *obj);
void func_080000C4_6B3064(Task *task, ObjSolid *obj);
void func_08000268_6B3208(Task *task, ObjSolid *obj);

void func_08000000_6B2FA0(Task *task, ObjSolid *obj)
{
    ENEMY_WORK(task)->flags_04 = 0x806008A0;
    ENEMY_WORK(task)->flags_08 |= 0x8000;
    ENEMY_WORK(task)->ebuf[6].u = ENEMY_WORK(task)->ebuf[0].u;
    ENEMY_WORK(task)->col_entry = 0;
    if (ENEMY_WORK(task)->ebuf[6].b[2] != 0) {
        // "Setting a pot with an item inside."
        PRINTF_DEAD(("ブツ入りの壷をセットします。\n"));
        ENEMY_WORK(task)->flags_04 |= 0x6C00300;
    }
    (*func_80216E1C_5D22EC)(task, 0);
    obj->sx = obj->sy = obj->sz = 0.25f;
    (*func_80218D7C_5D424C)(task, 0x19, 0x3C, 0);
    (*func_8021C654_5D7B24)(task);
    (*func_8003521C)((void (*)(Task *, Obj *)) func_080000C4_6B3064);
}

void func_080000C4_6B3064(Task *task, ObjSolid *obj)
{
    if (ENEMY_WORK(task)->flags_0c & 1) {
        // "The pot was attacked."
        PRINTF_DEAD(("壷は攻撃されました。\n"));
        (*func_8000F420)(0x26E, D_8020CBF0_5C8B00, obj, 800.0f);
        (*func_8003521C)((void (*)(Task *, Obj *)) func_0800011C_6B30BC);
    }
}

void func_0800011C_6B30BC(Task *task, ObjSolid *obj)
{
    (*func_8003521C)((void (*)(Task *, Obj *)) func_08000150_6B30F0);
}

void func_08000150_6B30F0(Task *task, ObjSolid *obj)
{
    int            i;
    unsigned short angle;

    obj->sx = obj->sy = obj->sz = 0.25f;
    i                           = 0;
    do {
        angle = (unsigned short) (0x400 / ENEMY_WORK(task)->ebuf[6].b[1]) * i;
        (*func_8021DDE8_5D92B8)(task, D_802287C0_5E3C90[ENEMY_WORK(task)->ebuf[1].u - 1], 9, 0.0f, 10.0f, 0.0f, angle);
        ENEMY_WORK(task)->ebuf[6].b[0]++;
        // "The pot was destroyed."
        PRINTF_DEAD(("壷は破壊されました。\n"));
    } while (++i != ENEMY_WORK(task)->ebuf[6].b[1]);
    (*func_8003521C)((void (*)(Task *, Obj *)) func_08000268_6B3208);
}

void func_08000268_6B3208(Task *task, ObjSolid *obj)
{
    (*func_802176C4_5D2B94)(task, 2);
    ENEMY_WORK(task)->flags_0c |= 2;
}
