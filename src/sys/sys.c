#include "sys/sys.h"
#include "common.h"

// clang-format off

// <<<<< bss >>>>>
Sys                 g_sys_real;
Sys                *g_sys;
Gfx                *g_sys_glistp;
int                 D_8015C5D0;
char                D_8015C5D4;
SaveStats           D_8015C5D8;
SaveFile            D_8015C608;
SaveFile            D_8015C910;
unsigned char       D_8015CC18[0x18];
unsigned int        D_8015CC30[36]; // EnemyMgr, size not fully known yet.
int                 D_8015CCC0[6];
unsigned char       D_8015CCD8[0x104];
EnemySpawn         *D_8015CDDC;
EnemyDef           *D_8015CDE0;
int                 D_8015CDE4;
int                 D_8015CDE8[2];
unsigned long long  D_8015CDF0[512];
unsigned long long  D_8015DDF0[1173];
int                 D_80160298[3];
int                 D_801602A4;
int                 D_801602A8[0x1BB2];

// clang-format on

void func_80004170(void)
{
    func_800041E0(&g_sys_real, sizeof(Sys));
    g_sys                              = &g_sys_real;
    D_8015C5D4                         = 0;
    g_sys->fill_color_alpha            = 1;
    g_sys->frame_buffer_bits_per_pixel = 2;
}

void func_800041E0(unsigned char *dst, int size)
{
    while (size--) {
        *dst++ = 0;
    }
}

void func_80004208(unsigned char *src, unsigned char *dst, int size)
{
    while (size--) {
        *dst++ = *src++;
    }
}
