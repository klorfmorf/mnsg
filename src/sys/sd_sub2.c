#include "sys/sd_sub2.h"
#include "common.h"
#include "sys/sd_main.h"
#include "sys/sd_vars.h"
#include "sys/sd_sub1.h"
#include "unk.h"

void func_8003B634(signed char *params);
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
    sptr->tmp  = *mptr++ << 8;
    sptr->tmpc = 0;
}

void func_8003B450(void)
{
    int diff;

    sptr->tmpc = *mptr;
    mptr++;
    sptr->tmpm = *mptr;
    mptr++;
    diff        = (unsigned short) (sptr->tmpm << 8) - sptr->tmp;
    sptr->tmpad = diff / sptr->tmpc;
}

void func_8003B4EC(void)
{
    int v;

    sptr->tmpc--;
    if (sptr->tmpc != 0) {
        v = sptr->tmp;
        v += sptr->tmpad;
        if (v < 0x100) {
            v = 0x100;
        } else if (v > 0xFF00) {
            v = 0xFF00;
        }
        sptr->tmp = v;
        return;
    }
    sptr->tmp = sptr->tmpm << 8;
}

void func_8003B564(void)
{
    unsigned int pan;
    InstParam   *params;

    pan = sptr->code & 0x7F0000;
    if (pan != 0) {
        pan >>= 8;
        if (pan > 0x7F00) {
            pan = 0x7F00;
        }
        sptr->panc = 0;
        sptr->pand = pan | 0x8000;
        func_8003BCFC();
    }
    sptr->snos = *mptr;
    mptr++;
    if (sptr->bank < 2) {
        params = D_8006E9A0[sptr->bank];
        params += sptr->snos;
    } else {
        params = &D_8006EF80;
    }
    func_8003B634((signed char *) params);
}

void func_8003B634(signed char *params)
{
    ALBank       *bank;
    ALInstrument *in;
    ALSound      *snd;
    unsigned char byte;

    bank            = D_801729A8[sptr->bank]->bankArray[0];
    in              = bank->instArray[sptr->snos];
    snd             = in->soundArray[0];
    sptr->wavetable = snd->wavetable;
    sptr->tone_tune = *params++ << 8;
    sptr->tone_tune += *params++ << 2;
    sptr->ar = D_8006E800[127 - *params++];
    byte     = *params++;
    sptr->dr = D_8006E800[61 - ((byte & 0xF0) >> 2)];
    sptr->sl = (byte & 0xF) << 2;
    byte     = *params++;
    if (byte == 0) {
        sptr->sr = 0;
    } else {
        sptr->sr = D_8006E800[127 - byte] + 1;
    }
    sptr->rr = D_8006E800[125 - *params * 4];
    params++;
    if (sptr->pand < 0x8000) {
        sptr->pand = *params << 8;
        sptr->panc = 0;
    }
    func_8003BCFC();
}

void func_8003B79C(void)
{
    signed char *d;

    d          = (signed char *) &D_8006EF88[sptr->note - 72];
    sptr->snos = *d++;
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
    if (sptr->code >> 24) {
        sptr->pvod = v * (sptr->code / 0x1000000);
    } else {
        sptr->pvod = v << 8;
    }
    sptr->pvoc = 0;
}

void func_8003B89C(void)
{
    int diff;

    sptr->pvoc = *mptr;
    mptr++;
    sptr->pvom = *mptr;
    mptr++;
    diff        = (unsigned short) (sptr->pvom << 8) - sptr->pvod;
    sptr->pvoad = diff / sptr->pvoc;
}

void func_8003B938(void)
{
    int v;

    sptr->flags |= 1;
    sptr->pvoc--;
    if (sptr->pvoc != 0) {
        v = sptr->pvod;
        v += sptr->pvoad;
        if (v < 0) {
            v = 0;
        } else if (v > 0xFF00) {
            v = 0xFF00;
        }
        sptr->pvod = v;
        return;
    }
    sptr->pvod = sptr->pvom << 8;
}

void func_8003B9B8(void)
{
    unsigned char v;

    sptr->ar = D_8006E800[0x7F - *mptr];
    mptr++;
    v = *mptr;
    mptr++;
    sptr->dr = D_8006E800[0x3D - ((v & 0xF0) >> 2)];
    sptr->sl = (v & 0xF) * 4;
}

void func_8003BA40(void)
{
    int            sustain;
    unsigned short old;

    sustain = *mptr++;
    if (sustain == 0) {
        sptr->sr = 0;
        if (sptr->ngg == 0 && sptr->env_step == 2) {
            sptr->env_time = 0x7FFF;
        }
    } else {
        old      = sptr->sr;
        sptr->sr = D_8006E800[0x7F - sustain] + 1;
        if (sptr->ngg == 0 && sptr->env_step == 2) {
            sptr->env_time = sptr->sr;
            if (old == 0) {
                sptr->env_vol = 0;
            }
        }
    }
}

void func_8003BB00(void)
{
    sptr->rr = D_8006E800[125 - *mptr * 4];
    mptr++;
    if (sptr->ngg == 0 && sptr->env_step == 3) {
        sptr->env_time = sptr->rr;
    }
}

void func_8003BB70(void)
{
    int v;
    int sp20;

    if (sptr->fx_mix != 0) {
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
    if (sptr->fx_mix != 0) {
        alSynSetFXMix(D_8007A230, &D_801C0A68[D_801C09CC], sptr->fx_mix);
    }
}

void func_8003BCAC(void)
{
    int v;

    sptr->panc = 0;
    v          = *mptr++;
    sptr->pand = v << 8;
    func_8003BCFC();
}

void func_8003BCFC(void)
{
    unsigned char pan;

    if (D_801C09D0 != 0) {
        pan = 0x40;
    } else {
        pan = (sptr->pand >> 8) & 0x7F;
    }
    alSynSetPan(D_8007A230, &D_801C0A68[D_801C09CC], pan);
}

void func_8003BD68(void)
{
    int diff;

    sptr->panc = *mptr;
    mptr++;
    sptr->panm = *mptr;
    mptr++;
    if (sptr->pand >= 0x8000 || !(sptr->flags & 4)) {
        diff        = (unsigned short) (sptr->panm << 8) - (sptr->pand & 0x7FFF);
        sptr->panad = diff / sptr->panc;
    }
}

void func_8003BE24(void)
{
    unsigned short flag;
    int            v;

    sptr->flags |= 1;
    flag = sptr->pand & 0x8000;
    sptr->panc--;
    if (sptr->panc != 0) {
        v = sptr->pand;
        v = (v & 0x7FFF) + sptr->panad;
        if (v < 0) {
            v = 0;
        } else if (v >= 0x8000) {
            v = 0x7F00;
        }
        sptr->pand = v;
    } else {
        sptr->pand = sptr->panm << 8;
    }
    sptr->pand |= flag;
    func_8003BCFC();
}

void func_8003BED4(void)
{
    sptr->ptps = *mptr++ << 8;
}

void func_8003BF08(void)
{
    sptr->tund = *(signed char *) mptr++ * 4;
}

void func_8003BF3C(void)
{
    unsigned char v;

    v = *mptr++;
    if (v < 0x64) {
        sptr->vibhs = v;
    } else {
        sptr->vibhs = 0;
        sptr->vibcs = v - 0x64;
    }
    v = *mptr++;
    if (v < 0x40) {
        if (v < 0x20) {
            sptr->vib_tc_ofst = 1;
            v                 = v * 8;
        } else {
            sptr->vib_tc_ofst = 2;
            v                 = v * 4;
        }
    } else if (v < 0x80) {
        sptr->vib_tc_ofst = 4;
        v                 = v * 2;
    } else if (v == 0xFF) {
        sptr->vib_tc_ofst = 0x10;
    } else {
        sptr->vib_tc_ofst = 8;
    }
    sptr->vibcad = v;
    sptr->vibdm  = *mptr << 8;
    mptr++;
    if (sptr->vibcs != 0) {
        sptr->vibad = sptr->vibdm / sptr->vibcs;
    }
}

void func_8003C0AC(void)
{
    sptr->vibhc = sptr->vibhs;
    sptr->vibcc = sptr->vibcs;
    if (sptr->vibcs == 0) {
        sptr->vibd = sptr->vibdm;
    } else {
        sptr->vibd = 0;
    }
    sptr->vib_tmp_cnt = 0;
    sptr->vib_tbl_cnt = sptr->vib_tmp_cnt;
}

void func_8003C108(void)
{
    if (sptr->vibhc != 0) {
        sptr->vibhc--;
        return;
    }
    if (sptr->vibcc != 0) {
        sptr->vibcc--;
        if (sptr->vibcc != 0) {
            sptr->vibd += sptr->vibad;
        } else {
            sptr->vibd = sptr->vibdm;
        }
    }
    func_8003C184();
}

void func_8003C184(void)
{
    if (sptr->vibhc == 0) {
        sptr->vib_tmp_cnt += sptr->vibcad;
        if (sptr->vib_tmp_cnt >= 0x100) {
            sptr->vib_tmp_cnt &= 0xFF;
            sptr->flags |= 2;
            sptr->vib_tbl_cnt += sptr->vib_tc_ofst;
            sptr->vib_tbl_cnt &= 0x3F;
            if (sptr->vibd < 0x8000) {
                sptr->vib_data = sptr->vibd >> 7;
                sptr->vib_data = (D_8006E900[sptr->vib_tbl_cnt & 0x1F] * sptr->vib_data) >> 8;
            } else {
                sptr->vib_data = (sptr->vibd >> 8) & 0x7F;
                sptr->vib_data += 2;
                sptr->vib_data = (D_8006E900[sptr->vib_tbl_cnt & 0x1F] * sptr->vib_data) >> 1;
            }
            if (sptr->vib_tbl_cnt >= 0x20) {
                sptr->vib_data = -sptr->vib_data;
            }
        }
    }
}

void func_8003C2B4(void)
{
    unsigned char v;

    v           = *mptr;
    sptr->vibcs = v;
    mptr++;
    if (v != 0) {
        sptr->vibad = sptr->vibdm / sptr->vibcs;
    }
}

void func_8003C328(void)
{
    sptr->rdms = *mptr;
    sptr->rdmd = *++mptr << 8;
    sptr->rdmd += *++mptr;
    mptr++;
    sptr->rdmo = 0;
    sptr->rdmc = sptr->rdmo;
    if (sptr->rdms == 0) {
        sptr->rdm_data = 0;
    }
}

void func_8003C3C0(void)
{
    sptr->rdmc += sptr->rdms;
    if (sptr->rdmc >= 0x100) {
        sptr->rdmc &= 0xFF;
        sptr->flags |= 2;
        sptr->rdm_data = D_8006E920[sptr->rdmo];
        sptr->rdmo++;
        sptr->rdmo &= 0x7F;
        sptr->rdm_data += D_8006E920[sptr->rdmo] << 8;
        sptr->rdm_data &= sptr->rdmd;
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

    ticks = (unsigned int) (sptr->swpc << 16) / sptr->tmp;
    ticks++;
    diff        = sptr->swpm - sptr->swpd;
    sptr->swpad = diff / ticks;
    if (sptr->swpad == 0) {
        if (diff < 0) {
            sptr->swpad--;
            return;
        }
        sptr->swpad++;
    }
}

void func_8003C540(void)
{
    int key;

    if (*mptr++ == 0xE4) {
        if (sptr->swss == 0) {
            sptr->swsk  = 0;
            sptr->swphc = *mptr++;
            sptr->swpc  = *mptr++;
            key         = *mptr++;
            key         = (key - sptr->note) << 8;
            sptr->swpm  = sptr->swpd + key;
            func_8003C498();
        } else {
            mptr += 3;
        }
        sptr->mpointer = mptr;
    }
}

void func_8003C620(void)
{
    if (sptr->swsk == 0) {
        if (sptr->swphc != 0) {
            sptr->swphc--;
        } else {
            sptr->flags |= 2;
            sptr->swpc--;
            if (sptr->swpc != 0) {
                sptr->swpd += sptr->swpad;
            } else {
                sptr->swpd = sptr->swpm;
            }
        }
    } else {
        func_8003C860();
    }
}

void func_8003C6B8(void)
{
    if (sptr->swsk == 0) {
        if (sptr->swphc == 0) {
            sptr->flags |= 2;
            sptr->swpd += sptr->swpad;
        }
    } else {
        func_8003C860();
    }
}

void func_8003C720(void)
{
    sptr->swsk  = 0;
    sptr->swshc = *mptr;
    mptr++;
    sptr->swsc = *mptr;
    mptr++;
    sptr->swss = *(signed char *) mptr << 8;
    mptr++;
}

void func_8003C790(void)
{
    if (sptr->swsk == 0) {
        sptr->swphc = sptr->swshc;
        sptr->swpc  = sptr->swsc;
        sptr->swpm  = sptr->swpd;
        sptr->swpd -= sptr->swss;
        func_8003C498();
        return;
    }
    sptr->swpm = sptr->swpd;
    sptr->swpd = sptr->swpad;
    sptr->swpc = 1;
}

void func_8003C820(void)
{
    sptr->swsk = 1;
    sptr->swss = *mptr++;
}

void func_8003C860(void)
{
    int diff;
    int step;

    sptr->flags |= 2;
    diff = sptr->swpm - sptr->swpd;
    step = diff;
    if (diff < 0) {
        step = -diff;
    }
    step = (sptr->swss * step) >> 8;
    if (step == 0) {
        step = 1;
    }
    if (diff < 0) {
        sptr->swpd = sptr->swpd - step;
        if (sptr->swpd < sptr->swpm) {
            sptr->swpd = sptr->swpm;
        }
    } else {
        sptr->swpd = sptr->swpd + step;
        if (sptr->swpm < sptr->swpd) {
            sptr->swpd = sptr->swpm;
        }
    }
    if (sptr->swpd == sptr->swpm) {
        sptr->swpc = 0;
    }
}

void func_8003C934(void)
{
    sptr->lp1_cnt  = 0;
    sptr->lp1_addr = mptr;
    sptr->lp1_vol  = 0;
    sptr->lp1_freq = sptr->lp1_vol;
}

void func_8003C970(void)
{
    unsigned char count = *mptr++;

    sptr->lp1_cnt++;
    if (!count || count != sptr->lp1_cnt) {
        sptr->lp1_vol += (signed char) *mptr++;
        sptr->lp1_freq += (signed char) *mptr++ * 8;
        mptr = sptr->lp1_addr;
    } else {
        sptr->lp1_freq = sptr->lp1_vol = 0;
        mptr += 2;
    }
}

void func_8003CA30(void)
{
    sptr->lp2_cnt  = 0;
    sptr->lp2_addr = mptr;
    sptr->lp2_vol  = 0;
    sptr->lp2_freq = sptr->lp2_vol;
}

void func_8003CA6C(void)
{
    unsigned char count = *mptr++;

    sptr->lp2_cnt += 1;
    // fake
    if (!count || count != sptr->lp2_cnt) {
        sptr->lp2_vol += (signed char) *mptr++;
        sptr->lp2_freq += (signed char) *mptr++ * 8;
        mptr = sptr->lp2_addr;
    } else {
        sptr->lp2_freq = sptr->lp2_vol = 0;
        mptr += 2;
    }
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
    sptr->kakfg   = 0;
    sptr->kak1ptr = mptr;
}

void func_8003CB8C(void)
{
    switch (sptr->kakfg) {
        case 0:
            sptr->kakfg++;
            return;
        case 1:
            sptr->kakfg++;
            sptr->kak2ptr = mptr;
            mptr          = sptr->kak1ptr;
            return;
        case 2:
            sptr->kakfg--;
            mptr = sptr->kak2ptr;
            return;
    }
}

void func_8003CC18(void)
{
    unsigned char v;

    v = *mptr;
    mptr++;
    if (D_80172972[0] != 0 && (sptr->code & 0x7FFF) >= 0x100) {
        v += 10;
        if (v >= 0x80) {
            v = 0x7F;
        }
    }
    if (v != sptr->fx_mix) {
        sptr->fx_mix = v;
        alSynSetFXMix(D_8007A230, &D_801C0A68[D_801C09CC], v);
    }
}

void func_8003CCCC(void)
{
    sptr->bank = *mptr++;
}

void func_8003CCFC(void)
{
    unsigned char flag;

    flag = *mptr++ & 1;
    if (flag) {
        if ((unsigned char) sptr->code < D_80172970) {
            sptr->mute = 0;
        } else {
            sptr->mute = 1;
        }
    } else if (D_80172970 != (unsigned char) sptr->code) {
        D_80172971 = 1;
    }
}

void func_8003CD84(void)
{
    if (sptr->voice_on != 0) {
        sptr->stop_cnt = 1;
        alSynSetVol(D_8007A230, &D_801C0A68[D_801C09CC], 0, 0x1388);
    }
    sptr->ngc      = *mptr++;
    sptr->ngg      = 1;
    sptr->mpointer = mptr;
}

void func_8003CE2C(void)
{
    sptr->ngc = *mptr++;
    sptr->ngg = *mptr++;
    if (sptr->ngg == 0) {
        sptr->ngo = 0;
    } else {
        sptr->ngo = (sptr->ngc * sptr->ngg) >> 7;
        if (sptr->ngo == 0) {
            sptr->ngo = 1;
        }
    }
    sptr->mpointer = mptr;
    if (sptr->env_time != 0) {
        func_8003B394();
        if (sptr->env_time != 0) {
            func_8003AFB0();
        }
    } else {
        func_8003AD28();
    }
}

void func_8003CF24(void)
{
    if (sptr->voice_on != 0) {
        sptr->stop_cnt = 1;
        alSynSetVol(D_8007A230, &D_801C0A68[D_801C09CC], 0, 0x1388);
    }
    sptr->code = 0;
    sptr->pri  = sptr->code;
}
