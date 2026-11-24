#include "common.h"
#include "sys/save_file.h"
#include "sys/sys.h"

void func_8000B5D0(void);

// clang-format off

// <<<<< data >>>>>
EntryPoint D_8005BA30[18] = {
    { 0, 0, 0, 0, 0, 0 },
    { 351, -20, 0, -190, 256, 19 },
    { 358, 150, 171, -85, 512, 19 },
    { 358, 150, 171, -85, 512, 19 },
    { 569, 0, 0, 0, 0, 0 },
    { 306, 1732, 434, 5, 512, 19 },
    { 361, 30, 35, -63, 768, 19 },
    { 375, -151, 112, -163, 0, 19 },
    { 322, 151, 231, -494, 0, 20 },
    { 322, 151, 231, -494, 0, 20 },
    { 327, 967, -165, 68, 768, 19 },
    { 327, 967, -165, 68, 768, 19 },
    { 377, 0, 70, -164, 0, 19 },
    { 570, 0, 0, 0, 0, 0 },
    { 333, 211, 200, -492, 0, 19 },
    { 332, -1, -47, -596, 0, 19 },
    { 183, 356, -60, -335, 902, 19 },
    { 571, 0, 0, 0, 0, 0 },
};

// clang-format on

void func_8000B5D0(void)
{
    g_sys->unk_cf8a0        = 0;
    D_8015C608.stats.unk_2c = 1;
    func_80004208(&D_8015C608.stats, &D_8015C5D8, sizeof(SaveStats));
    func_80004208(&D_8015C608, &D_8015C910, 0x304);
    D_8015C5D8.unk_00 = 1;
    PRINTF(("GST INT OK \n"));
}

void func_8000B640(void)
{
    func_800041E0(&D_8015C608, 0x304);
    D_8015C608.stats.unk_00 = 1;
    D_8015C608.stats.unk_14 = 3;
    D_8015C608.stats.unk_0c = 0xA;
    D_8015C608.stats.unk_08 = 0xA;
    D_8015C608.stats.unk_10 = 0x64;
    D_8015C608.stats.unk_2c = 1;
    D_8015C608.unk_94       = 1;
    D_8015C608.unk_98       = 1;
    D_8015C608.unk_c4       = 1;
    D_8015C608.unk_206      = 2;
    D_8015C608.room_id      = 0x1D1;
    D_8015C608.x            = -2;
    D_8015C608.y            = -0x28;
    D_8015C608.z            = 8;
    D_8015C608.player_yaw   = 0;
    func_80004208(&D_8015C608, &D_8015C910, 0x304);
    PRINTF(("SAVE INT OK \n"));
}

void func_8000B6E0(void)
{
    func_80004208(&D_8015C910, &D_8015C608, 0x304);
    func_8000B5D0();
}

void func_8000B718(void)
{
    D_8015C608.room_id    = D_8005BA30[D_8015C608.entry_id].room_id;
    D_8015C608.x          = D_8005BA30[D_8015C608.entry_id].x;
    D_8015C608.y          = D_8005BA30[D_8015C608.entry_id].y;
    D_8015C608.z          = D_8005BA30[D_8015C608.entry_id].z;
    D_8015C608.player_yaw = D_8005BA30[D_8015C608.entry_id].player_yaw;
    D_8015C608.camera_yaw = D_8005BA30[D_8015C608.entry_id].camera_yaw;
    func_80004208(&D_8015C5D8, &D_8015C608.stats, 0x30);
    if (D_8015C608.stats.unk_14 < 3) {
        D_8015C608.stats.unk_14 = 3;
    }
    if (D_8015C608.stats.unk_0c < 0xA) {
        D_8015C608.stats.unk_0c = 0xA;
    }
    func_80004208(&D_8015C608, &D_8015C910, 0x304);
}

void func_8000B7E4(void)
{
    if (g_sys_real.retrace_count >= 0x3C) {
        g_sys_real.retrace_count -= 0x3C;
        D_8015C608.unk_264++;
    }
}

void func_8000B824(void)
{
    if (D_8015C608.unk_fc >= 4) {
        D_8015C608.unk_fc -= 4;
        D_8015C5D8.unk_0c = D_8015C5D8.unk_08 += 2;
        PRINTF(("MANEKI NEKO CHECK \n"));
    }
}

void func_8000B864(void)
{
    D_8015C608.unk_29c = 0x190;
    D_8015C608.unk_2a0 = 0xC8;
}
