#include "system/lzkn64.h"
#include "sys.h"
#include "system/main.h"

unsigned int s_lzkn64_rom;
unsigned int s_lzkn64_pos;
int          s_lzkn64_rom_left;
int          s_lzkn64_left;
int          s_lzkn64_buf_left;
unsigned short s_lzkn64_plane;
unsigned short s_lzkn64_planes;

#ifdef NON_MATCHING
unsigned char *func_80005220(unsigned char *p, unsigned char *dst) {
    unsigned char *end;
    unsigned char *win;
    unsigned char byte;
    unsigned char fill;
    unsigned short cmd;
    unsigned short len;

    end = p + *(int *)p;
    p += 4;
    while (p < end) {
        cmd = byte = *p++;
        if (cmd < 0x80) {
            win = dst - (((byte << 8) + *p++) & 0x3FF);
            len = (cmd >> 2) + 2;
            while (len--) {
                *dst++ = *win++;
            }
        } else if (cmd < 0xA0) {
            len = cmd & 0x1F;
            while (len--) {
                *dst++ = *p++;
            }
        } else {
            if (cmd < 0xE0) {
                fill = *p++;
                len = (cmd & 0x1F) + 2;
            } else if (cmd < 0xFF) {
                fill = 0;
                len = (cmd & 0x1F) + 2;
            } else {
                fill = 0;
                len = *p++ + 2;
            }
            while (len--) {
                *dst++ = fill;
            }
        }
    }
    return dst;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/lzkn64/func_80005220.s")
#endif

#ifdef NON_MATCHING
unsigned char *func_80005394(unsigned int rom, unsigned char *dst, int size) {
    unsigned char *p;
    unsigned char *base;
    unsigned char *win;
    unsigned char fill;
    unsigned short off;
    unsigned int nib;
    unsigned int hdr;
    unsigned int end;
    int cmd;
    unsigned short len;

    s_lzkn64_rom = s_lzkn64_pos = rom;
    s_lzkn64_rom_left = s_lzkn64_left = size;
    s_lzkn64_left = size - 1;
    p = g_sys->decompression_buffer;
    func_80005984();
    while (s_lzkn64_left > 0) {
        hdr = *p << 24;
        p = func_80005900(p);
        hdr += *p << 16;
        p = func_80005900(p);
        hdr += *p << 8;
        p = func_80005900(p);
        hdr += *p;
        p = func_80005900(p);
        end = s_lzkn64_pos + hdr - 4;
        nib = hdr & 0xF0000000;
        if (nib != 0) {
            while (s_lzkn64_pos < end) {
                len = *p;
                p = func_80005900(p);
                cmd = len;
                if (len < 0x80) {
                    off = (*p + (len << 8)) & 0x3FF;
                    p = func_80005900(p);
                    win = dst - off;
                    len = (cmd >> 2) + 2;
                    while (len--) {
                        *dst++ = *win++;
                    }
                } else if (cmd < 0xA0) {
                    len = cmd & 0x1F;
                    while (len--) {
                        *dst++ = *p;
                        p = func_80005900(p);
                    }
                } else {
                    if (cmd < 0xE0) {
                        len = (cmd & 0x1F) + 2;
                        fill = *p;
                        p = func_80005900(p);
                    } else if (cmd < 0xFF) {
                        fill = 0;
                        len = (cmd & 0x1F) + 2;
                    } else {
                        fill = 0;
                        len = *p + 2;
                        p = func_80005900(p);
                    }
                    while (len--) {
                        *dst++ = fill;
                    }
                }
            }
        } else {
            s_lzkn64_planes = (nib >> 28) + 1;
            base = dst;
            for (s_lzkn64_plane = 0; s_lzkn64_plane < s_lzkn64_planes; s_lzkn64_plane++) {
                if (s_lzkn64_plane != 0) {
                    hdr = *p << 24;
                    p = func_80005900(p);
                    hdr += *p << 16;
                    p = func_80005900(p);
                    hdr += *p << 8;
                    p = func_80005900(p);
                    hdr += *p;
                    p = func_80005900(p);
                    end = s_lzkn64_pos + hdr - 4;
                    dst = base;
                }
                hdr &= 0x0FFFFFFF;
                while (s_lzkn64_pos < end) {
                    len = *p;
                    p = func_80005900(p);
                    cmd = len;
                    if (len < 0x80) {
                        off = (*p + (len << 8)) & 0x3FF;
                        p = func_80005900(p);
                        win = dst - s_lzkn64_planes * off;
                        len = (cmd >> 2) + 2;
                        while (len--) {
                            *dst = *win;
                            dst += s_lzkn64_planes;
                            win += s_lzkn64_planes;
                        }
                    } else if (cmd < 0xA0) {
                        len = cmd & 0x1F;
                        while (len--) {
                            *dst = *p;
                            dst += s_lzkn64_planes;
                            p = func_80005900(p);
                        }
                    } else {
                        if (cmd < 0xE0) {
                            len = (cmd & 0x1F) + 2;
                            fill = *p;
                            p = func_80005900(p);
                        } else if (cmd < 0xFF) {
                            fill = 0;
                            len = (cmd & 0x1F) + 2;
                        } else {
                            fill = 0;
                            len = *p + 2;
                            p = func_80005900(p);
                        }
                        while (len--) {
                            *dst = fill;
                            dst += s_lzkn64_planes;
                        }
                    }
                }
                base++;
            }
        
        }
        while (end++ & 0xF) {
            p = func_80005900(p);
        }
    }
    return dst;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/lzkn64/func_80005394.s")
#endif

unsigned char *func_80005900(unsigned char *p) {
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

void func_80005984(void) {
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
