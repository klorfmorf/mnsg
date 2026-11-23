#include "sys/string.h"
#include "sys/sys.h"
#include "unk.h"
#include "sys/string_data.h"
#include "sys/gfx_data.h"

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

void func_800042AC(short entry, unsigned char *string, short x, short y)
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

#ifdef NON_MATCHING
void func_8000433C(void)
{
    TextLabel     *label;
    short          index;
    short          count;
    short          nibble;
    int            type;
    unsigned char *string;
    int            character;
    short          x_low;
    short          y_low;
    short          x_high;
    short          y_high;
    short          x_offset;
    unsigned int   glyph;
    short          s_offset;
    short          t_offset;

    gSPDisplayList(D_8015C5CC++, D_8006D508);
    gDPLoadTLUT_pal16(D_8015C5CC++, 0, D_8005B248);
    gDPLoadTextureBlock_4b(D_8015C5CC++, D_80301000, G_IM_FMT_CI, 128, 32, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    label = g_sys->text_label;
    for (index = 0, count = 0; index < 16; index++, label++) {
        type = label->type;

        switch (type) {
            case TEXT_LABEL_NONE:
                break;
            case TEXT_LABEL_STRING:
                x_offset  = 0;
                string    = label->string;
                character = *string++;

                while (character != 0) {
                    if (character != 0x20) {
                        x_low = label->x + x_offset;
                        y_low = label->y;

                        x_high = x_low + 7;
                        y_high = y_low + 7;

                        glyph    = (character - 0x30) * 2;
                        s_offset = ((short *) D_8005B270)[glyph];
                        t_offset = ((short *) D_8005B270)[glyph + 1];

                        gSPScisTextureRectangle(D_8015C5CC++, x_low << 2, y_low << 2, x_high << 2, y_high << 2, G_TX_RENDERTILE, s_offset, t_offset, 0x1000, 0x0400);
                        count++;
                    }

                    x_offset += 8;
                    character = *string++;
                }
                break;
            case TEXT_LABEL_HEXADECIMAL:
                x_offset = 0;
                for (nibble = 0; nibble < 8; nibble++) {
                    x_low = label->x + x_offset;
                    y_low = label->y;

                    x_high = x_low + 7;
                    y_high = y_low + 7;

                    glyph    = label->number;
                    glyph    = (glyph >> ((7 - nibble) * 4)) & 0xF;
                    s_offset = D_8005B39C[glyph].s;
                    t_offset = D_8005B39C[glyph].t;

                    gSPScisTextureRectangle(D_8015C5CC++, x_low << 2, y_low << 2, x_high << 2, y_high << 2, G_TX_RENDERTILE, s_offset, t_offset, 0x1000, 0x0400);
                    count++;

                    x_offset += 8;
                }
                break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/string/func_8000433C.s")
#endif
