#include "enemy/file_12.h"
#include "common.h"
#include "sys/sys.h"
#include "unk.h"

void func_8020D36C_5C883C(Task *task, int x, int y, int z);

void func_8020D2A0_5C8770(Task *task)
{
    ObjSolid *player = ENEMY_MGR->player;
    int       size_x = ENEMY_MGR->size_x;
    int       size_y = ENEMY_MGR->size_y;
    int       size_z = ENEMY_MGR->size_z;

    func_8020D36C_5C883C(task, (player->tx - ENEMY_MGR->center_x) / ENEMY_MGR->cell_x + (float) size_x / 2,
        (player->ty - ENEMY_MGR->center_y) / ENEMY_MGR->cell_y + (float) size_y / 2,
        (player->tz - ENEMY_MGR->center_z) / ENEMY_MGR->cell_z + (float) size_z / 2);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/enemy/file_12/func_8020D36C_5C883C.s")
