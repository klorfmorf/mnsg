#include "system/sd_main.h"
#include "common.h"
#include "system/se_tbl1.h"
#include "system/se_tbl2.h"
#include "system/se_tbl3.h"

void func_80039D60();
void func_80039DE4();
void func_80039F3C();
void func_80039F60();
void func_80039F84();
void func_8003A060();
void func_8003A138();
void func_8003A1C4();
void func_8003A1E8();
void func_8003A204();
void func_8003A228();

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
int            D_801729A8[8];
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
unsigned char  D_801C09F0[12];
unsigned char  D_801C09FC[4];
int            D_801C0A00[8];
int            D_801C0A20;
unsigned short D_801C0A24;
unsigned char  D_801C0A26[2];
unsigned char  D_801C0A28[64];
unsigned char  D_801C0A68[0x1C0];
int            D_801C0C28[0x1B8];
unsigned char  D_801C1308[0x2C0];
unsigned char  D_801C15C8[0x160];
int            D_801C1728;
int            D_801C172C;
unsigned char  D_801C1730[0x6000];
int            D_801C7730[4];
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_800386E0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003889C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038938.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038A20.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038B98.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038BC8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038BF8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038C30.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038D14.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038D3C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038D64.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038D94.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038E20.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80038F68.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_800390D8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80039440.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80039554.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_800396DC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_800397B8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003987C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003996C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80039A70.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80039D60.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80039DE4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80039E9C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80039F3C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80039F60.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_80039F84.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003A060.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003A138.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003A1C4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003A1E8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003A204.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003A228.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003A24C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/sd_main/func_8003A2D0.s")
