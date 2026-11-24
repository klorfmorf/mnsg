#include "sys/sd_sub2.h"
#include "common.h"
#include "sys/sd_main.h"
#include "sys/sd_vars.h"
#include "sys/sd_sub1.h"
#include "unk.h"

void func_8003B564(void);
void func_8003B634(void *param);
void func_8003B83C(void);
void func_8003BCAC(void);
void func_8003BCFC(void);
void func_8003C498(void);
void func_8003C860(void);

extern InstParam D_8006E9A8[];
extern InstParam D_8006ED54[];

// clang-format off

// <<<<< data >>>>>
unsigned short D_8006E800[128] = {
    0x0000, 0x0001, 0x0002, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A,
    0x000B, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F, 0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015,
    0x0016, 0x0018, 0x001A, 0x001C, 0x001E, 0x001F, 0x0020, 0x0022, 0x0024, 0x0026, 0x0028, 0x002A,
    0x002C, 0x002E, 0x0032, 0x0036, 0x003A, 0x003E, 0x0042, 0x0046, 0x004A, 0x004D, 0x0050, 0x0054,
    0x0058, 0x005E, 0x0066, 0x006E, 0x0076, 0x007C, 0x0084, 0x008C, 0x0094, 0x009A, 0x00A0, 0x00A8,
    0x00B0, 0x00C0, 0x00D0, 0x00E0, 0x00F0, 0x00FE, 0x010C, 0x011C, 0x012C, 0x013A, 0x0148, 0x0158,
    0x0168, 0x0186, 0x01A4, 0x01C2, 0x01E0, 0x01F8, 0x0210, 0x022A, 0x0244, 0x0262, 0x0280, 0x029E,
    0x02BC, 0x02F8, 0x0334, 0x0370, 0x03AC, 0x03E8, 0x0424, 0x0460, 0x049C, 0x04D8, 0x0514, 0x0550,
    0x058C, 0x05F0, 0x0668, 0x06E0, 0x0758, 0x07D0, 0x0848, 0x08D4, 0x0960, 0x09C4, 0x0A28, 0x0A8C,
    0x0AF0, 0x0BE0, 0x0CD0, 0x0DD4, 0x0ED8, 0x0FC8, 0x10B8, 0x11BC, 0x12C0, 0x13B0, 0x14A0, 0x15A4,
    0x16A8, 0x1838, 0x19C8, 0x1B58, 0x1DB0, 0x2008, 0x2260, 0x2580,
};

unsigned char D_8006E900[32] = {
    0x00, 0x20, 0x38, 0x50, 0x68, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xE8, 0xF0, 0xF8, 0xFC,
    0xFF, 0xFC, 0xF8, 0xF0, 0xE8, 0xE0, 0xD0, 0xC0, 0xB0, 0xA0, 0x90, 0x80, 0x68, 0x50, 0x38, 0x20,
};

unsigned char D_8006E920[128] = {
    0x9F, 0x3C, 0xB2, 0x52, 0xAF, 0x45, 0xC7, 0x89, 0x10, 0x7F, 0xE0, 0x9D, 0xDC, 0x1F, 0x61, 0x16,
    0x39, 0xC9, 0x9C, 0xEB, 0x57, 0x08, 0x66, 0xF8, 0x5A, 0x24, 0xBF, 0x0E, 0x3E, 0x15, 0x4B, 0xDB,
    0xAB, 0xF5, 0x31, 0x0C, 0x43, 0x02, 0x55, 0xDE, 0x41, 0xDA, 0xBD, 0xAE, 0x19, 0xB0, 0x48, 0x57,
    0xBA, 0xA3, 0x36, 0x0B, 0xF9, 0xDF, 0x17, 0xA8, 0x04, 0x0C, 0xE0, 0x91, 0x18, 0x5D, 0xDD, 0xD3,
    0x28, 0x8A, 0xF2, 0x11, 0x59, 0x6F, 0x06, 0x0A, 0x34, 0x2A, 0x79, 0xAC, 0x5E, 0xA7, 0x83, 0xC6,
    0x39, 0xC1, 0xB4, 0x3A, 0x3F, 0xFE, 0x4F, 0xEF, 0x1F, 0x00, 0x30, 0x99, 0x4C, 0x28, 0x83, 0xED,
    0x8A, 0x2F, 0x2C, 0x66, 0x3F, 0xD6, 0x6C, 0xB7, 0x49, 0x22, 0xBC, 0x65, 0xFA, 0xCF, 0x02, 0xB1,
    0x46, 0xF0, 0x9A, 0xD7, 0xE2, 0x0F, 0x11, 0xC5, 0x74, 0xF6, 0x7A, 0x2C, 0x8F, 0xFB, 0x19, 0x6A,
};

InstParam *D_8006E9A0[2] = {
    D_8006E9A8, D_8006ED54,
};

InstParam D_8006E9A8[134] = {
    { 4, 26, 127, 0, 0, 20, 64 },
    { 4, 8, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 65, 20, 64 },
    { 9, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 85, 52, 14, 64 },
    { 6, 26, 127, 0, 0, 15, 64 },
    { 9, 26, 127, 0, 0, 20, 64 },
    { 9, 26, 127, 85, 55, 20, 64 },
    { 5, 26, 127, 0, 0, 20, 64 },
    { 5, 26, 127, 0, 0, 20, 64 },
    { 4, 26, 127, 0, 0, 20, 64 },
    { 4, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 90, 35, 15, 64 },
    { 9, 26, 127, 106, 40, 15, 64 },
    { 6, 26, 127, 95, 35, 12, 64 },
    { 6, 26, 127, 223, 75, 18, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
    { 5, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 154, 65, 20, 64 },
    { 1, 26, 127, 0, 0, 20, 64 },
    { 1, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
    { -8, 8, 127, 0, 0, 31, 64 },
    { 1, 26, 127, 0, 0, 20, 64 },
    { -8, 8, 127, 0, 0, 31, 64 },
    { -4, 26, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 175, 45, 16, 64 },
    { 9, 8, 127, 26, 50, 16, 64 },
    { -8, 8, 127, 0, 0, 31, 64 },
    { 1, 26, 127, 90, 57, 15, 64 },
    { -8, 8, 127, 0, 0, 31, 64 },
    { 1, 26, 127, 0, 0, 17, 64 },
    { 6, 26, 127, 0, 0, 18, 64 },
    { 6, 26, 127, 138, 30, 14, 64 },
    { -8, 8, 127, 0, 0, 31, 64 },
    { 4, 26, 127, 202, 55, 16, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { 4, 8, 127, 0, 0, 31, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { -8, 8, 127, 0, 0, 31, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { 11, 26, 127, 90, 55, 16, 64 },
    { 37, 50, 127, 85, 50, 15, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { 4, 8, 127, 0, 0, 31, 64 },
    { 45, 10, 127, 0, 30, 20, 64 },
    { 36, 9, 127, 0, 30, 20, 64 },
    { 33, 31, 127, 0, 0, 20, 64 },
    { 21, 29, 127, 0, 0, 20, 64 },
    { 45, 30, 127, 0, 0, 20, 64 },
    { 33, 38, 127, 0, 0, 20, 64 },
    { 26, 6, 127, 106, 25, 18, 64 },
    { 14, 7, 127, 106, 26, 18, 64 },
    { -1, 27, 127, 106, 45, 18, 64 },
    { 5, 22, 127, 0, 0, 20, 64 },
    { 12, 10, 127, 85, 20, 31, 64 },
    { 23, 30, 127, 143, 70, 20, 64 },
    { 11, 29, 127, 143, 70, 20, 64 },
    { 28, 10, 127, 85, 40, 14, 64 },
    { 19, 10, 127, 117, 45, 14, 64 },
    { 11, 9, 127, 119, 45, 14, 64 },
    { 0, 9, 127, 170, 45, 14, 64 },
    { 30, 27, 127, 95, 58, 15, 64 },
    { 20, 26, 127, 95, 59, 15, 64 },
    { 13, 26, 127, 95, 60, 15, 64 },
    { 6, 26, 127, 95, 60, 15, 64 },
    { 6, 29, 127, 165, 53, 16, 64 },
    { 17, 25, 127, 164, 0, 16, 64 },
    { 2, 27, 127, 164, 50, 16, 64 },
    { 2, 8, 127, 229, 27, 20, 64 },
    { 23, 29, 127, 239, 67, 18, 64 },
    { 11, 29, 127, 239, 68, 18, 64 },
    { -1, 30, 127, 239, 68, 18, 64 },
    { 17, 17, 127, 206, 45, 17, 64 },
    { -8, 8, 127, 0, 0, 31, 64 },
    { 42, 25, 127, 0, 0, 18, 64 },
    { 26, 28, 127, 0, 0, 18, 64 },
    { 14, 24, 127, 0, 0, 18, 64 },
    { 2, 25, 127, 0, 0, 18, 64 },
    { -7, 23, 127, 0, 0, 18, 64 },
    { 2, 54, 127, 0, 0, 31, 64 },
    { -2, 15, 127, 0, 0, 20, 64 },
    { 17, 20, 127, 0, 0, 18, 64 },
    { 5, 26, 127, 0, 0, 18, 64 },
    { 13, 40, 127, 0, 0, 18, 64 },
    { 4, 26, 127, 0, 0, 18, 64 },
    { -2, 26, 127, 0, 0, 18, 64 },
    { 23, 31, 127, 0, 0, 20, 64 },
    { 11, 31, 127, 0, 0, 20, 64 },
    { -1, 29, 127, 0, 0, 20, 64 },
    { 16, 9, 127, 0, 0, 20, 64 },
    { 0, 11, 127, 0, 0, 20, 64 },
    { 14, 33, 127, 0, 0, 20, 64 },
    { 2, 32, 127, 0, 0, 31, 64 },
    { 7, 11, 127, 0, 0, 20, 64 },
    { 14, 29, 127, 0, 0, 20, 64 },
    { 2, 28, 127, 0, 0, 20, 64 },
    { -5, 29, 127, 0, 0, 20, 64 },
    { 20, 18, 127, 85, 25, 22, 64 },
    { 8, 21, 127, 85, 25, 22, 64 },
    { 34, 226, 127, 0, 0, 22, 64 },
    { 17, 22, 127, 0, 0, 20, 64 },
    { 36, 0, 127, 0, 0, 22, 64 },
    { -6, 28, 127, 0, 0, 31, 64 },
    { 10, 17, 127, 0, 0, 20, 64 },
    { -2, 18, 127, 0, 0, 20, 64 },
    { 4, 34, 127, 0, 0, 20, 64 },
    { 24, 28, 127, 0, 0, 31, 64 },
    { 6, 27, 127, 0, 0, 20, 64 },
    { 9, 26, 127, 0, 0, 31, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { 6, 26, 127, 0, 0, 31, 64 },
    { 10, 27, 127, 0, 0, 20, 64 },
    { -2, 18, 127, 0, 0, 20, 64 },
    { 26, 20, 127, 0, 1, 20, 64 },
    { 21, 22, 127, 0, 1, 20, 64 },
    { 16, 23, 127, 0, 1, 20, 64 },
    { 26, 20, 127, 0, 0, 31, 64 },
    { 21, 33, 127, 0, 0, 20, 64 },
    { -1, 32, 127, 0, 0, 20, 64 },
    { 6, 26, 127, 0, 0, 20, 64 },
};

InstParam D_8006ED54[79] = {
    { -6, 28, 127, 0, 0, 31, 64 },
    { 5, 20, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { -6, 28, 127, 0, 0, 31, 64 },
    { 9, 26, 127, 0, 0, 31, 64 },
    { 9, 26, 127, 0, 0, 31, 64 },
    { 2, 54, 127, 0, 0, 31, 64 },
    { -2, 19, 127, 0, 0, 31, 64 },
    { 9, 26, 127, 0, 0, 31, 64 },
    { 9, 26, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { -4, 30, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { 0, 0, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { -18, 28, 127, 0, 0, 31, 64 },
    { -18, 28, 127, 0, 0, 31, 64 },
    { -4, 30, 127, 0, 0, 31, 64 },
    { -2, 19, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { -8, 8, 127, 0, 0, 31, 64 },
    { -6, 28, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { -18, 28, 127, 0, 0, 31, 64 },
    { 9, 26, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { 8, 30, 127, 0, 0, 31, 64 },
    { -4, 30, 127, 0, 0, 31, 64 },
    { -2, 19, 127, 0, 0, 31, 64 },
    { -4, 30, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { -2, 19, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { 2, 54, 127, 0, 0, 31, 64 },
    { -8, 8, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { -4, 30, 127, 0, 0, 31, 64 },
    { -6, 28, 127, 0, 0, 31, 64 },
    { -6, 28, 127, 0, 0, 31, 64 },
    { -6, 28, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { -2, 19, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { -23, 29, 127, 0, 0, 31, 64 },
    { 1, 29, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { 2, 54, 127, 0, 0, 31, 64 },
    { -6, 28, 127, 0, 0, 31, 64 },
    { -6, 28, 127, 0, 0, 31, 64 },
    { -6, 28, 127, 0, 0, 31, 64 },
    { -11, 29, 127, 0, 0, 31, 64 },
    { 12, 0, 127, 0, 0, 31, 64 },
    { -18, 28, 127, 0, 0, 31, 64 },
    { 5, 20, 127, 0, 0, 31, 64 },
    { -8, 8, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { 6, 28, 127, 0, 0, 31, 64 },
    { -2, 19, 127, 0, 0, 31, 64 },
};

InstParam D_8006EF80 = { 0, 0, 127, 0, 0, 31, 64 };

DrumInstParam D_8006EF88[53] = {
    { 0, { -8, 26, 127, 0, 0, 20, 64 } },
    { 1, { -8, 8, 127, 0, 0, 20, 64 } },
    { 2, { -6, 26, 127, 0, 0, 20, 64 } },
    { 3, { -6, 26, 127, 0, 65, 31, 64 } },
    { 4, { -3, 26, 127, 0, 0, 20, 64 } },
    { 5, { -6, 28, 127, 0, 0, 20, 64 } },
    { 6, { -6, 28, 127, 0, 0, 20, 64 } },
    { 7, { -6, 28, 127, 0, 0, 20, 64 } },
    { 8, { -6, 28, 127, 0, 0, 20, 62 } },
    { 9, { -6, 28, 127, 0, 0, 20, 66 } },
    { 10, { -2, 28, 127, 85, 52, 14, 35 } },
    { 10, { -5, 28, 127, 85, 52, 14, 50 } },
    { 10, { -8, 28, 127, 85, 52, 14, 78 } },
    { 10, { -12, 28, 127, 85, 52, 14, 93 } },
    { 11, { -2, 28, 127, 0, 0, 15, 15 } },
    { 11, { -5, 28, 127, 0, 0, 15, 40 } },
    { 11, { -8, 28, 127, 0, 0, 15, 80 } },
    { 11, { -12, 28, 127, 0, 0, 15, 110 } },
    { 12, { -3, 26, 127, 0, 0, 20, 32 } },
    { 13, { -3, 26, 127, 90, 35, 20, 32 } },
    { 14, { -5, 20, 127, 0, 0, 20, 32 } },
    { 15, { -5, 20, 127, 0, 0, 20, 32 } },
    { 16, { -8, 8, 127, 0, 0, 20, 72 } },
    { 17, { -8, 8, 127, 0, 0, 20, 72 } },
    { 18, { -6, 28, 127, 90, 35, 18, 96 } },
    { 20, { -6, 28, 127, 95, 35, 15, 68 } },
    { 20, { -4, 28, 127, 95, 35, 15, 52 } },
    { 21, { -6, 28, 126, 223, 75, 18, 100 } },
    { 22, { -6, 28, 127, 0, 0, 20, 25 } },
    { 23, { -7, 20, 127, 0, 0, 20, 60 } },
    { 24, { -6, 28, 127, 0, 0, 20, 10 } },
    { 25, { -6, 28, 127, 0, 0, 20, 10 } },
    { 26, { -6, 28, 127, 154, 65, 20, 117 } },
    { 27, { -11, 29, 127, 0, 0, 20, 20 } },
    { 28, { -11, 29, 127, 0, 0, 20, 107 } },
    { 29, { -6, 28, 127, 0, 0, 20, 90 } },
    { 31, { -11, 29, 127, 0, 0, 20, 38 } },
    { 33, { -12, 30, 127, 0, 0, 20, 28 } },
    { 34, { -6, 28, 127, 175, 45, 16, 40 } },
    { 37, { -11, 29, 127, 90, 57, 15, 94 } },
    { 37, { -33, 29, 127, 90, 57, 15, 34 } },
    { 39, { -11, 29, 127, 0, 0, 17, 67 } },
    { 40, { -6, 28, 127, 0, 0, 18, 12 } },
    { 41, { -6, 28, 127, 138, 30, 14, 72 } },
    { 43, { -13, 8, 127, 202, 55, 16, 58 } },
    { 121, { -6, 28, 127, 0, 0, 31, 64 } },
    { 122, { -6, 28, 127, 0, 0, 31, 64 } },
    { 123, { -6, 28, 127, 0, 0, 31, 64 } },
    { 124, { -6, 28, 127, 0, 0, 31, 64 } },
    { 19, { -3, 26, 127, 141, 65, 20, 64 } },
    { 44, { -6, 26, 127, 0, 0, 31, 64 } },
    { 45, { -6, 26, 127, 0, 0, 31, 64 } },
    { 30, { -6, 8, 127, 90, 35, 14, 64 } },
};

// clang-format on

void func_8003B410(void)
{
    sptr->unk_18 = *mptr++ << 8;
    sptr->unk_1d = 0;
}

void func_8003B450(void)
{
    int diff;

    sptr->unk_1d = *mptr;
    mptr++;
    sptr->unk_1c = *mptr;
    mptr++;
    diff         = (unsigned short) (sptr->unk_1c << 8) - sptr->unk_18;
    sptr->unk_1e = diff / sptr->unk_1d;
}

void func_8003B4EC(void)
{
    int v;

    sptr->unk_1d--;
    if (sptr->unk_1d != 0) {
        v = sptr->unk_18;
        v += sptr->unk_1e;
        if (v < 0x100) {
            v = 0x100;
        } else if (v > 0xFF00) {
            v = 0xFF00;
        }
        sptr->unk_18 = v;
        return;
    }
    sptr->unk_18 = sptr->unk_1c << 8;
}

#ifdef NON_MATCHING
void func_8003B564(void)
{
    unsigned int v;

    v = sptr->unk_00 & 0x7F0000;
    if (v != 0) {
        v >>= 8;
        if (v > 0x7F00) {
            v = 0x7F00;
        }
        sptr->unk_5b = 0;
        sptr->unk_58 = v | 0x8000;
        func_8003BCFC();
    }
    sptr->unk_0d = *mptr;
    mptr++;
    func_8003B634(sptr->unk_0c < 2 ? D_8006E9A0[sptr->unk_0c] + sptr->unk_0d : &D_8006EF80);
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_sub2/func_8003B564.s")
#endif

#ifdef NON_MATCHING
void func_8003B634(void *param)
{
    signed char  *inst = param;
    int           decay;
    int           sustain;
    ALBank       *bank;
    ALInstrument *in;
    ALSound      *snd;

    bank         = D_801729A8[sptr->unk_0c]->bankArray[0];
    in           = bank->instArray[sptr->unk_0d];
    snd          = in->soundArray[0];
    sptr->unk_14 = snd->wavetable;
    sptr->unk_2c = *inst++ << 8;
    sptr->unk_2c += *inst++ * 4;
    sptr->unk_4e = D_8006E800[0x7F - *inst++];
    decay        = *(unsigned char *) inst++;
    sptr->unk_50 = D_8006E800[0x3D - ((decay & 0xF0) >> 2)];
    sptr->unk_54 = (decay & 0xF) * 4;
    sustain      = *(unsigned char *) inst++;
    if (sustain == 0) {
        sptr->unk_52 = 0;
    } else {
        sptr->unk_52 = D_8006E800[0x7F - sustain] + 1;
    }
    sptr->unk_56 = D_8006E800[0x7D - *inst++ * 4];
    if (sptr->unk_58 < 0x8000) {
        sptr->unk_58 = *inst << 8;
        sptr->unk_5b = 0;
    }
    func_8003BCFC();
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_sub2/func_8003B634.s")
#endif

void func_8003B79C(void)
{
    signed char *d;

    d            = (signed char *) &D_8006EF88[sptr->unk_25 - 72];
    sptr->unk_0d = *d++;
    func_8003B634(d);
}

void func_8003B7E4(void)
{
    func_8003B83C();
    func_8003B564();
}

void func_8003B80C(void)
{
    func_8003B83C();
    func_8003B564();
    func_8003BCAC();
}

void func_8003B83C(void)
{
    unsigned char v;

    v = *mptr++;
    if (sptr->unk_00 >> 24) {
        sptr->unk_3a = v * (sptr->unk_00 / 0x1000000);
    } else {
        sptr->unk_3a = v << 8;
    }
    sptr->unk_47 = 0;
}

void func_8003B89C(void)
{
    int diff;

    sptr->unk_47 = *mptr;
    mptr++;
    sptr->unk_46 = *mptr;
    mptr++;
    diff         = (unsigned short) (sptr->unk_46 << 8) - sptr->unk_3a;
    sptr->unk_44 = diff / sptr->unk_47;
}

void func_8003B938(void)
{
    int v;

    sptr->unk_06 |= 1;
    sptr->unk_47--;
    if (sptr->unk_47 != 0) {
        v = sptr->unk_3a;
        v += sptr->unk_44;
        if (v < 0) {
            v = 0;
        } else if (v > 0xFF00) {
            v = 0xFF00;
        }
        sptr->unk_3a = v;
        return;
    }
    sptr->unk_3a = sptr->unk_46 << 8;
}

void func_8003B9B8(void)
{
    unsigned char v;

    sptr->unk_4e = D_8006E800[0x7F - *mptr];
    mptr++;
    v = *mptr;
    mptr++;
    sptr->unk_50 = D_8006E800[0x3D - ((v & 0xF0) >> 2)];
    sptr->unk_54 = (v & 0xF) * 4;
}

void func_8003BA40(void)
{
    int            sustain;
    unsigned short old;

    sustain = *mptr++;
    if (sustain == 0) {
        sptr->unk_52 = 0;
        if (sptr->unk_22 == 0 && sptr->unk_49 == 2) {
            sptr->unk_4c = 0x7FFF;
        }
    } else {
        old          = sptr->unk_52;
        sptr->unk_52 = D_8006E800[0x7F - sustain] + 1;
        if (sptr->unk_22 == 0 && sptr->unk_49 == 2) {
            sptr->unk_4c = sptr->unk_52;
            if (old == 0) {
                sptr->unk_4a = 0;
            }
        }
    }
}

void func_8003BB00(void)
{
    sptr->unk_56 = D_8006E800[125 - *mptr * 4];
    mptr++;
    if (sptr->unk_22 == 0 && sptr->unk_49 == 3) {
        sptr->unk_4c = sptr->unk_56;
    }
}

void func_8003BB70(void)
{
    int v;
    int sp20;

    if (sptr->unk_10 != 0) {
        alSynSetFXMix(D_8007A230, &D_801C0A68[D_801C09CC], 0);
    }
    v    = *mptr++;
    sp20 = v * 0x28;
    if (sp20 == 0) {
        sp20 = D_8006E2B0[3];
    }
    alSynSetFXParam(D_8007A230, D_801C7730[0], 3, &sp20);
    v    = *mptr++;
    sp20 = v << 7;
    if (sp20 == 0) {
        sp20 = D_8006E2B0[4];
    }
    alSynSetFXParam(D_8007A230, D_801C7730[0], 4, &sp20);
    if (sptr->unk_10 != 0) {
        alSynSetFXMix(D_8007A230, &D_801C0A68[D_801C09CC], sptr->unk_10);
    }
}

void func_8003BCAC(void)
{
    int v;

    sptr->unk_5b = 0;
    v            = *mptr++;
    sptr->unk_58 = v << 8;
    func_8003BCFC();
}

void func_8003BCFC(void)
{
    unsigned char pan;

    if (D_801C09D0 != 0) {
        pan = 0x40;
    } else {
        pan = (sptr->unk_58 >> 8) & 0x7F;
    }
    alSynSetPan(D_8007A230, &D_801C0A68[D_801C09CC], pan);
}

void func_8003BD68(void)
{
    int diff;

    sptr->unk_5b = *mptr;
    mptr++;
    sptr->unk_5a = *mptr;
    mptr++;
    if (sptr->unk_58 >= 0x8000 || !(sptr->unk_06 & 4)) {
        diff         = (unsigned short) (sptr->unk_5a << 8) - (sptr->unk_58 & 0x7FFF);
        sptr->unk_5c = diff / sptr->unk_5b;
    }
}

void func_8003BE24(void)
{
    unsigned short flag;
    int            v;

    sptr->unk_06 |= 1;
    flag = sptr->unk_58 & 0x8000;
    sptr->unk_5b--;
    if (sptr->unk_5b != 0) {
        v = sptr->unk_58;
        v = (v & 0x7FFF) + sptr->unk_5c;
        if (v < 0) {
            v = 0;
        } else if (v >= 0x8000) {
            v = 0x7F00;
        }
        sptr->unk_58 = v;
    } else {
        sptr->unk_58 = sptr->unk_5a << 8;
    }
    sptr->unk_58 |= flag;
    func_8003BCFC();
}

void func_8003BED4(void)
{
    sptr->unk_2e = *mptr++ << 8;
}

void func_8003BF08(void)
{
    sptr->unk_30 = *(signed char *) mptr++ * 4;
}

void func_8003BF3C(void)
{
    unsigned char v;

    v = *mptr++;
    if (v < 0x64) {
        sptr->unk_93 = v;
    } else {
        sptr->unk_93 = 0;
        sptr->unk_9e = v - 0x64;
    }
    v = *mptr++;
    if (v < 0x40) {
        if (v < 0x20) {
            sptr->unk_99 = 1;
            v            = v * 8;
        } else {
            sptr->unk_99 = 2;
            v            = v * 4;
        }
    } else if (v < 0x80) {
        sptr->unk_99 = 4;
        v            = v * 2;
    } else if (v == 0xFF) {
        sptr->unk_99 = 0x10;
    } else {
        sptr->unk_99 = 8;
    }
    sptr->unk_95 = v;
    sptr->unk_9a = *mptr << 8;
    mptr++;
    if (sptr->unk_9e != 0) {
        sptr->unk_a0 = sptr->unk_9a / sptr->unk_9e;
    }
}

void func_8003C0AC(void)
{
    sptr->unk_94 = sptr->unk_93;
    sptr->unk_9f = sptr->unk_9e;
    if (sptr->unk_9e == 0) {
        sptr->unk_9c = sptr->unk_9a;
    } else {
        sptr->unk_9c = 0;
    }
    sptr->unk_96 = 0;
    sptr->unk_98 = sptr->unk_96;
}

void func_8003C108(void)
{
    if (sptr->unk_94 != 0) {
        sptr->unk_94--;
        return;
    }
    if (sptr->unk_9f != 0) {
        sptr->unk_9f--;
        if (sptr->unk_9f != 0) {
            sptr->unk_9c += sptr->unk_a0;
        } else {
            sptr->unk_9c = sptr->unk_9a;
        }
    }
    func_8003C184();
}

void func_8003C184(void)
{
    if (sptr->unk_94 == 0) {
        sptr->unk_96 += sptr->unk_95;
        if (sptr->unk_96 >= 0x100) {
            sptr->unk_96 &= 0xFF;
            sptr->unk_06 |= 2;
            sptr->unk_98 += sptr->unk_99;
            sptr->unk_98 &= 0x3F;
            if (sptr->unk_9c < 0x8000) {
                sptr->unk_36 = sptr->unk_9c >> 7;
                sptr->unk_36 = (D_8006E900[sptr->unk_98 & 0x1F] * sptr->unk_36) >> 8;
            } else {
                sptr->unk_36 = (sptr->unk_9c >> 8) & 0x7F;
                sptr->unk_36 += 2;
                sptr->unk_36 = (D_8006E900[sptr->unk_98 & 0x1F] * sptr->unk_36) >> 1;
            }
            if (sptr->unk_98 >= 0x20) {
                sptr->unk_36 = -sptr->unk_36;
            }
        }
    }
}

void func_8003C2B4(void)
{
    unsigned char v;

    v            = *mptr;
    sptr->unk_9e = v;
    mptr++;
    if (v != 0) {
        sptr->unk_a0 = sptr->unk_9a / sptr->unk_9e;
    }
}

void func_8003C328(void)
{
    sptr->unk_92 = *mptr;
    sptr->unk_8e = *++mptr << 8;
    sptr->unk_8e += *++mptr;
    mptr++;
    sptr->unk_8d = 0;
    sptr->unk_90 = sptr->unk_8d;
    if (sptr->unk_92 == 0) {
        sptr->unk_38 = 0;
    }
}

void func_8003C3C0(void)
{
    sptr->unk_90 += sptr->unk_92;
    if (sptr->unk_90 >= 0x100) {
        sptr->unk_90 &= 0xFF;
        sptr->unk_06 |= 2;
        sptr->unk_38 = D_8006E920[sptr->unk_8d];
        sptr->unk_8d++;
        sptr->unk_8d &= 0x7F;
        sptr->unk_38 += D_8006E920[sptr->unk_8d] << 8;
        sptr->unk_38 &= sptr->unk_8e;
    }
}

void func_8003C47C(void)
{
    mptr += 3;
}

void func_8003C498(void)
{
    unsigned short ticks;
    int            diff;

    ticks = (unsigned int) (sptr->unk_7d << 16) / sptr->unk_18;
    ticks++;
    diff         = sptr->unk_80 - sptr->unk_28;
    sptr->unk_84 = diff / ticks;
    if (sptr->unk_84 == 0) {
        if (diff < 0) {
            sptr->unk_84--;
            return;
        }
        sptr->unk_84++;
    }
}

void func_8003C540(void)
{
    int key;

    if (*mptr++ == 0xE4) {
        if (sptr->unk_8a == 0) {
            sptr->unk_8c = 0;
            sptr->unk_7c = *mptr++;
            sptr->unk_7d = *mptr++;
            key          = *mptr++;
            key          = (key - sptr->unk_25) << 8;
            sptr->unk_80 = sptr->unk_28 + key;
            func_8003C498();
        } else {
            mptr += 3;
        }
        sptr->unk_08 = mptr;
    }
}

void func_8003C620(void)
{
    if (sptr->unk_8c == 0) {
        if (sptr->unk_7c != 0) {
            sptr->unk_7c--;
        } else {
            sptr->unk_06 |= 2;
            sptr->unk_7d--;
            if (sptr->unk_7d != 0) {
                sptr->unk_28 += sptr->unk_84;
            } else {
                sptr->unk_28 = sptr->unk_80;
            }
        }
    } else {
        func_8003C860();
    }
}

void func_8003C6B8(void)
{
    if (sptr->unk_8c == 0) {
        if (sptr->unk_7c == 0) {
            sptr->unk_06 |= 2;
            sptr->unk_28 += sptr->unk_84;
        }
    } else {
        func_8003C860();
    }
}

void func_8003C720(void)
{
    sptr->unk_8c = 0;
    sptr->unk_88 = *mptr;
    mptr++;
    sptr->unk_89 = *mptr;
    mptr++;
    sptr->unk_8a = *(signed char *) mptr << 8;
    mptr++;
}

void func_8003C790(void)
{
    if (sptr->unk_8c == 0) {
        sptr->unk_7c = sptr->unk_88;
        sptr->unk_7d = sptr->unk_89;
        sptr->unk_80 = sptr->unk_28;
        sptr->unk_28 -= sptr->unk_8a;
        func_8003C498();
        return;
    }
    sptr->unk_80 = sptr->unk_28;
    sptr->unk_28 = sptr->unk_84;
    sptr->unk_7d = 1;
}

void func_8003C820(void)
{
    sptr->unk_8c = 1;
    sptr->unk_8a = *mptr++;
}

void func_8003C860(void)
{
    int diff;
    int step;

    sptr->unk_06 |= 2;
    diff = sptr->unk_80 - sptr->unk_28;
    step = diff;
    if (diff < 0) {
        step = -diff;
    }
    step = (sptr->unk_8a * step) >> 8;
    if (step == 0) {
        step = 1;
    }
    if (diff < 0) {
        sptr->unk_28 = sptr->unk_28 - step;
        if (sptr->unk_28 < sptr->unk_80) {
            sptr->unk_28 = sptr->unk_80;
        }
    } else {
        sptr->unk_28 = sptr->unk_28 + step;
        if (sptr->unk_80 < sptr->unk_28) {
            sptr->unk_28 = sptr->unk_80;
        }
    }
    if (sptr->unk_28 == sptr->unk_80) {
        sptr->unk_7d = 0;
    }
}

void func_8003C934(void)
{
    sptr->unk_5e = 0;
    sptr->unk_60 = mptr;
    sptr->unk_40 = 0;
    sptr->unk_32 = sptr->unk_40;
}

void func_8003C970(void)
{
    unsigned int count;

    count = *mptr++;
    sptr->unk_5e++;
    // fake
    if (count == 0 || (count ^ 0) != sptr->unk_5e) {
        sptr->unk_40 += (signed char) *mptr++;
        sptr->unk_32 += (signed char) *mptr++ * 8;
        mptr = sptr->unk_60;
        return;
    }
    sptr->unk_32 = sptr->unk_40 = 0;
    mptr += 2;
}

void func_8003CA30(void)
{
    sptr->unk_64 = 0;
    sptr->unk_68 = mptr;
    sptr->unk_42 = 0;
    sptr->unk_34 = sptr->unk_42;
}

void func_8003CA6C(void)
{
    unsigned int temp_v0;

    temp_v0 = *mptr++;
    sptr->unk_64 += 1;
    // fake
    if (temp_v0 == 0 || (temp_v0 ^ 0) != sptr->unk_64) {
        sptr->unk_42 += (signed char) *mptr;
        mptr += 1;
        sptr->unk_34 += (signed char) *mptr * 8;
        mptr += 1;
        mptr = sptr->unk_68;
        return;
    }
    sptr->unk_42 = 0;
    sptr->unk_34 = sptr->unk_42;
    mptr += 2;
}

void func_8003CB2C(void)
{
    sptr->lp3_addr = mptr;
}

void func_8003CB48(void)
{
    mptr = sptr->lp3_addr;
}

void func_8003CB64(void)
{
    sptr->unk_70 = 0;
    sptr->unk_74 = mptr;
}

void func_8003CB8C(void)
{
    switch (sptr->unk_70) {
        case 0:
            sptr->unk_70++;
            return;
        case 1:
            sptr->unk_70++;
            sptr->unk_78 = mptr;
            mptr         = sptr->unk_74;
            return;
        case 2:
            sptr->unk_70--;
            mptr = sptr->unk_78;
            return;
    }
}

void func_8003CC18(void)
{
    unsigned char v;

    v = *mptr;
    mptr++;
    if (D_80172972[0] != 0 && (sptr->unk_00 & 0x7FFF) >= 0x100) {
        v += 10;
        if (v >= 0x80) {
            v = 0x7F;
        }
    }
    if (v != sptr->unk_10) {
        sptr->unk_10 = v;
        alSynSetFXMix(D_8007A230, &D_801C0A68[D_801C09CC], v);
    }
}

void func_8003CCCC(void)
{
    sptr->unk_0c = *mptr++;
}

#ifdef NON_MATCHING
void func_8003CCFC(void)
{
    unsigned char b = *mptr++;

    if (b & 1) {
        if (sptr->unk_00_b[3] < D_80172970) {
            sptr->unk_ac = 0;
            return;
        }
        sptr->unk_ac = 1;
        return;
    }
    if (sptr->unk_00_b[3] != D_80172970) {
        D_80172971 = 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/sd_sub2/func_8003CCFC.s")
#endif

void func_8003CD84(void)
{
    if (sptr->unk_0e != 0) {
        sptr->unk_0f = 1;
        alSynSetVol(D_8007A230, &D_801C0A68[D_801C09CC], 0, 0x1388);
    }
    sptr->unk_21 = *mptr++;
    sptr->unk_22 = 1;
    sptr->unk_08 = mptr;
}

void func_8003CE2C(void)
{
    sptr->unk_21 = *mptr++;
    sptr->unk_22 = *mptr++;
    if (sptr->unk_22 == 0) {
        sptr->unk_24 = 0;
    } else {
        sptr->unk_24 = (sptr->unk_21 * sptr->unk_22) >> 7;
        if (sptr->unk_24 == 0) {
            sptr->unk_24 = 1;
        }
    }
    sptr->unk_08 = mptr;
    if (sptr->unk_4c != 0) {
        func_8003B394();
        if (sptr->unk_4c != 0) {
            func_8003AFB0();
        }
    } else {
        func_8003AD28();
    }
}

void func_8003CF24(void)
{
    if (sptr->unk_0e != 0) {
        sptr->unk_0f = 1;
        alSynSetVol(D_8007A230, &D_801C0A68[D_801C09CC], 0, 0x1388);
    }
    sptr->unk_00 = 0;
    sptr->unk_04 = sptr->unk_00;
}
