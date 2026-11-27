#include "sys/rom_decode.h"
#include "sys/sys.h"
#include "sys/main.h"

unsigned char *func_80005900(unsigned char *p);
void           func_80005984(void);

// clang-format off

// <<<<< bss >>>>>
unsigned int   s_lzkn64_rom;
unsigned int   s_lzkn64_pos;
int            s_lzkn64_rom_left;
int            s_lzkn64_left;
int            s_lzkn64_buf_left;
unsigned short s_lzkn64_plane;
unsigned short s_lzkn64_planes;

// clang-format on

unsigned char *func_80005220(unsigned char *src, unsigned char *dst)
{
    unsigned char *end = src + *(int *) src;
    unsigned char  c;
    unsigned short n;
    unsigned short dist;
    unsigned char *from;
    unsigned char  fill;

    src += 4;
    while (src < end) {
        c = *src++;
        if (c < 0x80) {
            dist = ((c << 8) + *src++) & 0x3FF;
            n    = (c >> 2) + 2;
            from = dst - dist;
            while (n--) {
                *dst++ = *from++;
            }
        } else if (c < 0xA0) {
            n = c & 0x1F;
            while (n--) {
                *dst++ = *src++;
            }
        } else {
            if (c < 0xE0) {
                n    = (c & 0x1F) + 2;
                fill = *src++;
            } else if (c < 0xFF) {
                fill = 0;
                n    = (c & 0x1F) + 2;
            } else {
                fill = 0;
                n    = *src++ + 2;
            }
            while (n--) {
                *dst++ = fill;
            }
        }
    }
    return dst;
}

unsigned char *func_80005394(unsigned int rom, unsigned char *dst, int size)
{
    unsigned char *in;
    unsigned int   header;
    unsigned int   end;
    unsigned char  c;
    unsigned short n;
    unsigned short dist;
    unsigned char  fill;
    unsigned char *base;
    unsigned short passes;
    unsigned char *from;

    s_lzkn64_rom = s_lzkn64_pos = rom;
    s_lzkn64_rom_left = s_lzkn64_left = size;
    s_lzkn64_left--;
    in = g_sys->decompression_buffer;
    func_80005984();
    while (s_lzkn64_left > 0) {
        header = *in << 24;
        in     = func_80005900(in);
        header += *in << 16;
        in = func_80005900(in);
        header += *in << 8;
        in = func_80005900(in);
        header += *in;
        in  = func_80005900(in);
        end = s_lzkn64_pos + header - 4;
        if (header & 0xF0000000) {
            while (s_lzkn64_pos < end) {
                c  = *in;
                in = func_80005900(in);
                if (c < 0x80) {
                    dist = ((c << 8) + *in) & 0x3FF;
                    in   = func_80005900(in);
                    n    = (c >> 2) + 2;
                    from = dst - dist;
                    while (n--) {
                        *dst++ = *from++;
                    }
                } else if (c < 0xA0) {
                    n = c & 0x1F;
                    while (n--) {
                        *dst++ = *in;
                        in     = func_80005900(in);
                    }
                } else {
                    if (c < 0xE0) {
                        n    = (c & 0x1F) + 2;
                        fill = *in;
                        in   = func_80005900(in);
                    } else if (c < 0xFF) {
                        fill = 0;
                        n    = (c & 0x1F) + 2;
                    } else {
                        fill = 0;
                        n    = *in + 2;
                        in   = func_80005900(in);
                    }
                    while (n--) {
                        *dst++ = fill;
                    }
                }
            }
        } else {
            s_lzkn64_plane  = 0;
            passes          = (header & 0xF0000000) >> 28;
            s_lzkn64_planes = passes + 1;
            for (base = dst; s_lzkn64_plane < s_lzkn64_planes; base++, s_lzkn64_plane++) {
                if (s_lzkn64_plane != 0) {
                    header = *in << 24;
                    in     = func_80005900(in);
                    header += *in << 16;
                    in = func_80005900(in);
                    header += *in << 8;
                    in = func_80005900(in);
                    header += *in;
                    in  = func_80005900(in);
                    end = s_lzkn64_pos + header - 4;
                    dst = base;
                }
                header &= 0x0FFFFFFF;
                while (s_lzkn64_pos < end) {
                    c  = *in;
                    in = func_80005900(in);
                    if (c < 0x80) {
                        dist = ((c << 8) + *in) & 0x3FF;
                        n    = (c >> 2) + 2;
                        in   = func_80005900(in);
                        from = dst - dist * s_lzkn64_planes;
                        while (n--) {
                            *dst = *from;
                            dst += s_lzkn64_planes;
                            from += s_lzkn64_planes;
                        }
                    } else if (c < 0xA0) {
                        n = c & 0x1F;
                        while (n--) {
                            *dst = *in;
                            dst += s_lzkn64_planes;
                            in = func_80005900(in);
                        }
                    } else {
                        if (c < 0xE0) {
                            n    = (c & 0x1F) + 2;
                            fill = *in;
                            in   = func_80005900(in);
                        } else if (c < 0xFF) {
                            fill = 0;
                            n    = (c & 0x1F) + 2;
                        } else {
                            fill = 0;
                            n    = *in + 2;
                            in   = func_80005900(in);
                        }
                        while (n--) {
                            *dst = fill;
                            dst += s_lzkn64_planes;
                        }
                    }
                }
            }
        }
#ifndef JAPAN_0
        while (end++ & 0xF) {
            in = func_80005900(in);
        }
#endif
    }
    return dst;
}

unsigned char *func_80005900(unsigned char *p)
{
    s_lzkn64_pos++;
    s_lzkn64_buf_left--;
    s_lzkn64_left--;
    if (s_lzkn64_buf_left != 0) {
        p++;
    } else {
        p = g_sys->decompression_buffer;
        func_80005984();
    }
    return p;
}

void func_80005984(void)
{
    s_lzkn64_buf_left = 0x2000;
    s_lzkn64_rom_left -= s_lzkn64_buf_left;
    if (s_lzkn64_rom_left < 0) {
        s_lzkn64_buf_left += (s_lzkn64_rom_left + 1) & ~1;
        s_lzkn64_rom_left = 0;
    }
    if (s_lzkn64_buf_left > 0) {
        func_80001640(s_lzkn64_rom, g_sys->decompression_buffer, s_lzkn64_buf_left);
    }
    s_lzkn64_rom += s_lzkn64_buf_left;
}
