// Player overlay (598540).
#include "common.h"
#include "file_11.h"
#include "sys/task.h"
#include "sys/sys.h"
#include "5997A0.h"
#include "sys/anime.h"
#include "59D4E0.h"
#include "unk.h"

void func_801DD5C0_5994D0(Task *task, unsigned char arg1);

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DC630_598540.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DC70C_59861C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DC87C_59878C.s")

void func_801DC988_598898(void)
{
    int i, j;

    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            D_8020D238_5C9148[i][j] = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DC9C8_5988D8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DCA64_598974.s")

int func_801DCCF0_598C00(short amount)
{
    D_8015C5D8.unk_10 += amount;
    if ((short) D_8015C5D8.unk_10 < 0) {
        D_8015C5D8.unk_10 = 0;
        return 1;
    }
    if ((short) D_8015C5D8.unk_10 >= 0x2710) {
        D_8015C5D8.unk_10 = 0x270F;
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DCD48_598C58.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DCE10_598D20.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DCFB0_598EC0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DD114_599024.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DD254_599164.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DD2C4_5991D4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DD3C4_5992D4.s")

void func_801DD458_599368(Task *task)
{
    func_801E307C_59EF8C(task);
    PLAYER_WORK(task)->physics->unk_00 = 1;
    task->unk_30 &= ~1;
    PLAYER_WORK(task)->unk_78 = 0;
}

void func_801DD498_5993A8(Task *task)
{
    unsigned char model = PLAYER_WORK(task)->physics->unk_84;
    ObjSolid     *solid;

    if (model != 0) {
        solid = task->obj_head;
        anime_swap_models(solid, 0, D_80204048_5BFF58[model]);
    }
}

void func_801DD4D8_5993E8(Task *task, unsigned char arg1)
{
    func_801DD5C0_5994D0(task, arg1);
}

unsigned char func_801DD500_599410(Task *task)
{
    return PLAYER_WORK(task)->physics->unk_69;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/598540/func_801DD50C_59941C.s")

void func_801DD5C0_5994D0(Task *task, unsigned char arg1)
{
    PLAYER_WORK(task)->character       = arg1;
    D_8015C5D8.unk_04                  = PLAYER_WORK(task)->character;
    PLAYER_WORK(task)->physics->unk_69 = 1;
    PLAYER_WORK(task)->physics->unk_86 = 0;
    PLAYER_WORK(task)->unk_24          = 0;
    PLAYER_WORK(task)->physics->unk_30 = 0;
    PLAYER_WORK(task)->unk_8c          = 0.0f;
    PLAYER_WORK(task)->unk_0c          = 0.0f;
    PLAYER_WORK(task)->unk_10          = 0.0f;
    PLAYER_WORK(task)->unk_14          = 0.0f;
    PLAYER_WORK(task)->physics->unk_00 = 1;
    task->unk_30 &= ~1;
    task->unk_48              = 0;
    PLAYER_WORK(task)->unk_7f = 1;
    PLAYER_WORK(task)->state  = 0xBA;
    func_8003522C(task, func_801E0944_59C854);
}

void func_801DD654_599564(Task *task, unsigned char arg1)
{
    PLAYER_WORK(task)->character       = arg1;
    D_8015C5D8.unk_04                  = PLAYER_WORK(task)->character;
    PLAYER_WORK(task)->physics->unk_69 = 1;
    PLAYER_WORK(task)->unk_24          = 0;
    PLAYER_WORK(task)->physics->unk_30 = 0;
    PLAYER_WORK(task)->unk_8c          = 0.0f;
    PLAYER_WORK(task)->unk_0c          = 0.0f;
    PLAYER_WORK(task)->unk_10          = 0.0f;
    PLAYER_WORK(task)->unk_14          = 0.0f;
    PLAYER_WORK(task)->physics->unk_00 = 1;
    task->unk_30 &= ~1;
    PLAYER_WORK(task)->state = 0xBB;
    func_8003522C(task, func_801E0BF8_59CB08);
}
