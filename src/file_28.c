// Pot overlay.
#include "5D1B10.h"
#include "common.h"
#include "file_12.h"
#include "sys/sd_location.h"
#include "sys/task.h"
#include "unk.h"

void func_08000150_6B30F0(Task *task, Obj *obj);
void func_0800011C_6B30BC(Task *task, Obj *obj);
void func_080000C4_6B3064(Task *task, Obj *obj);
void func_08000268_6B3208(Task *task, Obj *obj);

void func_08000000_6B2FA0(Task *task, Obj *obj)
{
    ObjSolid *solid = (ObjSolid *) obj;

    ENEMY_WORK(task)->flags_04 = 0x806008A0;
    ENEMY_WORK(task)->flags_08 |= 0x8000;
    // Ebuf06 bytes: shards spawned, shard count, has an item. Ebuf01 is the enemy type of the shards.
    ENEMY_WORK(task)->ebuf[6].u = ENEMY_WORK(task)->ebuf[0].u;
    ENEMY_WORK(task)->unk_10    = 0;
    if (ENEMY_WORK(task)->ebuf[6].b[2] != 0) {
        PRINTF(("ブツ入りの壷をセットします。\n")); // "Setting a pot with an item inside."
        ENEMY_WORK(task)->flags_04 |= 0x6C00300;
    }
    (*func_80216E1C_5D22EC)(task, 0);
    solid->sx = solid->sy = solid->sz = 0.25f;
    (*func_80218D7C_5D424C)(task, 0x19, 0x3C, 0);
    (*func_8021C654_5D7B24)(task);
    (*func_8003521C)(func_080000C4_6B3064);
}

void func_080000C4_6B3064(Task *task, Obj *obj)
{
    ObjSolid *solid = (ObjSolid *) obj;

    if (ENEMY_WORK(task)->flags_0c & 1) {
        PRINTF(("壷は攻撃されました。\n")); // "The pot was attacked."
        (*func_8000F420)(0x26E, D_8020CBF0_5C8B00, solid, 800.0f);
        (*func_8003521C)(func_0800011C_6B30BC);
    }
}

void func_0800011C_6B30BC(Task *task, Obj *obj)
{
    (*func_8003521C)(func_08000150_6B30F0);
}

void func_08000150_6B30F0(Task *task, Obj *obj)
{
    ObjSolid      *solid = (ObjSolid *) obj;
    int            i;
    unsigned short angle;

    PRINTF(("壷は破壊されました。\n")); // "The pot was destroyed."
    solid->sx = solid->sy = solid->sz = 0.25f;
    i                                 = 0;
    do {
        angle = (unsigned short) (0x400 / ENEMY_WORK(task)->ebuf[6].b[1]) * i;
        (*func_8021DDE8_5D92B8)(task, D_802287C0_5E3C90[ENEMY_WORK(task)->ebuf[1].u - 1], 9, 0.0f, 10.0f, 0.0f, angle);
        // FAKE: the do-while (0) wrapper only steers the register coloring of the loop count byte.
        do {
            ENEMY_WORK(task)->ebuf[6].b[0]++;
            i++;
        } while (0);
    } while (i != ENEMY_WORK(task)->ebuf[6].b[1]);
    (*func_8003521C)(func_08000268_6B3208);
}

void func_08000268_6B3208(Task *task, Obj *obj)
{
    (*func_802176C4_5D2B94)(task, 2);
    ENEMY_WORK(task)->flags_0c |= 2;
}
