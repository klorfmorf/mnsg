#include "sys/vibration_pak.h"
#include "common.h"
#include "sys/sys.h"
#include "sys/joypad.h"

int func_80037CB0(int port, int on);
int func_80037B78(int a);

// clang-format off

// <<<<< bss >>>>>
VibrationPak D_8016DAF0[4];

// clang-format on

void func_800379D0(void)
{
    VibrationPak *pak;
    int           i;
    int           state;

    if (g_sys_real.demo_mode == 0) {
        pak = D_8016DAF0;
        for (i = 0; i != 4; i++, pak++) {
            if (pak->active != 0 && (state = pak->state) != 0) {
                switch (state) {
                    case 1:
                        if (pak->pattern & (1 << pak->bit)) {
                            func_80037CB0(i, 1);
                        } else {
                            func_80037CB0(i, 0);
                        }
                        if (pak->bit != 0) {
                            pak->bit = pak->bit - 1;
                        } else {
                            pak->bit = 0x1F;
                        }
                        pak->timer = pak->timer - 1;
                        if (pak->timer < 0 && pak->active != 0) {
                            pak->state = 2;
                        }
                        break;
                    case 3:
                        pak->active = 0;
                    case 2:
                        func_80037CB0(i, 0);
                        pak->state = 0;
                        break;
                }
            }
        }
    }
}

int func_80037B10(int arg)
{
    VibrationPak *pak = &D_8016DAF0[arg];

    pak->status   = func_80037B78(arg);
    pak->duration = 30;
    pak->state    = 0;
    return pak->status;
}

void func_80037B54(int a)
{
    func_80037C20(a, 3, 0);
}

int func_80037B78(int arg0)
{
    VibrationPak *pak;

    pak         = &D_8016DAF0[arg0];
    pak->status = osMotorInit(&D_80167170, &D_801671F0[arg0], arg0);
    if (pak->status != 0) {
        pak->active = 0;
    } else {
        func_80037C20(arg0, 2, 0);
        pak->active = 1;
    }
    return pak->status;
}

int func_80037C0C(int a)
{
    return D_8016DAF0[a].status;
}

int func_80037C20(int a, int b, int c)
{
    VibrationPak *p;

    switch (b) {
        case 1:
            p          = &D_8016DAF0[a];
            p->timer   = p->duration;
            p->state   = 1;
            p->pattern = c;
            p->bit     = 31;
            break;
        case 0:
        case 2:
        case 3:
            D_8016DAF0[a].state = b;
            break;
        default:
            PRINTF(("vpak_action: undefined action %d\n", b));
            return -1;
    }
    return 0;
}

void func_80037C9C(int a, int b)
{
    D_8016DAF0[a].duration = b;
}

int func_80037CB0(int port, int on)
{
    VibrationPak *pak;

    if (on) {
        pak         = &D_8016DAF0[port];
        pak->status = osMotorStart(&D_801671F0[port]);
    } else {
        pak         = &D_8016DAF0[port];
        pak->status = osMotorStop(&D_801671F0[port]);
    }
    if (pak->status == 0) {
        pak->retry = 0;
    } else if (pak->status == 4) {
        pak->retry++;
        if (pak->retry >= 5) {
            pak->retry = 0;
            func_80037B54(port);
        }
    } else {
        PRINTF(("motor_control: ???\n"));
    }
    return pak->status;
}
