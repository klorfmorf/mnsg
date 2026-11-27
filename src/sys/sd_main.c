#include "sys/sd_main.h"
#include "common.h"
#include "unk.h"
#include "sys/sd_sub1.h"
#include "sys/se_tbl1.h"
#include "sys/se_tbl2.h"
#include "sys/se_tbl3.h"
#include "sys/sys.h"
#include "sys/rom_decode.h"
#include "sys/audiomgr.h"
#include "sys/bgm_tbl.h"
#include "sys/demo.h"
#include "sys/main.h"

ALMicroTime   func_80038938(void *node);
void          func_80038A20(void);
void          func_8003889C(ALPlayer *player);
unsigned char func_80039440(unsigned char kind);
void          func_80038E20(void);
void          func_80038F68(void);
void          func_800396DC(void);
void          func_8003996C(unsigned char arg0, unsigned short arg1, unsigned char arg2);
void          func_80039A70(void);
void          func_80039E9C(int arg0);
void          func_80039F3C(void);
void          func_80039F60(void);
void          func_80039F84(void);
void          func_8003A060(void);
void          func_8003A138(void);
void          func_8003A1C4(void);
void          func_8003A1E8(void);
void          func_8003A204(void);
void          func_8003A228(void);
void          func_8003987C(void);
void          func_800397B8(unsigned short, unsigned char);
void          func_80039554(void);
void          func_800390D8(void);
void          func_8003A24C(void);

// clang-format off

// <<<<< data >>>>>
unsigned int D_8006E240[8] = {
    0x0007EC20, 0x00086B10, 0x0008B400, 0x00096E70, 0x00096F80, 0x00097090, 0x000971A0, 0x000972B0,
};

unsigned int D_8006E260[8] = {
    0x00086B10, 0x0008B400, 0x00096E70, 0x00096F80, 0x00097090, 0x000971A0, 0x000972B0, 0x000973C0,
};

unsigned char *D_8006E280[8] = {
    (unsigned char *) 0x000973C0, (unsigned char *) 0x001AB460, (unsigned char *) 0x002537E0,
    (unsigned char *) 0x00550330, (unsigned char *) 0x005508D0, (unsigned char *) 0x00550E70,
    (unsigned char *) 0x00551410, (unsigned char *) 0x005519B0,
};

SoundData *D_8006E2A0[3] = {
    D_80073038, D_8007477C, D_80075BD0,
};

unsigned char D_8006E2AC = 0;

s32 D_8006E2B0[10] = {
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

void (*D_8006E5D0[14])(void) = {
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

unsigned char D_8006E608[4] = {
    1, 2, 8, 8,
};

// <<<<< bss >>>>>
unsigned char  D_80172970;
unsigned char  D_80172971;
unsigned char  D_80172972[2];
unsigned short D_80172974;
unsigned short D_80172976;
unsigned short D_80172978;
ALPlayer       D_80172980;
ALHeap          D_80172998;
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
unsigned short D_801C09E8[4];
SoundSet      D_801C09F0;
unsigned char  D_801C09FC;
unsigned char  D_801C09FD;
unsigned int   D_801C0A00[8];
unsigned int   D_801C0A20;
unsigned short D_801C0A24;
unsigned char  D_801C0A26[2];
unsigned char *D_801C0A28[16];
ALVoice        D_801C0A68[16];
SoundWork      D_801C0C28[16];
SoundWork     *sptr;
unsigned char *mptr;
unsigned char  D_801C1730[0x6000];
void          *D_801C7730[4];

// clang-format on

void func_800386E0(void)
{
    ALSynConfig    config;
    amConfig       am_config;
    int            i;
    unsigned int   j;
    unsigned int   size;
    unsigned char *ptr;

    alHeapInit(&D_80172998, D_801729C8, 0x4E000);
    for (i = 0; i < 8; i++) {
        size          = D_8006E260[i] - D_8006E240[i];
        D_801729A8[i] = alHeapDBAlloc(0, 0, &D_80172998, 1, size);
        ptr           = (unsigned char *) D_801729A8[i];
        for (j = 0; j < size; j++) { *ptr++ = 0; }
        func_80001640(D_8006E240[i], D_801729A8[i], size);
    }
    for (i = 0; i < 8; i++) {
        alBnkfNew(D_801729A8[i], D_8006E280[i]);
    }
    config.maxVVoices        = 16;
    config.maxPVoices        = 16;
    config.maxUpdates        = 160;
    config.dmaproc           = NULL;
    config.outputRate        = 0;
    config.heap              = &D_80172998;
    config.fxType            = AL_FX_CUSTOM;
    config.params            = D_8006E2B0;
    am_config.outputRate     = 44100;
    am_config.framesPerField = 1;
    am_config.maxACMDSize    = 4096;
    amCreateAudioMgr(&config, 12, &am_config);
    func_8003889C(&D_80172980);
}

void func_8003889C(ALPlayer *player)
{
    D_801C09C8 = 6;
    D_801C09CA = D_801C09FD = D_801C09CD = D_801C09D0 = D_801C09FC = 0;
    D_801C09CF = D_801C09CE = 0;
    player->next            = NULL;
    player->handler         = func_80038938;
    player->clientData      = player;
    alSynAddPlayer(D_8007A230, player);
}

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

void func_80038A20(void)
{
    ALVoiceConfig config;
    int           i;
    ALBank       *bank;
    ALInstrument *instrument;
    ALSound      *sound;
    ALVoice      *voice;

    for (i = 0; i < 16; i++) {
        voice             = &D_801C0A68[i];
        config.priority   = 10;
        config.fxBus      = 0;
        config.unityPitch = 0;
        alSynAllocVoice(D_8007A230, voice, &config);
        sptr       = &D_801C0C28[i];
        sptr->bank = sptr->snos = 0;
        bank                    = D_801729A8[sptr->bank]->bankArray[0];
        instrument              = bank->instArray[sptr->snos];
        sound                   = instrument->soundArray[0];
        sptr->wavetable         = sound->wavetable;
        sptr->pitch             = 0.0f;
        sptr->last_vol[0]       = 0;
        sptr->last_vol[1]       = 0;
        sptr->voice_on          = 1;
        alSynStartVoiceParams(D_8007A230, voice, sptr->wavetable, 0.0f, 0, 0x40, 0, 0);
    }
    func_80039D60();
    D_801C7730[0] = alSynGetFXRef(D_8007A230, 0, 0);
}

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

void func_80038C30(unsigned short a, unsigned char b, unsigned char c)
{
    unsigned int cmd;
    int          i;

    if (!a) {
        return;
    }
    D_801C09C9 = 0xFF;
    if (!b || b >= 0x80) {
        cmd = a;
    } else {
        cmd = a + (b << 16);
    }
    if (c) {
        cmd |= c << 24;
    }
    if (D_801C09FD < 8) {
        if (D_801C09FD != 0) {
            for (i = 0; i < D_801C09FD; i++) {
                if (a == (D_801C0A00[i] & 0xFFFF)) {
                    D_801C09C9 = 0;
                    return;
                }
            }
        }
        D_801C0A00[D_801C09FD++] = cmd;
    }
    D_801C09C9 = 0;
}

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
    D_80172974 = a0;
    D_80172976 = a1;
    D_80172978 = a2 << 8;
}

void func_80038E20(void)
{
    int i;

    for (i = 0; i < 16; i++) {
        sptr = &D_801C0C28[i];
        if ((sptr->code & 0x7FFF) == D_80172974) {
            if (sptr->vol_scale != D_80172976) {
                sptr->flags |= 0x01;
                sptr->vol_scale = D_80172976;
            }
            if (D_80172978 != ((*sptr).pand & 0x7F00)) {
                sptr->flags |= 0x01;
                sptr->pand = D_80172978 | 0x8000;
                alSynSetPan(D_8007A230, &D_801C0A68[i], D_80172978 >> 8);
            }
        }
    }
    D_80172974 = 0;
}

void func_80038F68(void)
{
    unsigned int  *cmd;
    unsigned short id;
    int            run;

    cmd = D_801C0A00;
    while (D_801C09FD != 0) {
        D_801C0A20 = *cmd++;
        id         = D_801C0A20 & 0xFFFF;
        D_801C09FD--;
        run = 1;
        if ((D_801C0C28[0].code & 0x7FFF) == 0x50 && func_8000631C() != 0) {
            run = 0;
            if (id == 0xC0) {
                D_801C0A20 = 10;
                func_8003A138();
            }
        }
        if (run) {
            if (id < 0x100) {
                if (id < 0x10) {
                    D_8006E5D0[id - 1]();
                } else if (id < 0xF0) {
                    func_80039554();
                } else {
                    func_80038D64();
                }
            } else if (id < 0x8000) {
                func_800390D8();
            } else {
                func_8003A24C();
            }
        }
    }
}

void func_800390D8(void)
{
    unsigned short id = D_801C0A20 & 0x7FFF;
    SoundData     *tbl;
    unsigned char  reuse;
    unsigned char  voice;
    int            i;

    if (id >= 0x200) {
        if (id >= 0x3AE) {
            return;
        }
        tbl            = D_8006E2A0[(id >> 8) - 1];
        D_801C09F0.pri = tbl[id & 0xFF].pri;
        reuse          = D_801C09F0.pri & 0x80;
        D_801C09F0.pri &= 0x1F;
        voice           = tbl[id & 0xFF].voice_bank;
        D_801C09F0.bank = voice & 0xF;
        voice           = voice >> 4;
        if (id >= 0x35B) {
            for (i = 10; i < 16; i++) {
                if ((D_801C0C28[i].code & 0x7FFF) >= 0x35B) {
                    if (D_801C0C28[i].pri < D_801C09F0.pri) {
                        voice = i;
                        break;
                    }
                    return;
                }
            }
            if (i == 16) {
                voice = func_80039440(1);
                if (D_801C09F0.pri < D_801C0C28[voice].pri) {
                    return;
                }
            }
        } else {
            if (voice == 0) {
                for (i = 10; i < 16; i++) {
                    if (reuse) {
                        if (D_801C0A20 == D_801C0C28[i].code) {
                            voice = i;
                            break;
                        }
                    } else if (id == (D_801C0C28[i].code & 0x7FFF)) {
                        voice = i;
                        break;
                    }
                }
                if (voice == 0) {
                    voice = func_80039440(1);
                }
            }
            if (D_801C09F0.pri < D_801C0C28[voice].pri) {
                return;
            }
        }
        D_801C09F0.voice  = voice;
        D_801C09F0.tracks = 1;
        D_801C09F0.addr   = D_801C0A28;
        D_801C0A28[0]     = tbl[id & 0xFF].addr;
    } else {
        SoundData *music_tbl;

        if (id >= 0x182) {
            return;
        }
        music_tbl         = D_8006E2A0[(id >> 8) - 1];
        voice             = music_tbl[id & 0xFF].pri;
        D_801C09F0.pri    = voice & 0x1F;
        D_801C09F0.tracks = (voice >> 5) + 1;
        voice             = music_tbl[id & 0xFF].voice_bank;
        D_801C09F0.bank   = voice & 0xF;
        voice             = voice >> 4;
        if (D_801C09F0.tracks == 2) {
            if (voice == 0) {
                for (i = 14; i > 8; i -= 2) {
                    if (id == (D_801C0C28[i].code & 0x7FFF)) {
                        voice = i;
                        break;
                    }
                }
                if (voice == 0) {
                    voice = func_80039440(2);
                }
            }
            if (D_801C09F0.pri < D_801C0C28[voice].pri) {
                return;
            }
            if (D_801C09F0.pri < D_801C0C28[voice + 1].pri) {
                return;
            }
        }
        D_801C09F0.voice = voice;
        D_801C09F0.addr  = music_tbl[id & 0xFF].addr_tbl;
    }
    D_801C09F0.delay = 6;
    func_80039A70();
}

void func_80039438(void)
{
}

unsigned char func_80039440(unsigned char kind)
{
    unsigned char i;
    unsigned char j;
    unsigned char best;
    unsigned char min;

    best = 14;
    if (kind == 1) {
        best = 10;
        min  = D_801C0C28[best].pri;
        for (i = 11; i < 16; i++) {
            if (D_801C0C28[i].pri <= min) {
                best = i;
                min  = D_801C0C28[i].pri;
            }
        }
    } else {
        min = 0xFF;
        for (i = 14; i >= 10; i -= 2) {
            j = i;
            if (D_801C0C28[i].pri < D_801C0C28[i + 1].pri) {
                j++;
            }
            if (D_801C0C28[j].pri <= min) {
                best = i;
                min  = D_801C0C28[j].pri;
            }
        }
    }
    return best;
}

void func_80039554(void)
{
    unsigned short id;
    unsigned char  group;

    id = D_801C0A20 & 0x7FFF;
    if ((group = D_8006F14C[id - 0x10].group) == 0 || group != D_8006E2AC) {
        if (D_801C09D6[0] != 0) {
            func_80039D60();
        } else {
            func_80039DE4();
        }
    }
    if (id < 0xC0) {
        if (id < 0x6F) {
            if (D_8006F14C[id - 0x10].group != 0) {
                if (D_8006F14C[id - 0x10].group != D_8006E2AC) {
                    D_801C0A24    = id;
                    D_801C0A26[0] = 4;
                } else {
                    func_8003996C(0, id, 5);
                }
            } else {
                if (id != D_801C09FC) {
                    D_801C0A24    = id;
                    D_801C0A26[0] = 4;
                } else {
                    func_800397B8(id, 6);
                }
            }
        }
    } else if (id < 0xC1) {
        id -= 0xC0;
        D_801C09F0.tracks = D_8006F2C8[id].tracks;
        D_801C09F0.bank   = D_8006F2C8[id].bank;
        D_801C09F0.addr   = D_8006F2C8[id].addr;
        D_801C09F0.voice  = 0;
        D_801C09F0.pri    = 30;
        D_801C09F0.delay  = 6;
        func_80039A70();
    }
}

void func_800396DC(void)
{
    unsigned short index;

    D_801C0A26[0]--;
    if (D_801C0A26[0] == 0) {
        if (D_8015C5D4 != 0) {
            D_801C0A26[0] = 1;
            return;
        }
        index      = D_801C0A24 - 0x10;
        D_801C09FC = D_801C0A24;
        D_8006E2AC = D_8006F14C[index].group;
        if (D_8006E2AC != 0) {
            func_8003987C();
        } else {
            func_80005394(D_8006E2D8[index], D_801C1730, D_8006E454[index] - D_8006E2D8[index]);
            func_800397B8(D_801C0A24, 5);
            D_801C0A24 = 0;
        }
    }
}

void func_800397B8(unsigned short id, unsigned char delay)
{
    SoundEntry     *entry;
    unsigned short *offsets;
    int             i;

    entry             = &D_8006F14C[(unsigned short) ((unsigned int) id - 0x10)];
    D_801C09F0.tracks = entry->tracks;
    D_801C09F0.bank   = entry->bank;
    D_801C09F0.addr   = D_801C0A28;
    offsets           = (unsigned short *) D_801C1730;
    for (i = 0; i < D_801C09F0.tracks; i++) {
        D_801C0A28[i] = (unsigned char *) ((unsigned int) D_801C1730 + offsets[i]);
    }
    D_801C0A20       = id;
    D_801C09F0.voice = 0;
    D_801C09F0.pri   = 30;
    D_801C09F0.delay = delay;
    func_80039A70();
}

void func_8003987C(void)
{
    int            i;
    unsigned char *dest;
    unsigned short index;
    int            group;
    int            size;

    group = D_8006E2AC - 1;
    dest  = D_801C1730;
    for (i = 0; i < D_8006F130[group]; i++) {
        index = D_8006F138[group][i] - 0x10;
        size  = D_8006E454[index] - D_8006E2D8[index];
        func_80005394(D_8006E2D8[index], dest, size);
        dest += 6144;
    }
    func_8003996C(0, D_801C0A24, 5);
    D_801C0A24 = 0;
}

void func_8003996C(unsigned char force, unsigned short id, unsigned char delay)
{
    unsigned char *file;
    SoundEntry    *entry;
    int            i;

    D_80172970 = id;
    if (force == 0 && D_801C0C28[0].code != 0) {
        return;
    }
    entry             = &D_8006F14C[(unsigned short) ((unsigned int) id - 0x10)];
    D_801C09F0.tracks = entry->tracks;
    D_801C09F0.bank   = entry->bank;
    D_801C09F0.addr   = D_801C0A28;
    file              = &D_801C1730[entry->slot * 6144];
    for (i = 0; i < D_801C09F0.tracks; i++) {
        D_801C0A28[i] = file + ((unsigned short *) file)[i];
    }
    D_801C0A20       = id;
    D_801C09F0.voice = 0;
    D_801C09F0.pri   = 30;
    D_801C09F0.delay = delay;
    func_80039A70();
}

void func_80039A70(void)
{
    SoundWork      *voice;
    int             i;
    unsigned char **scripts;

    scripts = D_801C09F0.addr;
    for (i = 0; i < D_801C09F0.tracks; i++) {
        voice = &D_801C0C28[D_801C09F0.voice + i];
        if ((D_801C0A20 & 0x7FFF) >= 0x100) {
            if (D_80172972[0] != 0) {
                voice->fx_mix = 10;
                alSynSetFXMix(D_8007A230, &D_801C0A68[D_801C09F0.voice + i], 10);
            } else if (voice->fx_mix != 0) {
                voice->fx_mix = 0;
                alSynSetFXMix(D_8007A230, &D_801C0A68[D_801C09F0.voice + i], 0);
            }
            if (voice->voice_on != 0) {
                alSynSetVol(D_8007A230, &D_801C0A68[D_801C09F0.voice + i], 0, 5000);
                voice->stop_cnt = 2;
            }
        }
        voice->delay    = D_801C09F0.delay;
        voice->code     = D_801C0A20;
        voice->pri      = D_801C09F0.pri;
        voice->bank     = D_801C09F0.bank;
        voice->mpointer = scripts[i];
        voice->tmp      = 0x8000;
        voice->tmpd     = 0x80;
        voice->ngc = voice->ngg = 1;
        voice->ptps = voice->tund = 0;
        voice->lp1_freq = voice->lp2_freq = 0;
        voice->lp1_vol = voice->lp2_vol = 0;
        voice->swpc = voice->swss = 0;
        voice->rdms = voice->rdm_data = 0;
        voice->vibdm = voice->vibcs = 0;
        voice->tmpc                 = 0;
        voice->pvoc                 = 0;
        voice->panc                 = 0;
        voice->pand                 = 0;
        voice->mute                 = 0;
        voice->vol_scale            = 0;
    }
    for (i = 0; i < 4; i++) {
        if ((D_801C0A20 & 0x7FFF) == D_801C09E8[i]) {
            D_801C09E8[i] = 0;
            D_801C09E0[i] = 0;
        }
    }
}

void func_80039D60(void)
{
    int i;
    int j;

    D_801C09D6[0] = 0;
    for (i = 0; i < 16; i++) {
        D_801C0C28[i].code = 0x10;
    }
    func_80039DE4();
    for (i = 0; i < 4; i++) {
        D_801C09E8[i] = 0;
    }
    j = 0;
    while (j < 4) {
        D_801C09E0[j++] = 0;
    }
    D_80172972[0] = 0;
    D_80172974    = 0;
}

void func_80039DE4(void)
{
    int          i;
    unsigned int id;

    D_80172971    = 0;
    D_801C0A24    = 0;
    D_801C0A26[0] = 0;
    D_801C09D3 = D_801C09DA = D_801C09D8 = 0;
    D_801C09DB = D_801C09DC[0] = 0;
    for (i = 0; i < 16; i++) {
        id = D_801C0C28[i].code & 0x7FFF;
        if (id >= 0x10 && id < 0x100) {
            func_80039E9C(i);
        }
    }
}

void func_80039E9C(int arg0)
{
    sptr       = &D_801C0C28[arg0];
    sptr->code = 0;
    sptr->pri  = 0;
    if (sptr->voice_on != 0) {
        sptr->stop_cnt = 2;
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
        for (i = 0, p = D_801C0C28; i < 16; i++, p++) {
            q = sptr = p;
            if (p->code != 0) {
                q->flags |= 1;
                alSynSetPan(D_8007A230, &D_801C0A68[i], (sptr->pand >> 8) & 0x7F);
            }
        }
    }
}

void func_8003A060(void)
{
    int i;

    if (D_801C09D0 == 0) {
        D_801C09D0 = 1;
        for (i = 0; i < 16; i++) {
            sptr = &D_801C0C28[i];
            if (sptr->code != 0) {
                sptr->flags |= 0x01;
                alSynSetPan(D_8007A230, &D_801C0A68[i], 0x40);
            }
        }
    }
}

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
    unsigned short *p = D_801C09E8;
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

void func_8003A2D0(unsigned short index)
{
    int i;

    for (i = 0; i < 16; i++) {
        if (D_801C09E8[index] == D_801C0C28[i].code) {
            func_80039E9C(i);
        }
    }
    D_801C09E8[index] = D_801C09E0[index] = 0;
}
