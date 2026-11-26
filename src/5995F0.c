// Player overlay (5995F0).
#include "common.h"
#include "file_11.h"
#include "sys/sd_main.h"
#include "sys/gfx_util.h"
#include "sys/solid_atari.h"
#include "unk.h"

void func_801DD6E0_5995F0(Task *task, unsigned short index)
{
    func_80038BC8(D_80204060_5BFF70[index][PLAYER_WORK(task)->character]);
}

void func_801DD720_599630(Task *task, unsigned char index)
{
    unsigned short *table;
    int             i;

    if (task->unk_58 != 0) {
        table = D_802042A8_5C01B8[index];
        if (table != NULL) {
            for (i = 0; i < 4; i++) {
                D_8020D250_5C9160[PLAYER_WORK(task)->controller][i] = 0;
            }
            func_80032B20(task, D_8020D250_5C9160[PLAYER_WORK(task)->controller], PLAYER_WORK(task)->unk_74, PLAYER_WORK(task)->physics->unk_1c, PLAYER_WORK(task)->unk_7f);
            for (i = 0; i < 4; i++) {
                if (D_8020D250_5C9160[PLAYER_WORK(task)->controller][i] != 0 && table[i] != 0xFFFF) {
                    func_801DD6E0_5995F0(task, table[i]);
                }
            }
        }
    }
}

void func_801DD830_599740(Task *task, int index)
{
    unsigned short *entry;

    if (index != 0) {
        entry = D_80204324_5C0234[index];
        if (entry[0] != 0) {
            func_801DD6E0_5995F0(task, entry[func_8001DA08(entry[0]) + 1]);
        }
    }
}
