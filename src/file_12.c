#include "file_12.h"
#include "common.h"
#include "5D1B10.h"
#include "sys/sys.h"
#include "sys/step.h"
#include "sys/string.h"
#include "sys/save_flags.h"
#include "sys/task.h"
#include "unk.h"

void func_8020D2A0_5C8770(Task *task);
void func_8020D36C_5C883C(Task *task, int x, int y, int z);
void func_8020D848_5C8D18(Task *task, Obj *obj);

// Spawns the enemies around the grid cell of the player.
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

#pragma GLOBAL_ASM("asm/usa/nonmatchings/file_12/func_8020D36C_5C883C.s")

int func_8020D670_5C8B40(void)
{
    RoomDef *room = D_80231300_5EC7D0[g_sys->intended_room_id];

    if (g_sys->load_files_function != room->load_files_function) {
        return 1;
    }
    return 0;
}

void func_8020D6BC_5C8B8C(void)
{
    RoomDef *room = D_80231300_5EC7D0[g_sys->intended_room_id];

    g_sys->load_files_function = room->load_files_function;
    ((void (*)(void)) g_sys->load_files_function)();
}

// Init of the enemy manager.
void func_8020D724_5C8BF4(Task *task, Obj *obj)
{
    g_sys                 = &g_sys_real;
    ENEMY_MGR->next_id    = 1;
    ENEMY_MGR->unk_10a    = 0;
    ENEMY_MGR->limits[0]  = 20;
    ENEMY_MGR->limits[1]  = 15;
    ENEMY_MGR->limits[2]  = 20;
    ENEMY_MGR->limits[3]  = 5;
    ENEMY_MGR->limits[4]  = 20;
    ENEMY_MGR->unk_cc     = 60;
    ENEMY_MGR->parents[0] = task;
    ENEMY_MGR->unk_104    = 1.0f;
    ENEMY_MGR->parents[2] = func_80034E08(ENEMY_MGR->parents[1], func_80213C50_5CF120, 0);
    ENEMY_MGR->parents[3] = func_80034DD8(func_80213C50_5CF120, 0);
    ENEMY_MGR->parents[4] = func_80034DD8(func_80213C50_5CF120, 0);
    ENEMY_MGR->parents[5] = func_80034DD8(func_80213C50_5CF120, 0);
    ENEMY_MGR->parents[6] = func_80034E08(ENEMY_MGR->parents[5], func_80213C50_5CF120, 0);
    ENEMY_MGR->parents[7] = func_80034E08(ENEMY_MGR->parents[1], func_80213C50_5CF120, 0);
    ENEMY_MGR->parents[8] = func_80034E08(ENEMY_MGR->parents[5], func_80213C50_5CF120, 0);
    func_80023EE4();
    ENEMY_MGR->unk_158 = 0;
    ENEMY_MGR->unk_15c = 0;
    func_8003521C(func_8020D848_5C8D18);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/file_12/func_8020D848_5C8D18.s")

// Picks the next enemy id (stepping by `step`) that no enemy task under the parents of `task` and parents[1] uses.
// Returns 1 if one was found and 0 once all ids were tried.
int func_8020DC78_5C9148(Task *task, int step)
{
    unsigned char  start = ENEMY_MGR->unk_108;
    Task          *cur;
    unsigned short priority;

    do {
        ENEMY_MGR->unk_108 += step;
        priority = task->priority;
        for (cur = task->next; cur != NULL && cur->priority >= priority; cur = cur->next) {
            if (cur->exec[0] == func_8021925C_5D472C && ENEMY_WORK(cur)->id == ENEMY_MGR->unk_108) {
                return 1;
            }
        }
        cur      = ENEMY_MGR->parents[1];
        priority = cur->priority;
        for (cur = cur->next; cur != NULL && cur->priority >= priority; cur = cur->next) {
            if (cur->exec[0] == func_8021925C_5D472C && ENEMY_WORK(cur)->id == ENEMY_MGR->unk_108) {
                return 1;
            }
        }
    } while (start != ENEMY_MGR->unk_108);
    return 0;
}

// Exec of the enemy manager task.
void func_8020DD78_5C9248(Task *task, Obj *obj)
{
    ENEMY_MGR->unk_c8 = ENEMY_MGR->unk_c4;
    ENEMY_MGR->unk_c4 = 0;
    ENEMY_MGR->frame++;
    func_802192B4_5D4784(10);
    if (D_801FC60C_5B851C != NULL) {
        ENEMY_MGR->player  = D_801FC60C_5B851C;
        ENEMY_MGR->unk_12c = D_801FC604_5B8514;
    }
    if (ENEMY_MGR->cells != NULL) {
        func_8020D2A0_5C8770(task);
    }
}

void func_8020DDF8_5C92C8(Task *task, Obj *obj)
{
    g_sys = &g_sys_real;
    func_80004240();
    func_80003478();
}
