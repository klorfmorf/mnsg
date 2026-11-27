#include "sys/window_effect.h"
#include "common.h"
#include "sys/window.h"
#include "sys/sd_main.h"

void func_8000D918(Window *w);

void func_8000D400(Window *w)
{
    switch (w->effect) {
        case 1:
            w->state   = 2;
            w->clip_x0 = w->width / 2;
            w->clip_x1 = w->width / 2;
            w->clip_y0 = (w->strip_height * w->strip_count) / 2;
            w->clip_y1 = (w->strip_height * w->strip_count) / 2;
            break;
        case 2:
            w->state = 2;
            w->scale = w->rest_scale = 0.1f;
            func_8000D918(w);
            break;
        case 3:
            w->state = 2;
            w->scale = w->rest_scale = 0.1f;
            func_8000D918(w);
            break;
        default:
            func_8000D66C(w);
            break;
    }
}

void func_8000D4E0(Window *w)
{
    switch (w->effect) {
        case 1:
            w->clip_x0 -= 20;
            w->clip_y0 -= 10;
            w->clip_x1 += 20;
            w->clip_y1 += 10;
            if (w->clip_x0 < 0 && w->clip_y0 < 0) {
                func_8000D66C(w);
            }
            break;
        case 2:
            w->scale += 0.1;
            func_8000D918(w);
            if (w->scale >= 1.0) {
                w->scale = w->rest_scale = 1.0f;
                w->x                     = w->target_x;
                w->y                     = w->target_y;
                func_8000D66C(w);
            }
            break;
        case 3:
            w->scale += 0.2;
            func_8000D918(w);
            if (w->scale >= 1.0) {
                w->scale = w->rest_scale = 1.0f;
                w->x                     = w->target_x;
                w->y                     = w->target_y;
                func_8000D66C(w);
            }
            break;
        default:
            func_8000D66C(w);
            break;
    }
}

void func_8000D66C(Window *w)
{
    if (!(w->style & 1)) {
        func_80038BC8(0x249);
    }
    w->state = 4;
    w->flags &= ~0x1;
}

void func_8000D6D0(Window *w)
{
    switch (w->effect) {
        case 1:
            w->clip_x0 = 0;
            w->clip_y0 = 0;
            w->clip_x1 = w->width;
            w->clip_y1 = w->strip_height * w->strip_count;
            w->state   = 6;
            break;
        case 2:
            w->state    = 6;
            w->target_x = w->x;
            w->target_y = w->y;
            break;
        case 3:
            w->state    = 6;
            w->target_x = w->x;
            w->target_y = w->y;
            break;
        default:
            func_8000C878(w->id);
            w->x = w->target_x;
            w->y = w->target_y;
            break;
    }
}

void func_8000D79C(Window *w)
{
    switch (w->effect) {
        case 1:
            w->clip_x0 += 20;
            w->clip_y0 += 10;
            w->clip_x1 -= 20;
            w->clip_y1 -= 10;
            if (w->width / 2 < w->clip_x0 && w->strip_height / 2 < w->clip_y0) {
                func_8000C878(w->id);
            }
            break;
        case 2:
            w->scale -= 0.1;
            func_8000D918(w);
            if (w->scale <= 0.0f) {
                func_8000C878(w->id);
            }
            break;
        case 3:
            w->scale -= 0.2;
            func_8000D918(w);
            if (w->scale <= 0.0f) {
                func_8000C878(w->id);
            }
            break;
        default:
            func_8000C878(w->id);
            break;
    }
}

void func_8000D918(Window *w)
{
    int   half_w   = w->width / 2;
    float center_x = w->target_x + half_w;
    int   half_h   = (w->strip_height * w->strip_count) / 2;
    float center_y = w->target_y + half_h;
    float pos_x    = w->from_x + (center_x - w->from_x) * w->scale;
    float pos_y    = w->from_y + (center_y - w->from_y) * w->scale;

    w->x = pos_x - half_w * w->scale;
    w->y = pos_y - half_h * w->scale;
}

void func_8000D9F4(Window *w)
{
    int   half_w   = w->width / 2;
    float center_x = w->target_x + half_w;
    int   half_h   = (w->strip_height * w->strip_count) / 2;
    float center_y = w->target_y + half_h;

    w->x = center_x - half_w * w->scale;
    w->y = center_y - half_h * w->scale;
}

void func_8000DA94(Window *w)
{
    if (w->flags & 0x2) {
        if (w->scale < w->rest_scale - 0.07) {
            w->scale_speed = 0.01f;
        }
        if (w->rest_scale + 0.07 < w->scale) {
            w->scale_speed = -0.01f;
        }
        w->scale += w->scale_speed;
        func_8000D9F4(w);
    }
}

void func_8000DB38(int id)
{
    Window *w = D_80167C48[id];

    if (w != NULL) {
        w->flags |= 0x2;
        w->scale_speed = 0.01f;
    }
}

void func_8000DB78(int id)
{
    Window *w = D_80167C48[id];

    if (w != NULL) {
        w->flags &= ~0x2;
        w->scale_speed = 0.0f;
    }
}

void func_8000DBC0(WindowEntry *entry, float scale)
{
}

void func_8000DBCC(int arg0, int arg1)
{
}

void func_8000DBD8(int arg0, int arg1)
{
}
