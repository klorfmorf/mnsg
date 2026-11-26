// Player overlay (5907F0).
#include "common.h"
#include "file_11.h"
#include "sys/math.h"
#include "sys/gfx_util.h"
#include "5913D0.h"
#include "58B870.h"
#include "5944C0.h"
#include "sys/sys.h"
#include "unk.h"

int func_8001D394(float *v);
extern ObjSolid *D_801FC614_5B8524;
void func_801D5338_591248(unsigned short *angle);
int  func_801D4BF0_590B00(Task *task, PlayerMotion *motion);
void func_801D51A8_5910B8(Task *task, PlayerMotion *motion);
void func_801D5214_591124(Task *task, PlayerMotion *motion);
void func_801D5374_591284(Task *task);
#pragma intrinsic(sqrtf)

#ifdef NON_MATCHING
void func_801D48E0_5907F0(Task *task, ObjSolid *obj)
{
    PlayerMotion *motion = (PlayerMotion *) (obj->AModel & 0x8FFFFFFE);

    if (D_801FC628_5B8538->hidden != 0) {
        D_801FCBF0_5B8B00 = D_801FC628_5B8538->hidden;
    }
    PLAYER_WORK(D_801FC604_5B8514)->unk_91 = 0;
    D_8020D1E4_5C90F4                      = D_801FC628_5B8538->work_f[2];
    D_801FC628_5B8538->work_f[2]           = 0.0f;
    if (D_8020D1E4_5C90F4 < 0.0001 && (g_sys_real.player_controller[0].stick_magnitude < 0.1 || ((PLAYER_WORK(D_801FC604_5B8514)->physics->unk_00 & 2) && PLAYER_WORK(D_801FC604_5B8514)->physics->unk_04 < 0.1))) {
        if (CAMERA_WORK(task)->unk_8c != 0xFF) {
            CAMERA_WORK(task)->unk_8c++;
        }
    } else {
        CAMERA_WORK(task)->unk_8c = 0;
        CAMERA_WORK(task)->unk_56 = 0x100;
    }
    func_801D55E0_5914F0(motion);
    D_8020D1E2_5C90F2 = func_801D7818_593728(task, motion);
    D_8020D1E0_5C90F0 = func_80003A94(motion->z - motion->prev_z, motion->x - motion->prev_x);
    task->exec[1]     = (void (*)(Task *, Obj *))((unsigned int) task->exec[1] & 0xFF7FFFFF);
    if (obj->hidden != 0 || CAMERA_WORK(task)->unk_00 == 0 || PLAYER_WORK(D_801FC604_5B8514)->unk_71 >= 4 || task->exec[2] != func_801D85B0_5944C0) {
        task->exec[1] = (void (*)(Task *, Obj *))((unsigned int) task->exec[1] | 0x800000);
    }
    if (obj->hidden != 0 || CAMERA_WORK(task)->unk_00 == 0 || PLAYER_WORK(D_801FC604_5B8514)->unk_71 >= 4) {
        return;
    }
    func_801D2734_58E644(task, motion);
    if (CAMERA_WORK(task)->unk_75 != CAMERA_WORK(task)->unk_17 || CAMERA_WORK(task)->unk_75 == CAMERA_WORK(task)->unk_3c) {
        if (CAMERA_WORK(task)->unk_17 != 0xFF) {
            CAMERA_WORK(task)->unk_3c = CAMERA_WORK(task)->unk_17;
        }
    }
    D_8020D1A2_5C90B2 = CAMERA_WORK(task)->unk_3c;
    if (PLAYER_WORK(D_801FC604_5B8514)->unk_05 != 0) {
        CAMERA_WORK(task)->unk_3c = 9;
    }
    if (CAMERA_WORK(task)->unk_76 != 0) {
        CAMERA_WORK(task)->unk_3c = 0x11;
    }
    if (CAMERA_WORK(task)->unk_3c != CAMERA_WORK(task)->unk_75) {
        func_801D4828_590738(task);
        CAMERA_WORK(task)->unk_02 = 0;
        CAMERA_WORK(task)->unk_15 = 1;
    } else {
        func_801D4828_590738(task);
    }
    CAMERA_WORK(task)->unk_03 = 0;
    func_801D55E0_5914F0(motion);
    func_801D4BF0_590B00(task, motion);
    func_801D55E0_5914F0(motion);
    func_801D51A8_5910B8(task, motion);
    func_801D5214_591124(task, motion);
    func_801D5374_591284(task);
    if (task->exec[1] != NULL && !((unsigned int) task->exec[1] & 0x800000) && CAMERA_WORK(task)->unk_3c != 0x11) {
        func_801D54C0_5913D0(task, motion);
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/5907F0/func_801D48E0_5907F0.s")
#endif

int func_801D4BF0_590B00(Task *task, PlayerMotion *motion)
{
    float        sin;
    float        q;
    float        v[3];
    float        out[3];
    float        scaled;
    float        root;
    float        target[3];
    float        dist;
    float       *offset = ((ObjSolid *) task->obj_head)->work_f;
    unsigned int angle;

    angle  = func_80003A94(240.0f, 289.0f / func_80003DC0(motion->angle));
    scaled = (float) angle * 0.55;
    sin    = func_80003DC0(scaled);
    dist   = CAMERA_WORK(task)->unk_54 * (D_8020D1CC_5C90DC * sin) / 256;
    v[2]   = func_80003D88(CAMERA_WORK(task)->unk_0a, &v[0]);
    v[1]   = 0.0f;
    func_8001D394(v);
    func_8001D460(v, out, D_8020D1B0_5C90C0);
    out[2] = 0.0f;
    if (CAMERA_WORK(task)->unk_3c != 0x11) {
        target[0] = D_801FC614_5B8524->tx - motion->x;
        target[1] = (D_801FC60C_5B851C->ty + D_801FC614_5B8524->ty) * 0.5 - motion->y + 20.0;
        target[2] = D_801FC614_5B8524->tz - motion->z;
    } else {
        target[0] = D_801FC634_5B8544->tx - motion->x;
        target[1] = (D_801FC60C_5B851C->ty + D_801FC614_5B8524->ty) * 0.5 - motion->y + 20.0;
        target[2] = D_801FC634_5B8544->tz - motion->z;
    }
    if (CAMERA_WORK(task)->unk_0a == CAMERA_WORK(task)->unk_0c || CAMERA_WORK(task)->unk_06 == 0) {
        offset[0]                 = out[0];
        offset[1]                 = out[1];
        CAMERA_WORK(task)->unk_06 = 0;
        CAMERA_WORK(task)->unk_0c = CAMERA_WORK(task)->unk_0a;
    } else {
        offset[0] = offset[0] + (out[0] - offset[0]) / (CAMERA_WORK(task)->unk_06 + 1.0f);
        offset[1] = offset[1] + (out[1] - offset[1]) / (CAMERA_WORK(task)->unk_06 + 1.0f);
        CAMERA_WORK(task)->unk_06--;
    }
    root = sqrtf(D_8020D1CC_5C90DC * D_8020D1CC_5C90DC - dist * dist * 0.25);
    if ((D_8020D1CC_5C90DC < 0.0f ? -D_8020D1CC_5C90DC : D_8020D1CC_5C90DC) < 0.00001) {
        return 0;
    }
    q      = dist * root / D_8020D1CC_5C90DC;
    out[0] = offset[0] * -q;
    out[1] = offset[1] * -q;
    out[2] = -dist * dist / (2 * root);
    func_8001D5B8(out, v, D_8020D1B0_5C90C0);
    target[0] += v[0];
    target[1] += v[1];
    target[2] += v[2];
    if (CAMERA_WORK(task)->unk_74 != 0) {
        target[0] = (target[0] + D_8020D1C0_5C90D0[0]) / (CAMERA_WORK(task)->unk_74 + 1.0f) - D_8020D1C0_5C90D0[0];
        target[1] = (target[1] + D_8020D1C0_5C90D0[1]) / (CAMERA_WORK(task)->unk_74 + 1.0f) - D_8020D1C0_5C90D0[1];
        target[2] = (target[2] + D_8020D1C0_5C90D0[2]) / (CAMERA_WORK(task)->unk_74 + 1.0f) - D_8020D1C0_5C90D0[2];
        CAMERA_WORK(task)->unk_74--;
    }
    v[0]              = motion->x - motion->prev_x;
    v[1]              = motion->y - motion->prev_y;
    v[2]              = motion->z - motion->prev_z;
    D_8020D1A0_5C90B0 = func_80003A94(v[1], sqrtf(v[0] * v[0] + v[2] * v[2]));
    motion->prev_x    = target[0] + motion->x;
    motion->prev_y    = target[1] + motion->y;
    motion->prev_z    = target[2] + motion->z;
    return 0;
}

#ifdef NON_MATCHING
void func_801D51A8_5910B8(Task *task, PlayerMotion *motion)
{
    int target = CAMERA_WORK(task)->unk_56;
    int cur    = CAMERA_WORK(task)->unk_54;

    if (target < cur) {
        if (cur - target < 0x10) {
            CAMERA_WORK(task)->unk_54 = CAMERA_WORK(task)->unk_56;
        } else {
            CAMERA_WORK(task)->unk_54 = cur - 0x10;
        }
        return;
    }
    if (cur < target) {
        CAMERA_WORK(task)->unk_54 = cur + 2;
        cur                       = CAMERA_WORK(task)->unk_54;
        target                    = CAMERA_WORK(task)->unk_56;
    }
    if (target < cur) {
        CAMERA_WORK(task)->unk_54 = CAMERA_WORK(task)->unk_56;
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/5907F0/func_801D51A8_5910B8.s")
#endif

void func_801D5214_591124(Task *task, PlayerMotion *motion)
{
    float          out[3];
    float          dir[3];
    unsigned short angle;

    angle = D_801FC928_5B8838[CAMERA_WORK(task)->unk_3c][CAMERA_WORK(task)->unk_14][0];
    if (PLAYER_WORK(D_801FC604_5B8514)->physics->unk_59 != 0) {
        angle = 0x600;
    }
    CAMERA_WORK(task)->unk_12 = angle;
    if (CAMERA_WORK(task)->unk_3c != 0x11) {
        dir[0] = motion->x - D_801FC614_5B8524->tx;
        dir[2] = motion->z - D_801FC614_5B8524->tz;
        dir[1] = 0.0f;
        if (func_8001D394(dir)) {
            func_8001D460(&PLAYER_WORK(D_801FC604_5B8514)->unk_58, out, dir);
            out[0] = 0.0f;
            if (out[2] < 0.0f) {
                if (func_8001D394(out)) {
                    if (CAMERA_WORK(task)->unk_3c_h != 0) {
                        func_80003A94(-out[2], out[1]);
                    }
                }
            }
        }
    }
    func_801D5338_591248(&CAMERA_WORK(task)->unk_12);
}

void func_801D5338_591248(unsigned short *angle)
{
    if (!(*angle & 0x8000)) {
        if (*angle >= 0x3001) {
            *angle = 0x3000;
        }
    } else if (*angle < 0xDA00) {
        *angle = 0xDA00;
    }
}

void func_801D5374_591284(Task *task)
{
    float          vec[3];
    float          out[3];
    float          speed;
    float          abs_speed;
    float          cos;
    unsigned short angle;

    func_80003D88(CAMERA_WORK(task)->unk_12, &cos);
    speed = D_8020D1CC_5C90DC * cos;
    if (speed < 0.0f) {
        abs_speed = -speed;
    } else {
        abs_speed = speed;
    }
    if (abs_speed < 0.00001) {
        return;
    }
    vec[0] = func_80003F30(PLAYER_WORK(D_801FC604_5B8514)->angle + 0x200, &cos);
    vec[2] = cos;
    vec[1] = 0.0f;
    func_8001D718(vec, out, &PLAYER_WORK(D_801FC604_5B8514)->unk_28);
    angle = func_80003A94(out[2], out[0]);
    if ((unsigned short) (angle - CAMERA_WORK(task)->unk_0a + 0x800) >= 0x1000 && (unsigned short) (angle - CAMERA_WORK(task)->unk_08 + 0x800) < 0x1000) {
        CAMERA_WORK(task)->unk_07++;
    } else {
        CAMERA_WORK(task)->unk_07 = 0;
    }
    if (CAMERA_WORK(task)->unk_07 >= 5) {
        CAMERA_WORK(task)->unk_07 = 4;
        CAMERA_WORK(task)->unk_0a = angle;
        CAMERA_WORK(task)->unk_06 = 0x1E;
    }
    CAMERA_WORK(task)->unk_08 = angle;
}
