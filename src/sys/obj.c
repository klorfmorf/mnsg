#include "sys/obj.h"
#include "sys/gbg.h"
#include "structs.h"
#include "sys/sys.h"
#include "sys/anime.h"
#include "sys/rom_trans.h"
#include "sys/wave_uty.h"
#include "sys/gfx_data.h"
#include "unk.h"

void           func_80008920(ObjSprite *arg0);
unsigned short func_80009408(ObjSpriteFlags flags, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void           func_80009548(ObjSprite *arg0, ObjSpriteTex *tex);
void           func_8000A130(void);
void           func_8000A18C(void);
void           func_8000A344(void);
void           func_8000A430(void);
void           func_8000A480(ObjGbg *arg0);
void           func_8000A4F8(void);
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
unsigned int   D_80167A64;
unsigned short D_80167A68;
unsigned int   D_80167A6C;
unsigned short D_80167A70;
unsigned short D_80167A72;
unsigned short D_80167A74;

// clang-format on

void func_800086F0(void)
{
    D_80167A60 = func_800086F0;
    D_80167A68 = D_80167A70 = D_80167A72 = 0xFFFF;
    D_80167A74                           = 0;
    gSPDisplayList(g_sys_glistp++, D_8006D600);
    func_80009408(g_sys_real.sprite_override_flags, g_sys_real.sprite_color_r, g_sys_real.sprite_color_g, g_sys_real.sprite_color_b, g_sys_real.sprite_color_a);
}

void func_80008798(void)
{
    gSPDisplayList(g_sys_glistp++, D_8006D600);
}

void func_800087C4(ObjLayer *arg0)
{
    Obj  *obj;
    short i;

    if (g_sys_real.stop_processing_draw_lists != 1) {
        for (i = 0; i < arg0->size; i++) {
            obj = arg0->objects[i];
            if (obj->kind & OBJ_HIDDEN) {
                continue;
            }
            switch (obj->kind) {
                case OBJ_KIND_2D:
                    func_800086F0();
                    func_80008920((ObjSprite *) obj);
                    break;
                case OBJ_KIND_SOLID:
                    anime_draw((ObjSolid *) obj);
                    D_80167A60 = func_800086F0;
                    D_80167A68 = 0xFFFF;
                    break;
                case OBJ_KIND_MOJI:
                    break;
                case OBJ_KIND_BG:
                    D_80167A60 = func_800086F0;
                    D_80167A68 = 0xFFFF;
                    D_80167A72 = 0xFFFF;
                    break;
                case OBJ_KIND_GBG:
                    func_800215D0();
                    func_80021740((ObjGbg *) obj);
                    D_80167A60 = func_800086F0;
                    D_80167A68 = D_80167A72 = 0xFFFF;
                    break;
            }
        }
    }
}

void func_80008920(ObjSprite *sprite)
{
    ObjSpritePart *part = sprite->parts;
    ObjMoji       *moji;
    int            clip_x0;
    int            clip_y0;
    int            x;
    int            y;
    unsigned short scaled;
    unsigned short filter;
    int            scale_x;
    int            scale_y;
    int            dir_x;
    int            dir_y;
    int            tex_w;
    int            tex_h;
    int            s;
    int            t;
    int            clip_x0_in;
    int            clip_y0_in;
    int            clip_x1;
    int            clip_y1;
    int            clip_x1_in;
    int            clip_y1_in;
    int            left;
    int            top;
    int            right;
    int            bottom;
    int            step;
    int            pad;

    if (part == NULL) {
        return;
    }
    clip_x0 = 0;
    if (sprite->attr & SPRITE_ATTR_CLIP) {
        moji       = &g_sys_real.mojis[(sprite->attr & SPRITE_ATTR_CLIP_LAYER) >> 4];
        clip_x0    = moji->clip_x0 * 4;
        clip_y0    = moji->clip_y0 * 4;
        clip_x0_in = clip_x0 + 4;
        clip_y0_in = clip_y0 + 4;
        clip_x1    = moji->clip_x1 * 4;
        clip_y1    = moji->clip_y1 * 4;
        clip_x1_in = clip_x1 - 4;
        clip_y1_in = clip_y1 - 4;
    } else {
        clip_y0    = 0;
        clip_x0_in = 4;
        clip_y0_in = 4;
        clip_x1    = (SCREEN_WIDTH - 1) * 4;
        clip_y1    = (SCREEN_HEIGHT - 1) * 4;
        clip_x1_in = (SCREEN_WIDTH - 2) * 4;
        clip_y1_in = (SCREEN_HEIGHT - 2) * 4;
    }
    moji = &g_sys_real.mojis[sprite->attr & SPRITE_ATTR_SCROLL_LAYER];
    if (sprite->attr & SPRITE_ATTR_SCROLL_X) {
        x = sprite->x - moji->scroll_x;
    } else {
        x = sprite->x;
    }
    if (sprite->attr & SPRITE_ATTR_SCROLL_Y) {
        y = sprite->y - moji->scroll_y;
    } else {
        y = sprite->y;
    }

    step = 0x400;
    if (g_sys_real.sprite_override_flags.override_mode == 1) {
        if (g_sys_real.sprite_override_flags.mode == 0) {
            scaled = 0;
            step   = 0x1000;
            filter = 1;
        } else {
            scaled = sprite->flags.scaled;
            filter = 0;
            if (g_sys_real.sprite_override_flags.modulate_color == 1) {
                gDPSetPrimColor(g_sys_glistp++, 0, 0, (sprite->r * g_sys_real.sprite_color_r) >> 8,
                    (sprite->g * g_sys_real.sprite_color_g) >> 8,
                    (sprite->b * g_sys_real.sprite_color_b) >> 8,
                    (sprite->a * g_sys_real.sprite_color_a) >> 8);
            }
        }
    } else {
        filter = func_80009408(sprite->flags, sprite->r, sprite->g, sprite->b, sprite->a);
        if (filter == 1) {
            step   = 0x1000;
            scaled = 0;
        } else {
            scaled = sprite->flags.scaled;
        }
    }
    if (scaled == 0) {
        scale_x = step;
        scale_y = 0x400;
    } else {
        if (sprite->scale_x <= 1e-6) {
            return;
        }
        if (sprite->scale_y <= 1e-6) {
            return;
        }
        scale_x = 1024.0f / sprite->scale_x;
        scale_y = 1024.0f / sprite->scale_y;
    }
    dir_x = sprite->flags.flip_x ? -1 : 1;
    dir_y = sprite->flags.flip_y ? -1 : 1;

    for (;; part++) {
        if ((part->flags & SPRITE_PART_TEXTURE) == SPRITE_PART_TEXTURE) {
            func_80009548(sprite, &sprite->textures[part->flags & SPRITE_PART_TEX_MASK]);
            tex_w = (1 << sprite->flags.tex_width_shift) << 5;
            tex_h = (1 << sprite->flags.tex_height_shift) << 5;
        }
        if (part->flags & SPRITE_PART_SKIP) {
            if (part->flags & SPRITE_PART_END) {
                return;
            }
            continue;
        }
        if (sprite->flags.flip_x) {
            s = (part->s - tex_w + (part->width << 5)) * dir_x + tex_w - D_80167A74;
        } else {
            s = part->s - D_80167A74;
        }
        // The empty block and the unused local are needed to match.
        if (!clip_y0_in) {
        }
        if (sprite->flags.flip_y) {
            t = (part->t - tex_h + (part->height << 5)) * dir_y + tex_h - D_80167A74;
        } else {
            t = part->t - D_80167A74;
        }
        if (scaled == 0) {
            if (sprite->flags.flip_x) {
                left  = ((part->x + part->width) * dir_x + x) * 4;
                right = (x - filter + part->x * dir_x) * 4;
            } else {
                left  = (part->x * dir_x + x) * 4;
                right = left + (part->width - filter) * dir_x * 4;
            }
            if (sprite->flags.flip_y) {
                top    = ((part->y + part->height) * dir_y + y) * 4;
                bottom = (y - filter + part->y * dir_y) * 4;
            } else {
                top    = (part->y * dir_y + y) * 4;
                bottom = top + (part->height - filter) * dir_y * 4;
            }
            if (left < clip_x0) {
                if (right < clip_x0_in) {
                    if (sprite->attr & SPRITE_ATTR_KILL_OFF_X) {
                        sprite->header.kind = OBJ_KIND_NONE;
                    }
                    goto next;
                }
                s += (clip_x0 - left) << 3;
                left = clip_x0;
            }
            if (top < clip_y0) {
                if (bottom < clip_y0_in) {
                    if (sprite->attr & SPRITE_ATTR_KILL_OFF_Y) {
                        sprite->header.kind = OBJ_KIND_NONE;
                    }
                    goto next;
                }
                t += (clip_y0 - top) << 3;
                top = clip_y0;
            }
        } else {
            if (sprite->flags.flip_x) {
                right = (x + (float) (((dir_x * part->x) << 10) / scale_x)) * 4.0f;
                left  = (x + (float) (((dir_x * (part->x + part->width)) << 10) / scale_x)) * 4.0f;
            } else {
                left  = (x + (float) (((dir_x * part->x) << 10) / scale_x)) * 4.0f;
                right = (x + (float) (((dir_x * (part->x + part->width)) << 10) / scale_x)) * 4.0f;
            }
            if (sprite->flags.flip_y) {
                bottom = (y + (float) (((dir_y * part->y) << 10) / scale_y)) * 4.0f;
                top    = (y + (float) (((dir_y * (part->y + part->height)) << 10) / scale_y)) * 4.0f;
            } else {
                top    = (y + (float) (((dir_y * part->y) << 10) / scale_y)) * 4.0f;
                bottom = (y + (float) (((dir_y * (part->y + part->height)) << 10) / scale_y)) * 4.0f;
            }
            if (left < clip_x0) {
                if (right < clip_x0_in) {
                    if (sprite->attr & SPRITE_ATTR_KILL_OFF_X) {
                        sprite->header.kind = OBJ_KIND_NONE;
                    }
                    goto next;
                }
                s += ((clip_x0 - left) * scale_x) >> 7;
                left = clip_x0;
            }
            if (top < clip_y0) {
                if (bottom < clip_y0_in) {
                    if (sprite->attr & SPRITE_ATTR_KILL_OFF_Y) {
                        sprite->header.kind = OBJ_KIND_NONE;
                    }
                    goto next;
                }
                t += ((clip_y0 - top) * scale_y) >> 7;
                top = clip_y0;
            }
        }
        if (right > clip_x1) {
            if (left > clip_x1_in) {
                if (sprite->attr & SPRITE_ATTR_KILL_OFF_X) {
                    sprite->header.kind = OBJ_KIND_NONE;
                }
                goto next;
            }
            right = clip_x1;
        }
        if (bottom > clip_y1) {
            if (top > clip_y1_in) {
                if (sprite->attr & SPRITE_ATTR_KILL_OFF_Y) {
                    sprite->header.kind = OBJ_KIND_NONE;
                }
                goto next;
            }
            bottom = clip_y1;
        }
        gSPTextureRectangle(g_sys_glistp++, left, top, right, bottom, G_TX_RENDERTILE, s, t, scale_x, scale_y);
        gDPPipeSync(g_sys_glistp++);
    next:
        if (part->flags >= SPRITE_PART_END) {
            return;
        }
    }
}

unsigned short func_80009408(ObjSpriteFlags flags, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (flags.mode != D_80167A70) {
        D_80167A70 = flags.mode;
        gSPDisplayList(g_sys_glistp++, D_8005B950[D_80167A70]);
        if (D_80167A70 >= 5) {
            D_80167A74 = 0x10;
        } else {
            D_80167A74 = 0;
        }
    }
    if (flags.mode != 0) {
        gDPSetPrimColor(g_sys_glistp++, 0, 0, r, g, b, a);
        if (flags.dither_alpha == 0) {
            gDPSetAlphaCompare(g_sys_glistp++, G_AC_THRESHOLD);
        } else {
            gDPSetAlphaCompare(g_sys_glistp++, G_AC_DITHER);
        }
        return 0;
    }
    return 1;
}

void func_80009548(ObjSprite *sprite, ObjSpriteTex *tex)
{
    int          fmt;
    int          format_index;
    int          slot;
    int          segment;
    unsigned int base;

    if (sprite->palette_slot >= 16) {
        slot = tex->pal;
    } else {
        slot = sprite->palette_slot;
    }
    if (D_80167A60 == tex->data && slot == D_80167A68) {
        return;
    }
    D_80167A60 = tex->data;
    D_80167A68 = slot;
    D_80167A64 = (unsigned int) D_80167A60;
    D_80167A6C = (unsigned int) sprite->palette;
    if (tex->wave != 0) {
        segment    = func_80001E50(tex->wave);
        base       = func_800141C4(tex->wave);
        D_80167A64 = (unsigned int) tex->data + base - (segment << 24);
        gSPSegment(g_sys_glistp++, segment, OS_K0_TO_PHYSICAL(base));
        if (sprite->palette != NULL) {
            D_80167A6C = (unsigned int) sprite->palette + base - (segment << 24);
        }
    }
    format_index = tex->fmt & SPRITE_FMT_TYPE_MASK;
    fmt          = D_8007AAB4[format_index];
    gDPSetTextureLUT(g_sys_glistp++, D_8007AAA0[format_index]);
    switch (tex->fmt & SPRITE_FMT_SIZE_MASK) {
        case SPRITE_FMT_4B:
            if (D_80167A72 != 0) {
                D_80167A72 = 0;
                gDPLoadTLUT_pal256(g_sys_glistp++, g_sys_real.tlut_buffer);
            }
            if (slot == 15) {
                gDPLoadTLUT_pal16(g_sys_glistp++, 15, D_80167A6C);
                D_80167A68 = 0;
            }
            gDPLoadTextureBlock_4b(g_sys_glistp++, D_80167A64, fmt, tex->width, tex->height, slot,
                sprite->flags.wrap_s, sprite->flags.wrap_t, sprite->flags.tex_width_shift,
                sprite->flags.tex_height_shift, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case SPRITE_FMT_8B:
        default:
            gDPLoadTLUT_pal256(g_sys_glistp++, D_80167A6C);
            gDPLoadTextureBlock(g_sys_glistp++, D_80167A64, fmt, G_IM_SIZ_8b, tex->width, tex->height, 0,
                sprite->flags.wrap_s, sprite->flags.wrap_t, sprite->flags.tex_width_shift,
                sprite->flags.tex_height_shift, G_TX_NOLOD, G_TX_NOLOD);
            D_80167A68 = D_80167A72 = 0xFFFF;
            break;
        case SPRITE_FMT_16B:
            gDPLoadTextureBlock(g_sys_glistp++, D_80167A64, fmt, G_IM_SIZ_16b, tex->width, tex->height, 0,
                sprite->flags.wrap_s, sprite->flags.wrap_t, sprite->flags.tex_width_shift,
                sprite->flags.tex_height_shift, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
}

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
    g_sys_real.sprite_color_a             = 0xFF;
    g_sys_real.sprite_override_flags_word = 0;
    g_sys_real.sprite_color_b             = g_sys_real.sprite_color_a;
    g_sys_real.sprite_color_g             = g_sys_real.sprite_color_b;
    g_sys_real.sprite_color_r             = g_sys_real.sprite_color_g;
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
    sprite->flags_word             = 0;
    sprite->header.kind            = OBJ_KIND_2D | OBJ_HIDDEN;
    sprite->flags.wrap_s           = 1;
    sprite->flags.wrap_t           = 1;
    sprite->x_word                 = 0;
    sprite->flags.tex_width_shift  = 9;
    sprite->y_word                 = 0;
    sprite->palette_slot           = SPRITE_PALETTE_NONE;
    sprite->flags.tex_height_shift = 9;
    sprite->attr                   = 0;
    sprite->header.pri             = 0;
    sprite->header.s_pri           = 0;
    sprite->parts                  = NULL;
    sprite->textures               = NULL;
    sprite->r                      = 0xFF;
    sprite->g                      = 0xFF;
    sprite->b                      = 0xFF;
    sprite->a                      = 0xFF;
    sprite->scale_x                = 1.0f;
    sprite->scale_y                = 1.0f;
}

ObjSprite *func_8000A2C8(int group)
{
    int        full;
    int        i;
    ObjSprite *sprite;

    full = 1;
    for (i = 0, sprite = &g_sys_real.sprites[D_8005B970[group][0]]; i < D_8005B970[group][1]; i++, sprite++) {
        if (sprite->header.kind == OBJ_KIND_NONE) {
            full = 0;
            break;
        }
    }
    if (full == 1) {
        sprite = NULL;
    }
    return sprite;
}

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
    moji->header.kind   = OBJ_KIND_MOJI | OBJ_HIDDEN;
    moji->unk_31        = 0;
    moji->header.pri    = 0;
    moji->header.s_pri  = 0;
    moji->unk_8         = 0;
    moji->r             = 0xFF;
    moji->g             = 0xFF;
    moji->b             = 0xFF;
    moji->a             = 0xFF;
    moji->scroll_x_word = 0;
    moji->scroll_y_word = 0;
    moji->unk_14        = 0;
    moji->unk_18        = 0;
    moji->palette_src   = 0;
    moji->width         = SCREEN_WIDTH;
    moji->height        = SCREEN_HEIGHT;
    moji->unk_20        = 1;
    moji->unk_22        = 1;
    moji->unk_30        = 2;
    moji->unk_32        = 0;
    moji->clip_x0       = 0;
    moji->clip_y0       = 0;
    moji->clip_x1       = SCREEN_WIDTH;
    moji->clip_y1       = SCREEN_HEIGHT;
    moji->unk_44        = 0;
    moji->unk_46        = 0;
    moji->unk_48        = 10;
    moji->unk_4a        = 7;
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
    arg0->header.kind    = OBJ_KIND_GBG | OBJ_HIDDEN;
    arg0->header.pri     = 0;
    arg0->header.s_pri   = 0;
    arg0->unk_8          = 0;
    arg0->texture_data   = 0;
    arg0->palette_data   = 0;
    arg0->wave_no        = 0;
    arg0->flags          = GBG_PANORAMA | GBG_8B | GBG_CI;
    arg0->texture_width  = SCREEN_WIDTH;
    arg0->texture_height = SCREEN_HEIGHT;
    arg0->min_x          = 0;
    arg0->min_y          = 0;
    arg0->max_x          = SCREEN_WIDTH - 1;
    arg0->max_y          = SCREEN_HEIGHT - 1;
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
        g_sys->layers[i].sort_flags = 1;
    }
}
