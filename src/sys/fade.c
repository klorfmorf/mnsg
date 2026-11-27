#include "sys/fade.h"
#include "common.h"
#include "sys/sys.h"
#include "sys/obj_alloc.h"
#include "sys/task.h"
#include "sys/sprite.h"

void func_80036E34(Task *task, Obj *obj);

// clang-format off

// <<<<< data >>>>>
// 8x8 RGBA16 white texture.
unsigned short D_8006D360[64] = {
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

ObjSpritePart D_8006D3E0 = { SPRITE_PART_END | SPRITE_PART_TEXTURE | 1, 8, 8, 0, 0, 0, 0 };

ObjSpriteTex D_8006D3EC[2] = {
    { 8, 8, 16, 0, 0, D_8006D360, 0, 0 },
    { 8, 8, 16, 0, 0, D_8006D360, 0, 0 },
};

// clang-format on

int func_80036840(void *arg0)
{
    return func_80036860(arg0, 0x10);
}

int func_80036860(Task *task, unsigned char step)
{
    ObjSprite *fade;

    if (g_sys->fade == NULL) {
        return;
    }
    osViBlack(0);
    fade = g_sys->fade;
    if (step < fade->a) {
        fade->a -= step;
        return 1;
    }
    fade->a = 0;
    func_80036158(task, &g_sys->fade->header, 1);
    return 0;
}

int func_80036908(void *arg0)
{
    return func_80036928(arg0, 0x10);
}

int func_80036928(Task *task, unsigned char step)
{
    if (g_sys->fade != NULL) {
        if (g_sys->fade->a != 0xFF) {
            if (g_sys->fade->a < 0xFF - step) {
                g_sys->fade->a += step;
            } else {
                g_sys->fade->a = 0xFF;
                osViBlack(1);
            }
            return 1;
        }
        osViBlack(1);
        return 0;
    }
}

void func_800369B4(void *task)
{
    func_80036A28(task);
    g_sys->fade->a = 0xFF;
}

void func_800369F0(void *task)
{
    func_80036A28(task);
    g_sys->fade->a = 0;
}

void func_80036A28(Task *task)
{
    ObjSprite *fade;

    if (g_sys->fade != NULL) {
        func_80036158(task, &g_sys->fade->header, 1);
    }
    if (func_80035EEC(task, OBJ_KIND_2D, 1) == NULL) {
        func_80035044(task);
        return;
    }
    g_sys->fade             = (ObjSprite *) task->obj_tail;
    fade                    = (ObjSprite *) task->obj_tail;
    g_sys->sprite_tex_table = D_8006D3EC;
    func_800086D8(fade, &D_8006D3E0);
    fade->header.kind            = OBJ_KIND_2D;
    fade->flags.scaled           = 1;
    fade->flags.mode             = 3;
    fade->header.pri             = 11;
    fade->x                      = 0;
    fade->y                      = 0;
    fade->header.s_pri           = 0xFF;
    fade->r                      = 0;
    fade->g                      = 0;
    fade->b                      = 0;
    fade->a                      = 0x80;
    fade->palette_slot           = 0;
    fade->flags.tex_width_shift  = 6;
    fade->flags.tex_height_shift = 5;
    fade->scale_x                = 40.0f;
    fade->scale_y                = 30.0f;
}

void func_80036B7C(Task *task)
{
    ObjSprite *fade;

    if (g_sys_real.color_fade != NULL) {
        func_80036158(task, &g_sys_real.color_fade->header, 1);
    }
    if (func_80035EEC(task, OBJ_KIND_2D, 1) == NULL) {
        func_80035044(task);
        return;
    }
    g_sys_real.color_fade   = (ObjSprite *) task->obj_tail;
    fade                    = (ObjSprite *) task->obj_tail;
    g_sys->sprite_tex_table = D_8006D3EC;
    func_800086D8(fade, &D_8006D3E0);
    fade->header.kind            = OBJ_KIND_2D;
    fade->flags.scaled           = 1;
    fade->flags.mode             = 3;
    fade->header.pri             = 11;
    fade->x                      = 0;
    fade->y                      = 0;
    fade->header.s_pri           = 0xEF;
    fade->r                      = 0;
    fade->g                      = 0;
    fade->b                      = 0;
    fade->a                      = 0x80;
    fade->palette_slot           = 0;
    fade->flags.tex_width_shift  = 6;
    fade->flags.tex_height_shift = 5;
    fade->scale_x                = 40.0f;
    fade->scale_y                = 30.0f;
}

Task *func_80036CB4(Task *task, int r, int g, int b, int frames)
{
    if (frames >= 0) {
        return func_80036D2C(task, r, g, b, frames, -1, 0);
    } else {
        return func_80036D2C(task, r, g, b, 0, 0, -frames);
    }
}

void func_80036D0C(void *arg0)
{
    func_80036E2C(arg0);
}

Task *func_80036D2C(Task *parent, int r, int g, int b, int rise_frames, int hold_frames, int fall_frames)
{
    Task     *task = (*func_80034E08)(parent, (void (*)(Task *, Obj *)) func_80036E34, 0);
    FadeWork *work;

    if (task == NULL) {
        return NULL;
    }
    (*func_80036B7C)(task);
    g_sys_real.color_fade->r = r;
    g_sys_real.color_fade->g = g;
    g_sys_real.color_fade->b = b;
    g_sys_real.color_fade->a = 0xFF;
    work                     = FADE_WORK(task);
    work->rise_frames        = rise_frames;
    work->hold_frames        = hold_frames;
    work->fall_frames        = fall_frames;
    if (rise_frames != 0) {
        work->alpha_step = 256.0f / rise_frames;
    } else {
        work->alpha_step = 256.0f;
    }
    PRINTF(("L->dalpha: %.1f\n", work->alpha_step));
    work->active = 1;
    return task;
}

int func_80036E2C(Task *task)
{
    FadeWork *work = FADE_WORK(task);

    return work->active;
}

void func_80036E34(Task *task, Obj *obj)
{
    FadeWork *work = FADE_WORK(task);

    switch (work->step) {
        case 0:
            work->alpha += work->alpha_step;
            PRINTF(("INC: %.1f (%.1f)\n", work->alpha, work->alpha_step));
            if (work->alpha >= 255.0f) {
                work->alpha      = 255.0f;
                work->hold_timer = work->hold_frames;
                work->step++;
            } else {
                break;
            }

        case 1:
            work->alpha = 255.0f;
            PRINTF(("HOLD\n"));
            if (work->hold_timer-- == 0) {
                work->step++;
                if (work->fall_frames != 0) {
                    work->alpha_step = 256.0f / work->fall_frames;
                } else {
                    work->alpha_step = 256.0f;
                }
            } else {
                break;
            }

        case 2:
            work->alpha -= work->alpha_step;
            PRINTF(("DEC: %.1f\n", work->alpha));
            if (work->alpha <= 0.0f) {
                work->alpha = 0.0f;
                work->step++;
            } else {
                break;
            }

        case 3:
            work->active = 0;
            break;
    }
    g_sys->color_fade->a = work->alpha;
}
