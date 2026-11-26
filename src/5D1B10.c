#include "5D1B10.h"
#include "common.h"
#include "file_12.h"
#include "sys/sys.h"
#include "sys/task.h"
#include "sys/wave_uty.h"
#include "unk.h"

void func_80217144_5D2614(Task *task);
void func_80218F30_5D4400(Task *task, Obj *obj);
void func_8021925C_5D472C(Task *task, Obj *obj);
void func_8021928C_5D475C(Task *task);
void func_80218FE8_5D44B8(Task *task);
void func_80218E7C_5D434C(Task *task);
void func_80216AB8_5D1F88(Task *task);
void func_80217114_5D25E4(Task *task);
void func_80218350_5D3820(Task *task);
void func_80218804_5D3CD4(Task *task);
void func_8021893C_5D3E0C(Task *task);
void func_80218990_5D3E60(Task *task);
void func_80219F20_5D53F0(Task *task);
void func_8021A328_5D57F8(Task *task);
void func_8021A978_5D5E48(Task *task);
void func_80216CE0_5D21B0(Task *task, ObjSolid *solid, int arg2);

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/D_8023A480_5F5950.s")

void func_80216640_5D1B10(Task *task, Obj *obj)
{
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021664C_5D1B1C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80216838_5D1D08.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80216AB8_5D1F88.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80216CE0_5D21B0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80216DF8_5D22C8.s")

void func_80216E1C_5D22EC(Task *task, int arg1)
{
    ObjSolid *solid = (ObjSolid *) task->obj_head;

    solid->sx = 0.1f;
    solid->sy = 0.1f;
    solid->sz = 0.1f;
    func_80216CE0_5D21B0(task, solid, arg1);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80216E54_5D2324.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80216ED0_5D23A0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80216FFC_5D24CC.s")

void func_80217114_5D25E4(Task *task)
{
    ObjSolid *solid;

    if (ENEMY_WORK(task)->flags_04 & 0x20) {
        solid         = (ObjSolid *) task->obj_head;
        solid->hidden = 0;
    } else {
        solid         = (ObjSolid *) task->obj_head;
        solid->hidden = 1;
    }
}

void func_80217144_5D2614(Task *task)
{
    task->unk_4e             = 2;
    task->unk_50             = 0x28;
    task->unk_52             = 0;
    task->unk_48             = -1;
    task->unk_34             = 0;
    task->unk_4c             = 1;
    task->unk_3c             = 0x64;
    task->unk_3e             = 0xA0;
    task->unk_40             = 0;
    task->unk_38             = 0;
    task->unk_44             = 0;
    ENEMY_WORK(task)->unk_3c = 0xA;
    ENEMY_WORK(task)->unk_3d = 5;
    ENEMY_WORK(task)->unk_3e = 5;
    ENEMY_WORK(task)->unk_3f = 0;
    ENEMY_WORK(task)->unk_31 = 1;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_802171A8_5D2678.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80217360_5D2830.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80217558_5D2A28.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_802176C4_5D2B94.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80217F1C_5D33EC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021804C_5D351C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80218090_5D3560.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021816C_5D363C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80218234_5D3704.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_802182BC_5D378C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80218350_5D3820.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80218548_5D3A18.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80218804_5D3CD4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021893C_5D3E0C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80218990_5D3E60.s")

void func_80218A54_5D3F24(Task *task, EnemySpawn *spawn)
{
    ObjSolid *solid;

    D_8015CDE0                 = (EnemyDef *) spawn->def;
    D_8015CDE0                 = (EnemyDef *) func_80014840((int) D_8015CDE0, ENEMY_MGR->wave_no);
    ENEMY_WORK(task)->type     = D_8015CDE0->type;
    ENEMY_WORK(task)->type2    = D_8015CDE0->type;
    ENEMY_WORK(task)->category = D_80229FE4_5E54B4[ENEMY_WORK(task)->type];

    solid             = (ObjSolid *) task->obj_head;
    solid->header.pri = 2;
    solid->tx         = spawn->x;
    solid->ty         = spawn->y;
    solid->tz         = spawn->z;
    solid->rx         = spawn->rx;
    solid->ry         = spawn->ry;
    solid->rz         = spawn->rz;

    ENEMY_WORK(task)->ebuf[0].u = D_8015CDE0->ebuf[0];
    ENEMY_WORK(task)->ebuf[1].u = D_8015CDE0->ebuf[1];
    ENEMY_WORK(task)->ebuf[2].u = D_8015CDE0->ebuf[2];
    ENEMY_WORK(task)->spawn     = NULL;
    ENEMY_WORK(task)->unk_19    = 0x19;
    ENEMY_WORK(task)->unk_48    = 0;
    ENEMY_WORK(task)->unk_1a    = 0x14;
    ENEMY_WORK(task)->unk_3a    = 1;
    ENEMY_WORK(task)->id        = ENEMY_MGR->next_id;
    ENEMY_MGR->next_id++;
    task->status = 1;

    func_80217144_5D2614(task);
    solid->scratch_f[0] = (float) ENEMY_WORK(task)->unk_3d / 2;
    solid->scratch_f[1] = ENEMY_WORK(task)->unk_3c;
    func_8021928C_5D475C(task);
    func_80035214(task, func_8021925C_5D472C);
    func_80035244(task, func_80218F30_5D4400);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80218C28_5D40F8.s")

void func_80218D7C_5D424C(Task *task, int arg1, int arg2, int arg3)
{
    task->unk_3c = arg1;
    task->unk_3e = arg2;
    task->unk_40 = arg3;
    task->unk_48 = 0;
}

void func_80218D90_5D4260(Task *task, int a, int b, int c, int d)
{
    ENEMY_WORK(task)->unk_3c = a;
    ENEMY_WORK(task)->unk_3d = b;
    ENEMY_WORK(task)->unk_3e = c;
    ENEMY_WORK(task)->unk_3f = d;
}

void func_80218DA8_5D4278(Task *task, int arg1, int arg2, int arg3)
{
    task->unk_48 = -1;
    task->unk_4e = arg1 / 10;
    task->unk_50 = arg2;
    task->unk_52 = arg3;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80218DCC_5D429C.s")

void func_80218DF8_5D42C8(Task *task)
{
    ENEMY_WORK(task)->flags_04 = 0x821;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80218E04_5D42D4.s")

void func_80218E7C_5D434C(Task *task)
{
    if (task->obj_head != NULL) {
        func_80217114_5D25E4(task);
        func_80216AB8_5D1F88(task);
        func_80224B88_5E0058(task);
        func_8021893C_5D3E0C(task);
        func_8021C444_5D7914(task);
        func_8021B808_5D6CD8(task);
        func_8021C518_5D79E8(task);
        func_8021A978_5D5E48(task);
        func_80218990_5D3E60(task);
        func_8021B610_5D6AE0(task);
        func_80219F20_5D53F0(task);
        func_80218350_5D3820(task);
        func_80218804_5D3CD4(task);
        ENEMY_WORK(task)->flags_0c &= ~0x40000;
    }
    func_8021A328_5D57F8(task);
}

// Exec of a live enemy; once it is dead (flags_0c bit 1) the task ends and a respawn task takes over its spawn point.
void func_80218F30_5D4400(Task *task, Obj *obj)
{
    Task       *respawn;
    int         pad[2];
    EnemySpawn *spawn;
    int         delay;

    func_80218E7C_5D434C(task);
    task->unk_38 = 0;
    task->unk_34 = 0;
    if (ENEMY_WORK(task)->flags_0c & 2) {
        spawn = ENEMY_WORK(task)->spawn;
        delay = ENEMY_WORK(task)->unk_1a;
        func_80034ED4();
        if (spawn != NULL) {
            respawn = func_80034E08(ENEMY_MGR->parents[0], func_80213ED0_5CF3A0, 0);
            if (respawn != NULL) {
                ENEMY_WORK(respawn)->category = 0;
                ENEMY_WORK(respawn)->spawn    = spawn;
                ENEMY_WORK(respawn)->flags_0c = 8;
                ENEMY_WORK(respawn)->unk_1a   = delay + 5;
                func_80035244(respawn, func_80218F30_5D4400);
            } else {
                spawn->spawned = 0;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80218FE8_5D44B8.s")

void func_8021925C_5D472C(Task *task, Obj *obj)
{
    func_80218FE8_5D44B8(task);
}

void func_8021927C_5D474C(Task *task)
{
    ENEMY_WORK(task)->player = ENEMY_MGR->player;
}

void func_8021928C_5D475C(Task *task)
{
    ENEMY_WORK(task)->player = ENEMY_MGR->player;
}

void func_8021929C_5D476C(Task *task)
{
}

void func_802192A4_5D4774(Task *task)
{
}

void func_802192AC_5D477C(Task *task)
{
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_802192B4_5D4784.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80219330_5D4800.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80219448_5D4918.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80219578_5D4A48.s")

void func_802196E4_5D4BB4(Task *task)
{
    ENEMY_WORK(task)->unk_1c[0] = 0.0f;
    ENEMY_WORK(task)->unk_1c[1] = 0.0f;
    ENEMY_WORK(task)->unk_1c[2] = 0.0f;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_802196FC_5D4BCC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_802197D8_5D4CA8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80219810_5D4CE0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_802198D4_5D4DA4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_802199B0_5D4E80.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80219AA4_5D4F74.s")

void func_80219C94_5D5164(Task *task, Obj *obj)
{
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80219CA0_5D5170.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80219E08_5D52D8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80219E40_5D5310.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80219E70_5D5340.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_80219F20_5D53F0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A22C_5D56FC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A26C_5D573C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A308_5D57D8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A310_5D57E0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A328_5D57F8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A4DC_5D59AC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A4E4_5D59B4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A644_5D5B14.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A67C_5D5B4C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A764_5D5C34.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A7E8_5D5CB8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A858_5D5D28.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A910_5D5DE0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021A978_5D5E48.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021AAE0_5D5FB0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021AB18_5D5FE8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021AB90_5D6060.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021AC08_5D60D8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/5D1B10/func_8021ACA4_5D6174.s")
