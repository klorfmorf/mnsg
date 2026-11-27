#include "sys/sd_sub1.h"
#include "common.h"
#include "sys/sd_main.h"
#include "sys/sd_vars.h"
#include "sys/sd_sub2.h"
#include "unk.h"

void func_8003A71C(void);
void func_8003A838(void);
void func_8003AC0C(void);
void func_8003AE04(void);
void func_8003AEB0(void);
void func_8003B1BC(void);
void func_8003B248(void);
void func_8003B2B4(void);
void func_8003B304(void);
void func_8003B348(void);

// clang-format off

// <<<<< data >>>>>
void *D_8006E610[48] = {
    func_8003B410,
    func_8003B450,
    func_8003B564,
    func_8003B7E4,
    func_8003B80C,
    func_8003B83C,
    func_8003B89C,
    func_8003B9B8,
    func_8003BA40,
    func_8003BB00,
    func_8003BB70,
    func_8003CF24,
    func_8003CF24,
    func_8003BCAC,
    func_8003BD68,
    func_8003BED4,
    func_8003BF08,
    func_8003BF3C,
    func_8003C2B4,
    func_8003C328,
    func_8003C47C,
    func_8003C720,
    func_8003C820,
    func_8003C934,
    func_8003C970,
    func_8003CA30,
    func_8003CA6C,
    func_8003CB2C,
    func_8003CB48,
    func_8003CB64,
    func_8003CB8C,
    func_8003CC18,
    func_8003CCCC,
    func_8003CCFC,
    func_8003CD84,
    func_8003CE2C,
    func_8003CF24,
    func_8003CF24,
    func_8003CF24,
    func_8003CF24,
    func_8003CF24,
    func_8003CF24,
    func_8003CF24,
    func_8003CF24,
    func_8003CF24,
    func_8003CF24,
    func_8003CF24,
    func_8003CF24,
};

float D_8006E6D0[76] = {
    0.03125f, 0.03310822f, 0.03507694f, 0.037162717f, 0.03937253f, 0.04171372f,
    0.044194154f, 0.046822064f, 0.04960625f, 0.052555967f, 0.055681124f, 0.058992095f,
    0.0625f, 0.06621644f, 0.07015388f, 0.074325435f, 0.07874506f, 0.08342744f,
    0.08838831f, 0.09364413f, 0.0992125f, 0.105111934f, 0.11136225f, 0.11798419f,
    0.125f, 0.13243288f, 0.14030775f, 0.14865087f, 0.15749012f, 0.16685487f,
    0.17677662f, 0.18728825f, 0.198425f, 0.21022387f, 0.2227245f, 0.23596838f,
    0.25f, 0.26486576f, 0.2806155f, 0.29730174f, 0.31498024f, 0.33370975f,
    0.35355324f, 0.3745765f, 0.39685f, 0.42044774f, 0.445449f, 0.47193676f,
    0.5f, 0.5297315f, 0.561231f, 0.5946035f, 0.6299605f, 0.6674195f,
    0.7071065f, 0.749153f, 0.7937f, 0.8408955f, 0.890898f, 0.9438735f,
    1.0f, 1.059463f, 1.122462f, 1.189207f, 1.259921f, 1.334839f,
    1.414213f, 1.498306f, 1.5874f, 1.681791f, 1.781796f, 1.887747f,
    2.0f, 2.0f, 0.0f, 0.0f,
};

// clang-format on

void func_8003A370(void)
{
    int i;

    if (D_801C09CE != 0 && !(D_801C09CA & 1)) {
        D_801C09CF += D_801C09CE;
        if (D_801C09CF == 0xA0 || D_801C09CF == 0) {
            D_801C09CE = 0;
        }
    }
    if (D_801C09D6[0] != 0 && D_801C09CD == 0 && !(D_801C09CA & 3)) {
        D_801C09D5--;
        if (D_801C09D5 == 0) {
            D_801C09D5 = D_801C09D4;
            D_801C09D6[0] -= 4;
            if (D_801C09D6[0] < 0x10) {
                func_80039D60();
            }
        }
    }
    if (D_801C09D3 != 0 && D_801C09CD == 0 && !(D_801C09CA & 3)) {
        D_801C09D2--;
        if (D_801C09D2 == 0) {
            D_801C09D2 = D_801C09D1;
            D_801C09D3 -= 4;
            if (D_801C09D3 < 0x10) {
                func_80039DE4();
            }
        }
    }
    if (D_801C09CD == 0 && !(D_801C09CA & 1)) {
        for (i = 0; i < 4; i++) {
            if (D_801C09E8[i] != 0) {
                D_801C09E0[i] -= 3;
                if (D_801C09E0[i] < 0x10) {
                    func_8003A2D0(i);
                }
            }
        }
    }
    if (D_801C09DA != 0 && D_801C09CD == 0 && !(D_801C09CA & 7)) {
        D_801C09DA--;
        D_801C09D8++;
    }
    if (D_801C09DB != 0 && !(D_801C09CA & 1)) {
        D_801C09DC[0] += D_801C09DB;
        if (D_801C09DC[0] == 0xD0 || D_801C09DC[0] == 0) {
            D_801C09DB = 0;
        }
    }
    for (D_801C09CC = 0; D_801C09CC < 0x10; D_801C09CC++) {
        sptr = D_801C0C28 + D_801C09CC;
        if (sptr->stop_cnt != 0) {
            sptr->stop_cnt--;
            if (sptr->stop_cnt == 0 && sptr->voice_on != 0) {
                sptr->voice_on = 0;
                alSynStopVoice(D_8007A230, &D_801C0A68[D_801C09CC]);
            }
        }
        if (sptr->code != 0) {
            if (sptr->delay != 0) {
                sptr->delay--;
            } else if ((sptr->code & 0x7FFF) < 0x100) {
                if (D_801C09CD == 0) {
                    sptr->tmpd += D_801C09D8;
                    func_8003A71C();
                }
            } else {
                func_8003A71C();
            }
        }
    }
}

void func_8003A71C(void)
{
    sptr->tmpd += sptr->tmp >> 8;
    if (sptr->tmpd >= 0x100) {
        sptr->tmpd &= 0xFF;
        sptr->ngc--;
        if (sptr->ngc == 0) {
            func_8003A838();
            func_8003C540();
        } else {
            func_8003AC0C();
        }
        if (sptr->tmpc != 0) {
            func_8003B4EC();
        }
        if (sptr->pvoc != 0) {
            func_8003B938();
        }
        if (sptr->panc != 0) {
            func_8003BE24();
        }
    } else {
        func_8003AE04();
    }
    if (sptr->rdms != 0) {
        func_8003C3C0();
    }
}

void func_8003A838(void)
{
    unsigned char cmd;
    unsigned char tie;

    tie = 0;
    if (sptr->ngg == 0) {
        tie = 1;
    } else if (sptr->voice_on != 0) {
        sptr->stop_cnt = 0;
        sptr->voice_on = 0;
        alSynStopVoice(D_8007A230, &D_801C0A68[D_801C09CC]);
    }
    mptr = sptr->mpointer;
    cmd  = *mptr++;
    while (cmd >= 0xD0) {
        ((void (*)()) D_8006E610[cmd - 0xD0])();
        if (cmd >= 0xF2) {
            return;
        }
        cmd = *mptr++;
    }
    sptr->swpad = sptr->swpd;
    if (cmd < 0x68) {
        sptr->note = cmd;
    } else {
        sptr->note = cmd - 0x68;
    }
    if (sptr->note >= 0x48) {
        if (sptr->note == 0x67) {
            sptr->note = *mptr;
            mptr++;
        }
        sptr->flags |= 4;
        func_8003B79C();
        sptr->note = 0x3C;
    } else {
        sptr->flags &= 0xFB;
    }
    sptr->swpd = sptr->note << 8;
    sptr->swpd += sptr->tone_tune;
    sptr->swpd += sptr->ptps;
    sptr->swpd += sptr->tund;
    sptr->swpd += sptr->lp1_freq;
    sptr->swpd += sptr->lp2_freq;
    if (cmd < 0x68) {
        sptr->ngs = *mptr;
        mptr++;
    }
    sptr->ngc = sptr->ngs;
    cmd       = *mptr++;
    if (cmd < 0x80) {
        sptr->last_ngg = cmd;
        cmd            = *mptr++;
    }
    sptr->ngg = sptr->last_ngg;
    if (sptr->ngg == 0) {
        sptr->ngo = 0;
    } else {
        sptr->ngo = (sptr->ngc * sptr->ngg) >> 7;
        if (sptr->ngo == 0) {
            sptr->ngo = 1;
        }
    }
    sptr->vol      = cmd & 0x7F;
    sptr->mpointer = mptr;
    if (sptr->swss == 0) {
        sptr->swpc = 0;
    } else {
        func_8003C790();
    }
    sptr->vib_data = 0;
    if (sptr->vibdm != 0) {
        func_8003C0AC();
    }
    if (sptr->mute == 0) {
        func_8003AEB0();
        if (tie == 0) {
            sptr->last_vol[1] = 0xFFFF;
            func_8003B1BC();
            sptr->voice_on = 1;
            alSynStartVoice(D_8007A230, &D_801C0A68[D_801C09CC], sptr->wavetable);
        } else if (sptr->env_time != 0) {
            func_8003B394();
            if (sptr->env_time != 0) {
                func_8003AFB0();
            }
        } else {
            func_8003AFB0();
        }
    }
}

void func_8003AC0C(void)
{
    unsigned char ticks;

    if (sptr->swpc != 0) {
        func_8003C620();
    }
    if (sptr->vibdm != 0) {
        func_8003C108();
    }
    if (sptr->flags & 2) {
        func_8003AEB0();
    }
    if (sptr->ngg != 0 && sptr->ngc == 1) {
        func_8003B348();
        return;
    }
    ticks = sptr->ngo;
    if (ticks != 0) {
        sptr->ngo = ticks - 1;
        if (sptr->ngo == 0) {
            func_8003B304();
            return;
        }
    }
    if (sptr->env_time != 0) {
        func_8003B394();
    }
    if (sptr->flags & 1) {
        func_8003AFB0();
        return;
    }
    func_8003AD28();
}

void func_8003AD28(void)
{
    unsigned int id;
    int          i;

    if (D_801C09CE != 0) {
        func_8003AFB0();
        return;
    }
    if (D_801C09D6[0] != 0) {
        func_8003AFB0();
        return;
    }
    id = sptr->code & 0x7FFF;
    if (id < 0x100 && (D_801C09D3 != 0 || D_801C09DB != 0)) {
        func_8003AFB0();
        return;
    }
    for (i = 0; i < 4; i++) {
        if (id == D_801C09E8[i]) {
            func_8003AFB0();
            return;
        }
    }
}

void func_8003AE04(void)
{
    if (sptr->swpc != 0) {
        func_8003C6B8();
    }
    if (sptr->vibdm != 0) {
        func_8003C184();
    }
    if (sptr->flags & 2) {
        func_8003AEB0();
    }
    if (sptr->env_time != 0) {
        func_8003B394();
    }
    if (sptr->flags & 1) {
        func_8003AFB0();
    }
}

void func_8003AEB0(void)
{
    int            note;
    unsigned short frac;
    float          pitch;

    sptr->flags &= 0xFD;
    note = sptr->swpd + sptr->rdm_data + sptr->vib_data;
    if (note < 0) {
        note = 0;
    } else if (note > 0x4800) {
        note = 0x4800;
    }
    frac = note & 0xFF;
    note >>= 8;
    pitch = D_8006E6D0[note + 1] - D_8006E6D0[note];
    pitch = frac * pitch / 256;
    pitch += D_8006E6D0[note];
    if (pitch != sptr->pitch) {
        sptr->pitch = pitch;
        alSynSetPitch(D_8007A230, D_801C0A68 + D_801C09CC, pitch);
    }
}

void func_8003AFB0(void)
{
    int             vol;
    unsigned int    id;
    int             i;
    unsigned short *slot;

    slot = D_801C09E8;
    sptr->flags &= 0xFE;
    vol = sptr->vol + sptr->lp1_vol + sptr->lp2_vol;
    vol *= sptr->pvod;
    if (vol >= 0x800000) {
        vol = 0x7FFF;
    } else if (vol < 0) {
        vol = 0;
    } else {
        vol >>= 8;
    }
    vol = (sptr->env_vol * vol) >> 8;
    if (sptr->vol_scale != 0) {
        vol = (sptr->vol_scale * vol) >> 8;
    }
    if (D_801C09D6[0] != 0) {
        vol = (D_801C09D6[0] * vol) >> 8;
    }
    id = sptr->code & 0x7FFF;
    if (id < 0x100) {
        if (D_801C09D3 != 0) {
            vol = (D_801C09D3 * vol) >> 8;
        }
        if (D_801C09DC[0] != 0) {
            vol = (D_801C09DC[0] * vol) >> 8;
        }
    }
    if (D_801C09CF != 0) {
        vol = (D_801C09CF * vol) >> 8;
    }
    for (i = 0; i < 4; i++) {
        if (id == slot[i]) {
            vol = (D_801C09E0[i] * vol) >> 8;
            break;
        }
    }
    if ((short) sptr->last_vol[0] != vol || sptr->last_vol[1] != sptr->env_time) {
        sptr->last_vol[0] = vol;
        sptr->last_vol[1] = sptr->env_time;
        alSynSetVol(D_8007A230, &D_801C0A68[D_801C09CC], (unsigned short) vol, sptr->env_time * 5000);
    }
}

void func_8003B1BC(void)
{
    sptr->env_time = 0;
    if (sptr->ar != 0) {
        sptr->env_vol = 0x20;
        func_8003AFB0();
        sptr->env_step = 0;
        sptr->env_vol  = 0x100;
        sptr->env_time = sptr->ar;
        func_8003AFB0();
        return;
    }
    sptr->env_vol = 0x100;
    func_8003AFB0();
    func_8003B248();
}

void func_8003B248(void)
{
    if (sptr->sl != 0) {
        sptr->env_step = 1;
        sptr->env_vol -= sptr->sl;
        sptr->env_time = sptr->dr;
        func_8003AFB0();
    } else {
        func_8003B2B4();
    }
}

void func_8003B2B4(void)
{
    sptr->env_step = 2;
    if (sptr->sr != 0) {
        sptr->env_vol  = 0;
        sptr->env_time = sptr->sr;
        func_8003AFB0();
    }
}

void func_8003B304(void)
{
    sptr->env_step = 3;
    sptr->env_vol  = 0;
    sptr->env_time = sptr->rr;
    func_8003AFB0();
}

void func_8003B348(void)
{
    sptr->stop_cnt = 1;
    sptr->env_step = 3;
    sptr->env_vol  = 0;
    sptr->env_time = 1;
    func_8003AFB0();
}

void func_8003B394(void)
{
    sptr->env_time--;
    if (sptr->env_time == 0) {
        switch (sptr->env_step) {
            case 0:
                func_8003B248();
                break;
            case 1:
                func_8003B2B4();
                break;
        }
    }
}
