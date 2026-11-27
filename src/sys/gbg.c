#include "sys/gbg.h"
#include "common.h"
#include "sys/sys.h"
#include "sys/wave_uty.h"
#include "unk.h"

void func_80021894(unsigned char *texture_data, unsigned char *palette_data, float u, float v);
void func_80022214(ObjGbg *gbg);
void func_80022A74(ObjGbg *gbg);
void func_80021B98(unsigned char *texture_data, float u, float v, int width, int height, int x, int y);
void func_80022500(int x, int y, int u, int v, int width, int height, ObjGbg *gbg);
void func_80022348(int x, int y, int u, int v, int width, int height, ObjGbg *gbg);
void func_80022EC0(ObjGbg *gbg);
void func_80022DF4(int x, int y, int u, int v, int width, int height, ObjGbg *gbg);

// clang-format off

// <<<<< data >>>>>
Gfx D_8006D0F0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPEndDisplayList(),
};

int D_8006D158 = 0;

int D_8006D15C = 0;

int D_8006D160 = SCREEN_WIDTH;

int D_8006D164 = SCREEN_HEIGHT;

// clang-format on

void func_800215D0(void)
{
    static int D_8006D168 = SCREEN_HEIGHT;

    if (g_sys->controller[1].button_pressed & U_JPAD) {
        D_8006D168--;
    }
    if (g_sys->controller[1].button_pressed & D_JPAD) {
        D_8006D168++;
    }
    D_8006D164 = D_8006D168;
    gDPSetColorImage(g_sys_glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, OS_K0_TO_PHYSICAL(g_frame_buffers[g_sys->current_frame_buffer]));
    gSPDisplayList(g_sys_glistp++, D_8006D0F0);
}

int func_800216B0(int x0, int y0, int x1, int y1)
{
    if (x0 < 0) {
        return 0;
    }
    if (x1 > SCREEN_WIDTH) {
        return 0;
    }
    if (y0 < 0) {
        return 0;
    }
    if (y1 > SCREEN_HEIGHT) {
        return 0;
    }
    if (x1 < x0) {
        return 0;
    }
    if (y1 < y0) {
        return 0;
    }
    D_8006D158 = x0;
    D_8006D15C = y0;
    D_8006D160 = x1;
    D_8006D164 = y1;
    return 1;
}

void func_80021740(ObjGbg *gbg)
{
    if (!(gbg->flags & GBG_RAW_DATA)) {
        gSPSegment(g_sys_glistp++, WAVE_SEGMENT, func_800141C4(gbg->wave_no));
        gbg->texture_data = (unsigned char *) WAVE_SEGMENT_ADDR;
    }

    if (gbg->texture_data == (unsigned char *) -1) {
        PRINTF(("gbgDraw: undecoded wave %d\n", gbg->wave_no));
        // Crash on purpose.
        *(volatile int *) -1 = 0;
    }

    gbg->bits_per_pixel = 8;
    if (gbg->flags & GBG_4B) {
        gbg->bits_per_pixel = 4;
    } else if (!(gbg->flags & GBG_8B)) {
        gbg->bits_per_pixel = 16;
    }

    if (!(gbg->flags & GBG_RAW_DATA)) {
        gbg->palette_data = gbg->texture_data + gbg->texture_width * gbg->texture_height * gbg->bits_per_pixel / 8;
    }

    if (gbg->flags & GBG_PANORAMA) {
        func_80021894(gbg->texture_data, gbg->palette_data, gbg->u, gbg->v);
    } else if (gbg->flags & GBG_CLIP) {
        func_80022214(gbg);
    } else {
        func_80022A74(gbg);
    }
}

void func_80021894(unsigned char *texture_data, unsigned char *palette_data, float u, float v)
{
    float frac = u - (int) u;
    float tex_u;
    float tex_v;
    int   x;
    int   y;
    int   width;
    int   height;

    if (u < 0.0f) {
        u += (-(int) u / 1280 + 1) * 640.0f * 2;
        u = u + frac;
    }
    if (1280.0f <= u) {
        u = (int) u % 1280;
        u = u + frac;
    }

    if (240.0f < v) {
        v = 240.0f;
    } else if (v < 0.0f) {
        v = 0.0f;
    }

    gDPLoadTLUT_pal256(g_sys_glistp++, palette_data);

    tex_v = v / 2;
    for (y = D_8006D15C; y < D_8006D164; y += 20, tex_v += 10.0f) {
        if (D_8006D164 - 24 < y) {
            height = (D_8006D164 - y + 1) / 2;
        } else {
            height = 12;
        }

        for (x = D_8006D158, tex_u = u / 2; x < D_8006D160; x += 326) {
            if (D_8006D160 - 328 < x) {
                width = (D_8006D160 - x + 1) / 2;
            } else {
                width = 164;
            }

            func_80021B98(texture_data, tex_u, tex_v, width, height, x, y);
            tex_u += width - 1;
        }
    }
}

void func_80021B98(unsigned char *texture_data, float u, float v, int width, int height, int x, int y)
{
    int uls;
    int ult;

    uls = u;
    ult = v;
    if (width + u - 2 - 1 > 640.0f) {
        gDPLoadTextureTile(g_sys_glistp++, texture_data, G_IM_FMT_CI, G_IM_SIZ_8b, 640, 0, uls, ult, 640, ult + height - 1, 0,
            G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
        gSPTextureRectangle(g_sys_glistp++, x << 2, y << 2, (x + (640 - uls) * 2 - 1) << 2,
            (y + height * 2 - 1) << 2, G_TX_RENDERTILE, (int) (u * 32), (int) (v * 32), 0x200, 0x200);
        gDPLoadTextureTile(g_sys_glistp++, texture_data, G_IM_FMT_CI, G_IM_SIZ_8b, 640, 0, 0, ult, uls + width - 641,
            ult + height - 1, 0, G_TX_WRAP, G_TX_CLAMP, 0, 0, 0, 0);
        gSPTextureRectangle(g_sys_glistp++, (x + (640 - uls) * 2 - 2) << 2, y << 2, (x + width * 2 - 1) << 2,
            (y + height * 2 - 1) << 2, G_TX_RENDERTILE, (int) (u * 32) - (uls << 5), (int) (v * 32),
            0x200, 0x200);
    } else {
        gDPLoadTextureTile(g_sys_glistp++, texture_data, G_IM_FMT_CI, G_IM_SIZ_8b, 640, 0, uls, ult, uls + width - 1,
            ult + height - 1, 0, G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
        gSPTextureRectangle(g_sys_glistp++, x << 2, y << 2, (x + width * 2 - 1) << 2, (y + height * 2 - 1) << 2,
            G_TX_RENDERTILE, (int) (u * 32), (int) (v * 32), 0x200, 0x200);
    }
}

void func_80022214(ObjGbg *gbg)
{
    int x   = gbg->x;
    int top = gbg->y;
    int u   = gbg->u;
    int v   = gbg->v;
    int next;
    int rows = 2048.0f / gbg->w;
    int y;

    func_80022EC0(gbg);

    for (y = top; y < (int) gbg->h + top; y += rows) {
        next = y + rows;
        if ((int) gbg->h + top < next) {
            rows = (int) gbg->h + top - y;
            next = y + rows;
        }
        func_80022348(x, y, u, v, (int) gbg->w, rows, gbg);
        v += rows;
    }
}

void func_80022348(int x, int y, int u, int v, int width, int height, ObjGbg *gbg)
{
    int diff;
    int n;

    if (u < 0) {
        n = -u / gbg->texture_width + 1;
        u += n * gbg->texture_width;
    }
    u %= gbg->texture_width;

    if (v < 0) {
        n = -v / gbg->texture_height + 1;
        v += n * gbg->texture_height;
    }
    v %= gbg->texture_height;

    if (x < gbg->min_x) {
        diff = gbg->min_x - x;
        x    = gbg->min_x;
        u += diff;
        width -= diff;
    }
    if (x < gbg->max_x) {
        if (!(x + width < gbg->max_x)) {
            width = gbg->max_x - x;
        }
        if (y < gbg->min_y) {
            diff = gbg->min_y - y;
            y    = gbg->min_y;
            v += diff;
            height -= diff;
        }
        if (y < gbg->max_y) {
            if (!(y + height < gbg->max_y)) {
                height = gbg->max_y - y;
            }
            func_80022500(x, y, u, v, width, height, gbg);
        }
    }
}

void func_80022500(int x, int y, int u, int v, int width, int height, ObjGbg *gbg)
{
    int fmt;

    if (gbg->flags & GBG_CI) {
        fmt = G_IM_FMT_CI;
    } else if (gbg->flags & GBG_IA) {
        fmt = G_IM_FMT_IA;
    } else {
        fmt = G_IM_FMT_RGBA;
    }

    if (gbg->flags & GBG_4B) {
        gDPLoadTextureTile_4b(g_sys_glistp++, gbg->texture_data, G_IM_FMT_CI, gbg->texture_width, gbg->texture_height, u, v,
            u + width - 1, v + height - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else if (gbg->flags & GBG_8B) {
        gDPLoadTextureTile(g_sys_glistp++, gbg->texture_data, fmt, G_IM_SIZ_8b, gbg->texture_width, gbg->texture_height, u, v,
            u + width - 1, v + height - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else {
        gDPLoadTextureTile(g_sys_glistp++, gbg->texture_data, G_IM_FMT_RGBA, G_IM_SIZ_16b, gbg->texture_width, gbg->texture_height, u, v,
            u + width - 1, v + height - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    }

    gSPTextureRectangle(g_sys_glistp++, x << 2, y << 2, (x + width) << 2, (y + height) << 2, G_TX_RENDERTILE,
        u << 5, v << 5, 0x0400, 0x0400);
}

void func_80022A74(ObjGbg *gbg)
{
    int x    = gbg->x;
    int y    = gbg->y;
    int u    = gbg->u;
    int v    = gbg->v;
    int rows = 2048 / (int) gbg->w;
    int row;
    int n;

    if (u < 0) {
        n = -u / gbg->texture_width + 1;
        u += n * gbg->texture_width;
    }
    u %= gbg->texture_width;

    if (v < 0) {
        n = -v / gbg->texture_height + 1;
        v += n * gbg->texture_height;
    }
    v %= gbg->texture_height;

    func_80022EC0(gbg);

    if (gbg->texture_height < (int) gbg->h + v) {
        // Down to the bottom of the texture, then again from its top.
        for (row = v; row < gbg->texture_height; row += rows, y += rows) {
            if (gbg->texture_height < row + rows) {
                func_80022DF4(x, y, u, row, (int) gbg->w, rows - (row + rows - gbg->texture_height), gbg);
                v -= row + rows - gbg->texture_height;
                y -= row + rows - gbg->texture_height;
            } else {
                func_80022DF4(x, y, u, row, (int) gbg->w, rows, gbg);
            }
        }
        for (row = 0; row < (int) gbg->h + v - gbg->texture_height; row += rows, y += rows) {
            func_80022DF4(x, y, u, row, (int) gbg->w, rows, gbg);
        }
    } else {
        for (row = v; row < (int) gbg->h + v; row += rows, y += rows) {
            func_80022DF4(x, y, u, row, (int) gbg->w, rows, gbg);
        }
    }
}

void func_80022DF4(int x, int y, int u, int v, int width, int height, ObjGbg *gbg)
{
    if (gbg->texture_width < (int) gbg->w + u) {
        func_80022500(x, y, u, v, gbg->texture_width - u, height, gbg);
        func_80022500(x + (gbg->texture_width - u), y, 0, v, width - (gbg->texture_width - u), height, gbg);
    } else {
        func_80022500(x, y, u, v, (int) gbg->w, height, gbg);
    }
}

void func_80022EC0(ObjGbg *gbg)
{
    gSPDisplayList(g_sys_glistp++, D_8006D0F0);

    if (gbg->flags & GBG_XLU) {
        gDPSetPrimColor(g_sys_glistp++, 0, 0, 255, 255, 255, gbg->alpha);
        gDPSetRenderMode(g_sys_glistp++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        if (gbg->flags & GBG_CUTOUT) {
            gDPSetCombineLERP(g_sys_glistp++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
            gDPSetAlphaCompare(g_sys_glistp++, G_AC_THRESHOLD);
            gDPSetBlendColor(g_sys_glistp++, 0, 0, 0, 1);
        } else {
            gDPSetCombineLERP(g_sys_glistp++, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE);
        }
    } else if (gbg->flags & GBG_CUTOUT) {
        gDPSetRenderMode(g_sys_glistp++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
        gDPSetAlphaCompare(g_sys_glistp++, G_AC_THRESHOLD);
        gDPSetBlendColor(g_sys_glistp++, 0, 0, 0, 1);
    }

    gDPSetTextureFilter(g_sys_glistp++, G_TF_POINT);

    if (gbg->flags & GBG_CI) {
        if (gbg->flags & GBG_8B) {
            gDPLoadTLUT_pal256(g_sys_glistp++, gbg->palette_data);
        } else {
            gDPLoadTLUT_pal16(g_sys_glistp++, 0, gbg->palette_data);
        }
    } else {
        gDPSetTextureLUT(g_sys_glistp++, G_TT_NONE);
    }
}
