#include "konami/konami.h"
#include "audio_interface.h"
#include "sys.h"
#include "system/game_loop.h"

void func_801CB460_69E080(void) {
    KonamiLogoSteps steps = D_801D6C30_6A9850;

    steps.fn[g_sys->step_sub]();
}

void func_801CB4BC_69E0DC(void) {
    g_sys->retraces_per_game_step = 1;
    osViSetSpecialFeatures(0x15);
    osViBlack(0);
    func_80038BC8(1);
    func_801CB610_69E230();
    func_801CBF5C_69EB7C(&D_801D536C_6A7F8C);
    g_sys->step_sub++;
}

void func_801CB53C_69E15C(void) {
    if (g_sys->controller[0].button_pressed & 0x9000) {
        if (D_801D7008_6A9C28 == 1) {
            D_801D7008_6A9C28 = 2;
        } else if (D_801D7008_6A9C28 >= 2) {
            func_80038BC8(1);
            g_sys->stepw = 4;
            g_sys->step_sub = 0;
            D_801D6D00_6A9920 = 0;
        }
    }
    if (D_801D7008_6A9C28 == 5) {
        g_sys->stepw_end = 1;
    }
}

void func_801CB610_69E230(void) {
    D_801D7010_6A9C30 = 0;
    D_801D7014_6A9C34 = 0.0f;
    D_801D7018_6A9C38 = 0;
    D_801D6D00_6A9920 = 1;
    D_801D7028_6A9C48 = 0;
    D_801D7020_6A9C40 = 0;
    D_801D7024_6A9C44 = 0;
    D_801D702C_6A9C4C.amount = 0xFF;
    D_801D7008_6A9C28 = 0;
}

Gfx *func_801CB668_69E288(int buf, Gfx *dl) {
    unsigned char alpha;

    D_801D700C_6A9C2C = buf;
    D_801D701C_6A9C3C = dl;
    if (D_801D6D00_6A9920 == 0) {
        return D_801D701C_6A9C3C;
    } else {
        switch (D_801D7008_6A9C28) {
        case 0:
            alpha = D_801D702C_6A9C4C.byte[3];
            if (alpha == 0) {
                D_801D7008_6A9C28 += 1;
            }
            func_801CBF98_69EBB8();
            func_801CB95C_69E57C(alpha);
            D_801D702C_6A9C4C.amount -= 0x10;
            if (D_801D702C_6A9C4C.amount < 0) {
                D_801D702C_6A9C4C.amount = 0;
            }
            return D_801D701C_6A9C3C;
        case 1:
            if (D_801D7014_6A9C34 >= 1.0) {
                D_801D7010_6A9C30 += 1;
                D_801D7014_6A9C34 = 0.0f;
            }
            if (D_801D7010_6A9C30 >= 0x17) {
                D_801D7010_6A9C30 = 0x17;
                D_801D7018_6A9C38 = 1;
                D_801D7008_6A9C28 += 1;
            }
            func_801CBF98_69EBB8();
            func_801CB9CC_69E5EC();
            D_801D7014_6A9C34 += 0.25;
            return D_801D701C_6A9C3C;
        case 2:
            D_801D7010_6A9C30 = 0x17;
            D_801D7018_6A9C38 = 1;
            if (D_801D7028_6A9C48 == 0) {
                func_80038BC8(0x2F);
            }
            D_801D7028_6A9C48 += 1;
            if (D_801D7028_6A9C48 >= 7) {
                func_801CBF5C_69EB7C(&D_801D5348_6A7F68);
                D_801D7028_6A9C48 = 0;
                D_801D7008_6A9C28 += 1;
            }
            func_801CBF98_69EBB8();
            func_801CB9CC_69E5EC();
            return D_801D701C_6A9C3C;
        case 3:
            D_801D7028_6A9C48 += 1;
            if (D_801D7028_6A9C48 > 0x100) {
                D_801D702C_6A9C4C.amount = 0;
                D_801D7008_6A9C28 += 1;
            }
            if (D_801D7020_6A9C40 != 0x1F) {
                D_801D7020_6A9C40 += 1;
            }
            func_801CBF98_69EBB8();
            return D_801D701C_6A9C3C;
        case 4:
            alpha = D_801D702C_6A9C4C.byte[3];
            if (alpha == 0xFF) {
                D_801D7008_6A9C28 += 1;
            }
            func_801CBF98_69EBB8();
            func_801CB95C_69E57C(alpha);
            D_801D702C_6A9C4C.amount += 0x10;
            if (D_801D702C_6A9C4C.amount >= 0x100) {
                D_801D702C_6A9C4C.amount = 0xFF;
            }
            return D_801D701C_6A9C3C;
        case 5:
            func_80038BC8(1);
            D_801D6D00_6A9920 = 0;
            func_80003728(4);
            return D_801D701C_6A9C3C;
        }
    }
}

void func_801CB95C_69E57C(unsigned char alpha) {
    if (alpha != 0) {
        gDPPipeSync(D_801D701C_6A9C3C++);
        gDPSetPrimColor(D_801D701C_6A9C3C++, 0, 0, 0, 0, 0, alpha);
        gSPDisplayList(D_801D701C_6A9C3C++, D_801D5430_6A8050);
    }
}

void func_801CB9CC_69E5EC(void) {
    KonamiLogoMtx *m = &D_801D6D08_6A9928[D_801D700C_6A9C2C];

    func_801CBC8C_69E8AC(m, D_801CCFC0_69FBE0, D_801D7010_6A9C30, D_801D7014_6A9C34);
    gSPDisplayList(D_801D701C_6A9C3C++, D_801D5390_6A7FB0);
    func_801CBAF8_69E718(D_801D54B8_6A80D8, &m->obj[0], D_801CCA80_69F6A0, D_801D7010_6A9C30, D_801D7014_6A9C34);
    func_801CBAF8_69E718(D_801D5E48_6A8A68, &m->obj[1], D_801CC7E0_69F400, D_801D7010_6A9C30, D_801D7014_6A9C34);
    func_801CBAF8_69E718(D_801D67D8_6A93F8, &m->obj[2], D_801CCD20_69F940, D_801D7010_6A9C30, D_801D7014_6A9C34);
    gDPPipeSync(D_801D701C_6A9C3C++);
}

#ifdef NON_MATCHING
void func_801CBAF8_69E718(Gfx *dl, Mtx *mtx, KonamiLogoKey *keys, int frame, float t) {
    KonamiLogoKey *next;
    float x, y, z;
    float rx, ry;

    keys += frame;
    next = keys + 1;
    if (D_801D7018_6A9C38 == 1) {
        next = keys;
    }
    x = keys->b[0] + (next->b[0] - keys->b[0]) * t;
    y = keys->b[1] + (next->b[1] - keys->b[1]) * t;
    z = keys->b[2] + (next->b[2] - keys->b[2]) * t;
    rx = keys->a[0] + (next->a[0] - keys->a[0]) * t;
    ry = keys->a[1] + (next->a[1] - keys->a[1]) * t;
    guPosition(mtx, rx, ry, keys->a[2] + (next->a[2] - keys->a[2]) * t, (keys->c + (next->c - keys->c) * t) * 0.01, x, y, z);
    gSPMatrix(D_801D701C_6A9C3C++, mtx, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(D_801D701C_6A9C3C++, dl);
    gSPPopMatrix(D_801D701C_6A9C3C++, G_MTX_MODELVIEW);
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/konami/konami/func_801CBAF8_69E718.s")
#endif

#ifdef NON_MATCHING
void func_801CBC8C_69E8AC(KonamiLogoMtx *m, KonamiLogoKey *keys, int frame, float t) {
    KonamiLogoKey *next;
    unsigned short perspnorm;
    float eye_x, eye_y, eye_z;
    float at_x, at_y, at_z;

    keys += frame;
    next = keys + 1;
    if (D_801D7018_6A9C38 == 1) {
        next = keys;
    }
    eye_x = keys->a[0] + (next->a[0] - keys->a[0]) * t;
    eye_y = keys->a[1] + (next->a[1] - keys->a[1]) * t;
    eye_z = keys->a[2] + (next->a[2] - keys->a[2]) * t;
    at_x = keys->b[0] + (next->b[0] - keys->b[0]) * t;
    at_y = keys->b[1] + (next->b[1] - keys->b[1]) * t;
    at_z = keys->b[2] + (next->b[2] - keys->b[2]) * t;
    gSPViewport(D_801D701C_6A9C3C++, &D_801D6C38_6A9858);
    guPerspective(&m->proj, &perspnorm, keys->c + (next->c - keys->c) * t, 1.3333334f, 1.0f, 1000.0f, 1.0f);
    gSPPerspNormalize(D_801D701C_6A9C3C++, perspnorm);
    gSPMatrix(D_801D701C_6A9C3C++, &m->proj, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    guLookAt(&m->view, eye_x, eye_y, eye_z, at_x, at_y, at_z, 0.0f, 1.0f, 0.0f);
    gSPMatrix(D_801D701C_6A9C3C++, &m->view, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPClipRatio(D_801D701C_6A9C3C++, FRUSTRATIO_3);
    gDPSetScissor(D_801D701C_6A9C3C++, G_SC_NON_INTERLACE, 0, 0, 319, 239);
    guMtxIdent(&m->ident);
    gSPMatrix(D_801D701C_6A9C3C++, &m->ident, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/konami/konami/func_801CBC8C_69E8AC.s")
#endif

void func_801CBF5C_69EB7C(KonamiLogoMap *map) {
    D_801D7030_6A9C50 = *map;
}

#ifdef NON_MATCHING
void func_801CBF98_69EBB8(void) {
    unsigned char *pal;
    if (D_801D7030_6A9C50.enabled != 0) {
        gSPDisplayList(D_801D701C_6A9C3C++, D_801D6C48_6A9868);
        pal = (D_801D7020_6A9C40 << 5) + D_801D7044_6A9C64;
        gDPLoadTLUT_pal16(D_801D701C_6A9C3C++, 0, pal);
        func_801CC0C4_69ECE4(&D_801D7030_6A9C50);
        gDPPipeSync(D_801D701C_6A9C3C++);
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/konami/konami/func_801CBF98_69EBB8.s")
#endif

void func_801CC0C4_69ECE4(KonamiLogoMap *map) {
    int tx;
    int ty;
    int sx, sy;
    int size;
    int w, h;
    int left, top;
    int lim;
    int dsdx, dtdy;
    int x0, y0;
    int mx;
    int cur_tile;
    int xl, yl, xh, yh, s, t;
    unsigned char *cells;
    unsigned short *tiles;
    int my;
    int offs;
    int cell, px, py;
    int tile;
    int cx;
    int cy;
    int unused_0;
    int unused_1;
    int unused_2;

    cells = map->cells;
    tiles = map->tiles;
    cur_tile = 0xFFFF;
    lim = 0xFFFF;
    sx = 0;
    sy = 0;
    size = 32;
    dsdx = 4 << 10;
    dtdy = 1 << 10;
    w = 320;
    h = 240;
    left = 0;
    top = 0;
    for (ty = 0; ty < 9; ty++) {
        if (ty < 0) {
            continue;
        }
        if (ty > lim) {
            continue;
        }
        my = ty * size + sy;
        y0 = ty * size - sy;
        yl = y0;
        yh = y0 + size - 1;
        t = 0;
        if (y0 >= h) {
            continue;
        }
        if (yh < top) {
            continue;
        }
        if (y0 < top) {
            t = top - y0;
            yl = top;
        }
        if (yh >= h) {
            yh = h - 1;
        }
        yl <<= 2;
        yh <<= 2;
        t <<= 5;
        for (tx = 0; tx < 11; tx++) {
            if (tx < 0) {
                continue;
            }
            if (tx > lim) {
                continue;
            }
            mx = tx * size + sx;
            x0 = tx * size - sx;
            xl = x0;
            xh = x0 + size - 1;
            s = 0;
            if (x0 >= w) {
                continue;
            }
            if (xh < left) {
                continue;
            }
            if (x0 < left) {
                s = left - x0;
                xl = left;
            }
            if (xh >= w) {
                xh = w - 1;
            }
            xl <<= 2;
            xh <<= 2;
            s <<= 5;

            cx = mx / map->cell_w;
            cx %= map->cols;
            cy = my / map->cell_h;
            cy %= map->rows;
            px = (mx % map->cell_w) / size;
            py = (my % map->cell_h) / size;
            cell = *(cells + cx + map->cols * cy);
            tile = tiles[(map->cell_w / size) * cell * (map->cell_h / size) + px + (map->cell_w / size) * py];
            if (tile != cur_tile) {
                cur_tile = tile;
                switch (map->format) {
                case 0:
                    gDPLoadTextureBlock(D_801D701C_6A9C3C++, map->image + ((tile << 10) / 4) * 2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                case 1:
                    offs = ((map->offsets[tile] & 0xF00) << 3) + ((map->offsets[tile] & 0xFF) << 7);
                    gDPLoadTextureBlock(D_801D701C_6A9C3C++, map->image + ((offs << 2) * 2), G_IM_FMT_CI, G_IM_SIZ_8b, 32, 32, 0,
                                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                case 2:
                    offs = ((map->offsets[tile] & 0xF00) << 2) + ((map->offsets[tile] & 0xFF) << 6);
                    gDPLoadTextureBlock_4b(D_801D701C_6A9C3C++, map->image + ((offs << 2) * 2), G_IM_FMT_CI, 32, 32, 0,
                                           G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                }
            }
            gSPTextureRectangle(D_801D701C_6A9C3C++, xl, yl, xh, yh, G_TX_RENDERTILE, s, t, dsdx, dtdy);
        }
    }
}
