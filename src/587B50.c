// Player overlay (587B50).
#include "common.h"
#include "587B50.h"
#include "file_11.h"
#include "sys/wave_uty.h"
#include "598540.h"
#include "sys/sys.h"
#include "5A12F0.h"
#include "5B20B0.h"
#include "sys/task.h"
#include "unk.h"

extern ObjSolid *D_801FC614_5B8524;
void func_801CC000_587F10(Task *task);
int func_8001D394(float *v);
void func_801CBF0C_587E1C(Task *task);

void func_801CBC40_587B50(void)
{
    Task     *task = D_801FC604_5B8514;
    ObjSolid *solid;

    if (task != NULL) {
        task->wave.data = func_800141C4(task->wave.wave_no);
        solid           = task->obj_head;

        solid->SegWave[2].wave_no = g_sys->unk_c2d90;
        solid->SegWave[1].wave_no = D_80204020_5BFF30[PLAYER_WORK(task)->character];
        solid->SegWave[1].data    = D_8020D220_5C9130[PLAYER_WORK(task)->controller];
        func_801DC9C8_5988D8(task, PLAYER_WORK(task)->character);
        func_801DCA64_598974(task, 0, D_8020D260_5C9170);
    }
}

void func_801CBCE4_587BF4(void)
{
    PlayerWaveList list = D_801FC7B8_5B86C8;

    func_80013AC4(list.wave);
}

void func_801CBD14_587C24(void)
{
    D_801FC600_5B8510       = 0;
    (&D_801FC604_5B8514)[1] = NULL;
    D_801FC604_5B8514       = NULL;
    (&D_801FC60C_5B851C)[1] = NULL;
    D_801FC60C_5B851C       = NULL;
    (&D_801FC614_5B8524)[1] = NULL;
    D_801FC614_5B8524       = NULL;
    (&D_801FC61C_5B852C)[1] = NULL;
    D_801FC61C_5B852C       = NULL;
    D_801FC624_5B8534       = NULL;
    D_801FC628_5B8538       = 0;
    func_801DC988_598898();
}

void func_801CBD88_587C98(void)
{
    Task *task = D_801FC604_5B8514;

    if (task != NULL) {
        func_801DC988_598898();
        func_801E7FB4_5A3EC4(task);
        D_801FC60C_5B851C->tx              = g_sys->next_entry.x;
        D_801FC60C_5B851C->ty              = g_sys->next_entry.y - 2;
        D_801FC60C_5B851C->tz              = g_sys->next_entry.z;
        PLAYER_WORK(task)->angle           = g_sys->next_entry.facing;
        PLAYER_WORK(task)->physics->unk_a4 = PLAYER_WORK(task)->angle << 6;
        if (PLAYER_WORK(task)->character != 1 || PLAYER_WORK(task)->physics->unk_86 != 0xFFFF) {
            D_801FC60C_5B851C->sz = D_8020A7D8_5C66E8;
            D_801FC60C_5B851C->sx = D_801FC60C_5B851C->sy = D_801FC60C_5B851C->sz;
        }
        func_801CBF0C_587E1C(task);
        D_801FC60C_5B851C->hidden = 0;
        D_801FC614_5B8524->tx = D_801FC61C_5B852C->tx = D_801FC60C_5B851C->tx;
        D_801FC614_5B8524->ty = D_801FC61C_5B852C->ty = D_801FC60C_5B851C->ty;
        D_801FC614_5B8524->tz = D_801FC61C_5B852C->tz = D_801FC60C_5B851C->tz;
    }
}

void func_801CBF0C_587E1C(Task *task)
{
    func_801CC000_587F10(task);
    func_801CBFCC_587EDC(task);
    func_801CC4C0_5883D0(task, PLAYER_WORK(task)->unk_88, PLAYER_WORK(task)->unk_8c);
    func_801CD084_588F94(task);
    if (func_801E7E90_5A3DA0(task) != 0) {
        func_801F6FE8_5B2EF8(task);
        func_801DACDC_596BEC(task, 0xAE);
        return;
    }
    if (PLAYER_WORK(task)->character == 0) {
        if (PLAYER_WORK(task)->physics->unk_86 == 0) {
            PLAYER_WORK(task)->physics->unk_84 = 2;
        }
    }
    if (func_801E7DE8_5A3CF8(task) != 0 || PLAYER_WORK(task)->physics->unk_86 == 0) {
        func_801DACDC_596BEC(task, 0);
    }
}

void func_801CBFCC_587EDC(Task *task)
{
    PlayerByteTable table = D_801FC7BC_5B86CC;

    PLAYER_WORK(task)->physics->unk_58 = table.byte[PLAYER_WORK(task)->character];
}

void func_801CC000_587F10(Task *task)
{
    PLAYER_WORK(task)->unk_05          = 0;
    PLAYER_WORK(task)->unk_06          = 0;
    PLAYER_WORK(task)->unk_07          = 0;
    PLAYER_WORK(task)->camera          = D_801FC624_5B8534;
    PLAYER_WORK(task)->unk_24          = 0;
    PLAYER_WORK(task)->unk_26          = 0;
    PLAYER_WORK(task)->controller      = 0;
    PLAYER_WORK(task)->unk_3a          = 0;
    PLAYER_WORK(task)->unk_3c          = 1;
    PLAYER_WORK(task)->unk_3e          = 0;
    PLAYER_WORK(task)->unk_40          = 0;
    PLAYER_WORK(task)->unk_44          = 0;
    PLAYER_WORK(task)->unk_71          = 0;
    PLAYER_WORK(task)->unk_72          = 0;
    PLAYER_WORK(task)->unk_78          = 0;
    PLAYER_WORK(task)->unk_84          = 0;
    PLAYER_WORK(task)->unk_90          = 0;
    PLAYER_WORK(task)->unk_91          = 0;
    PLAYER_WORK(task)->unk_92          = 0;
    PLAYER_WORK(task)->unk_20          = 0.0f;
    PLAYER_WORK(task)->unk_1c          = 0.0f;
    PLAYER_WORK(task)->unk_18          = 0.0f;
    PLAYER_WORK(task)->unk_14          = 0.0f;
    PLAYER_WORK(task)->unk_10          = 0.0f;
    PLAYER_WORK(task)->unk_0c          = 0.0f;
    PLAYER_WORK(task)->unk_30          = 0.0f;
    PLAYER_WORK(task)->unk_28          = 0.0f;
    PLAYER_WORK(task)->unk_48          = 0.0f;
    PLAYER_WORK(task)->unk_54          = 0.0f;
    PLAYER_WORK(task)->unk_4c          = 0.0f;
    PLAYER_WORK(task)->unk_60          = 0.0f;
    PLAYER_WORK(task)->unk_58          = 0.0f;
    PLAYER_WORK(task)->unk_6c          = 0.0f;
    PLAYER_WORK(task)->unk_68          = 0.0f;
    PLAYER_WORK(task)->unk_64          = 0.0f;
    PLAYER_WORK(task)->unk_8c          = 0.0f;
    PLAYER_WORK(task)->unk_88          = 0.0f;
    PLAYER_WORK(task)->unk_2c          = 1.0f;
    PLAYER_WORK(task)->unk_50          = 1.0f;
    PLAYER_WORK(task)->unk_5c          = 1.0f;
    PLAYER_WORK(task)->physics->unk_00 = 0;
    PLAYER_WORK(task)->physics->unk_02 = 0;
    PLAYER_WORK(task)->physics->unk_04 = 0.0f;
    PLAYER_WORK(task)->physics->unk_08 = 0;
    PLAYER_WORK(task)->physics->unk_0c = PLAYER_WORK(task)->physics->unk_10 = PLAYER_WORK(task)->physics->unk_14 = 0.0f;
    PLAYER_WORK(task)->physics->unk_18                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_19                                                                           = 0;
    PLAYER_WORK(task)->physics->angle                                                                            = 0;
    PLAYER_WORK(task)->physics->speed = PLAYER_WORK(task)->physics->speed_prev = PLAYER_WORK(task)->physics->speed_prev2 = 0.0f;
    PLAYER_WORK(task)->physics->unk_2c = PLAYER_WORK(task)->physics->unk_2d = PLAYER_WORK(task)->physics->unk_2e = 0;
    PLAYER_WORK(task)->physics->unk_2f                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_30                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_32                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_34                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_36                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_38                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_3c = PLAYER_WORK(task)->physics->unk_44 = 0.0f;
    PLAYER_WORK(task)->physics->unk_40                                      = 1.0f;
    PLAYER_WORK(task)->physics->unk_48                                      = D_8020A7DC_5C66EC;
    PLAYER_WORK(task)->physics->unk_4c                                      = 0;
    if (func_801E7E90_5A3DA0(task) != 0) {
        PLAYER_WORK(task)->physics->unk_50 = D_8020A7E0_5C66F0;
    } else {
        PLAYER_WORK(task)->physics->unk_50 = D_8020A7E4_5C66F4;
    }
    PLAYER_WORK(task)->physics->unk_54 = 0.0f;
    PLAYER_WORK(task)->physics->unk_58 = 0;
    PLAYER_WORK(task)->physics->unk_59 = 0;
    PLAYER_WORK(task)->physics->unk_5c = PLAYER_WORK(task)->physics->unk_64 = 0.0f;
    PLAYER_WORK(task)->physics->unk_60                                      = 1;
    PLAYER_WORK(task)->physics->unk_68                                      = 0;
    PLAYER_WORK(task)->physics->unk_69                                      = 0;
    PLAYER_WORK(task)->physics->unk_6a                                      = 0;
    PLAYER_WORK(task)->physics->unk_6c                                      = 0.0f;
    PLAYER_WORK(task)->physics->unk_6c = PLAYER_WORK(task)->physics->unk_70 = PLAYER_WORK(task)->physics->unk_74 = 0.0f;
    PLAYER_WORK(task)->physics->unk_78                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_7c                                                                           = NULL;
    PLAYER_WORK(task)->physics->unk_80                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_85                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_88                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_8c                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_90                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_94                                                                           = 0;
    PLAYER_WORK(task)->physics->unk_98 = PLAYER_WORK(task)->physics->unk_9c = PLAYER_WORK(task)->physics->unk_a0 = 0;
    PLAYER_WORK(task)->physics->unk_a6 = PLAYER_WORK(task)->physics->unk_a8 = 0;
    PLAYER_WORK(task)->physics->unk_aa                                      = 0;
    PLAYER_WORK(task)->physics->unk_ac = PLAYER_WORK(task)->physics->unk_b0 = 0;
    PLAYER_WORK(task)->physics->afterline                                   = NULL;
    func_801CC454_588364(task);
}

void func_801CC30C_58821C(Task *task)
{
    ObjSolid *solid = task->obj_head;

    func_801CC454_588364(task);
    solid->init_glist                  = (unsigned int) D_801FC680_5B8590 | 0x40000000;
    solid->header.pri                  = 2;
    PLAYER_WORK(task)->unk_35          = 0xB9;
    PLAYER_WORK(task)->unk_36          = 0xB4;
    PLAYER_WORK(task)->physics->unk_5c = solid->tx;
    PLAYER_WORK(task)->physics->unk_60 = solid->ty;
    PLAYER_WORK(task)->physics->unk_64 = solid->tz;
    PLAYER_WORK(task)->unk_5c          = 1.0f;
    PLAYER_WORK(task)->unk_2c          = 1.0f;
    PLAYER_WORK(task)->unk_58          = 0.0f;
    PLAYER_WORK(task)->unk_28          = 0.0f;
    PLAYER_WORK(task)->unk_60          = 0.0f;
    PLAYER_WORK(task)->unk_30          = 0.0f;
    PLAYER_WORK(task)->physics->unk_48 = D_8020A7E8_5C66F8;
    func_8001D394(&PLAYER_WORK(task)->unk_58);
    func_80035214(task, func_801CB824_587734);
    func_80035244(task, func_801CBACC_5879DC);
    PLAYER_WORK(task)->state = 0xC;
    if (g_sys_real.unk_3ae20 == 1) {
        func_801DACDC_596BEC(task, 0xBC);
        return;
    }
    func_801DACDC_596BEC(task, 0);
}

void func_801CC424_588334(Task *task)
{
    PLAYER_WORK(task)->unk_72          = 0;
    PLAYER_WORK(task)->physics->unk_00 = 0;
    PLAYER_WORK(task)->physics->unk_02 = 0;
    PLAYER_WORK(task)->physics->unk_04 = 0.0f;
    PLAYER_WORK(task)->physics->unk_34 = 0;
    PLAYER_WORK(task)->unk_90          = 0;
}

void func_801CC454_588364(Task *task)
{
    task->unk_30 = 3;
    task->unk_38 = 0;
    task->unk_34 = 0;
    task->unk_3c = D_801FC660_5B8570[PLAYER_WORK(task)->character];
    task->unk_3e = D_801FC668_5B8578[PLAYER_WORK(task)->character];
    task->unk_52 = 0;
    task->unk_40 = 0;
    task->unk_42 = 0;
    task->unk_44 = 0;
    task->unk_48 = 0;
    task->unk_4c = 0x14;
    task->unk_54 = 0;
    task->unk_58 = 0;
    task->unk_50 = task->unk_52;
    task->unk_4e = task->unk_52;
}
