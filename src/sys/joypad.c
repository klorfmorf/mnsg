#include "sys/joypad.h"
#include "common.h"
#include "sys/sys.h"
#include "sys/math.h"
#include "unk.h"

#pragma intrinsic(sqrtf)

// clang-format off

// <<<<< bss >>>>>
OSMesgQueue    D_80167170;
unsigned char  D_80167188[8];
unsigned char  D_80167190[2];
unsigned char  D_80167192[2];
int            D_80167194;
unsigned char  D_80167198[8];
OSContPad      D_801671A0[4];
unsigned short D_801671B8;
unsigned short D_801671BA;
unsigned char  D_801671BC;
unsigned char  D_801671BD;
unsigned char  D_801671BE;
unsigned char  D_801671BF;
DemoKeyState  D_801671C0[4];
DemoKey       *D_801671E0[4];
OSPfs          D_801671F0[4];
unsigned char  D_80167390[0x10];

// clang-format on

void func_80004910(void)
{
    D_801671BD          = 0;
    D_801671BC          = 0;
    D_801671E0[0]       = NULL;
    D_801671E0[1]       = NULL;
    D_801671E0[2]       = NULL;
    D_801671E0[3]       = NULL;
    D_801671C0[0].index = 0;
    D_801671C0[0].time  = 0;
    D_801671C0[1].index = 0;
    D_801671C0[1].time  = 0;
    D_801671C0[2].index = 0;
    D_801671C0[2].time  = 0;
    D_801671C0[3].index = 0;
    D_801671C0[3].time  = 0;
}

void func_80004964(unsigned char arg0, DemoKey *arg1)
{
    DemoKeyState *state;

    D_801671E0[arg0] = arg1;
    state            = &D_801671C0[arg0];
    state->index     = 0;
    if (g_sys->demo_mode == 2) {
        state->time = arg1->time + 1;
    } else {
        state->time = arg1->time;
    }
    PRINTF(("demo_key_sys[key].demo_key_time = %d\n", state->time));
}

int func_800049D0(void)
{
    OSMesgQueue   queue;
    OSMesg        msg;
    short         i;
    unsigned char bitpattern;

    osCreateMesgQueue(&queue, &msg, 1);
    osSetEventMesg(OS_EVENT_SI, &queue, (OSMesg) 1);
    osContInit(&queue, &bitpattern, (OSContStatus *) D_80167190);
    osCreateMesgQueue(&D_80167170, (OSMesg *) D_80167188, 1);
    osSetEventMesg(OS_EVENT_SI, &D_80167170, 0);
    for (i = 0; i < 4; i++) {
        if ((bitpattern & (1 << i)) && !(D_80167190[i * 4 + 3] & 8)) {
            g_sys->controller[i].status = 1;
        } else {
            g_sys->controller[i].status = 0;
        }
    }
    func_80004910();
    D_801671B8 = 0;
    D_801671BA = 0;
}

#ifdef NON_MATCHING
void func_80004AF8(void)
{
    short          i;
    OSContPad     *pad;
    Controller    *ctrl;
    Controller    *game;
    DemoKeyState  *sys;
    DemoKey       *rec;
    unsigned short buttons;

    osRecvMesg(&D_80167170, NULL, OS_MESG_BLOCK);
    osContGetReadData(D_801671A0);
#ifndef JAPAN_0
    for (i = 0; i < 4; i++) {
        if (g_sys->controller[i].status == 0) {
            PRINTF(("OOOOOOOOOOOOOOOOFFFFFFFFFFFFF %d\n", i));
            D_801671A0[i].button  = 0;
            D_801671A0[i].stick_x = 0;
            D_801671A0[i].stick_y = 0;
        }
    }
#endif
    D_801671B8 = D_801671A0[0].button;
    ctrl       = g_sys_real.controller;
    game       = g_sys_real.player_controller;
    D_801671BA = D_801671A0[1].button;
    D_801671BD = D_801671BC != 0 ? 1 : 0;
    // The recording code around these prints is gone.
    PRINTF(("DEMO_KEY_START\n"));
    PRINTF(("DEMO_KEY_END\n"));
    PRINTF(("DEMO_KEY_DATA[%d] { %d, %d, %d },\n", D_801671BD, D_801671A0[0].button, D_801671A0[0].stick_x, D_801671A0[0].stick_y));
    for (i = 0; i < 4; i++, ctrl++, game++) {
        if (i != 0) {
            pad          = &D_801671A0[i];
            pad->button  = 0;
            pad->stick_x = 0;
            pad->stick_y = 0;
        }
        pad = &D_801671A0[i];
        if (D_801671E0[i] != NULL) {
            DemoKey *data = D_801671E0[i];

            sys          = &D_801671C0[i];
            rec          = &data[sys->index];
            pad->button  = rec->button;
            pad->stick_x = rec->stick_x;
            pad->stick_y = rec->stick_y;
            if (sys->time != 0) {
                if (--sys->time == 0) {
                    sys->index++;
                    sys->time = data[sys->index].time;
                }
            } else {
                D_801671E0[i] = NULL;
            }
        }
        buttons                = pad->button;
        ctrl->button_pressed   = (ctrl->button_held_down ^ buttons) & buttons;
        ctrl->button_held_down = buttons;
        ctrl->stick_raw_x      = pad->stick_x;
        ctrl->stick_raw_y      = pad->stick_y;
        if (ctrl->stick_raw_x < 0 ? (ctrl->stick_raw_x += 7) > 0 : (ctrl->stick_raw_x -= 7) < 0) {
            ctrl->stick_raw_x = 0;
        }
        if (ctrl->stick_raw_y < 0 ? (ctrl->stick_raw_y += 7) > 0 : (ctrl->stick_raw_y -= 7) < 0) {
            ctrl->stick_raw_y = 0;
        }
        if (ctrl->stick_raw_x == 0 && ctrl->stick_raw_y == 0) {
            ctrl->stick_x = ctrl->stick_y = ctrl->stick_magnitude = 0.0f;
        } else {
            ctrl->stick_x         = func_80003E10(((unsigned short) (float) ((float) -(ctrl->stick_raw_x - 180) * 1.42222222222222) - ANGLE_QUARTER) & ANGLE_MASK);
            ctrl->stick_y         = func_80003E10(((unsigned short) (float) ((float) -(ctrl->stick_raw_y - 180) * 1.42222222222222) - ANGLE_QUARTER) & ANGLE_MASK);
            ctrl->stick_magnitude = sqrtf(ctrl->stick_x * ctrl->stick_x + ctrl->stick_y * ctrl->stick_y);
        }
        if (g_sys_real.player_input_locked == 0 && g_sys_real.event_input_locked == 0) {
            *game = *ctrl;
        } else {
            if (game->stick_raw_x < 0 ? (game->stick_raw_x += 7) > 0 : (game->stick_raw_x -= 7) < 0) {
                game->stick_raw_x = 0;
            }
            if (game->stick_raw_y < 0 ? (game->stick_raw_y += 7) > 0 : (game->stick_raw_y -= 7) < 0) {
                game->stick_raw_y = 0;
            }
            if (game->stick_raw_x == 0 && game->stick_raw_y == 0) {
                game->stick_x = game->stick_y = game->stick_magnitude = 0.0f;
            } else {
                game->stick_x         = func_80003E10(((unsigned short) (float) ((float) -(game->stick_raw_x - 180) * 1.42222222222222) - ANGLE_QUARTER) & ANGLE_MASK);
                game->stick_y         = func_80003E10(((unsigned short) (float) ((float) -(game->stick_raw_y - 180) * 1.42222222222222) - ANGLE_QUARTER) & ANGLE_MASK);
                game->stick_magnitude = sqrtf(game->stick_x * game->stick_x + game->stick_y * game->stick_y);
            }
        }
    }
    g_sys_real.player_controller[4] = g_sys_real.controller[0];
}
#else
// The strings of the prints above.
const char D_8007A908[] =
    "OOOOOOOOOOOOOOOOFFFFFFFFFFFFF %d\n\0\0\0"
    "DEMO_KEY_START\n\0"
    "DEMO_KEY_END\n\0\0\0"
    "DEMO_KEY_DATA[%d] { %d, %d, %d },\n";

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/joypad/func_80004AF8.s")
#endif
