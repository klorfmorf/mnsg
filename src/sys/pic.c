#define NO_PROTO_bitRead

#include "sys/pic.h"
#include "sys/sys.h"
#include "sys/bit.h"
#include "sys/wave_uty.h"
#include "unk.h"

void *picDecode8(int arg0, void *buf, Pic *pic);
void *picDecode4(int arg0, void *buf, Pic *pic);
void  picReadPalette(int n, Pic *pic);
void  picReadHeader(Pic *pic);
void  picExpand16(Pic *pic);
void  picExpandChain16(Pic *pic, int x, int y, int c);
void  picExpand8(Pic *pic);
void  picExpand4(Pic *pic);
int   picReadLenIndexed(Pic *pic);
void  picExpandChain8(Pic *pic, int x, int y, int c);
void  picExpandChain4(Pic *pic, int x, int y, int c);
int   picReadLen(void);
int   picReadColor(Pic *pic);
void  picColorCacheInit(void);
int   picNewColor(Pic *pic, int c);
int   picGetColor(Pic *pic, int idx);
int   picPoint(int x, int y);
void  picPset(Pic *pic, int x, int y, int c);
void  picPset8(int x, int y, int c);
int   picPoint4(int x, int y);
void  picPset4(int x, int y, int c);
int   picParseHex(unsigned char *s);
void  picClearTransparent(Pic *pic);
void  picFlagSet(unsigned char *bits, int i);
void  picFlagClear(unsigned char *bits, int i);
int   picFlagTest(unsigned char *bits, int i);

// clang-format off

// <<<<< data >>>>>
WaveReq D_8006ADD0 = {
    0x40000001,
    D_80301000,
};

WaveReq D_8006ADD8 = {
    0x40000003,
    D_80304000,
};

// <<<<< bss >>>>>
int             s_pic_bit_len;
int             s_pic_width;
int             s_pic_height;
int             s_pic_transparent;
unsigned char  *s_pic_buff_ptr;
unsigned char   s_pic_bit_buff;
ColorCacheEntry s_pic_color_cache[128];
int             s_pic_color_cache_top;
unsigned short *s_pic_image16;
unsigned char  *s_pic_image_indexed;
unsigned char  *s_pic_chain_flags;
// clang-format on

Pic *picOpen(unsigned char *data, Pic *pic)
{
    bitInit(data);
    pic->data      = data;
    s_pic_bit_len  = 8;
    s_pic_buff_ptr = pic->data;
    s_pic_bit_buff = *s_pic_buff_ptr;
    picColorCacheInit();
    picReadHeader(pic);

    return pic;
}

Pic *picDecode(int arg0, void *buf, Pic *pic)
{
    int size;
    int i;

    picColorCacheInit();

    switch (pic->bits) {
        case 15:
        case 16:
            pic->image = s_pic_image16 = buf;
            size                       = pic->width * pic->height;

            for (i = 0; i < size; i++) {
                s_pic_image16[i] = 0;
            }
            picExpand16(pic);

            if (pic->bits == 15 && pic->transparent != PIC_NO_COLOR) {
                picClearTransparent(pic);
            }
            break;
        case 8:
            picDecode8(arg0, buf, pic);
            break;
        case 4:
            picDecode4(arg0, buf, pic);
            break;
        default:
            PRINTF(("picDecode: unknown format\n"));
            break;
    }

    return pic;
}

void *picDecode8(int arg0, void *buf, Pic *pic)
{
    int size;
    int i;
    int allocated;
    int c;

    allocated           = FALSE;
    s_pic_image_indexed = buf;
    pic->image          = buf;

    if (pic->type == PIC_TYPE_PALETTE) {
        pic->palette = (unsigned short *) (((int) pic->image + pic->width * pic->height + 7) & ~7);
        picReadPalette(256, pic);
    }
    size              = pic->width * pic->height;
    s_pic_chain_flags = amemAlloc(g_sys->memory_blocks, size / 8 + 1);

    if (s_pic_chain_flags == NULL) {
        if (g_sys->disable_graphics_tasks) {
            PRINTF(("PIC: warning: use frame buffer\n"));
            s_pic_chain_flags = (unsigned char *) g_frame_buffers[(g_sys->current_frame_buffer == 2) ? 0 : g_sys->current_frame_buffer + 1];
        } else {
            PRINTF(("PIC: fatal: no memory\n"));

            return NULL;
        }
    } else {
        allocated = TRUE;
    }

    for (i = 0; i < size; i++) {
        s_pic_image_indexed[i] = 0;
        picFlagClear(s_pic_chain_flags, i);
    }
    picExpand8(pic);

    for (i = 0; i < size; i++) {
        if (picFlagTest(s_pic_chain_flags, i)) {
            c = s_pic_image_indexed[i];
        }
        s_pic_image_indexed[i] = c;
    }

    if (allocated) {
        amemFree(g_sys->memory_blocks, s_pic_chain_flags);
    }

    return buf;
}

void *picDecode4(int arg0, void *buf, Pic *pic)
{
    int width;
    int size;
    int i;
    int x;
    int y;
    int c;
    int n;
    int allocated = FALSE;

    width      = (pic->width + 1) & ~1;
    size       = pic->height * width;
    pic->image = s_pic_image_indexed = buf;

    if (pic->type == PIC_TYPE_PALETTE) {
        pic->palette = (unsigned short *) (((unsigned int) pic->image + (size / 2 + (size & 1)) + 7) & ~7);
        picReadPalette(16, pic);
    }
    s_pic_chain_flags = amemAlloc(g_sys->memory_blocks, size / 8 + 1);

    if (s_pic_chain_flags == NULL) {
        if (g_sys->disable_graphics_tasks) {
            PRINTF(("PIC: warning: use frame buffer\n"));
            s_pic_chain_flags = (unsigned char *) g_frame_buffers[(g_sys->current_frame_buffer == 2) ? 0 : g_sys->current_frame_buffer + 1];
        } else {
            PRINTF(("PIC: fatal: no memory\n"));

            return NULL;
        }
    } else {
        allocated = TRUE;
    }

    for (i = 0; i < size / 8 + 1; i++) {
        s_pic_chain_flags[i] = 0;
    }
    i = 0;
    picExpand4(pic);

    for (y = 0; y < pic->height; y++) {
        for (x = 0; x < width; x++) {
            if (picFlagTest(s_pic_chain_flags, i++)) {
                c = picPoint4(x, y);
            }
            picPset4(x, y, c);
        }
    }

    if (allocated) {
        amemFree(g_sys->memory_blocks, s_pic_chain_flags);
    }
}

int  bitRead(unsigned int n);
void picReadPalette(int n, Pic *pic)
{
    int i;
    int r;
    int g;
    int b;

    for (i = 0; i < n; i++) {
        g = bitRead(5);
        r = bitRead(5);
        b = bitRead(5);

        if (bitRead(1)) {
            g = 1;
            b = 1;
            r = 1;
        }
        pic->palette[i] = (r << 11) | (g << 6) | (b << 1) | 1;

        if (pic->transparent != PIC_NO_COLOR && pic->transparent == (pic->palette[i] & 0xFFFE)) {
            pic->palette[i] &= 0xFFFE;
        }
    }
}

void picReadHeader(Pic *pic)
{
    unsigned char hex[4];
    int           mode;
    int           c;

    bitRead(8);
    bitRead(8);
    bitRead(8);
    s_pic_transparent = PIC_NO_COLOR;
    c                 = (unsigned char) bitRead(8);
    hex[0]            = c;

    if (c != 0x1A) {
        hex[1]            = bitRead(8);
        hex[2]            = bitRead(8);
        hex[3]            = bitRead(8);
        s_pic_transparent = picParseHex(hex);

        while (bitRead(8) != 0x1A) {}
    }
    while (bitRead(8) != 0) {}
    bitRead(8);
    mode = bitRead(4);
    bitRead(4);
    pic->bits    = bitRead(16);
    s_pic_width  = bitRead(16);
    s_pic_height = bitRead(16);

    if (s_pic_height > 512) {
        s_pic_height = 512;
    }
    pic->width       = s_pic_width;
    pic->height      = s_pic_height;
    pic->image       = NULL;
    pic->palette     = NULL;
    pic->transparent = s_pic_transparent;

    if (mode == 4) {
        pic->type = PIC_TYPE_NO_PALETTE;
        pic->size = ((s_pic_width + 1) & ~1) * s_pic_height * pic->bits / 8;
    } else if (pic->bits == 15 || pic->bits == 16) {
        pic->type = PIC_TYPE_DIRECT;
        pic->size = s_pic_width * s_pic_height * 2;
    } else {
        pic->type = PIC_TYPE_PALETTE;
        // clang-format off
        pic->size = ((s_pic_width * s_pic_height * pic->bits) / 8 + (s_pic_width * s_pic_height & 1) * 2 +
                     (pic->bits == 4) * 32 + (pic->bits == 8) * 512 + 7) & ~7;
        // clang-format on
    }
}

void picExpand16(Pic *pic)
{
    int x = -1;
    int y = 0;
    int c = 0;
    int l;
    int a;

    for (;;) {
        l = picReadLen();

        while (--l) {
            if (++x == s_pic_width) {
                x = 0;

                if (++y == s_pic_height) {
                    return;
                }
            }

            if ((a = picPoint(x, y)) != 0) {
                if (pic->bits == 16) {
                    c = a;
                } else {
                    c = a & 0xFFFE;
                }
            }
            picPset(pic, x, y, c);
        }

        if (++x == s_pic_width) {
            x = 0;

            if (++y == s_pic_height) {
                return;
            }
        }
        c = picReadColor(pic);
        picPset(pic, x, y, c);

        if (bitRead(1)) {
            picExpandChain16(pic, x, y, c);
        }
    }
}

void picExpandChain16(Pic *pic, int x, int y, int c)
{
    int in_range = TRUE;

    for (;;) {
        switch (bitRead(2)) {
            case 0:
                if (bitRead(1) == 0) {
                    return;
                }

                if (bitRead(1) == 0) {
                    x -= 2;
                } else {
                    x += 2;
                }
                break;
            case 1:
                x--;
                break;
            case 2:
                break;
            case 3:
                x++;
                break;
        }

        if (x >= s_pic_width) {
            return;
        }

        if (++y >= s_pic_height) {
            in_range = FALSE;
        }

        if (in_range) {
            picPset(pic, x, y, c);
        }
    }
}

void picExpand8(Pic *pic)
{
    int i;
    int x;
    int y;

    picPset8(0, 0, 0);
    i = -1;

    while (i < pic->width * pic->height) {
        i += picReadLenIndexed(pic);

        if (i < pic->width * pic->height) {
            x = i % pic->width;
            y = i / pic->width;
            picExpandChain8(pic, x, y, bitRead(pic->bits));
        }
    }
}

void picExpand4(Pic *pic)
{
    int i;
    int x;
    int y;

    picPset4(0, 0, 0);
    i = -1;

    while (i < pic->width * pic->height) {
        i += picReadLenIndexed(pic);

        if (i < pic->width * pic->height) {
            x = i % pic->width;
            y = i / pic->width;
            picExpandChain4(pic, x, y, bitRead(pic->bits));
        }
    }
}

int picReadLenIndexed(Pic *pic)
{
    int base;
    int n;

    // clang-format off
    base = 2; n = 1; while (bitRead(1) == 1) {
        // clang-format on
        base *= 2;
        n++;
    }

    return bitRead(n) + base - 1;
}

void picExpandChain8(Pic *pic, int x, int y, int c)
{
    unsigned char done;

    picPset8(x, y, c);

    if (bitRead(1) == 1) {
        done = FALSE;

        do {
            switch (bitRead(2)) {
                case 1:
                    x--;
                    y++;
                    picPset8(x, y, c);
                    break;
                case 2:
                    y++;
                    picPset8(x, y, c);
                    break;
                case 3:
                    x++;
                    y++;
                    picPset8(x, y, c);
                    break;
                case 0:
                    if (bitRead(1) == 0) {
                        done = TRUE;
                    } else if (bitRead(1) == 0) {
                        x -= 2;
                        y++;
                        picPset8(x, y, c);
                    } else {
                        x += 2;
                        y++;
                        picPset8(x, y, c);
                    }
                    break;
            }
        } while (!done);
    }
}

void picExpandChain4(Pic *pic, int x, int y, int c)
{
    unsigned char done;

    picPset4(x, y, c);

    if (bitRead(1) == 1) {
        done = FALSE;

        do {
            switch (bitRead(2)) {
                case 1:
                    x--;
                    y++;
                    picPset4(x, y, c);
                    break;
                case 2:
                    y++;
                    picPset4(x, y, c);
                    break;
                case 3:
                    x++;
                    y++;
                    picPset4(x, y, c);
                    break;
                case 0:
                    if (bitRead(1) == 0) {
                        done = TRUE;
                    } else if (bitRead(1) == 0) {
                        x -= 2;
                        y++;
                        picPset4(x, y, c);
                    } else {
                        x += 2;
                        y++;
                        picPset4(x, y, c);
                    }
                    break;
            }
        } while (!done);
    }
}

int picReadLen(void)
{
    int a = 1;

    while (bitRead(1)) {
        a++;
    }

    return bitRead(a) + (1 << a) - 1;
}

int picReadColor(Pic *pic)
{
    unsigned int bits = pic->bits;

    if (bits == 15 || bits == 16) {
        if (bitRead(1) == 0) {
            return picNewColor(pic, bitRead(pic->bits));
        }
        return picGetColor(pic, bitRead(7));
    }

    return bitRead(bits);
}

void picColorCacheInit(void)
{
    int i;

    for (i = 0; i < 128; i++) {
        s_pic_color_cache[i].color = 0;
        s_pic_color_cache[i].prev  = i + 1;
        s_pic_color_cache[i].next  = i - 1;
    }
    s_pic_color_cache[127].prev = 0;
    s_pic_color_cache[0].next   = 127;
    s_pic_color_cache_top       = 0;
}

int picNewColor(Pic *pic, int c)
{
    if (pic->bits == 15) {
        c                                              = ((c >> 5) & 0x3FF) + ((c & 0x1F) << 10);
        s_pic_color_cache_top                          = s_pic_color_cache[s_pic_color_cache_top].prev;
        s_pic_color_cache[s_pic_color_cache_top].color = c;

        return c << 1;
    }
    c                                              = ((c & 0xFFC0) >> 5) | ((c & 0x3E) << 10) | (c & 1);
    s_pic_color_cache_top                          = s_pic_color_cache[s_pic_color_cache_top].prev;
    s_pic_color_cache[s_pic_color_cache_top].color = c;

    return c;
}

int picGetColor(Pic *pic, int idx)
{
    int c;

    if (s_pic_color_cache_top != idx) {
        s_pic_color_cache[s_pic_color_cache[idx].prev].next                   = s_pic_color_cache[idx].next;
        s_pic_color_cache[s_pic_color_cache[idx].next].prev                   = s_pic_color_cache[idx].prev;
        s_pic_color_cache[s_pic_color_cache[s_pic_color_cache_top].prev].next = idx;
        s_pic_color_cache[idx].prev                                           = s_pic_color_cache[s_pic_color_cache_top].prev;
        s_pic_color_cache[s_pic_color_cache_top].prev                         = idx;
        s_pic_color_cache[idx].next                                           = s_pic_color_cache_top;
        s_pic_color_cache_top                                                 = idx;
    }

    if (pic->bits == 16) {
        c = s_pic_color_cache[idx].color;
    } else {
        c = s_pic_color_cache[idx].color * 2;
    }

    return c;
}

int picPoint(int x, int y)
{
    unsigned short c = s_pic_image16[s_pic_width * y + x];

    return (((c & 0x3E) >> 1) << 11) | (((c & 0x7C0) >> 6) << 6) | (((c & 0xF800) >> 11) << 1) | (c & 1);
}

void picPset(Pic *pic, int x, int y, int c)
{
    int a;

    if (x >= 0 && x < s_pic_width && y >= 0 && y <= s_pic_height) {
        a                                  = (pic->bits == 16) ? (c & 1) : 1;
        s_pic_image16[s_pic_width * y + x] = (((c & 0x3E) >> 1) << 11) | (((c & 0x7C0) >> 6) << 6) |
                                             (((c & 0xF800) >> 11) << 1) | a;
    } else {
        PRINTF(("PIC: decode overrun(pset). x=%d, y=%d\n", x, y));
    }
}

void picReset(int x, int y)
{
    if (x >= 0 && x < s_pic_width && y >= 0 && y <= s_pic_height) {
        s_pic_image16[s_pic_width * y + x] = 0;
    } else {
        PRINTF(("PIC: decode overrun(reset). x=%d, y=%d\n", x, y));
    }
}

void picUnused(void)
{
}

void picPset8(int x, int y, int c)
{
    if (x < 0 || x >= s_pic_width || y < 0 || y > s_pic_height) {
        PRINTF(("PIC: decode overrun(pset8). x=%d, y=%d\n", x, y));
    }
    s_pic_image_indexed[s_pic_width * y + x] = c;
    picFlagSet(s_pic_chain_flags, s_pic_width * y + x);
}

int picPoint4(int x, int y)
{
    int width = s_pic_width;
    int i;

    width = (width + 1) & ~1;
    i     = width * y + x;

    if (i & 1) {
        return s_pic_image_indexed[i / 2] & 0xF;
    }

    return (s_pic_image_indexed[i / 2] & 0xF0) >> 4;
}

void picPset4(int x, int y, int c)
{
    int  width = (s_pic_width + 1) & ~1;
    int  i;
    char color;

    if (x >= 0 && x < s_pic_width && y >= 0 && y <= s_pic_height) {
        i     = width * y + x;
        color = c;

        if (i & 1) {
            s_pic_image_indexed[i / 2] |= color;
        } else {
            s_pic_image_indexed[i / 2] |= color << 4;
        }
        picFlagSet(s_pic_chain_flags, i);
    } else {
        PRINTF(("PIC: decode overrun(pset4). x=%d, y=%d\n", x, y));
    }
}

int picParseHex(unsigned char *s)
{
    int   value = 0;
    int   i;
    int   j;
    int   shift;
    char *digits = "0123456789abcdef";

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j++) {
            if (*s == digits[j]) {
                shift = -i * 4 + 12;
                goto found;
            }
        }

        return PIC_NO_COLOR;
    found:
        s++;
        value += j << shift;
    }

    return value;
}

void picClearTransparent(Pic *pic)
{
    int x;
    int y;

    for (y = 0; y < pic->height; y++) {
        for (x = 0; x < pic->width; x++) {
            if (pic->transparent == (picPoint(x, y) & 0xFFFE)) {
                picReset(x, y);
            }
        }
    }
}

void picFlagSet(unsigned char *bits, int i)
{
    bits[i >> 3] |= 1 << (i & 7);
}

void picFlagClear(unsigned char *bits, int i)
{
    bits[i >> 3] &= ~(1 << (i & 7));
}

int picFlagTest(unsigned char *bits, int i)
{
    int set;

    if (bits[i >> 3] & (1 << (i & 7))) {
        set = TRUE;
    } else {
        set = FALSE;
    }

    return set;
}
