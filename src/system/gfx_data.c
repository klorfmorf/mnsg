#include "system/gfx_data.h"
#include "common.h"

extern Gfx D_8006DA80[];

// clang-format off

// <<<<< data >>>>>
Vp D_8006D4D0 = { { { 640, 480, G_MAXZ / 2, 0 }, { 640, 480, G_MAXZ / 2, 0 } } };

Gfx D_8006D4E0[] = {
    gsDPPipeSync(),
    gsSPViewport(&D_8006D4D0),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx D_8006D508[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_8006D580[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetPrimColor(0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPEndDisplayList(),
};

Gfx D_8006D600[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPEndDisplayList(),
};

Gfx D_8006D648[] = {
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx D_8006D678[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx D_8006D6A8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx D_8006D6D8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx D_8006D708[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx D_8006D738[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx D_8006D768[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx D_8006D798[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx D_8006D7C8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx D_8006D7F8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsSPEndDisplayList(),
};

Gfx D_8006D868[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetFillColor(0x395F395F),
    gsDPFillRectangle(0, 0, 319, 239),
    gsSPEndDisplayList(),
};

Gfx D_8006D898[] = {
    gsDPPipeSync(),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx D_8006D920[] = {
    gsDPPipeSync(),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPEndDisplayList(),
};

Gfx D_8006D9B8[] = {
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsSPEndDisplayList(),
};

Gfx D_8006D9F0[] = {
    gsDPPipeSync(),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsSPEndDisplayList(),
};

Gfx D_8006DA80[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
    gsSPEndDisplayList(),
};

Gfx D_8006DB10[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0x6B, 0x9C, 0xFF, 0xFF),
    gsSPFogPosition(970, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DB30[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0x89, 0xC5, 0xF5, 0xA0),
    gsSPFogPosition(930, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DB50[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0xFF, 0x5D, 0x00, 0x30),
    gsSPFogPosition(970, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DB70[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0xFF, 0x5D, 0x00, 0x30),
    gsSPFogPosition(970, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DB90[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0x1B, 0x4B, 0xFE, 0xA0),
    gsSPFogPosition(950, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DBB0[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0x00, 0x00, 0x37, 0xC0),
    gsSPFogPosition(800, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DBD0[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0xFA, 0xAA, 0x00, 0x01),
    gsSPFogPosition(900, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DBF0[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0x00, 0x64, 0xFF, 0x04),
    gsSPFogPosition(900, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DC10[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0xFF, 0x46, 0x00, 0x04),
    gsSPFogPosition(900, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DC30[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0x00, 0x96, 0x96, 0x04),
    gsSPFogPosition(900, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DC50[] = {
    gsSPDisplayList(D_8006DA80),
    gsDPSetFogColor(0xDC, 0xF0, 0xFF, 0x04),
    gsSPFogPosition(900, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DC70[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetPrimColor(0, 0, 0xFF, 0xFF, 0xFF, 0x60),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsSPEndDisplayList(),
};

Gfx D_8006DCD8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, TEXEL0),
    gsDPSetFogColor(0xFF, 0xFF, 0xFF, 0x80),
    gsSPFogPosition(970, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DD80[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetPrimColor(0, 0, 0xFF, 0xFF, 0xFF, 0x60),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsSPEndDisplayList(),
};

Gfx D_8006DDE8[] = {
    gsDPPipeSync(),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsSPEndDisplayList(),
};

Gfx D_8006DE80[] = {
    gsDPPipeSync(),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx D_8006DEE0[] = {
    gsSPDisplayList(D_8006DE80),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_INTER | FORCE_BL | G_RM_FOG_SHADE_A, AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_INTER | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsDPSetCombineLERP(TEXEL0, 0, TEXEL1, PRIMITIVE, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, 0, 0, 0, PRIMITIVE),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsSPEndDisplayList(),
};

Gfx D_8006DF28[] = {
    gsSPDisplayList(D_8006DEE0),
    gsDPSetFogColor(0x6B, 0x9C, 0xFF, 0xFF),
    gsSPFogPosition(970, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DF48[] = {
    gsSPDisplayList(D_8006DEE0),
    gsDPSetFogColor(0xFF, 0x5D, 0x00, 0x30),
    gsSPFogPosition(970, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DF68[] = {
    gsSPDisplayList(D_8006DEE0),
    gsDPSetFogColor(0x00, 0x00, 0x37, 0xC0),
    gsSPFogPosition(800, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DF88[] = {
    gsSPDisplayList(D_8006DEE0),
    gsDPSetFogColor(0x00, 0x00, 0x00, 0xC0),
    gsSPFogPosition(800, 1000),
    gsSPEndDisplayList(),
};

Gfx D_8006DFA8[] = {
    gsSPDisplayList(D_8006DE80),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0x20),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsSPEndDisplayList(),
};

Gfx D_8006DFF8[] = {
    gsSPEndDisplayList(),
};

Gfx D_8006E000[] = {
    gsSPEndDisplayList(),
};

Gfx D_8006E008[] = {
    gsSPEndDisplayList(),
};

Gfx D_8006E010[] = {
    gsSPEndDisplayList(),
};

Gfx D_8006E018[] = {
    gsSPEndDisplayList(),
};

Gfx D_8006E020[] = {
    gsSPEndDisplayList(),
};

Gfx D_8006E028[] = {
    gsSPEndDisplayList(),
};

Gfx D_8006E030[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x002D1800),
    gsDPSetDepthImage(0x002D1800),
    gsDPSetFillColor(0xFFFCFFFC),
    gsDPFillRectangle(0, 0, 319, 239),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_8006E078[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_8006E0F0[] = {
    gsSPDisplayList(D_8006E030),
};

Gfx D_8006E0F8[] = {
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_4b, 320, 0x00000000),
    gsSPDisplayList(D_8006E078),
    gsSPEndDisplayList(),
};

Gfx D_8006E110[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_8006E170[] = {
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 0, 0),
    gsSP1Quadrangle(1, 3, 2, 3, 0),
    gsSP2Triangles(2, 3, 4, 0, 4, 3, 2, 0),
    gsSP1Quadrangle(3, 5, 4, 5, 0),
    gsSP2Triangles(4, 5, 6, 0, 6, 5, 4, 0),
    gsSP1Quadrangle(5, 7, 6, 7, 0),
    gsSP2Triangles(6, 7, 8, 0, 8, 7, 6, 0),
    gsSP1Quadrangle(7, 9, 8, 9, 0),
    gsSP2Triangles(8, 9, 10, 0, 10, 9, 8, 0),
    gsSP1Quadrangle(9, 11, 10, 11, 0),
    gsSPEndDisplayList(),
};

Gfx D_8006E1C8[] = {
    gsSPDisplayList(D_8006E170),
    gsSP2Triangles(12, 13, 14, 0, 14, 13, 12, 0),
    gsSP1Quadrangle(13, 15, 14, 15, 0),
    gsSP2Triangles(14, 15, 16, 0, 16, 15, 14, 0),
    gsSP1Quadrangle(15, 17, 16, 17, 0),
    gsSP2Triangles(16, 17, 18, 0, 18, 17, 16, 0),
    gsSP1Quadrangle(17, 19, 18, 19, 0),
    gsSP2Triangles(18, 19, 20, 0, 20, 19, 18, 0),
    gsSP1Quadrangle(19, 21, 20, 21, 0),
    gsSP2Triangles(20, 21, 22, 0, 22, 21, 20, 0),
    gsSP1Quadrangle(21, 23, 22, 23, 0),
    gsSPEndDisplayList(),
};
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/gfx_data/func_80037DB0.s")
