#include "douchu/5B6060.h"
#include "common.h"
#include "sys/sys.h"
#include "unk.h"

extern StageIdleType D_80209D24_5C5C34[];
extern double        D_8020C828_5C8738;
extern double        D_8020C830_5C8740;

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA150_5B6060.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA19C_5B60AC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA378_5B6288.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA3FC_5B630C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA420_5B6330.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA4A4_5B63B4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA4FC_5B640C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA5A8_5B64B8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA5D4_5B64E4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA6C4_5B65D4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA6E4_5B65F4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FA7B0_5B66C0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FAB00_5B6A10.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FACC4_5B6BD4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FACF0_5B6C00.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FAD8C_5B6C9C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FADC4_5B6CD4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FAEC0_5B6DD0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FB018_5B6F28.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FB1C0_5B70D0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FB230_5B7140.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FB240_5B7150.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FB270_5B7180.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FB2A4_5B71B4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/func_801FB2D0_5B71E0.s")

void func_801FB934_5B7844(void)
{
    unsigned char i;

    g_sys_real.stage_player_idle_type = 0;
    i                                 = 0;
    while (D_80209D24_5C5C34[i].stage_id != 0xFFFF) {
        if (g_sys_real.intended_stage_id == D_80209D24_5C5C34[i].stage_id) {
            g_sys_real.stage_player_idle_type = D_80209D24_5C5C34[i].type;
            return;
        }
        i++;
    }
}

double func_801FB9AC_5B78BC(double x)
{
    double r;
    int    sign;
    int    i;

    r = 0.0;
    if (x > 1.0) {
        sign = 1;
        x    = 1.0 / x;
    } else if (x < -1.0) {
        sign = -1;
        x    = 1.0 / x;
    } else {
        sign = 0;
    }
    for (i = 24; i > 0; i--) {
        r = (i * i * x * x) / ((2 * i + 1) + r);
    }
    if (sign > 0) {
        return D_8020C828_5C8738 - x / (1.0 + r);
    }
    if (sign < 0) {
        return D_8020C830_5C8740 - x / (1.0 + r);
    }
    return x / (1.0 + r);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/D_8020C6A0_5C85B0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/jtbl_8020C7F8_5C8708.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/D_8020C820_5C8730.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/D_8020C824_5C8734.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/D_8020C828_5C8738.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/douchu/5B6060/D_8020C830_5C8740.s")
