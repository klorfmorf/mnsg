#include "sys/pal.h"
#include "common.h"
#include "sys/sys.h"

void func_80007EA0(unsigned short idx);
void func_80008068(unsigned char bank, unsigned char entry, unsigned char slot);
void func_80008330(unsigned char moji, unsigned char bank, unsigned char entry, unsigned char row, unsigned char range);

extern unsigned short *D_80167860[16];
extern unsigned short *D_801678A0[16];
extern unsigned short *D_801678E0[16];
extern unsigned short *D_80167920[16];
extern unsigned short *D_80167960[16];
extern unsigned short *D_801679A0[16];
extern unsigned short *D_801679E0[16];
extern unsigned short *D_80167A20[16];

// clang-format off

// <<<<< data >>>>>
unsigned short D_8005B3F0[28] = {
    0xFFFE, 0xF89B, 0xF91D, 0xF99F, 0xFA21, 0xFAA3, 0xFB27, 0xFBA9, 0xFC2B, 0xFCAD, 0xFCEF, 0xFD71, 0xFDF3, 0x2001, 0x0001, 0x0001,
    0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0xB800, 0x0000, 0x0000, 0x0000,
};

unsigned short D_8005B428[256] = {
    0x04FF, 0x0023, 0xFFC1, 0xFB41, 0xF801, 0x3D0D, 0x7941, 0x7001, 0x8001, 0x9001, 0xA001, 0xB001, 0xC001, 0xD001, 0xE001, 0xF7FF,
    0x0081, 0x1081, 0x2081, 0x3081, 0x4081, 0x5081, 0x6081, 0x7081, 0x8081, 0x9081, 0xA081, 0xB081, 0xC081, 0xD081, 0xE081, 0xF081,
    0x0101, 0x1101, 0x2101, 0x3101, 0x4101, 0x5101, 0x6101, 0x7101, 0x8101, 0x9101, 0xA101, 0xB101, 0xC101, 0xD101, 0xE101, 0xF101,
    0x0181, 0x1181, 0x2181, 0x3181, 0x4181, 0x5181, 0x6181, 0x7181, 0x8181, 0x9181, 0xA181, 0xB181, 0xC181, 0xD181, 0xE181, 0xF181,
    0x0201, 0x1201, 0x2201, 0x3201, 0x4201, 0x5201, 0x6201, 0x7201, 0x8201, 0x9201, 0xA201, 0xB201, 0xC201, 0xD201, 0xE201, 0xF201,
    0x0281, 0x1281, 0x2281, 0x3281, 0x4281, 0x5281, 0x6281, 0x7281, 0x8281, 0x9281, 0xA281, 0xB281, 0xC281, 0xD281, 0xE281, 0xF281,
    0x0301, 0x1301, 0x2301, 0x3301, 0x4301, 0x5301, 0x6301, 0x7301, 0x8301, 0x9301, 0xA301, 0xB301, 0xC301, 0xD301, 0xE301, 0xF301,
    0x0381, 0x1381, 0x2381, 0x3381, 0x4381, 0x5381, 0x6381, 0x7381, 0x8381, 0x9381, 0xA381, 0xB381, 0xC381, 0xD381, 0xE381, 0xF381,
    0x0401, 0x1401, 0x2401, 0x3401, 0x4401, 0x5401, 0x6401, 0x7401, 0x8401, 0x9401, 0xA401, 0xB401, 0xC401, 0xD401, 0xE401, 0xF401,
    0x0481, 0x1481, 0x2481, 0x3481, 0x4481, 0x5481, 0x6481, 0x7481, 0x8481, 0x9481, 0xA481, 0xB481, 0xC481, 0xD481, 0xE481, 0xF481,
    0x0501, 0x1501, 0x2501, 0x3501, 0x4501, 0x5501, 0x6501, 0x7501, 0x8501, 0x9501, 0xA501, 0xB501, 0xC501, 0xD501, 0xE501, 0xF501,
    0x0581, 0x1581, 0x2581, 0x3581, 0x4581, 0x5581, 0x6581, 0x7581, 0x8581, 0x9581, 0xA581, 0xB581, 0xC581, 0xD581, 0xE581, 0xF581,
    0x0601, 0x1601, 0x2601, 0x3601, 0x4601, 0x5601, 0x6601, 0x7601, 0x8601, 0x9601, 0xA601, 0xB601, 0xC601, 0xD601, 0xE601, 0xF601,
    0x0681, 0x1681, 0x2681, 0x3681, 0x4681, 0x5681, 0x6681, 0x7681, 0x8681, 0x9681, 0xA681, 0xB681, 0xC681, 0xD681, 0xE681, 0xF681,
    0x0701, 0x1701, 0x2701, 0x3701, 0x4701, 0x5701, 0x6701, 0x7701, 0x8701, 0x9701, 0xA701, 0xB701, 0xC701, 0xD701, 0xE701, 0xF701,
    0x0781, 0x1781, 0x2781, 0x3781, 0x4781, 0x5781, 0x6781, 0x7781, 0x8781, 0x9781, 0xA781, 0xB781, 0xC781, 0xD781, 0xE781, 0xF781,
};

unsigned short D_8005B628[36] = {
    0xFFFE, 0xDF7F, 0xC6BD, 0xB63B, 0xA579, 0x94F7, 0x7C35, 0x6BB3, 0x5B31, 0x4A6F, 0x31ED, 0x212B, 0x10A9, 0x0027, 0x0007, 0xFFFF,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0102, 0x0304, 0x0506, 0x0708, 0x090A,
    0x0B0C, 0x0D0E, 0x0F00, 0x0000,
};

unsigned short *D_8005B670[16] = {
    D_8005B3F0, D_8005B3F0, D_8005B428, D_8005B3F0,
    D_8005B628, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
};

unsigned short **D_8005B6B0[12] = {
    D_8005B670, D_80167860, D_801678A0, D_801678E0,
    D_80167920, D_80167960, D_801679A0, D_801679E0,
    D_80167A20, NULL, NULL, NULL,
};

// <<<<< bss >>>>>
unsigned short *D_80167860[16];
unsigned short *D_801678A0[16];
unsigned short *D_801678E0[16];
unsigned short *D_80167920[16];
unsigned short *D_80167960[16];
unsigned short *D_801679A0[16];
unsigned short *D_801679E0[16];
unsigned short *D_80167A20[16];

// clang-format on

int func_80007970(unsigned short *src, unsigned short *dst, unsigned short n)
{
    short i;

    if (n > 256) {
        PRINTF((" basp, ldp, size = %x, %x, %x\n", src, dst, n));
        return 0;
    }
    for (i = 0; i < n; i++) {
        *dst++ = *src++;
    }
    return 1;
}

int func_800079C0(ObjSprite *sprite, unsigned short *data)
{
    short           i;
    unsigned short *pal;
    ObjSpriteTex   *tex;

    pal = g_sys_real.tlut_buffer;
    tex = sprite->textures;
    if (sprite->attr & SPRITE_ATTR_PALETTE) {
        func_80007C90(sprite);
    }
    switch (tex->fmt & SPRITE_FMT_SIZE_MASK) {
        case SPRITE_FMT_4B:
            for (i = 0; i < 15; i++, pal += 16) {
                if (g_sys_real.palette_slot_refs[i] == 0 || data == g_sys_real.palette_slot_srcs[i]) {
                    if (data != g_sys_real.palette_slot_srcs[i]) {
                        func_80007970(data, pal, 16);
                    }
                    g_sys_real.palette_slot_refs[i]++;
                    g_sys_real.palette_slot_srcs[i] = data;
                    sprite->palette_slot            = i;
                    sprite->palette                 = data;
                    sprite->attr |= SPRITE_ATTR_PALETTE;
                    return 1;
                }
            }
            g_sys_real.palette_slot_refs[15]++;
            g_sys_real.palette_slot_srcs[15] = data;
            sprite->palette_slot             = 15;
            sprite->palette                  = data;
            return 1;
        case SPRITE_FMT_8B:
            PRINTF(("pal: autoLoadPalW 256 set.\n"));
            sprite->palette_slot = 0;
            sprite->palette      = data;
            sprite->attr |= SPRITE_ATTR_PALETTE;
            return 1;
    }
    PRINTF(("pal: autoLoadPalW erorr!!\n"));
    return 0;
}

void func_80007B3C(ObjSprite *sprite)
{
    func_800079C0(sprite, sprite->palette);
}

void func_80007B5C(ObjSprite *src, ObjSprite *dst)
{
    func_800079C0(dst, src->palette);
}

int func_80007B84(ObjSprite *src, ObjSprite *dst)
{
    ObjSpriteTex *tex;

    tex = src->textures;
    if (src->attr & SPRITE_ATTR_PALETTE) {
        if (dst->attr & SPRITE_ATTR_PALETTE) {
            func_80007C90(dst);
        }
        switch (tex->fmt & SPRITE_FMT_SIZE_MASK) {
            case SPRITE_FMT_4B:
                dst->palette_slot = src->palette_slot;
                g_sys_real.palette_slot_refs[src->palette_slot]++;
                dst->palette = g_sys_real.palette_slot_srcs[dst->palette_slot] = src->palette;
                dst->attr |= SPRITE_ATTR_PALETTE;
                return 1;
            case SPRITE_FMT_8B:
                dst->palette_slot = src->palette_slot;
                dst->palette      = src->palette;
                dst->attr |= SPRITE_ATTR_PALETTE;
                return 1;
        }
    }
    PRINTF(("pal: autoCpItiPalW erorr!!\n"));
    return 0;
}

int func_80007C90(ObjSprite *sprite)
{
    ObjSpriteTex *tex;
    unsigned char idx;

    tex = sprite->textures;
    if (sprite->attr & SPRITE_ATTR_PALETTE) {
        switch (tex->fmt & SPRITE_FMT_SIZE_MASK) {
            case SPRITE_FMT_4B:
                if (sprite->palette_slot >= 16) {
                    idx = tex->pal;
                } else {
                    idx = sprite->palette_slot;
                }
                if (g_sys_real.palette_slot_refs[idx] > 0) {
                    g_sys_real.palette_slot_refs[idx] -= 1;
                }
                sprite->palette_slot = SPRITE_PALETTE_NONE;
                sprite->attr &= ~SPRITE_ATTR_PALETTE;
                return 1;
            case SPRITE_FMT_8B:
                sprite->palette_slot = SPRITE_PALETTE_NONE;
                sprite->attr &= ~SPRITE_ATTR_PALETTE;
                return 1;
        }
    }
    PRINTF(("pal: autoDelPalW erorr!!\n"));
    return 0;
}

void func_80007D40(unsigned short *src)
{
    unsigned short *base;
    short           i;

    base = src;
    for (i = 0; i < 16; i++, src += 16) {
        g_sys_real.palette_slot_srcs[i] = src;
    }
    func_80007970(base, g_sys_real.tlut_buffer, 0x100);
}

void func_80007DA8(unsigned short *src, unsigned short idx)
{
    g_sys_real.palette_slot_srcs[idx] = src;
    func_80007970(src, &g_sys_real.tlut_buffer[idx * 16], 16);
}

void func_80007E00(unsigned short *src)
{
    func_80007E5C();
    func_80007D40(src);
}

void func_80007E28(unsigned short *src, unsigned short idx)
{
    func_80007EA0(idx);
    func_80007DA8(src, idx);
}

void func_80007E5C(void)
{
    short i;

    for (i = 0; i < 16; i++) {
        func_80007EA0(i);
    }
}

void func_80007EA0(unsigned short idx)
{
    g_sys_real.palette_slot_refs[idx] = 0;
    g_sys_real.palette_slot_srcs[idx] = 0;
}

void func_80007ED8(unsigned char bank, unsigned char entry, unsigned char slot, unsigned char range)
{
    unsigned char i;
    unsigned char first;
    unsigned char last;
    unsigned char table;
    unsigned char offset;

    PRINTF(("tblPalDefBG(%x,%x,%x,%x);\n", bank, entry, slot, range));
    first = range & 0xF;
    last  = (range & 0xF0) >> 4;
    switch (entry) {
        case PAL_ENTRY_CLEAR:
            for (i = first; i <= last; i++) {
                (&g_sys_real.tlut_buffer[slot * 16])[i] = 0;
            }
            break;
        case PAL_ENTRY_KEEP:
            break;
        default:
            table  = (entry & 0xF0) >> 4;
            offset = (entry & 0xF) * 16;
            PRINTF(("(%x, %x);\n", table, offset));
            for (i = first; i <= last; i++) {
                func_80007970(D_8005B6B0[bank][table] + offset + i, &(&g_sys_real.tlut_buffer[slot * 16])[i], 1);
            }
            break;
    }
}

void func_80008068(unsigned char bank, unsigned char entry, unsigned char slot)
{
    unsigned char i;

    switch (entry) {
        case PAL_ENTRY_CLEAR:
            g_sys_real.palette_slot_srcs[slot] = NULL;
            for (i = 0; i < 16; i++) {
                (&g_sys_real.tlut_buffer[slot * 16])[i] = 0;
            }
            break;
        case PAL_ENTRY_KEEP:
            break;
        default:
            func_80007DA8(&D_8005B6B0[bank][(unsigned char) ((entry & 0xF0) >> 4)][(unsigned char) ((entry & 0xF) * 16)], slot);
            break;
    }
}

void func_8000814C(unsigned char *tbl)
{
    unsigned char i;

    for (i = 0; i < 16; i++) {
        func_80008068(tbl[0], tbl[i + 1], i);
    }
}

void func_800081AC(ObjSprite *sprite, unsigned char bank, unsigned char entry)
{
    unsigned char i;

    switch (entry) {
        case PAL_ENTRY_CLEAR:
            for (i = 0; i < 16; i++) {
                sprite->palette[i] = 0;
            }
            break;
        case PAL_ENTRY_KEEP:
            break;
        default:
            func_800079C0(sprite, &D_8005B6B0[bank][(unsigned char) ((entry & 0xF0) >> 4)][(unsigned char) ((entry & 0xF) * 16)]);
            break;
    }
}

void func_80008258(ObjSprite *sprite, unsigned char bank, unsigned char entry)
{
    sprite->palette_slot = 0;
    sprite->palette      = &D_8005B6B0[bank][(unsigned char) ((entry & 0xF0) >> 4)][(unsigned char) ((entry & 0xF) * 16)];
    sprite->attr |= SPRITE_ATTR_PALETTE;
}

void func_800082B4(unsigned char idx, unsigned short *src, unsigned short n)
{
    func_80007970(src, g_sys_real.mojis[idx].palette, n);
    g_sys_real.mojis[idx].palette_src = src;
}

void func_80008330(unsigned char moji, unsigned char bank, unsigned char entry, unsigned char row, unsigned char range)
{
    unsigned char i;
    unsigned char first;
    unsigned char last;

    first = range & 0xF;
    last  = (range & 0xF0) >> 4;
    switch (entry) {
        case PAL_ENTRY_CLEAR:
            for (i = first; i <= last; i++) {
                (&g_sys_real.mojis[moji].palette[row * 16])[i] = 0;
            }
            break;
        case PAL_ENTRY_KEEP:
            break;
        default:
            g_sys_real.mojis[moji].palette_src = &D_8005B6B0[bank][(unsigned char) ((entry & 0xF0) >> 4)][(unsigned char) ((entry & 0xF) * 16)];
            for (i = first; i <= last; i++) {
                func_80007970(&g_sys_real.mojis[moji].palette_src[i], &(&g_sys_real.mojis[moji].palette[row * 16])[i], 1);
            }
            break;
    }
}

void func_800084F4(unsigned char moji, unsigned char bank, unsigned char entry, unsigned char row)
{
    func_80008330(moji, bank, entry, row, 0xF0);
}

void func_80008548(unsigned char moji, unsigned char *tbl)
{
    unsigned char i;

    for (i = 0; i < 16; i++) {
        func_800084F4(moji, tbl[0], tbl[i + 1], i);
    }
}

void func_800085BC(unsigned char moji, unsigned char bank, unsigned char entry)
{
    unsigned char i;

    for (i = 0; i < 16; i++) {
        func_800084F4(moji, bank, entry + i, i);
    }
}
