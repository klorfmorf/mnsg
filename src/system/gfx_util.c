#include "system/gfx_util.h"
#include "system/math.h"

#pragma intrinsic(sqrtf)

void func_8001D394(float *v);
void func_8001D718(float *src, float *dst, float *vec);
void func_8001D898(float *src, float *dst, float *vec);

// clang-format off

// <<<<< rodata >>>>>
const double D_8007B8D0[] = { 6.283185307179586 };
const double D_8007B8D8[] = { 6.283185307179586 };
const double D_8007B8E0[] = { 3.141592653589793 };
const double D_8007B8E8[] = { 1e-05 };
const double D_8007B8F0[] = { 1e-05 };
const double D_8007B8F8[] = { 1e-05 };
const double D_8007B900[] = { 1e-05 };
const double D_8007B908[] = { 1e-05 };

// <<<<< bss >>>>>
unsigned short D_801689F0;
unsigned short D_801689F2;
unsigned short D_801689F4;
int            D_801689F8;
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001C970.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001C9BC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001C9D8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001CA0C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001CB40.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001CC38.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001CD4C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001CF5C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001D14C.s")

int func_8001D230(float *v, float x, float y, float z, unsigned short angle)
{
    float          vec[3];
    float          t[3];
    float          len;
    unsigned short rot;

    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    func_8001D898(v, t, vec);
    len = sqrtf(t[0] * t[0] + t[2] * t[2]);
    if (((len < 0.0f) ? -len : len) < 1e-5) {
        v[0] = t[0];
        v[1] = t[1];
        v[2] = t[2];
        return 1;
    }
    rot = func_800040A8(t[1], len);
    if (0.0f <= t[1]) {
        rot = (rot + angle) & 0x3FF;
        if (rot > 0x100) {
            rot = 0x100;
        }
    } else {
        rot = (rot - angle) & 0x3FF;
        if (rot < 0x300) {
            rot = 0x300;
        }
    }
    len  = func_80003EA0(rot) / len;
    t[1] = func_80003E10(rot);
    t[0] *= len;
    t[2] *= len;
    func_8001D718(t, v, vec);
    func_8001D394(v);
    return 0;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001D394.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001D460.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001D5B8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001D718.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001D898.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001DA08.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001DB04.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001DE74.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001DF94.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001E0BC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001E2BC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001E380.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001E3E4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001E444.s")

void func_8001E4A4(float (*mf)[4], unsigned short rx, unsigned short ry, unsigned short rz)
{
    float sx, cx, sy, cy, sz, cz;
    float cxsy, sxsy;
    int   pad[4];

    rx       = (rx == 0x8000) ? 0 : rx;
    ry       = (ry == 0x8000) ? 0 : ry;
    rz       = (rz == 0x8000) ? 0 : rz;
    sx       = func_80003F30(rx, &cx);
    sy       = func_80003F30(ry, &cy);
    sz       = func_80003F30(rz, &cz);
    cxsy     = cx * sy;
    sxsy     = sx * sy;
    mf[0][0] = cy * cz;
    mf[0][1] = cy * sz;
    mf[0][2] = -sy;
    mf[1][0] = sxsy * cz - cx * sz;
    mf[1][1] = sxsy * sz + cx * cz;
    mf[1][2] = sx * cy;
    mf[2][0] = cxsy * cz + sx * sz;
    mf[2][1] = cxsy * sz - sx * cz;
    mf[2][2] = cx * cy;
    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;
}

void func_8001E634(float (*mf)[4], unsigned short rx, unsigned short ry, unsigned short rz)
{
    float sx, cx, sy, cy, sz, cz;
    float cxsy, sxsy;
    int   pad[4];

    rx       = (rx == 0x8000) ? 0 : rx;
    ry       = (ry == 0x8000) ? 0 : ry;
    rz       = (rz == 0x8000) ? 0 : rz;
    sx       = func_80003F30(rx, &cx);
    sy       = func_80003F30(ry, &cy);
    sz       = func_80003F30(rz, &cz);
    cxsy     = cx * sy;
    sxsy     = sx * sy;
    mf[0][0] = cy * cz;
    mf[1][0] = cy * sz;
    mf[2][0] = -sy;
    mf[0][1] = sxsy * cz - cx * sz;
    mf[1][1] = sxsy * sz + cx * cz;
    mf[2][1] = sx * cy;
    mf[0][2] = cxsy * cz + sx * sz;
    mf[1][2] = cxsy * sz - sx * cz;
    mf[2][2] = cx * cy;
    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001E7C4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001E868.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001E90C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001E9B0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001EC04.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001EEF4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001F19C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001F2D8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001F5F8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001F6C8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_util/func_8001F878.s")
