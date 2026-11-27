#include "sys/ripple.h"
#include "common.h"
#include "macros.h"
#include "sys/task.h"
#include "structs.h"
#include "sys/amem.h"
#include "sys/sys.h"
#include "sys/gfx_data.h"

#pragma intrinsic(sqrtf)

void   func_80024848(Task *task, Obj *obj);
void   func_80024734(RippleSurface *grid);
void   func_80024FAC(RippleSurface *grid, Gfx **gfxp);
void   func_80025790(RippleSurface *grid, Gfx **gfxp);
void   func_800258D0(RippleSurface *grid, Gfx **gfxp, int layer);
void   func_8002599C(RippleSurface *grid, Gfx **gfxp);
Gfx   *func_80026FE8(Gfx *gfx, int alpha, Gfx *dl, int layers, int tmem, void *image, unsigned int width, unsigned int height, int uls, int ult, int uls2, int ult2, int masks, int maskt);
void   func_80025398(RippleSurface *, Gfx **);
int    func_800248BC(Task *task);
int    func_80024BAC(Task *task);
void   func_80025D74(Task *task);
void   func_80026040(Task *task);
Vec3f *func_80027364(Vec3f *a, Vec3f *b, Vec3f *out);

// clang-format off

// <<<<< data >>>>>
Lights1 D_8006D180 = gdSPDefLights1(0x60, 0x60, 0x60, 0, 0, 0, 0, 0, 0);

Gfx D_8006D198[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_CULL_BOTH | G_FOG | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPNumLights(2),
    gsSPLight(&D_8006D180.a, 3),
    gsSPEndDisplayList(),
};

Gfx D_8006D220[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPClearGeometryMode(G_CULL_BOTH | G_FOG | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsSPTexture(0x07C0, 0x07C0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx D_8006D298[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_CULL_BOTH | G_FOG | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx D_8006D308[] = {
    gsSPEndDisplayList(),
};

// clang-format on

void func_80024160(Task *task, Obj *obj)
{
    RippleSurface *grid = RIPPLE_WORK(task)->surface;
    int            cells_size;
    int            i;
    int            dl_size;
    int            x;
    int            y;

    PRINTF(("Eripple start\n"));
    if (!(grid->flags & RIPPLE_STATIC_BUFFERS)) {
        cells_size          = (grid->cols + 2) * (grid->rows + 2) * sizeof(float);
        grid->accelerations = amemAlloc(g_sys->memory_blocks, cells_size);
        grid->velocities    = amemAlloc(g_sys->memory_blocks, cells_size);
        grid->heights       = amemAlloc(g_sys->memory_blocks, cells_size);
        grid->divisors      = amemAlloc(g_sys->memory_blocks, cells_size);
        grid->normals       = amemAlloc(g_sys->memory_blocks,
            (grid->cols + 1) * (grid->rows * 2 + 2) * sizeof(Vec3f));
    }
    for (i = 0; i < ((grid->flags & RIPPLE_DOUBLE_BUFFER) ? 2 : 1); i++) {
        if (!(grid->flags & RIPPLE_STATIC_BUFFERS)) {
            grid->vertices[i] = amemAlloc(g_sys->memory_blocks, grid->cols * grid->rows * sizeof(Vtx));
        }
    }
    RIPPLE_WORK(task)->vertex_size = func_800248BC(task);
    for (i = 0; i < ((grid->flags & RIPPLE_DOUBLE_BUFFER) ? 2 : 1); i++) {
        if (!(grid->flags & RIPPLE_STATIC_BUFFERS)) {
            grid->glists[i] = amemAlloc(g_sys->memory_blocks, grid->cols * grid->rows * sizeof(Gfx) + 0x100);
        }
    }
    dl_size = func_80024BAC(task);
    for (x = 0; x < grid->cols + 2; x++) {
        for (y = 0; y < grid->rows + 2; y++) {
            grid->heights[((x) + (y) * (grid->cols + 2))]       = 0.0f;
            grid->divisors[((x) + (y) * (grid->cols + 2))]      = 1.0f;
            grid->accelerations[((x) + (y) * (grid->cols + 2))] = 0.0f;
            grid->velocities[((x) + (y) * (grid->cols + 2))]    = 0.0f;
        }
    }
    for (y = 0; y < grid->rows * 2 + 2; y++) {
        for (x = 0; x < grid->cols + 1; x++) {
            grid->normals[x + y * (grid->cols + 1)].x = 0.0f;
            grid->normals[x + y * (grid->cols + 1)].y = 1.0f;

            grid->normals[x + y * (grid->cols + 1)].x = 0.0f;
        }
    }
    for (i = 0; i < ((grid->flags & RIPPLE_DOUBLE_BUFFER) ? 2 : 1); i++) {
        osWritebackDCache(grid->vertices[i], RIPPLE_WORK(task)->vertex_size);
        osWritebackDCache(grid->glists[i], dl_size);
    }
    RIPPLE_WORK(task)->flags_04 = 0x20;
    RIPPLE_WORK(task)->flags_08 |= 0xC0;
    if (grid->exec != NULL) {
        func_8003521C(grid->exec);
    } else {
        func_8003521C((void (*)(Task *, Obj *)) func_80025B38);
    }
}

RippleSurface *func_80024670(void)
{
    RippleSurface *grid = amemAlloc(g_sys->memory_blocks, sizeof(RippleSurface));

    if (grid != NULL) {
        func_800246BC(grid);
    }
    return grid;
}

void func_800246BC(RippleSurface *grid)
{
    grid->cols         = 15;
    grid->rows         = 15;
    grid->width        = 2000;
    grid->depth        = 2000;
    grid->flags        = RIPPLE_SMOOTH;
    grid->damping      = 0.02f;
    grid->time_step    = 0.04f;
    grid->r            = 0;
    grid->g            = 0;
    grid->b            = 0x60;
    grid->a            = 0x80;
    grid->texture      = 0;
    grid->env_texture  = 0;
    grid->env_texture2 = 0;
    grid->exec         = 0;
    grid->update       = 0;
    grid->tex_scale_s  = 1.0f;
    grid->tex_scale_t  = 1.0f;
}

void func_80024734(RippleSurface *grid)
{
    int i;

    PRINTF(("Eripple end\n"));
    amemFree(g_sys->memory_blocks, grid->heights);
    amemFree(g_sys->memory_blocks, grid->velocities);
    amemFree(g_sys->memory_blocks, grid->accelerations);
    amemFree(g_sys->memory_blocks, grid->divisors);
    amemFree(g_sys->memory_blocks, grid->normals);
    for (i = 0; i < ((grid->flags & RIPPLE_DOUBLE_BUFFER) ? 2 : 1); i++) {
        amemFree(g_sys->memory_blocks, grid->vertices[i]);
        amemFree(g_sys->memory_blocks, grid->glists[i]);
    }
}

void func_80024848(Task *task, Obj *obj)
{
    if (--RIPPLE_WORK(task)->kill_timer == 0) {
        func_80024734(RIPPLE_WORK(task)->surface);
        PRINTF(("Eripple died\n"));
        func_80034ED4();
    }
}

void func_80024888(Task *task)
{
    PRINTF(("ripple_kill\n"));
    ((ObjSolid *) task->obj_head)->AModel = 0;
    RIPPLE_WORK(task)->kill_timer         = 5;
    func_8003522C(task, func_80024848);
}

int func_800248BC(Task *task)
{
    RippleSurface *grid    = RIPPLE_WORK(task)->surface;
    float          scale_s = 31.0f / ((float) grid->width / 2) * grid->tex_scale_s;
    float          scale_t = 31.0f / ((float) grid->depth / 2) * grid->tex_scale_t;
    int            layer;
    Vtx           *vtx;
    int            x;
    int            y;
    float          vx;
    float          vz;
    int            size;

    for (layer = 0; layer < ((grid->flags & RIPPLE_DOUBLE_BUFFER) ? 2 : 1); layer++) {
        vtx = grid->vertices[layer];
        for (y = 1; y < grid->rows + 1; y++) {
            vz = -(float) grid->depth / 2 + grid->depth / (grid->rows - 1.0f) * (y - 1);
            for (x = 1; x < grid->cols + 1; x++) {
                vx           = -(float) grid->width / 2 + grid->width / (grid->cols - 1.0f) * (x - 1);
                vtx->v.ob[1] = 0;
                vtx->v.ob[0] = vx;
                if (x & 1) {
                    vtx->v.ob[2] = vz;
                } else {
                    vtx->v.ob[2] = grid->depth / (grid->rows - 1) / 2 + vz;
                }
                vtx->v.flag = 0;
                if (grid->flags & RIPPLE_TEXTURED) {
                    vtx->v.tc[0] = (int) (vx * scale_s) << 6;
                    if (x & 1) {
                        vtx->v.tc[1] = (int) (vz * scale_t) << 6;
                    } else {
                        vtx->v.tc[1] = (int) ((grid->depth / (grid->rows - 1.0f) / 2 + vz) * scale_t) << 6;
                    }
                } else {
                    vtx->v.tc[0] = 0;
                    vtx->v.tc[1] = 0;
                }
                vtx->v.cn[0] = 0;
                vtx->v.cn[1] = 0x7F;
                vtx->v.cn[2] = 0;
                vtx->v.cn[3] = 0xFF;
                vtx++;
            }
        }
        size = (unsigned char *) vtx - (unsigned char *) grid->vertices[layer];
    }
    return size;
}

int func_80024BAC(Task *task)
{
    RippleSurface *grid   = RIPPLE_WORK(task)->surface;
    Task          *header = task;
    Gfx          **gfxp;
    int            layer;
    int            layers;
    int            row;
    int            col;
    int            cols;
    int            width;
    int            index;
    int            count;
    int            odd;
    Lights1       *ambient;
    unsigned int   id;
    Gfx           *mesh;
    Gfx           *end;
    Gfx           *gfx;
    int            v0;
    int            v1;
    int            v2;
    int            v3;
    int            v4;
    int            v5;
    int            size;

    gfxp = &gfx;
    for (layer = 0; layer < (layers = ((grid->flags & RIPPLE_DOUBLE_BUFFER) ? 2 : 1)); layer++) {
        gfx   = (Gfx *) grid->glists[layer];
        width = grid->cols;
        gDPPipeSync(gfx++);
        if (grid->flags & RIPPLE_TEXTURED) {
            if (grid->flags & RIPPLE_SCROLL) {
                func_800258D0(grid, gfxp, layer);
            } else {
                func_80024FAC(grid, gfxp);
            }
        } else if (grid->flags & RIPPLE_HILITE) {
            func_80025398(grid, gfxp);
        } else if (grid->flags & RIPPLE_LOOKAT) {
            func_8002599C(grid, gfxp);
        } else {
            func_80025790(grid, gfxp);
        }
        gSPNumLights(gfx++, NUMLIGHTS_2);
        ambient = &D_8006D180;
        gSPLight(gfx++, ambient, 3);
        if (grid->flags & RIPPLE_COPY_GLIST) {
            if (grid->flags & (RIPPLE_HILITE | RIPPLE_LOOKAT)) {
                ((ObjSolid *) header->obj_head)->init_glist = ((unsigned int) grid->glists[layer] | ANIME_GLIST_COPY | ANIME_GLIST_LOOKAT);
            } else {
                ((ObjSolid *) header->obj_head)->init_glist = ((unsigned int) grid->glists[layer] | ANIME_GLIST_COPY);
            }
            id                                      = (unsigned int) D_8006D308 + ANIME_KIND_MODEL;
            ((ObjSolid *) header->obj_head)->AModel = id;
        } else {
            gSPEndDisplayList(gfx++);
            if (grid->flags & (RIPPLE_HILITE | RIPPLE_LOOKAT)) {
                ((ObjSolid *) header->obj_head)->init_glist = ((unsigned int) grid->glists[layer] | ANIME_GLIST_LOOKAT);
            } else {
                ((ObjSolid *) header->obj_head)->init_glist = (unsigned int) grid->glists[layer];
            }
            id                                      = (unsigned int) gfx + ANIME_KIND_MODEL;
            ((ObjSolid *) header->obj_head)->AModel = id;
        }
        mesh                     = gfx;
        grid->mesh_glists[layer] = (unsigned int) mesh;
        for (row = 0; row < grid->rows - 1; row++) {
            index = row * width;
            count = width * 2;
            gSPVertex(gfx++, &grid->vertices[layer][index], count, 0);
            v0 = 0;
            v3 = 1;
            for (col = 0; col < (cols = width - 1); col++) {
                odd = col & 1;
                if (odd) {
                    v1 = v0 + width;
                    v2 = v1 + 1;
                    gSP2Triangles(gfx++, v0, v1, v2, 0, v0, v2, v3, 0);
                } else {
                    v4 = v0 + width;
                    v5 = v4 + 1;
                    gSP2Triangles(gfx++, v0, v4, v3, 0, v3, v4, v5, 0);
                }
                v0++;
                v3++;
            }
        }
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
        end  = gfx;
        size = (unsigned int) end - (unsigned int) grid->glists[layer];
    }
    return size;
}

void func_80024FAC(RippleSurface *grid, Gfx **gfxp)
{
    Gfx *gfx  = *gfxp;
    int  mask = 6;

    gSPDisplayList(gfx++, D_8006D198);
    gDPSetPrimColor(gfx++, 0, 0, grid->r, grid->g, grid->b, grid->a);
    if (grid->flags & RIPPLE_CI4) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        gDPLoadTextureBlock_4b(gfx++, grid->texture, G_IM_FMT_CI, 64, 64, 0, (grid->flags & RIPPLE_MIRROR_S) != 0,
            (grid->flags & RIPPLE_MIRROR_T) != 0, mask, mask, G_TX_NOLOD, G_TX_NOLOD);
        gDPLoadTLUT_pal16(gfx++, 0, grid->palette);
    } else {
        gDPLoadTextureBlock(gfx++, grid->texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
            (grid->flags & RIPPLE_MIRROR_S) != 0, (grid->flags & RIPPLE_MIRROR_T) != 0,
            mask, mask, G_TX_NOLOD, G_TX_NOLOD);
    }
    if (grid->flags & RIPPLE_SMOOTH) {
        gSPSetGeometryMode(gfx++, G_SHADING_SMOOTH);
    }
    if (grid->flags & RIPPLE_XLU) {
        gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
        gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2);
    } else {
        gDPSetRenderMode(gfx++, G_RM_AA_ZB_OPA_INTER, G_RM_AA_ZB_OPA_INTER2);
    }
    gDPSetCombineLERP(gfx++, TEXEL0, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, SHADE, 0, 0, 0, 0, PRIMITIVE);
    *gfxp = gfx;
}

void func_80025398(RippleSurface *grid, Gfx **gfxp)
{
    Gfx *gfx = *gfxp;

    gSPDisplayList(gfx++, D_8006D220);
    gDPSetPrimColor(gfx++, 0, 0, grid->r, grid->g, grid->b, grid->a);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_AA_ZB_XLU_INTER2);
    gDPLoadTextureBlock(gfx++, grid->env_texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP | G_TX_NOMIRROR,
        G_TX_WRAP | G_TX_NOMIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    if (grid->env_texture2 != NULL) {
        if (grid->flags & RIPPLE_XLU) {
            gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
            gDPSetCombineLERP(gfx++, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, TEXEL1, SCALE, COMBINED, 0, 0,
                0, COMBINED);
        } else {
            gDPSetCombineLERP(gfx++, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 1, TEXEL0, TEXEL1, SCALE, COMBINED, 0, 0, 0,
                COMBINED);
        }
        gDPLoadMultiBlock(gfx++, grid->env_texture2, 0x100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
            G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    } else if (grid->flags & RIPPLE_XLU) {
        gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
        gDPSetCombineLERP(gfx++, TEXEL0, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    } else {
        gDPSetCombineLERP(gfx++, TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    }
    gDPSetHilite1Tile(gfx++, G_TX_RENDERTILE, &g_sys->graphics_buffer[g_sys->current_graphics_pool].hilites[0], 32, 32);
    gDPSetHilite2Tile(gfx++, 1, &g_sys->graphics_buffer[g_sys->current_graphics_pool].hilites[0], 32, 32);
    *gfxp = gfx;
}

void func_80025790(RippleSurface *grid, Gfx **gfxp)
{
    Gfx *gfx = *gfxp;

    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPSetPrimColor(gfx++, 0, 0, grid->r, grid->g, grid->b, grid->a);
    gSPClearGeometryMode(gfx++, G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
    if (grid->flags & RIPPLE_SMOOTH) {
        gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_LIGHTING);
    } else {
        gSPSetGeometryMode(gfx++, G_SHADE | G_LIGHTING);
    }
    if (grid->flags & RIPPLE_XLU) {
        gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2);
    } else {
        gDPSetRenderMode(gfx++, G_RM_AA_ZB_OPA_INTER, G_RM_AA_ZB_OPA_INTER2);
    }
    gSPTexture(gfx++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineLERP(gfx++, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE);
    *gfxp = gfx;
}

void func_800258D0(RippleSurface *grid, Gfx **gfxp, int layer)
{
    Gfx *gfx = *gfxp;

    grid->texture_glists[layer] = gfx;
    gfx                         = func_80026FE8(gfx, grid->a, D_8006DEE0, 2, 0x100, grid->texture, 64, 32, 0, 5, 30, 0, 6, 5);
    if (grid->flags & RIPPLE_FOG) {
        gDPSetRenderMode(gfx++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_INTER2);
    }
    *gfxp = gfx;
}

void func_8002599C(RippleSurface *grid, Gfx **gfxp)
{
    Gfx *gfx = *gfxp;

    gSPDisplayList(gfx++, D_8006D298);
    gDPSetPrimColor(gfx++, 0, 0, grid->r, grid->g, grid->b, grid->a);
    gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2);
    gDPLoadTextureBlock(gfx++, grid->texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_WRAP | G_TX_NOMIRROR,
        G_TX_WRAP | G_TX_NOMIRROR, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
    if (grid->flags & RIPPLE_XLU) {
        gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
        gDPSetCombineLERP(gfx++, TEXEL0, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, SHADE, 0, 0, 0, 0, PRIMITIVE);
    } else {
        gDPSetCombineLERP(gfx++, TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, TEXEL0, 0, SHADE, 0, 0, 0, 0, 1);
    }
    *gfxp = gfx;
}

void func_80025B38(Task *task, Obj *obj)
{
    RippleSurface *grid   = RIPPLE_WORK(task)->surface;
    Task          *header = task;
    int            layer;
    int            scroll;
    Gfx           *gfx;
    Vtx           *vtx;
    int            size;

    if (grid->update != NULL) {
        grid->update(task);
    }
    if ((grid->flags & (RIPPLE_REBUILD | RIPPLE_COPY_GLIST)) == (RIPPLE_REBUILD | RIPPLE_COPY_GLIST)) {
        func_80024BAC(task);
    }
    if (!(grid->flags & RIPPLE_NO_SIMULATE)) {
        func_80025D74(task);
    }
    func_80026040(task);
    if (grid->flags & RIPPLE_SMOOTH) {
        func_80026114(task);
    }
    layer = (grid->flags & RIPPLE_DOUBLE_BUFFER) ? g_sys->current_graphics_pool : 0;
    vtx   = grid->vertices[layer];
    size  = RIPPLE_WORK(task)->vertex_size;
    osWritebackDCache(vtx, size);
    if (grid->flags & RIPPLE_SCROLL) {
        scroll       = grid->scroll + 0.5;
        gfx          = func_80026FE8(grid->texture_glists[layer], grid->a, D_8006DEE0, 2, 0x100, grid->texture, 64, 32,
            scroll, scroll + 5, 30 - scroll, scroll, 6, 5);
        grid->scroll = grid->scroll + 0.5;

        osWritebackDCache((void *) ((unsigned int) grid->texture_glists[layer] & ANIME_ADDR_MASK),
            (unsigned int) gfx & ANIME_ADDR_MASK - (unsigned int) grid->texture_glists[layer] & ANIME_ADDR_MASK);
    }
    if (grid->flags & RIPPLE_DOUBLE_BUFFER) {
        if (grid->flags & RIPPLE_COPY_GLIST) {
            if (grid->flags & RIPPLE_HILITE) {
                ((ObjSolid *) header->obj_head)->init_glist = ((unsigned int) grid->glists[layer] | ANIME_GLIST_COPY | ANIME_GLIST_LOOKAT);
            } else {
                ((ObjSolid *) header->obj_head)->init_glist = ((unsigned int) grid->glists[layer] | ANIME_GLIST_COPY);
            }
        } else {
            ((ObjSolid *) header->obj_head)->AModel = grid->mesh_glists[g_sys->current_graphics_pool] + ANIME_KIND_MODEL;
        }
    }
}

void func_80025D74(Task *task)
{
    RippleSurface *grid = RIPPLE_WORK(task)->surface;
    int            x;
    int            y;

    for (y = 1; y < grid->rows + 1; y++) {
        for (x = 1; x < grid->cols + 1; x++) {
            grid->heights[((x) + (y) * (grid->cols + 2))] += grid->velocities[((x) + (y) * (grid->cols + 2))] * grid->time_step;
        }
    }
    for (y = 1; y < grid->rows + 1; y++) {
        for (x = 1; x < grid->cols + 1; x++) {
            if (!(x & 1)) {
                grid->accelerations[((x) + (y) * (grid->cols + 2))] =
                    (grid->heights[((x - 1) + (y) * (grid->cols + 2))] + grid->heights[((x) + (y - 1) * (grid->cols + 2))] +
                        grid->heights[((x + 1) + (y) * (grid->cols + 2))] + grid->heights[((x - 1) + (y + 1) * (grid->cols + 2))] +
                        grid->heights[((x) + (y + 1) * (grid->cols + 2))] + grid->heights[((x + 1) + (y + 1) * (grid->cols + 2))] -
                        6.0f * grid->heights[((x) + (y) * (grid->cols + 2))]) /
                        grid->divisors[((x) + (y) * (grid->cols + 2))] -
                    grid->velocities[((x) + (y) * (grid->cols + 2))] * grid->damping;
            } else {
                grid->accelerations[((x) + (y) * (grid->cols + 2))] =
                    (grid->heights[((x - 1) + (y - 1) * (grid->cols + 2))] + grid->heights[((x) + (y - 1) * (grid->cols + 2))] +
                        grid->heights[((x + 1) + (y - 1) * (grid->cols + 2))] + grid->heights[((x - 1) + (y) * (grid->cols + 2))] +
                        grid->heights[((x) + (y + 1) * (grid->cols + 2))] + grid->heights[((x + 1) + (y) * (grid->cols + 2))] -
                        6.0f * grid->heights[((x) + (y) * (grid->cols + 2))]) /
                        grid->divisors[((x) + (y) * (grid->cols + 2))] -
                    grid->velocities[((x) + (y) * (grid->cols + 2))] * grid->damping;
            }
            grid->velocities[((x) + (y) * (grid->cols + 2))] += grid->accelerations[((x) + (y) * (grid->cols + 2))] * grid->time_step;
        }
    }
}

void func_80026040(Task *task)
{
    RippleSurface *grid  = RIPPLE_WORK(task)->surface;
    int            layer = (grid->flags & RIPPLE_DOUBLE_BUFFER) ? g_sys->current_graphics_pool : 0;
    Vtx           *vtx   = grid->vertices[layer];
    int            x;
    int            y;

    for (y = 1; y < grid->rows + 1; y++) {
        for (x = 1; x < grid->cols + 1; x++) {
            vtx->v.ob[1] = grid->heights[x + y * (grid->cols + 2)];
            vtx++;
        }
    }
}

void func_80026114(Task *task)
{
    RippleSurface *grid    = RIPPLE_WORK(task)->surface;
    float          step_x  = grid->width / (grid->cols - 1.0f);
    float          step_z  = grid->depth / (grid->rows - 1.0f);
    Vec3f         *normals = grid->normals;
    Vtx           *vtx;
    int            layer;
    int            stride;
    int            cell;
    float          scaled_x;
    float          scaled_y;
    float          scaled_z;
    int            top;
    int            middle;
    int            bottom;
    int            next;
    int            face_rows;
    int            odd_column;
    int            odd_row;
    float          face_sq;
    float          face_length;
    Vtx          **layers;
    int            row_end;
    int            odd_vertex;
    float          mean_sq;
    Vec3f          a;
    Vec3f          b;
    Vec3f          normal;
    float          mean_length;
    int            x;
    int            y;

    for (y = 0; y < (face_rows = grid->rows * 2 + 2); y++) {
        for (x = 0; x < grid->cols + 1; x++) {
            odd_column = x & 1;
            odd_row    = y & 1;
            if (!odd_column) {
                if (!odd_row) {
                    cell = y / 2;
                    next = cell + 1;
                    a.x  = step_x;
                    a.y  = grid->heights[((x + 1) + (cell) * (grid->cols + 2))] - grid->heights[((x) + (cell) * (grid->cols + 2))];
                    a.z  = -step_z / 2;
                    b.x  = step_x;
                    b.y  = grid->heights[((x + 1) + (next) * (grid->cols + 2))] - grid->heights[((x) + (cell) * (grid->cols + 2))];
                    b.z  = step_z / 2;
                } else {
                    cell = (y - 1) / 2;
                    next = cell + 1;
                    a.x  = step_x;
                    a.y  = grid->heights[((x + 1) + (next) * (grid->cols + 2))] - grid->heights[((x) + (cell) * (grid->cols + 2))];
                    a.z  = step_z / 2;
                    b.x  = 0.0f;
                    b.y  = grid->heights[((x) + (next) * (grid->cols + 2))] - grid->heights[((x) + (cell) * (grid->cols + 2))];
                    b.z  = step_z;
                }
            } else {
                if (!odd_row) {
                    cell = y / 2;
                    next = cell + 1;
                    a.x  = step_x;
                    a.y  = grid->heights[((x + 1) + (cell) * (grid->cols + 2))] - grid->heights[((x) + (cell) * (grid->cols + 2))];
                    a.z  = step_z / 2;
                    b.x  = 0.0f;
                    b.y  = grid->heights[((x) + (next) * (grid->cols + 2))] - grid->heights[((x) + (cell) * (grid->cols + 2))];
                    b.z  = step_z;
                } else {
                    cell = (y + 1) / 2;
                    next = cell - 1;
                    a.x  = step_x;
                    a.y  = grid->heights[((x + 1) + (next) * (grid->cols + 2))] - grid->heights[((x) + (cell) * (grid->cols + 2))];
                    a.z  = -step_z / 2;
                    b.x  = step_x;
                    b.y  = grid->heights[((x + 1) + (cell) * (grid->cols + 2))] - grid->heights[((x) + (cell) * (grid->cols + 2))];
                    b.z  = step_z / 2;
                }
            }
            func_80027364(&a, &b, &normal);
            face_sq                             = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;
            face_length                         = sqrtf(face_sq);
            scaled_x                            = normal.x * 127.0 / face_length;
            normals[x + y * (grid->cols + 1)].x = scaled_x;
            scaled_y                            = normal.y * 127.0 / face_length;
            normals[x + y * (grid->cols + 1)].y = scaled_y;
            scaled_z                            = normal.z * 127.0 / face_length;
            normals[x + y * (grid->cols + 1)].z = scaled_z;
        }
    }

    layer  = (grid->flags & RIPPLE_DOUBLE_BUFFER) ? g_sys->current_graphics_pool : 0;
    layers = grid->vertices;
    vtx    = layers[layer];
    stride = grid->cols + 1;
    for (y = 1; y < (row_end = grid->rows + 1); y++) {
        for (x = 1; x < stride; x++) {
            odd_vertex = x & 1;
            if (odd_vertex) {
                top      = y * 2 - 2;
                middle   = y * 2 - 1;
                bottom   = y * 2;
                normal.x = (normals[x - 1 + top * stride].x + normals[x + top * stride].x +
                               normals[x - 1 + middle * stride].x + normals[x + middle * stride].x +
                               normals[x - 1 + bottom * stride].x + normals[x + bottom * stride].x) /
                           6.0f;
                normal.y = (normals[x - 1 + top * stride].y + normals[x + top * stride].y +
                               normals[x - 1 + middle * stride].y + normals[x + middle * stride].y +
                               normals[x - 1 + bottom * stride].y + normals[x + bottom * stride].y) /
                           6.0f;
                normal.z = (normals[x - 1 + top * stride].z + normals[x + top * stride].z +
                               normals[x - 1 + middle * stride].z + normals[x + middle * stride].z +
                               normals[x - 1 + bottom * stride].z + normals[x + bottom * stride].z) /
                           6.0f;
            } else {
                top      = y * 2 - 1;
                middle   = y * 2;
                bottom   = y * 2 + 1;
                normal.x = (normals[x - 1 + top * stride].x + normals[x + top * stride].x +
                               normals[x - 1 + middle * stride].x + normals[x + middle * stride].x +
                               normals[x - 1 + bottom * stride].x + normals[x + bottom * stride].x) /
                           6.0f;
                normal.y = (normals[x - 1 + top * stride].y + normals[x + top * stride].y +
                               normals[x - 1 + middle * stride].y + normals[x + middle * stride].y +
                               normals[x - 1 + bottom * stride].y + normals[x + bottom * stride].y) /
                           6.0f;
                normal.z = (normals[x - 1 + top * stride].z + normals[x + top * stride].z +
                               normals[x - 1 + middle * stride].z + normals[x + middle * stride].z +
                               normals[x - 1 + bottom * stride].z + normals[x + bottom * stride].z) /
                           6.0f;
            }
            mean_sq      = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;
            mean_length  = sqrtf(mean_sq);
            vtx->v.cn[0] = normal.x * 127.0 / mean_length;
            vtx->v.cn[1] = normal.y * 127.0 / mean_length;
            vtx->v.cn[2] = normal.z * 127.0 / mean_length;
            vtx++;
        }
    }
}

float func_80026AAC(ColHit *ray, Task *task)
{
    RippleSurface *grid   = RIPPLE_WORK(task)->surface;
    Task          *header = task;
    Vec3f          normal;
    ObjSolid      *model = (ObjSolid *) header->obj_head;
    float          y;
    float          x;
    float          gx;
    float          gz;
    int            ix;
    int            odd;
    int            row;
    float          z;
    int            iz;
    int            half;
    int            col;
    int            r2;
    float          px;
    float          py;
    float          pz;
    float          cell_w;
    float          cell_h;

    x      = ray->x;
    z      = ray->z;
    cell_w = grid->width / 10;
    cell_h = grid->depth / 10;
    gx     = x - model->tx;
    gz     = z - model->tz;
    gx     = gx / (cell_w / ((float) grid->cols - 1)) + ((float) grid->cols - 1) / 2;
    gz     = gz / (cell_h / ((float) grid->rows - 1)) + ((float) grid->rows - 1) / 2;
    if (gx < 0.0f || gz < 0.0f || (float) grid->cols - 1 < gx) {
        ray->result = 0;
        return 0.0f;
    }
    ix  = gx;
    iz  = gz * 2;
    odd = ix & 1;
    if ((odd == 0 && (iz & 1) == 0) || (odd != 0 && (iz & 1) != 0)) {
        if (gz - (float) iz / 2 < (gx - ix) * 0.5) {
            row = iz - 1;
        } else {
            row = iz;
        }
    } else if (gz - (float) (iz + 1) * 0.5 < -(gx - ix) * 0.5) {
        row = iz - 1;
    } else {
        row = iz;
    }
    if (ix >= grid->cols || row >= grid->rows * 2 - 2 || row < 0) {
        ray->result = 0;
        return 0.0f;
    }
    col    = ix + 1;
    r2     = row + 2;
    normal = grid->normals[ix + 1 + r2 * (grid->cols + 1)];
    if ((r2 & 1) == 0) {
        half = r2 / 2;
    } else {
        half = (r2 + 1) / 2;
    }
    px = -cell_w / 2 + cell_w / ((float) grid->cols - 1) * (col - 1);
    py = grid->heights[col + half * (grid->cols + 2)];
    if ((col & 1) == 0) {
        pz = -cell_h / 2 + cell_h / ((float) grid->rows - 1) * (float) (half - 1 + .5);
    } else {
        pz = -cell_h / 2 + cell_h / ((float) grid->rows - 1) * (half - 1);
    }
    if (normal.y != 0.0) {
        gx = (gx - ((float) grid->cols - 1) / 2) * (cell_w / (grid->cols - 1));
        gz = (gz - ((float) grid->rows - 1) / 2) * (cell_h / (grid->rows - 1));
        y  = -((gx - px) * normal.x + normal.z * (gz - pz)) / normal.y * 10 + py;
    } else {
        y = 0.0f;
    }
    ray->hit_x    = 0.0f;
    ray->hit_y    = y / 10 - ray->y + model->ty;
    ray->hit_z    = 0.0f;
    ray->normal_x = normal.x;
    ray->normal_y = normal.y;
    ray->normal_z = normal.z;
    if (ray->hit_y >= 0.0f) {
        ray->result = COL_HIT;
    } else {
        ray->result = 0;
    }
    ray->solid = (ObjSolid *) header->obj_head;
    return 0.0f;
}

Gfx *func_80026FE8(Gfx *gfx, int alpha, Gfx *dl, int layers, int tmem, void *image, unsigned int width, unsigned int height, int uls,
    int ult, int uls2, int ult2, int masks, int maskt)
{
    Gfx *start = gfx;

    gSPDisplayList(gfx++, dl);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, TEXEL1, 0, TEXEL0, 0, TEXEL1, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, alpha);
    GDP_LOAD_MULTI_BLOCK_AT(gfx++, image, 0, G_TX_RENDERTILE, width, height, uls, ult, masks, maskt);
    if (layers == 2) {
        GDP_LOAD_MULTI_BLOCK_AT(gfx++, image, tmem, 1, width, height, uls2, ult2, masks, maskt);
    }

    osWritebackDCache((void *) ((unsigned int) start & ANIME_ADDR_MASK), (unsigned int) gfx & ANIME_ADDR_MASK - (unsigned int) start & ANIME_ADDR_MASK);
    return gfx;
}

Vec3f *func_80027364(Vec3f *a, Vec3f *b, Vec3f *out)
{
    out->x = a->z * b->y - a->y * b->z;
    out->y = a->x * b->z - a->z * b->x;
    out->z = a->y * b->x - a->x * b->y;
    return out;
}

void func_800273D4(Task *task, Obj *obj)
{
    if (task == NULL) {
        PRINTF(("KILLED???\n"));
    }
}
