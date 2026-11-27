#include "douchu/598540.h"
#include "common.h"
#include "sys/task.h"
#include "sys/sys.h"
#include "douchu/5997A0.h"
#include "sys/anime.h"
#include "douchu/59D4E0.h"
#include "unk.h"

void func_801DD5C0_5994D0(Task *task, unsigned char arg1);

extern unsigned int *D_80204048_5BFF58[];
extern unsigned char D_8020D238_5C9148[1][2];

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DC630_598540.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DC70C_59861C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DC87C_59878C.s")

void func_801DC988_598898(void)
{
    int i, j;

    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            D_8020D238_5C9148[i][j] = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DC9C8_5988D8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DCA64_598974.s")

int func_801DCCF0_598C00(short amount)
{
    D_8015C5D8.money += amount;
    if ((short) D_8015C5D8.money < 0) {
        D_8015C5D8.money = 0;
        return 1;
    }
    if ((short) D_8015C5D8.money >= 0x2710) {
        D_8015C5D8.money = 0x270F;
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DCD48_598C58.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DCE10_598D20.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DCFB0_598EC0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DD114_599024.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DD254_599164.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DD2C4_5991D4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DD3C4_5992D4.s")

void func_801DD458_599368(Task *task)
{
    func_801E307C_59EF8C(task);
    PLAYER_WORK(task)->physics->forced_move = 1;
    task->hit_flags &= ~1;
    PLAYER_WORK(task)->invincible_frames = 0;
}

void func_801DD498_5993A8(Task *task)
{
    unsigned char model = PLAYER_WORK(task)->physics->model_swap;
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
    return PLAYER_WORK(task)->physics->changing_character;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/func_801DD50C_59941C.s")

void func_801DD5C0_5994D0(Task *task, unsigned char arg1)
{
    PLAYER_WORK(task)->character                   = arg1;
    D_8015C5D8.character                           = PLAYER_WORK(task)->character;
    PLAYER_WORK(task)->physics->changing_character = 1;
    PLAYER_WORK(task)->physics->ability_timer      = 0;
    PLAYER_WORK(task)->action_timer                = 0;
    PLAYER_WORK(task)->physics->state_timer        = 0;
    PLAYER_WORK(task)->move_accel                  = 0.0f;
    PLAYER_WORK(task)->vel_x                       = 0.0f;
    PLAYER_WORK(task)->vel_y                       = 0.0f;
    PLAYER_WORK(task)->vel_z                       = 0.0f;
    PLAYER_WORK(task)->physics->forced_move        = 1;
    task->hit_flags &= ~1;
    task->hit_ref                 = 0;
    PLAYER_WORK(task)->anime_mode = 1;
    PLAYER_WORK(task)->state      = 0xBA;
    func_8003522C(task, (void (*)(Task *, Obj *)) func_801E0944_59C854);
}

void func_801DD654_599564(Task *task, unsigned char arg1)
{
    PLAYER_WORK(task)->character                   = arg1;
    D_8015C5D8.character                           = PLAYER_WORK(task)->character;
    PLAYER_WORK(task)->physics->changing_character = 1;
    PLAYER_WORK(task)->action_timer                = 0;
    PLAYER_WORK(task)->physics->state_timer        = 0;
    PLAYER_WORK(task)->move_accel                  = 0.0f;
    PLAYER_WORK(task)->vel_x                       = 0.0f;
    PLAYER_WORK(task)->vel_y                       = 0.0f;
    PLAYER_WORK(task)->vel_z                       = 0.0f;
    PLAYER_WORK(task)->physics->forced_move        = 1;
    task->hit_flags &= ~1;
    PLAYER_WORK(task)->state = 0xBB;
    func_8003522C(task, (void (*)(Task *, Obj *)) func_801E0BF8_59CB08);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/598540/D_8020AF60_5C6E70.s")
