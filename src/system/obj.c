#include "system/obj.h"
#include "system/gbg.h"
#include "structs.h"
#include "system/sys.h"
#include "system/anime.h"
#include "unk.h"
#include "system/gfx_data.h"

void           func_80008920(ObjSprite *arg0);
unsigned short func_80009408(ObjSpriteFlags flags, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void           func_80009548(ObjSprite *arg0, ObjSpriteTex *tex);
void           func_8000A130(void);
void           func_8000A18C(void);
void           func_8000A228(ObjSprite *sprite);
void           func_8000A344(void);
void           func_8000A394(ObjMoji *moji);
void           func_8000A430(void);
void           func_8000A480(ObjGbg *arg0);
void           func_8000A4F8(void);
void           func_8000A5C4(ObjSolid *solid);
void           func_8000A614(void);

// clang-format off

// <<<<< data >>>>>
Gfx *D_8005B950[8] = {
    D_8006D648,
    D_8006D678,
    D_8006D708,
    D_8006D7C8,
    D_8006D6A8,
    D_8006D6D8,
    D_8006D738,
    D_8006D798,
};

short D_8005B970[1][2] = {
    { 0x0000, 0x0018 },
};

ObjSolid D_8005B974 = {
    { NULL, 0x82, 0x05, 0x0000 },
    0.0f, 0.0f, 0.0f,
    0, 0, 0,
    0.1f, 0.1f, 0.1f,
    0.0f,
    0,
    0,
    { { 0, 0 } },
    0,
    1,
    { 0.1f, 0.1f },
    0.0f,
    NULL,
    NULL,
    0,
    0,
    { 0 },
    NULL,
};

unsigned int D_8005BA0C = 0;

// <<<<< rodata >>>>>
const unsigned int D_8007AAA0[] = {
    0x00000000,
    0x00008000,
    0x0000C000,
    0x0000C000,
    0x00008000
};

const unsigned int D_8007AAB4[] = {
    0x00000000,
    0x00000002,
    0x00000003,
    0x00000004,
    0x00000001
};

// <<<<< bss >>>>>
void (*D_80167A60)(void);
int            D_80167A64;
unsigned short D_80167A68;
int            D_80167A6C;
unsigned short D_80167A70;
unsigned short D_80167A72;
unsigned short D_80167A74;
// clang-format on

void func_800086F0(void)
{
    D_80167A60 = func_800086F0;
    D_80167A68 = D_80167A70 = D_80167A72 = 0xFFFF;
    D_80167A74                           = 0;
    gSPDisplayList(D_8015C5CC++, D_8006D600);
    func_80009408(g_sys_real.unk_c5d10, g_sys_real.unk_c5d06, g_sys_real.unk_c5d08, g_sys_real.unk_c5d0a, g_sys_real.unk_c5d0c);
}

void func_80008798(void)
{
    gSPDisplayList(D_8015C5CC++, D_8006D600);
}

void func_800087C4(ObjLayer *arg0)
{
    Obj  *obj;
    short i;

    if (g_sys_real.stop_processing_draw_lists != 1) {
        for (i = 0; i < arg0->size; i++) {
            obj = arg0->objects[i];
            if (obj->kind & 0x80) {
                continue;
            }
            switch (obj->kind) {
                case 1:
                    func_800086F0();
                    func_80008920((ObjSprite *) obj);
                    break;
                case 2:
                    anime_draw((ObjSolid *) obj);
                    D_80167A60 = func_800086F0;
                    D_80167A68 = 0xFFFF;
                    break;
                case 3:
                    break;
                case 4:
                    D_80167A60 = func_800086F0;
                    D_80167A68 = 0xFFFF;
                    D_80167A72 = 0xFFFF;
                    break;
                case 5:
                    func_800215D0();
                    func_80021740((ObjGbg *) obj);
                    D_80167A60 = func_800086F0;
                    D_80167A68 = D_80167A72 = 0xFFFF;
                    break;
            }
        }
    }
}

#ifdef NON_MATCHING
void func_80008920(ObjSprite *arg0)
{
    ObjSpritePart *part;
    ObjMoji       *moji;
    int            scale;
    int            scale_x;
    int            base_x, base_y;
    unsigned short scaled;
    unsigned short filter;
    int            scale_y;
    int            dir_x;
    int            s, t;
    int            tex_w, tex_h;
    int            clip_x0, clip_y0;
    int            clip_x0_in, clip_y0_in;
    int            clip_x1, clip_y1;
    int            clip_x1_in, clip_y1_in;
    int            dir_y;
    int            xl, yl, xh, yh;
    ObjSpriteTex  *tex;

    part = arg0->unk_34;
    if (part == NULL) {
        return;
    }

    clip_x0 = 0;
    if (arg0->unk_18 & 0x400) {
        moji = g_sys_real.mojis;
        moji += (arg0->unk_18 & 0xF0) >> 4;
        clip_x0    = moji->unk_34 * 4;
        clip_y0    = moji->unk_36 * 4;
        clip_x0_in = clip_x0 + 4;
        clip_y0_in = clip_y0 + 4;
        clip_x1    = moji->unk_38 * 4;
        clip_y1    = moji->unk_3a * 4;
        clip_x1_in = clip_x1 - 4;
        clip_y1_in = clip_y1 - 4;
    } else {
        clip_x0_in = 4;
        clip_y0_in = 4;
        clip_y0    = 0;
        clip_x1    = 0x4FC;
        clip_y1    = 0x3BC;
        clip_x1_in = 0x4F8;
        clip_y1_in = 0x3B8;
    }

    moji = g_sys_real.mojis;
    moji += arg0->unk_18 & 0xF;
    if (arg0->unk_18 & 0x100) {
        base_x = arg0->unk_1c - moji->unk_c;
    } else {
        base_x = arg0->unk_1c;
    }
    if (arg0->unk_18 & 0x200) {
        base_y = arg0->unk_20 - moji->unk_10;
    } else {
        base_y = arg0->unk_20;
    }

    scale = 0x400;
    if (g_sys_real.unk_c5d10.unk_b25 == 1) {
        scaled = 0;
        if (g_sys_real.unk_c5d10.mode == 0) {
            scale  = 0x1000;
            filter = 1;
        } else {
            scaled = arg0->unk_8.scaled;
            filter = 0;
            if (g_sys_real.unk_c5d10.unk_b27 == 1) {
                gDPSetPrimColor(D_8015C5CC++, 0, 0,
                    (arg0->unk_d * g_sys_real.unk_c5d06) >> 8,
                    (arg0->unk_e * g_sys_real.unk_c5d08) >> 8,
                    (arg0->unk_f * g_sys_real.unk_c5d0a) >> 8,
                    (arg0->unk_10 * g_sys_real.unk_c5d0c) >> 8);
            }
        }
    } else {
        filter = func_80009408(arg0->unk_8, arg0->unk_d, arg0->unk_e, arg0->unk_f, arg0->unk_10);
        if (filter == 1) {
            scale  = 0x1000;
            scaled = 0;
        } else {
            scaled = arg0->unk_8.scaled;
        }
    }

    if (scaled == 0) {
        scale_x = scale;
        scale_y = 0x400;
    } else {
        if (arg0->unk_2c <= 1e-06) {
            return;
        }
        if (arg0->unk_30 <= 1e-06) {
            return;
        }
        scale_x = 1024.0f / arg0->unk_2c;
        scale_y = 1024.0f / arg0->unk_30;
    }

    if (arg0->unk_8.flip_x) {
        dir_x = -1;
    } else {
        dir_x = 1;
    }
    if (arg0->unk_8.flip_y) {
        dir_y = -1;
    } else {
        dir_y = 1;
    }

    for (;; part++) {
        if ((part->flags & 0x4000) == 0x4000) {
            tex = &arg0->unk_14[part->flags & 0x1FFF];
            func_80009548(arg0, tex);
            tex_w = (1 << arg0->unk_8.tex_width_shift) << 5;
            tex_h = (1 << arg0->unk_8.tex_height_shift) << 5;
        }
        if (part->flags & 0x2000) {
            if (part->flags & 0x8000) {
                return;
            }
            continue;
        }

        if (arg0->unk_8.flip_x) {
            s = (((part->s - tex_w) + (part->width << 5)) * dir_x + tex_w) - D_80167A74;
        } else {
            s = part->s - D_80167A74;
        }
        if (arg0->unk_8.flip_y) {
            t = (((part->t - tex_h) + (part->height << 5)) * dir_y + tex_h) - D_80167A74;
        } else {
            t = part->t - D_80167A74;
        }

        if (scaled == 0) {
            if (arg0->unk_8.flip_x) {
                xl = ((part->x + part->width) * dir_x + base_x) * 4;
                xh = ((base_x - filter) + part->x * dir_x) * 4;
            } else {
                xl = (part->x * dir_x + base_x) * 4;
                xh = (part->width - filter) * dir_x * 4 + xl;
            }
            if (arg0->unk_8.flip_y) {
                yl = ((part->y + part->height) * dir_y + base_y) * 4;
                yh = ((base_y - filter) + part->y * dir_y) * 4;
            } else {
                yl = (part->y * dir_y + base_y) * 4;
                yh = (part->height - filter) * dir_y * 4 + yl;
            }
            if (xl < clip_x0) {
                if (xh < clip_x0_in) {
                    if (arg0->unk_18 & 0x2000) {
                        arg0->header.kind = 0;
                    }
                    goto next;
                }
                s += (clip_x0 - xl) * 8;
                xl = clip_x0;
            }
            if (yl < clip_y0) {
                if (yh < clip_y0_in) {
                    if (arg0->unk_18 & 0x4000) {
                        arg0->header.kind = 0;
                    }
                    goto next;
                }
                t += (clip_y0 - yl) * 8;
                yl = clip_y0;
            }
        } else {
            if (arg0->unk_8.flip_x) {
                xh = ((float) base_x + (float) ((dir_x * part->x << 10) / scale_x)) * 4.0f;
                xl = ((float) base_x + (float) ((dir_x * (part->x + part->width) << 10) / scale_x)) * 4.0f;
            } else {
                xl = ((float) base_x + (float) ((dir_x * part->x << 10) / scale_x)) * 4.0f;
                xh = ((float) base_x + (float) ((dir_x * (part->x + part->width) << 10) / scale_x)) * 4.0f;
            }
            if (arg0->unk_8.flip_y) {
                yh = ((float) base_y + (float) ((dir_y * part->y << 10) / scale_y)) * 4.0f;
                yl = ((float) base_y + (float) ((dir_y * (part->y + part->height) << 10) / scale_y)) * 4.0f;
            } else {
                yl = ((float) base_y + (float) ((dir_y * part->y << 10) / scale_y)) * 4.0f;
                yh = ((float) base_y + (float) ((dir_y * (part->y + part->height) << 10) / scale_y)) * 4.0f;
            }
            if (xl < clip_x0) {
                if (xh < clip_x0_in) {
                    if (arg0->unk_18 & 0x2000) {
                        arg0->header.kind = 0;
                    }
                    goto next;
                }
                s += ((clip_x0 - xl) * scale_x) >> 7;
                xl = clip_x0;
            }
            if (yl < clip_y0) {
                if (yh < clip_y0_in) {
                    if (arg0->unk_18 & 0x4000) {
                        arg0->header.kind = 0;
                    }
                    goto next;
                }
                t += ((clip_y0 - yl) * scale_y) >> 7;
                yl = clip_y0;
            }
        }

        if (clip_x1 < xh) {
            if (clip_x1_in < xl) {
                if (arg0->unk_18 & 0x2000) {
                    arg0->header.kind = 0;
                }
                goto next;
            }
            xh = clip_x1;
        }
        if (clip_y1 < yh) {
            if (clip_y1_in < yl) {
                if (arg0->unk_18 & 0x4000) {
                    arg0->header.kind = 0;
                }
                goto next;
            }
            yh = clip_y1;
        }

        gSPTextureRectangle(D_8015C5CC++, xl, yl, xh, yh, G_TX_RENDERTILE, s, t, scale_x, scale_y);
        gDPPipeSync(D_8015C5CC++);
    next:
        if (part->flags >= 0x8000) {
            return;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj/func_80008920.s")
#endif

unsigned short func_80009408(ObjSpriteFlags flags, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (flags.mode != D_80167A70) {
        D_80167A70 = flags.mode;
        gSPDisplayList(D_8015C5CC++, D_8005B950[D_80167A70]);
        if (D_80167A70 >= 5) {
            D_80167A74 = 0x10;
        } else {
            D_80167A74 = 0;
        }
    }
    if (flags.mode != 0) {
        gDPSetPrimColor(D_8015C5CC++, 0, 0, r, g, b, a);
        if (flags.unk_b28 == 0) {
            gDPSetAlphaCompare(D_8015C5CC++, G_AC_THRESHOLD);
        } else {
            gDPSetAlphaCompare(D_8015C5CC++, G_AC_DITHER);
        }
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj/func_80009548.s")

void func_8000A0F0(void)
{
    func_8000A130();
    func_8000A4F8();
    func_8000A344();
    func_8000A430();
    func_8000A614();
}

void func_8000A130(void)
{
    ObjSprite *sprite = g_sys_real.sprites;
    int        i;

    for (i = 0; i < 24; i++) {
        func_8000A228(sprite);
        sprite++;
        sprite[-1].unk_3c = 0;
    }
    func_8000A18C();
}

void func_8000A18C(void)
{
    g_sys_real.unk_c5d0c      = 0xFF;
    g_sys_real.unk_c5d10_word = 0;
    g_sys_real.unk_c5d0a      = g_sys_real.unk_c5d0c;
    g_sys_real.unk_c5d08      = g_sys_real.unk_c5d0a;
    g_sys_real.unk_c5d06      = g_sys_real.unk_c5d08;
}

void func_8000A1BC(int start, int end)
{
    ObjSprite *sprite = &g_sys_real.sprites[start];
    int        i;

    for (i = start; i < end; i++) {
        func_8000A228(sprite);
        sprite++;
    }
}

void func_8000A228(ObjSprite *sprite)
{
    sprite->unk_8_word             = 0;
    sprite->header.kind            = 0x81;
    sprite->unk_8.unk_b22          = 1;
    sprite->unk_8.unk_b19          = 1;
    sprite->unk_1c_word            = 0;
    sprite->unk_8.tex_width_shift  = 9;
    sprite->unk_20_word            = 0;
    sprite->unk_c                  = 0xFF;
    sprite->unk_8.tex_height_shift = 9;
    sprite->unk_18                 = 0;
    sprite->header.pri             = 0;
    sprite->header.s_pri           = 0;
    sprite->unk_34                 = NULL;
    sprite->unk_14                 = NULL;
    sprite->unk_d                  = 0xFF;
    sprite->unk_e                  = 0xFF;
    sprite->unk_f                  = 0xFF;
    sprite->unk_10                 = 0xFF;
    sprite->unk_2c                 = 1.0f;
    sprite->unk_30                 = 1.0f;
}

#ifdef NON_MATCHING
ObjSprite *func_8000A2C8(int group)
{
    int        full;
    short     *entry;
    int        i;
    ObjSprite *sprite;

    full   = 1;
    entry  = D_8005B970[group];
    sprite = &g_sys_real.sprites[entry[0]];
    for (i = 0; i < D_8005B970[group][1]; i++) {
        if (sprite->header.kind == 0) {
            full = 0;
            break;
        }
        sprite++;
    }
    if (full == 1) {
        sprite = NULL;
    }
    return sprite;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/obj/func_8000A2C8.s")
#endif

void func_8000A344(void)
{
    ObjMoji *moji = g_sys_real.mojis;
    int      i;

    for (i = 0; i < 2; i++) {
        func_8000A394(moji);
        moji++;
    }
}

void func_8000A394(ObjMoji *moji)
{
    moji->header.kind  = 0x83;
    moji->unk_31       = 0;
    moji->header.pri   = 0;
    moji->header.s_pri = 0;
    moji->unk_8        = 0;
    moji->unk_3c       = 0xFF;
    moji->unk_3e       = 0xFF;
    moji->unk_40       = 0xFF;
    moji->unk_42       = 0xFF;
    moji->unk_c_word   = 0;
    moji->unk_10_word  = 0;
    moji->unk_14       = 0;
    moji->unk_18       = 0;
    moji->unk_28       = 0;
    moji->unk_1c       = 0x140;
    moji->unk_1e       = 0xF0;
    moji->unk_20       = 1;
    moji->unk_22       = 1;
    moji->unk_30       = 2;
    moji->unk_32       = 0;
    moji->unk_34       = 0;
    moji->unk_36       = 0;
    moji->unk_38       = 0x140;
    moji->unk_3a       = 0xF0;
    moji->unk_44       = 0;
    moji->unk_46       = 0;
    moji->unk_48       = 0xA;
    moji->unk_4a       = 7;
}

void func_8000A430(void)
{
    ObjGbg *gbg = g_sys_real.gbgs;
    int     i;

    for (i = 0; i < 2; i++) {
        func_8000A480(gbg);
        gbg++;
    }
}

void func_8000A480(ObjGbg *arg0)
{
    arg0->header.kind    = 0x85;
    arg0->header.pri     = 0;
    arg0->header.s_pri   = 0;
    arg0->unk_8          = 0;
    arg0->texture_data   = 0;
    arg0->palette_data   = 0;
    arg0->wave_no        = 0;
    arg0->flags          = 0x8009;
    arg0->texture_width  = 320;
    arg0->texture_height = 240;
    arg0->min_x          = 0;
    arg0->min_y          = 0;
    arg0->max_x          = 319;
    arg0->max_y          = 239;
    arg0->bits_per_pixel = 8;
    arg0->u              = 0.0f;
    arg0->v              = 0.0f;
    arg0->x              = 0.0f;
    arg0->y              = 0.0f;
    arg0->w              = 0.0f;
    arg0->h              = 0.0f;
}

void func_8000A4F8(void)
{
    ObjSolid *solid = g_sys_real.solids;
    int       i;

    for (i = 0; i < 192; i++) {
        func_8000A5C4(solid);
        solid++;
    }
}

void func_8000A548(int first, int last)
{
    ObjSolid *solid;
    int       i;

    solid = &g_sys_real.solids[first];
    for (i = first; i < last + 1; i++) {
        func_8000A5C4(solid);
        solid++;
    }
}

void func_8000A5C4(ObjSolid *solid)
{
    Obj *next;

    next               = solid->header.next;
    *solid             = D_8005B974;
    solid->header.next = next;
}

void func_8000A614(void)
{
    int i;

    for (i = 0; i < 12; i++) {
        g_sys->layers[i].unk_371 = 1;
    }
}
