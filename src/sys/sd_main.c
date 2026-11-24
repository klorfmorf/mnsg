#include "sys/sd_main.h"
#include "common.h"
#include "sys/bgm_tbl.h"
#include "sys/sd_sub1.h"
#include "sys/se_tbl1.h"
#include "sys/se_tbl2.h"
#include "sys/se_tbl3.h"
#include "unk.h"

ALMicroTime func_80038938(void *node);
void        func_80038A20(void);
void        func_80038C30(unsigned short a, unsigned char b, unsigned char c);
void        func_80038E20(void);
void        func_80038F68(void);
void        func_800396DC(void);
void        func_8003996C(unsigned char arg0, unsigned short arg1, unsigned char arg2);
void        func_80039A70(unsigned short *arg0, unsigned int *arg1, SoundSet *arg2, int arg3);
void        func_80039E9C(int arg0);
void        func_80039F3C(void);
void        func_80039F60(void);
void        func_80039F84(void);
void        func_8003A060(void);
void        func_8003A138(void);
void        func_8003A1C4(void);
void        func_8003A1E8(void);
void        func_8003A204(void);
void        func_8003A228(void);

// clang-format off

// <<<<< data >>>>>
unsigned int D_8006E240[8] = {
    0x0007EC20, 0x00086B10, 0x0008B400, 0x00096E70, 0x00096F80, 0x00097090, 0x000971A0, 0x000972B0,
};

unsigned int D_8006E260[8] = {
    0x00086B10, 0x0008B400, 0x00096E70, 0x00096F80, 0x00097090, 0x000971A0, 0x000972B0, 0x000973C0,
};

unsigned int D_8006E280[8] = {
    0x000973C0, 0x001AB460, 0x002537E0, 0x00550330, 0x005508D0, 0x00550E70, 0x00551410, 0x005519B0,
};

void *D_8006E2A0[3] = {
    D_80073038, D_8007477C, D_80075BD0,
};

unsigned char D_8006E2AC[4] = {
    0x00, 0x00, 0x00, 0x00,
};

// Reverb parameters: section count, total delay, then one section of
// input, output, fbcoef, ifbcoef, gain, chorus rate, chorus depth, filter coef.
int D_8006E2B0[10] = {
    1, 12000,
    0, 7160, 12000, 0, 32767, 0, 0, 0,
};

unsigned int D_8006E2D8[95] = {
    0x00551F50, 0x00552670, 0x005538F0, 0x005539F0, 0x00553BA0, 0x00553D40, 0x00554800, 0x00555450,
    0x00555EC0, 0x00556920, 0x00556AE0, 0x00557510, 0x00558060, 0x005594A0, 0x00559950, 0x00559E40,
    0x0055A3A0, 0x0055B4A0, 0x0055B8F0, 0x0055BAC0, 0x0055C2A0, 0x0055CC50, 0x0055D7A0, 0x0055DB00,
    0x0055E290, 0x0055E930, 0x0055EA40, 0x0055F1B0, 0x0055FB40, 0x00560230, 0x005605F0, 0x00560FA0,
    0x00561080, 0x00561790, 0x005618B0, 0x005619F0, 0x00561B20, 0x00562210, 0x00562D90, 0x00563820,
    0x005641F0, 0x00564930, 0x00564A50, 0x00565C70, 0x005668E0, 0x00566A30, 0x00567210, 0x00567660,
    0x00567AB0, 0x00567D40, 0x00568280, 0x005688E0, 0x00568DE0, 0x00569C40, 0x0056AC00, 0x0056ADE0,
    0x0056B8A0, 0x0056BB90, 0x0056C250, 0x0056C320, 0x0056C3C0, 0x0056C470, 0x0056C4B0, 0x0056CB60,
    0x0056D490, 0x0056E900, 0x0056ECB0, 0x0056F280, 0x0056F600, 0x0056FC10, 0x00570420, 0x005708C0,
    0x00570D50, 0x00570F60, 0x005717B0, 0x00571F90, 0x00572B10, 0x00572EC0, 0x00573160, 0x00573AE0,
    0x00573D10, 0x00573DA0, 0x00573EE0, 0x00573F90, 0x00574570, 0x00574770, 0x005747C0, 0x00574C00,
    0x005751C0, 0x005756E0, 0x00575AB0, 0x005765C0, 0x00576C70, 0x00576D10, 0x00576D40,
};

unsigned int D_8006E454[95] = {
    0x00552670, 0x005538F0, 0x005539F0, 0x00553BA0, 0x00553D40, 0x00554800, 0x00555450, 0x00555EC0,
    0x00556920, 0x00556AE0, 0x00557510, 0x00558060, 0x005594A0, 0x00559950, 0x00559E40, 0x0055A3A0,
    0x0055B4A0, 0x0055B8F0, 0x0055BAC0, 0x0055C2A0, 0x0055CC50, 0x0055D7A0, 0x0055DB00, 0x0055E290,
    0x0055E930, 0x0055EA40, 0x0055F1B0, 0x0055FB40, 0x00560230, 0x005605F0, 0x00560FA0, 0x00561080,
    0x00561790, 0x005618B0, 0x005619F0, 0x00561B20, 0x00562210, 0x00562D90, 0x00563820, 0x005641F0,
    0x00564930, 0x00564A50, 0x00565C70, 0x005668E0, 0x00566A30, 0x00567210, 0x00567660, 0x00567AB0,
    0x00567D40, 0x00568280, 0x005688E0, 0x00568DE0, 0x00569C40, 0x0056AC00, 0x0056ADE0, 0x0056B8A0,
    0x0056BB90, 0x0056C250, 0x0056C320, 0x0056C3C0, 0x0056C470, 0x0056C4B0, 0x0056CB60, 0x0056D490,
    0x0056E900, 0x0056ECB0, 0x0056F280, 0x0056F600, 0x0056FC10, 0x00570420, 0x005708C0, 0x00570D50,
    0x00570F60, 0x005717B0, 0x00571F90, 0x00572B10, 0x00572EC0, 0x00573160, 0x00573AE0, 0x00573D10,
    0x00573DA0, 0x00573EE0, 0x00573F90, 0x00574570, 0x00574770, 0x005747C0, 0x00574C00, 0x005751C0,
    0x005756E0, 0x00575AB0, 0x005765C0, 0x00576C70, 0x00576D10, 0x00576D40, 0x00576E00,
};

void *D_8006E5D0[14] = {
    func_80039D60,
    func_80039DE4,
    func_80039F3C,
    func_80039F60,
    func_80039F84,
    func_8003A060,
    func_8003A138,
    func_8003A138,
    func_8003A138,
    func_8003A138,
    func_8003A1C4,
    func_8003A1E8,
    func_8003A204,
    func_8003A228,
};

// Indexed by 7..10 (see func_8003A138).
unsigned char D_8006E608[4] = {
    1, 2, 8, 8,
};

// <<<<< bss >>>>>
unsigned char  D_80172970;
unsigned char  D_80172971;
unsigned char  D_80172972[2];
unsigned short D_80172974;
short          D_80172976;
unsigned short D_80172978[4];
unsigned char  D_80172980[24];
unsigned char  D_80172998[16];
ALBankFile    *D_801729A8[8];
unsigned char  D_801729C8[0x4E000];
unsigned char  D_801C09C8;
unsigned char  D_801C09C9;
unsigned short D_801C09CA;
unsigned char  D_801C09CC;
unsigned char  D_801C09CD;
signed char    D_801C09CE;
unsigned char  D_801C09CF;
unsigned char  D_801C09D0;
unsigned char  D_801C09D1;
unsigned char  D_801C09D2;
unsigned char  D_801C09D3;
unsigned char  D_801C09D4;
unsigned char  D_801C09D5;
unsigned char  D_801C09D6[2];
unsigned short D_801C09D8;
unsigned char  D_801C09DA;
signed char    D_801C09DB;
unsigned char  D_801C09DC[4];
unsigned char  D_801C09E0[8];
unsigned short D_801C09E8;
unsigned short D_801C09EA;
unsigned short D_801C09EC;
unsigned short D_801C09EE;
unsigned short D_801C09F0[6];
unsigned char  D_801C09FC[4];
int            D_801C0A00[8];
int            D_801C0A20;
unsigned short D_801C0A24;
unsigned char  D_801C0A26[2];
unsigned char  D_801C0A28[64];
ALVoice        D_801C0A68[16];
SoundWork      D_801C0C28[16];
SoundWork     *sptr;
unsigned char *mptr;
unsigned char  D_801C1730[0x6000];
int            D_801C7730[4];

// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_800386E0.s")

#ifdef NON_MATCHING
void func_8003889C(ALPlayer *player)
{
    D_801C09C8    = 6;
    D_801C09FC[1] = D_801C09CD = D_801C09D0 = 0;
    D_801C09FC[0]                           = 0;
    D_801C09CA                              = D_801C09FC[0];
    D_801C09CE                              = 0;
    D_801C09CF                              = D_801C09CE;
    player->next                            = NULL;
    player->handler                         = func_80038938;
    player->clientData                      = player;
    alSynAddPlayer(D_8007A230, player);
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_8003889C.s")
#endif

ALMicroTime func_80038938(void *node)
{
    if (D_801C09C8 != 0) {
        if (D_801C09C8 == 6) {
            func_80038A20();
        }
        D_801C09C8--;
    } else {
        if (D_801C0A24 != 0) {
            func_800396DC();
        }
        if (D_80172974 != 0) {
            func_80038E20();
        }
        if (D_801C09C9 == 0) {
            func_80038F68();
        }
        func_8003A370();
        D_801C09CA++;
        if (D_80172971 != 0) {
            D_80172971 = 0;
            func_8003996C(1, D_80172970, 0);
        }
    }
    return 5000;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_80038A20.s")

void func_80038B98(unsigned short arg0)
{
    func_80038C30(arg0, 0, 0);
}

void func_80038BC8(unsigned short arg0)
{
    func_80038C30(arg0, 0, 0);
}

void func_80038BF8(unsigned short arg0, unsigned char arg1)
{
    func_80038C30(arg0, arg1, 0);
}

#ifdef NON_MATCHING
void func_80038C30(unsigned short a, unsigned char b, unsigned char c)
{
    int  v;
    int  n;
    int  i;
    int *p;

    if (a != 0) {
        D_801C09C9 = 0xFF;
        if (b == 0 || b >= 0x80) {
            v = a;
        } else {
            v = a + (b << 16);
        }
        if (c != 0) {
            v |= c << 24;
        }
        n = D_801C09FC[1];
        if (n < 8) {
            if (n != 0) {
                i = 0;
                p = D_801C0A00;
                do {
                    i++;
                    if (a == (*p & 0xFFFF)) {
                        D_801C09C9 = 0;
                        return;
                    }
                    p++;
                } while (i < n);
            }
            D_801C0A00[D_801C09FC[1]] = v;
            D_801C09FC[1]++;
        }
        D_801C09C9 = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_80038C30.s")
#endif

void func_80038D14(void)
{
    func_80038C30(0xF0, 0, 0);
}

void func_80038D3C(void)
{
    func_80038C30(0xF1, 0, 0);
}

void func_80038D64(void)
{
    if (D_801C0A20 == 0xF0) {
        D_80172972[0] = 1;
    } else {
        D_80172972[0] = 0;
    }
}

#ifdef NON_MATCHING
void func_80038D94(unsigned short a0, unsigned short a1, unsigned char a2)
{
    if (!a1) {
        a1++;
    } else if (a1 > 0x100) {
        a1 = 0x100;
    }
    if (a2 < 0) {
        a2 = 0;
    } else if (a2 > 0x7F) {
        a2 = 0x7F;
    }
    D_80172974    = a0;
    D_80172976    = a1;
    D_80172978[0] = a2 << 8;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_80038D94.s")
#endif

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_80038E20.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_80038F68.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_800390D8.s")

#ifdef NON_MATCHING
int func_80039440(unsigned char arg0)
{
    SoundWork    *w = D_801C0C28;
    unsigned char i;
    unsigned char best;
    unsigned char ret = 0xE;

    if (arg0 == 1) {
        ret  = 0xA;
        best = D_801C0C28[10].unk_04;
        for (i = 0xB; i < 0x10; i++) {
            if (best >= w[i].unk_04) {
                ret  = i;
                best = w[i].unk_04;
            }
        }
    } else {
        best = 0xFF;
        for (i = 0xE; i >= 0xA; i -= 2) {
            unsigned char k = (w[i].unk_04 < w[i + 1].unk_04) ? i + 1 : i;

            if (best >= w[k].unk_04) {
                ret  = i;
                best = w[k].unk_04;
            }
        }
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_80039440.s")
#endif

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_80039554.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_800396DC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_800397B8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_8003987C.s")

#ifdef NON_MATCHING
void func_8003996C(unsigned char arg0, unsigned short arg1, unsigned char arg2)
{
    SoundSet       *set   = (SoundSet *) D_801C09F0;
    unsigned int   *table = (unsigned int *) D_801C0A28;
    unsigned char  *entry;
    unsigned short *base;
    int             count;
    int             i;

    D_80172970 = arg1;
    if (arg0 == 0 && D_801C0C28[0].unk_00 != 0) {
        return;
    }
    entry = &D_8006F14C[(unsigned short) (arg1 - 0x10) * 4];
    count = entry[0];
    base  = (unsigned short *) (D_801C1730 + entry[3] * 0x1800);

    set->unk_00 = entry[0];
    set->unk_03 = entry[1];
    set->unk_08 = table;
    for (i = 0; i < count; i++) {
        table[i] = base[i] + (unsigned int) base;
    }
    D_801C0A20  = arg1;
    set->unk_01 = 0;
    set->unk_02 = 0x1E;
    set->unk_04 = arg2;
    func_80039A70(base, table, set, count);
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_8003996C.s")
#endif

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_80039A70.s")

#ifdef NON_MATCHING
void func_80039D60(void)
{
    int *p;
    int  i;

    D_801C09D6[0] = 0;
    p             = D_801C0C28;
    do {
        p += 44;
        p[-44] = 0x10;
    } while ((unsigned int) p < (unsigned int) &sptr);
    func_80039DE4();
    D_801C09EA = 0;
    D_801C09EC = 0;
    D_801C09EE = 0;
    D_801C09E8 = 0;
    for (i = 0; i < 4; i++) {
        D_801C09E0[i] = 0;
    }
    D_80172972[0] = 0;
    D_80172974    = 0;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_80039D60.s")
#endif

#ifdef NON_MATCHING
void func_80039DE4(void)
{
    int i;

    D_80172971    = 0;
    D_801C0A24    = 0;
    D_801C0A26[0] = 0;
    D_801C09DC[0] = D_801C09D3 = D_801C09DA = D_801C09D8 = 0;
    D_801C09DB                                           = 0;
    for (i = 0; i < 16; i++) {
        unsigned int id = D_801C0C28[i].unk_00 & 0x7FFF;

        if (id >= 0x10 && id < 0x100) {
            func_80039E9C(i);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_80039DE4.s")
#endif

void func_80039E9C(int arg0)
{
    sptr         = (SoundWork *) D_801C0C28 + arg0;
    sptr->unk_00 = 0;
    sptr->unk_04 = 0;
    if (sptr->unk_0e != 0) {
        sptr->unk_0f = 2;
        alSynSetVol(D_8007A230, &D_801C0A68[arg0], 0, 0x1388);
    }
}

void func_80039F3C(void)
{
    if (D_801C09CF != 0xA0) {
        D_801C09CE = -1;
    }
}

void func_80039F60(void)
{
    if (D_801C09CF != 0) {
        D_801C09CE = 1;
    }
}

void func_80039F84(void)
{
    int        i;
    SoundWork *p;
    SoundWork *q;

    if (D_801C09D0 != 0) {
        D_801C09D0 = 0;
        for (i = 0, p = (SoundWork *) D_801C0C28; i < 16; i++, p++) {
            q = sptr = p;
            if (p->unk_00 != 0) {
                q->unk_06 |= 1;
                alSynSetPan(D_8007A230, &D_801C0A68[i], (sptr->unk_58 >> 8) & 0x7F);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_8003A060.s")

void func_8003A138(void)
{
    if (D_801C0A20 != 10) {
        if (D_801C09D3 == 0) {
            D_801C09D3 = 0xFF;
        }
        D_801C09D2 = D_801C09D1 = D_8006E608[D_801C0A20 - 7];
        return;
    }
    if (D_801C09D6[0] == 0) {
        D_801C09D6[0] = 0xFF;
    }
    D_801C09D5 = D_801C09D4 = D_8006E608[D_801C0A20 - 7];
}

void func_8003A1C4(void)
{
    if (D_801C09D8 < 0x100) {
        D_801C09DA = 0xC;
    }
}

void func_8003A1E8(void)
{
    D_801C09DA = D_801C09D8 = 0;
}

void func_8003A204(void)
{
    if (D_801C09DC[0] == 0) {
        D_801C09DB = -1;
    }
}

void func_8003A228(void)
{
    if (D_801C09DC[0] != 0) {
        D_801C09DB = 1;
    }
}

void func_8003A24C(void)
{
    unsigned short *p = &D_801C09E8;
    int             i;

    D_801C0A20 &= 0x7FFF;
    for (i = 0; i < 4; i++) {
        if (D_801C0A20 == p[i]) {
            return;
        }
    }
    for (i = 0; 1;) {
        if (p[i] == 0) {
            p[i]          = D_801C0A20;
            D_801C09E0[i] = 0xFF;
            return;
        }
        i++;
        if (i >= 4) {
            break;
        }
    }
}

#ifdef NON_MATCHING
void func_8003A2D0(unsigned short arg0)
{
    int             i;
    unsigned short *s;

    s = &(&D_801C09E8)[arg0];
    for (i = 0; i < 16; i++) {
        if (*s == D_801C0C28[i].unk_00) {
            func_80039E9C(i);
        }
    }
    D_801C09E0[arg0] = 0;
    *s               = D_801C09E0[arg0];
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_main/func_8003A2D0.s")
#endif
