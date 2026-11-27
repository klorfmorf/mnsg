#include "sys/save_file.h"
#include "common.h"
#include "sys/sys.h"

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
    g_sys->used_stage_select = 0;
    D_8015C608.stats.weapon  = 1;
    func_80004208(&D_8015C608.stats, &D_8015C5D8, sizeof(SaveStats));
    func_80004208(&D_8015C608, &D_8015C910, 0x304);
    D_8015C5D8.unk_00 = 1;
    PRINTF(("GST INT OK \n")); // game start intro ok
}

void func_8000B640(void)
{
    func_800041E0(&D_8015C608, 0x304);
    D_8015C608.stats.unk_00        = 1;
    D_8015C608.stats.lives         = 3;
    D_8015C608.stats.health        = 10;
    D_8015C608.stats.max_health    = 10;
    D_8015C608.stats.money         = 100;
    D_8015C608.stats.weapon        = 1;
    D_8015C608.character_joined[0] = 1;
    D_8015C608.character_joined[1] = 1;
    D_8015C608.has_weapon_3[0]     = 1;
    D_8015C608.stage_group         = 2;
    D_8015C608.stage_id            = 0x1D1;
    D_8015C608.x                   = -2;
    D_8015C608.y                   = -40;
    D_8015C608.z                   = 8;
    D_8015C608.player_yaw          = 0;
    func_80004208(&D_8015C608, &D_8015C910, 0x304);
    PRINTF(("SAVE INT OK \n")); // save intro ok
}

void func_8000B6E0(void)
{
    func_80004208(&D_8015C910, &D_8015C608, 0x304);
    func_8000B5D0();
}

void func_8000B718(void)
{
    D_8015C608.stage_id   = D_8005BA30[D_8015C608.entry_id].stage_id;
    D_8015C608.x          = D_8005BA30[D_8015C608.entry_id].x;
    D_8015C608.y          = D_8005BA30[D_8015C608.entry_id].y;
    D_8015C608.z          = D_8005BA30[D_8015C608.entry_id].z;
    D_8015C608.player_yaw = D_8005BA30[D_8015C608.entry_id].player_yaw;
    D_8015C608.camera_yaw = D_8005BA30[D_8015C608.entry_id].camera_yaw;
    func_80004208(&D_8015C5D8, &D_8015C608.stats, sizeof(SaveStats));
    if (D_8015C608.stats.lives < 3) {
        D_8015C608.stats.lives = 3;
    }
    if (D_8015C608.stats.health < 10) {
        D_8015C608.stats.health = 10;
    }
    func_80004208(&D_8015C608, &D_8015C910, 0x304);
}

void func_8000B7E4(void)
{
    if (g_sys_real.retrace_count >= 60) {
        g_sys_real.retrace_count -= 60;
        D_8015C608.play_seconds++;
    }
}

void func_8000B824(void)
{
    if (D_8015C608.lucky_cats >= 4) {
        D_8015C608.lucky_cats -= 4;
        D_8015C5D8.health = D_8015C5D8.max_health += 2;
        PRINTF(("MANEKI NEKO CHECK \n"));
    }
}

void func_8000B864(void)
{
    D_8015C608.unk_29c = 400;
    D_8015C608.unk_2a0 = 200;
}
