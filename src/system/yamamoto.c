#include "structs.h"
#include "system/anime.h"
#include "system/window.h"

// clang-format off

// <<<<< data >>>>>
AnimeCamera D_80063740 = {
    { 0.0f, 0.0f, 100.0f },
    { 0.0f, 0.0f, 0.0f },
    0,
    2560,
    20.0f,
    2000.0f,
    { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    32, 32, 0, 0,
    &g_anime_default_vp,
    3,
    0, 0, 320, 240,
    -160.0f, -120.0f, 160.0f, 120.0f
};

unsigned int D_800637A0[2] = {
    0x646464FF, 0xFFFF0000,
};

unsigned int D_800637A8[6] = {
    0x80808000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
};

Gfx D_800637C0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

unsigned int D_80063828[16] = {
    0x0000318D, 0x18C70001, 0x0000318D, 0x18C70001, 0x0000318D, 0x18C70001, 0x0000318D, 0x18C70001,
    0x00000000, 0x00000000, 0x318D318D, 0x318D318D, 0x18C718C7, 0x18C718C7, 0x00010001, 0x00010001,
};

unsigned int D_80063868[16] = {
    0x000018C7, 0x318D4A53, 0x000018C7, 0x318D4A53, 0x000018C7, 0x318D4A53, 0x000018C7, 0x318D4A53,
    0x00000000, 0x00000000, 0x18C718C7, 0x18C718C7, 0x318D318D, 0x318D318D, 0x4A534A53, 0x4A534A53,
};

Gfx D_800638A8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0x80),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPEndDisplayList(),
};

void *D_80063918 = (void *) D_80063320;

unsigned int D_8006391C = 8;

unsigned int D_80063920 = 0x0000000C;

unsigned int D_80063924 = 2;

unsigned int D_80063928[2] = {
    0x00000002, 0x00000000,
};

Gfx D_80063930[] = {
    gsSPEndDisplayList(),
};

// <<<<< rodata >>>>>
#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/D_8007ACA0.s")

// <<<<< bss >>>>>
unsigned short D_80167C70[4];
unsigned char  D_80167C78[8];
int            D_80167C80[158];
SpriteList     D_80167EF8[16];
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80010180.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_8001018C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800101AC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80010230.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800102E0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80010318.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80010358.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80010374.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800103DC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800105AC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800106B0.s")

int func_800106F0(int list, int x, int y, int w, int h, int tex, int s, int t)
{
    ObjSpritePart *part;
    int            index = D_80167EF8[list].count;

    if (index >= D_80167EF8[list].max) {
        return -1;
    }
    part         = &D_80167EF8[list].parts[index];
    part->flags  = 0x4000 + tex;
    part->width  = w;
    part->height = h;
    part->x      = x;
    part->y      = y;
    part->s      = s << 5;
    part->t      = t << 5;
    D_80167EF8[list].count++;
    return index;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80010784.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_8001080C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80010864.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800108BC.s")

Gfx *func_800108E4(Gfx *gdl, int x, int y, int w, int h, int r, int g, int b, int a)
{
    gDPSetPrimColor(gdl++, 0, 0, r, g, b, a);
    gDPFillRectangle(gdl++, x, y, x + w, y + h);
    gSPEndDisplayList(gdl);
    return gdl;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80010980.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800109A4.s")

Gfx *func_80010B60(Gfx *gdl)
{
    gSPDisplayList(gdl++, D_800638A8);
    gDPLoadTLUT_pal16(gdl++, 0, D_80063918);
    gDPLoadTLUT_pal16(gdl++, 1, (unsigned char *) D_80063918 + 0x20);
    gSPEndDisplayList(gdl);
    return gdl;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80010C6C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80010E9C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_8001110C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_8001136C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800114B8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800115B8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800115E0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800115F8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80011610.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80011634.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800116AC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800116DC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80011734.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80011760.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80011908.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80011934.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80011968.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_8001198C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_800119D4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80011A38.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80011A9C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/yamamoto/func_80011B58.s")
