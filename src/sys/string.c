#include "sys/string.h"
#include "sys/sys.h"
#include "sys/string_data.h"
#include "sys/gfx_data.h"
#include "unk.h"

void func_80004240(void)
{
    TextLabel *label;
    short      i;

    for (label = g_sys->text_label, i = 0; i < 16; label++, i++) {
        label->type = TEXT_LABEL_NONE;
    }
}

void func_8000427C(short entry)
{
    TextLabel *label = &g_sys->text_label[entry];

    label->type = TEXT_LABEL_NONE;
}

void func_800042AC(short entry, char *string, short x, short y)
{
    TextLabel *label = &g_sys->text_label[entry];

    label->type   = TEXT_LABEL_STRING;
    label->x      = x;
    label->y      = y;
    label->string = string;
}

void func_800042F4(short entry, unsigned int number, short x, short y)
{
    TextLabel *label = &g_sys->text_label[entry];

    label->type   = TEXT_LABEL_HEXADECIMAL;
    label->x      = x;
    label->y      = y;
    label->number = number;
}

void func_8000433C(void)
{
    TextLabel   *text;
    short        i;
    short        j;
    char        *str;
    short        dx;
    short        x;
    short        y;
    short        x2;
    short        y2;
    short        s;
    short        t;
    short        count;
    unsigned int digit;

    gSPDisplayList(g_sys_glistp++, D_8006D508);
    gDPLoadTLUT_pal16(g_sys_glistp++, 0, D_8005B248);
    gDPLoadTextureBlock_4b(g_sys_glistp++, D_80301000, G_IM_FMT_CI, 128, 32, 0, G_TX_MIRROR, G_TX_MIRROR, G_TX_NOMASK,
        G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    text = g_sys->text_label;
    for (i = 0, count = 0; i < 16; i++, text++) {
        switch (text->type) {
            case TEXT_LABEL_NONE:
                break;
            case TEXT_LABEL_STRING:
                str = text->string;
                dx  = 0;
                while (*str != '\0') {
                    if (*str != ' ') {
                        x  = text->x + dx;
                        y  = text->y;
                        x2 = x + 7;
                        y2 = y + 7;
                        s  = D_8005B270[(*str - 0x30) << 1];
                        t  = D_8005B270[((*str - 0x30) << 1) + 1];
                        gSPScisTextureRectangle(g_sys_glistp++, x << 2, y << 2, x2 << 2, y2 << 2, G_TX_RENDERTILE, s, t,
                            4 << 10, 1 << 10);
                        count++;
                    }
                    str++;
                    dx += 8;
                }
                break;
            case TEXT_LABEL_HEXADECIMAL:
                dx = 0;
                for (j = 0; j < 8; j++) {
                    x     = text->x + dx;
                    y     = text->y;
                    x2    = x + 7;
                    y2    = y + 7;
                    digit = text->number;
                    digit >>= (7 - j) * 4;
                    s = D_8005B39C[(digit & 0xF) << 1];
                    t = D_8005B39C[((digit & 0xF) << 1) + 1];
                    gSPScisTextureRectangle(g_sys_glistp++, x << 2, y << 2, x2 << 2, y2 << 2, G_TX_RENDERTILE, s, t,
                        4 << 10, 1 << 10);
                    count++;
                    dx += 8;
                }
                break;
        }
    }
}
