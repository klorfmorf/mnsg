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
void func_8003B410();
void func_8003B450();
void func_8003B564();
void func_8003B7E4();
void func_8003B80C();
void func_8003B83C();
void func_8003B89C();
void func_8003B9B8();
void func_8003BA40();
void func_8003BB00();
void func_8003BB70();
void func_8003BCAC();
void func_8003BD68();
void func_8003BED4();
void func_8003BF08();
void func_8003BF3C();
void func_8003C2B4();
void func_8003C328();
void func_8003C47C();
void func_8003C720();
void func_8003C820();
void func_8003C934();
void func_8003C970();
void func_8003CA30();
void func_8003CA6C();
void func_8003CB2C();
void func_8003CB48();
void func_8003CB64();
void func_8003CB8C();
void func_8003CC18();
void func_8003CCCC();
void func_8003CCFC();
void func_8003CD84();
void func_8003CE2C();
void func_8003CF24();

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
            if ((&D_801C09E8)[i] != 0) {
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
        sptr = (SoundWork *) D_801C0C28 + D_801C09CC;
        if (sptr->unk_0f != 0) {
            sptr->unk_0f--;
            if (sptr->unk_0f == 0 && sptr->unk_0e != 0) {
                sptr->unk_0e = 0;
                alSynStopVoice(D_8007A230, &D_801C0A68[D_801C09CC]);
            }
        }
        if (sptr->unk_00 != 0) {
            if (sptr->unk_05 != 0) {
                sptr->unk_05--;
            } else if ((sptr->unk_00 & 0x7FFF) < 0x100) {
                if (D_801C09CD == 0) {
                    sptr->unk_1a += D_801C09D8;
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
    sptr->unk_1a += sptr->unk_18 >> 8;
    if (sptr->unk_1a >= 0x100) {
        sptr->unk_1a &= 0xFF;
        sptr->unk_21--;
        if (sptr->unk_21 == 0) {
            func_8003A838();
            func_8003C540();
        } else {
            func_8003AC0C();
        }
        if (sptr->unk_1d != 0) {
            func_8003B4EC();
        }
        if (sptr->unk_47 != 0) {
            func_8003B938();
        }
        if (sptr->unk_5b != 0) {
            func_8003BE24();
        }
    } else {
        func_8003AE04();
    }
    if (sptr->unk_92 != 0) {
        func_8003C3C0();
    }
}

void func_8003A838(void)
{
    unsigned char cmd;
    unsigned char tie;

    tie = 0;
    if (sptr->unk_22 == 0) {
        tie = 1;
    } else if (sptr->unk_0e != 0) {
        sptr->unk_0f = 0;
        sptr->unk_0e = 0;
        alSynStopVoice(D_8007A230, &D_801C0A68[D_801C09CC]);
    }
    mptr = sptr->unk_08;
    cmd  = *mptr++;
    while (cmd >= 0xD0) {
        ((void (*)()) D_8006E610[cmd - 0xD0])();
        if (cmd >= 0xF2) {
            return;
        }
        cmd = *mptr++;
    }
    sptr->unk_84 = sptr->unk_28;
    if (cmd < 0x68) {
        sptr->unk_25 = cmd;
    } else {
        sptr->unk_25 = cmd - 0x68;
    }
    if (sptr->unk_25 >= 0x48) {
        if (sptr->unk_25 == 0x67) {
            sptr->unk_25 = *mptr;
            mptr++;
        }
        sptr->unk_06 |= 4;
        func_8003B79C();
        sptr->unk_25 = 0x3C;
    } else {
        sptr->unk_06 &= 0xFB;
    }
    sptr->unk_28 = sptr->unk_25 << 8;
    sptr->unk_28 += sptr->unk_2c;
    sptr->unk_28 += sptr->unk_2e;
    sptr->unk_28 += sptr->unk_30;
    sptr->unk_28 += sptr->unk_32;
    sptr->unk_28 += sptr->unk_34;
    if (cmd < 0x68) {
        sptr->unk_20 = *mptr;
        mptr++;
    }
    sptr->unk_21 = sptr->unk_20;
    cmd          = *mptr++;
    if (cmd < 0x80) {
        sptr->unk_23 = cmd;
        cmd          = *mptr++;
    }
    sptr->unk_22 = sptr->unk_23;
    if (sptr->unk_22 == 0) {
        sptr->unk_24 = 0;
    } else {
        sptr->unk_24 = (sptr->unk_21 * sptr->unk_22) >> 7;
        if (sptr->unk_24 == 0) {
            sptr->unk_24 = 1;
        }
    }
    sptr->unk_48 = cmd & 0x7F;
    sptr->unk_08 = mptr;
    if (sptr->unk_8a == 0) {
        sptr->unk_7d = 0;
    } else {
        func_8003C790();
    }
    sptr->unk_36 = 0;
    if (sptr->unk_9a != 0) {
        func_8003C0AC();
    }
    if (sptr->unk_ac == 0) {
        func_8003AEB0();
        if (tie == 0) {
            sptr->unk_a8[1] = 0xFFFF;
            func_8003B1BC();
            sptr->unk_0e = 1;
            alSynStartVoice(D_8007A230, &D_801C0A68[D_801C09CC], sptr->unk_14);
        } else if (sptr->unk_4c != 0) {
            func_8003B394();
            if (sptr->unk_4c != 0) {
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

    if (sptr->unk_7d != 0) {
        func_8003C620();
    }
    if (sptr->unk_9a != 0) {
        func_8003C108();
    }
    if (sptr->unk_06 & 2) {
        func_8003AEB0();
    }
    if (sptr->unk_22 != 0 && sptr->unk_21 == 1) {
        func_8003B348();
        return;
    }
    ticks = sptr->unk_24;
    if (ticks != 0) {
        sptr->unk_24 = ticks - 1;
        if (sptr->unk_24 == 0) {
            func_8003B304();
            return;
        }
    }
    if (sptr->unk_4c != 0) {
        func_8003B394();
    }
    if (sptr->unk_06 & 1) {
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
    id = sptr->unk_00 & 0x7FFF;
    if (id < 0x100 && (D_801C09D3 != 0 || D_801C09DB != 0)) {
        func_8003AFB0();
        return;
    }
    for (i = 0; i < 4; i++) {
        if (id == (&D_801C09E8)[i]) {
            func_8003AFB0();
            return;
        }
    }
}

void func_8003AE04(void)
{
    if (sptr->unk_7d != 0) {
        func_8003C6B8();
    }
    if (sptr->unk_9a != 0) {
        func_8003C184();
    }
    if (sptr->unk_06 & 2) {
        func_8003AEB0();
    }
    if (sptr->unk_4c != 0) {
        func_8003B394();
    }
    if (sptr->unk_06 & 1) {
        func_8003AFB0();
    }
}

void func_8003AEB0(void)
{
    int            note;
    unsigned short frac;
    float          pitch;

    sptr->unk_06 &= 0xFD;
    note = sptr->unk_28 + sptr->unk_38 + sptr->unk_36;
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
    if (pitch != sptr->unk_a4) {
        sptr->unk_a4 = pitch;
        alSynSetPitch(D_8007A230, D_801C0A68 + D_801C09CC, pitch);
    }
}

void func_8003AFB0(void)
{
    int             vol;
    unsigned int    id;
    int             i;
    unsigned short *slot;

    slot = &D_801C09E8;
    sptr->unk_06 &= 0xFE;
    vol = sptr->unk_48 + sptr->unk_40 + sptr->unk_42;
    vol *= sptr->unk_3a;
    if (vol >= 0x800000) {
        vol = 0x7FFF;
    } else if (vol < 0) {
        vol = 0;
    } else {
        vol >>= 8;
    }
    vol = (sptr->unk_4a * vol) >> 8;
    if (sptr->unk_ae != 0) {
        vol = (sptr->unk_ae * vol) >> 8;
    }
    if (D_801C09D6[0] != 0) {
        vol = (D_801C09D6[0] * vol) >> 8;
    }
    id = sptr->unk_00 & 0x7FFF;
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
    if ((short) sptr->unk_a8[0] != vol || sptr->unk_a8[1] != sptr->unk_4c) {
        sptr->unk_a8[0] = vol;
        sptr->unk_a8[1] = sptr->unk_4c;
        alSynSetVol(D_8007A230, &D_801C0A68[D_801C09CC], (unsigned short) vol, sptr->unk_4c * 5000);
    }
}

void func_8003B1BC(void)
{
    sptr->unk_4c = 0;
    if (sptr->unk_4e != 0) {
        sptr->unk_4a = 0x20;
        func_8003AFB0();
        sptr->unk_49 = 0;
        sptr->unk_4a = 0x100;
        sptr->unk_4c = sptr->unk_4e;
        func_8003AFB0();
        return;
    }
    sptr->unk_4a = 0x100;
    func_8003AFB0();
    func_8003B248();
}

void func_8003B248(void)
{
    if (sptr->unk_54 != 0) {
        sptr->unk_49 = 1;
        sptr->unk_4a -= sptr->unk_54;
        sptr->unk_4c = sptr->unk_50;
        func_8003AFB0();
    } else {
        func_8003B2B4();
    }
}

void func_8003B2B4(void)
{
    sptr->unk_49 = 2;
    if (sptr->unk_52 != 0) {
        sptr->unk_4a = 0;
        sptr->unk_4c = sptr->unk_52;
        func_8003AFB0();
    }
}

void func_8003B304(void)
{
    sptr->unk_49 = 3;
    sptr->unk_4a = 0;
    sptr->unk_4c = sptr->unk_56;
    func_8003AFB0();
}

void func_8003B348(void)
{
    sptr->unk_0f = 1;
    sptr->unk_49 = 3;
    sptr->unk_4a = 0;
    sptr->unk_4c = 1;
    func_8003AFB0();
}

void func_8003B394(void)
{
    sptr->unk_4c--;
    if (sptr->unk_4c == 0) {
        switch (sptr->unk_49) {
            case 0:
                func_8003B248();
                break;
            case 1:
                func_8003B2B4();
                break;
        }
    }
}
