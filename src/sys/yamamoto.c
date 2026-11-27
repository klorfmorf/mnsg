#include "sys/yamamoto.h"
#include "structs.h"
#include "sys/anime.h"
#include "sys/window.h"
#include "sys/wave_uty.h"
#include "sys/amem.h"
#include "sys/rom_trans.h"
#include "sys/task.h"
#include "sys/sys.h"
#include "sys/obj_alloc.h"
#include "sys/pal.h"
#include "sys/sprite.h"
#include "sys/solid_atari.h"
#include "unk.h"

void func_80011634(YamamotoObj *obj, unsigned short id);

// clang-format off

// <<<<< data >>>>>

AnimeCamera D_80063740 = {
    { 0.0f, 0.0f, 100.0f },
    { 0.0f, 0.0f, 0.0f },
    0,
    2560,
    20.0f,
    2000.0f,
    { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    32, 32, 0, 0,
    &g_anime_default_vp,
    3,
    0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
    -160.0f, -120.0f, 160.0f, 120.0f
};

unsigned int D_800637A0[2] = {
    0x646464FF, 0xFFFF0000,
};

unsigned int D_800637A8[6] = {
    0x80808000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
};

Gfx D_800637C0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

unsigned int D_80063828[16] = {
    0x0000318D, 0x18C70001, 0x0000318D, 0x18C70001, 0x0000318D, 0x18C70001, 0x0000318D, 0x18C70001,
    0x00000000, 0x00000000, 0x318D318D, 0x318D318D, 0x18C718C7, 0x18C718C7, 0x00010001, 0x00010001,
};

unsigned int D_80063868[16] = {
    0x000018C7, 0x318D4A53, 0x000018C7, 0x318D4A53, 0x000018C7, 0x318D4A53, 0x000018C7, 0x318D4A53,
    0x00000000, 0x00000000, 0x18C718C7, 0x18C718C7, 0x318D318D, 0x318D318D, 0x4A534A53, 0x4A534A53,
};

Gfx D_800638A8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetTextureConvert(G_TC_FILT),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0x80),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPEndDisplayList(),
};

void *D_80063918 = (void *) D_80063320;

unsigned int D_8006391C = 8;

unsigned int D_80063920 = 0x0000000C;

unsigned int D_80063924 = 2;

unsigned int D_80063928[2] = {
    0x00000002, 0x00000000,
};

Gfx D_80063930[] = {
    gsSPEndDisplayList(),
};

// <<<<< bss >>>>>
unsigned short D_80167C70[4];
ObjSpriteTex   D_80167C78[40];
SpriteList     D_80167EF8[16];

// clang-format on

void func_80010180(int a, int b)
{
}

void func_8001018C(int a)
{
    int i;

    for (i = 0; i < 16; i++) {
        PRINTF((" --> handle=%d  address=%08X max=%d \n", i, D_80167EF8[i].parts, D_80167EF8[i].max));
        PRINTF((" --> (head) %08X %d %08X %08X \n", D_80167EF8[i].parts, D_80167EF8[i].count, D_80167EF8[i].in_use, D_80167EF8[i].unk_06));
    }
}

void func_800101AC(void)
{
    unsigned int i;
    int         *p;

    g_sys->sprite_tex_table = D_80167C78;
    func_80007E5C();
    p = (int *) D_80167C78;
    for (i = 0; i < 160; i++) {
        *p++ = 0;
    }
    p = (int *) D_80167EF8;
    i = 0;
    while (i < 48) {
        *p++ = 0;
        i++;
    }
}

int func_80010230(unsigned short a, unsigned short b, unsigned char c, unsigned char d, void *e, unsigned short f)
{
    unsigned int  i;
    ObjSpriteTex *entry;

    for (i = 0; i < 40 && D_80167C78[i].data != 0; i++) {
    }
    PRINTF(("w=%03d h=%03d %04X %04X %08X %d\n", a, b, c, d, e, f));
    if (i == 40) {
        return -1;
    }
    entry         = &D_80167C78[i];
    entry->width  = a;
    entry->height = b;
    entry->fmt    = c;
    entry->pal    = d;
    entry->data   = e;
    entry->wave   = f;
    return i;
}

void func_800102E0(int index)
{
    YamamotoEntry *e;

    if (index != -1) {
        e         = &((YamamotoEntry *) D_80167C78)[index];
        e->width  = 0;
        e->height = 0;
        e->fmt    = 0;
        e->pal    = 0;
        e->data   = 0;
        e->wave   = 0;
    }
}

void func_80010318(void)
{
    int i;

    for (i = 0; i < 40; i++) {
        func_800102E0(i);
    }
}

void func_80010358(int list)
{
    D_80167EF8[list].count = 0;
}

void func_80010374(int list)
{
    if (list != -1) {
        if (D_80167EF8[list].parts != NULL) {
            amemFree(g_sys->memory_blocks, D_80167EF8[list].parts);
        }
        D_80167EF8[list].parts  = NULL;
        D_80167EF8[list].in_use = 0;
    }
}

int func_800103DC(Task *owner, unsigned int max, int pri)
{
    unsigned int list;
    ObjSprite   *sprite;

    for (list = 0; list < 16 && D_80167EF8[list].in_use != 0; list++) {
    }
    if (list == 16) {
        return -1;
    }
    if (D_80167EF8[list].parts != NULL) {
        return -1;
    }
    D_80167EF8[list].parts = amemAlloc(g_sys->memory_blocks, max * sizeof(ObjSpritePart));
    if (D_80167EF8[list].parts == NULL) {
        return -1;
    }
    if (func_80035EEC(owner, OBJ_KIND_2D, 1) == NULL) {
        func_80010374(list);
        func_80035044(owner);
        return -1;
    }
    D_80167EF8[list].in_use = 1;
    D_80167EF8[list].max    = max;
    func_80010358(list);
    sprite = (ObjSprite *) owner->obj_tail;
    func_800086D8(sprite, D_80167EF8[list].parts);
    sprite->header.kind            = OBJ_KIND_2D;
    sprite->flags.scaled           = 0;
    sprite->flags.mode             = 1;
    sprite->scale_x                = 1.0f;
    sprite->scale_y                = 1.0f;
    sprite->header.pri             = pri;
    sprite->flags.tex_width_shift  = 0;
    sprite->palette_slot           = 0;
    sprite->x                      = 0;
    sprite->y                      = 0;
    sprite->flags.tex_height_shift = 0;
    return list;
}

void func_800105AC(int index)
{
    int            i;
    unsigned short id;
    ObjSpritePart *rect;
    unsigned int  *p;

    if (D_80167EF8[index].in_use != 0) {
        if (D_80167EF8[index].max < D_80167EF8[index].count) {
            D_80167EF8[index].count = D_80167EF8[index].max;
        }
        id = 0xFFF;
        for (i = 0; i < D_80167EF8[index].count; i++) {
            rect = &D_80167EF8[index].parts[i];
            if (rect->flags == id & 0x0FFF) {
                rect->flags &= ~(SPRITE_PART_TEXTURE | 0x0FFF);
            } else {
                id = rect->flags & 0x0FFF;
            }
            rect->flags &= ~SPRITE_PART_END;
        }
        if (i == 0) {
            for (i = 0, p = (unsigned int *) D_80167EF8[index].parts; i < (int) (sizeof(ObjSpritePart) / sizeof(unsigned int)); i++) {
                *p++ = 0;
            }
            D_80167EF8[index].parts->flags = SPRITE_PART_END;
        } else {
            D_80167EF8[index].parts[i - 1].flags |= SPRITE_PART_END;
        }
    }
}

void func_800106B0(void)
{
    int i;

    for (i = 0; i < 16; i++) {
        func_800105AC(i);
    }
}

int func_800106F0(int list, int x, int y, int w, int h, int tex, int s, int t)
{
    ObjSpritePart *part;
    int            index = D_80167EF8[list].count;

    if (index >= D_80167EF8[list].max) {
        PRINTF(("Warning: in write_sprite\n"));
        return -1;
    }
    part         = &D_80167EF8[list].parts[index];
    part->flags  = SPRITE_PART_TEXTURE + tex;
    part->width  = w;
    part->height = h;
    part->x      = x;
    part->y      = y;
    part->s      = s << 5;
    part->t      = t << 5;
    D_80167EF8[list].count++;
    return index;
}

int func_80010784(int list, int index, int x, int y, int w, int h, int tex, int s, int t)
{
    SpriteList    *sl = &D_80167EF8[list];
    ObjSpritePart *part;

    if (index >= sl->max) {
        PRINTF(("Warning: in write_sprite\n"));
        return -1;
    }
    part         = &sl->parts[index];
    part->flags  = SPRITE_PART_TEXTURE + tex;
    part->width  = w;
    part->height = h;
    part->x      = x;
    part->y      = y;
    part->s      = s << 5;
    part->t      = t << 5;
    return index;
}

int func_8001080C(int list, int index)
{
    SpriteList *sl = &D_80167EF8[list];

    if (index >= sl->max) {
        PRINTF(("Warning: in write_sprite\n"));
        return -1;
    }
    sl->parts[index].flags |= SPRITE_PART_SKIP;
    return index;
}

int func_80010864(int list, int index)
{
    SpriteList *sl = &D_80167EF8[list];

    if (index >= sl->max) {
        PRINTF(("Warning: in write_sprite\n"));
        return -1;
    }
    sl->parts[index].flags &= ~SPRITE_PART_SKIP;
    return index;
}

Gfx *func_800108BC(Gfx *gfx)
{
    gSPDisplayList(gfx++, D_800637C0);
    gSPEndDisplayList(gfx);
    return gfx;
}

Gfx *func_800108E4(Gfx *gdl, int x, int y, int w, int h, int r, int g, int b, int a)
{
    gDPSetPrimColor(gdl++, 0, 0, r, g, b, a);
    gDPFillRectangle(gdl++, x, y, x + w, y + h);
    gSPEndDisplayList(gdl);
    return gdl;
}

void func_80010980(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
    D_8006391C    = a0;
    D_80063920    = a1;
    D_80063924    = a2;
    D_80063928[0] = a3;
}

Gfx *func_800109A4(Gfx *gdl, int idx)
{
    switch (idx) {
        case 0:
        default:
            D_80063918 = D_80063320;
            break;
        case 1:
            D_80063918 = D_80063828;
            break;
        case 2:
            D_80063918 = D_80063868;
            break;
        case 3:
            D_80063918 = D_800633A0;
            break;
        case 4:
            D_80063918 = D_800633E0;
            break;
        case 5:
            D_80063918 = D_80063420;
            break;
        case 6:
            D_80063918 = D_80063360;
            break;
    }
    gDPPipeSync(gdl++);
    gDPLoadTLUT_pal16(gdl++, 0, D_80063918);
    gDPLoadTLUT_pal16(gdl++, 1, (unsigned char *) D_80063918 + 0x20);
    gSPEndDisplayList(gdl);
    return gdl;
}

Gfx *func_80010B60(Gfx *gdl)
{
    gSPDisplayList(gdl++, D_800638A8);
    gDPLoadTLUT_pal16(gdl++, 0, D_80063918);
    gDPLoadTLUT_pal16(gdl++, 1, (unsigned char *) D_80063918 + 0x20);
    gSPEndDisplayList(gdl);
    return gdl;
}

#ifdef NON_MATCHING
Gfx *func_80010C6C(Gfx *gfx, int x, int y, int code)
{
    int width = D_8006391C, height = D_80063920;

    code -= ' ';
    code &= 0xFF;
    gDPPipeSync(gfx++);
    gDPLoadTextureTile_4b(gfx++, D_800629A0 + (code >> 1) * 48, G_IM_FMT_CI, 8, 12, 0, 0, 7, 11, code & 1,
        G_TX_MIRROR, G_TX_MIRROR, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gfx++, x << 2, y << 2, (x + width) << 2, (y + height) << 2, G_TX_RENDERTILE, 0, 16 << 5,
        0x2000 / width, 0x3000 / height);
    gSPEndDisplayList(gfx);
    return gfx;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_80010C6C.s")
#endif

#ifdef NON_MATCHING
Gfx *func_80010E9C(Gfx *gfx, int x, int y, unsigned char *text)
{
    int pos_y = y + 1;
    int pos_x = x;

    for (; *text != 0; text++) {
        switch (*text) {
            default:
                gfx = func_80010C6C(gfx, pos_x, pos_y, *text);
                pos_x += (int) (D_8006391C * D_8005BB10[*text - ' ']) / D_8005BB10[0] + D_80063924;
                break;
            case ' ':
                pos_x += (int) (D_8006391C * 4) / D_8005BB10[0] + D_80063924;
                break;
            case 1:
                pos_x = x;
                pos_y += D_80063920 + D_80063928[0];
                break;
            case 2:
                gfx = func_800109A4(gfx, text[1]);
                text++;
                break;
            case 3:
                func_80010980(D_8006391C, D_80063920, text[1], D_80063928[0]);
                text++;
                break;
            case 4:
                func_80010980(text[1], D_80063920, D_80063924, D_80063928[0]);
                text++;
                break;
            case 5:
                pos_x = x;
                pos_y += (D_80063920 + D_80063928[0]) / 2;
                break;
        }
    }
    return gfx;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_80010E9C.s")
#endif

#ifdef NON_MATCHING
Gfx *func_8001110C(Gfx *gfx, int x, int y, int value, int place)
{
    int           digit;
    unsigned char started = 0;
    unsigned char code;

    if (place == 2) {
        started = 1;
        place   = 10;
    }
    while (place > 0) {
        digit = value / place;
        value %= place;
        switch (digit) {
            default:
            case 0:
                if (!started && place != 1) {
                    goto next;
                }
#ifdef JAPAN_0
                code = 0xB0;
#else
                code = '0';
#endif
                started = 1;
                break;
            case 1:
#ifdef JAPAN_0
                code = 0xB0 + 1;
#else
                code = '1';
#endif
                started = 1;
                break;
            case 2:
#ifdef JAPAN_0
                code = 0xB0 + 2;
#else
                code = '2';
#endif
                started = 1;
                break;
            case 3:
#ifdef JAPAN_0
                code = 0xB0 + 3;
#else
                code = '3';
#endif
                started = 1;
                break;
            case 4:
#ifdef JAPAN_0
                code = 0xB0 + 4;
#else
                code = '4';
#endif
                started = 1;
                break;
            case 5:
#ifdef JAPAN_0
                code = 0xB0 + 5;
#else
                code = '5';
#endif
                started = 1;
                break;
            case 6:
#ifdef JAPAN_0
                code = 0xB0 + 6;
#else
                code = '6';
#endif
                started = 1;
                break;
            case 7:
#ifdef JAPAN_0
                code = 0xB0 + 7;
#else
                code = '7';
#endif
                started = 1;
                break;
            case 8:
#ifdef JAPAN_0
                code = 0xB0 + 8;
#else
                code = '8';
#endif
                started = 1;
                break;
            case 9:
#ifdef JAPAN_0
                code = 0xB0 + 9;
#else
                code = '9';
#endif
                started = 1;
                break;
        }
#ifdef JAPAN_0
        gfx = func_80010C6C(gfx, x, y, code);
#else
        gfx = func_80010C6C(gfx, x, y + 1, code);
#endif
    next:
#ifdef JAPAN_0
        x += D_8006391C + D_80063924;
#else
        x = x + D_8006391C * D_8005BB10[0] / D_8005BB10[0] + D_80063924;
#endif
        place /= 10;
    }
    return gfx;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_8001110C.s")
#endif

int func_8001136C(Task *task)
{
    Link2DWork *link   = LINK2D_WORK(task);
    Link2DWork *parent = link->parent;
    Obj        *node;

    if (parent != NULL) {
        link->x = parent->x + link->offset_x;
        link->y = parent->y + link->offset_y;
    } else {
        link->x = link->offset_x;
        link->y = link->offset_y;
    }
    for (node = task->obj_head; node != NULL; node = node->next) {
        switch (node->kind) {
            case 1:
                ((ObjSprite *) node)->x = link->x;
                ((ObjSprite *) node)->y = link->y;
                break;
            case 2:
                ((ObjSolid *) node)->tx = (float) (link->x + ((ObjSolid *) node)->work_pos.x) * 5 / 8 + -100.0f + 0.3;
                ((ObjSolid *) node)->ty = 65.0f - (float) (link->y + ((ObjSolid *) node)->work_pos.y) * 5 / 8 + 9.7;
                ((ObjSolid *) node)->tz = -200.0f;
                break;
        }
    }
}

AnimeCamera *func_800114B8(Task *task, int count, int draw_list)
{
    ObjSolid *model;

    switch (count) {
        default:
            model = (ObjSolid *) func_80035EEC(task, OBJ_KIND_SOLID, 1);
            if (model == NULL) {
                PRINTF(("Error: in link2D_create_camera\n"));
                return NULL;
            }
            model->header.kind = OBJ_KIND_SOLID;
            model->AModel      = (unsigned int) D_800637A0 + ANIME_KIND_LIGHT;
            model->header.pri  = draw_list;

        case 1:
            model = (ObjSolid *) func_80035EEC(task, OBJ_KIND_SOLID, 1);
            if (model == NULL) {
                PRINTF(("Error: in link2D_create_camera\n"));
                return NULL;
            }
            model->header.kind = OBJ_KIND_SOLID;
            model->AModel      = (unsigned int) D_800637A8 + ANIME_KIND_AMBIENT;
            model->header.pri  = draw_list;

        case 0:
            model = (ObjSolid *) func_80035EEC(task, OBJ_KIND_SOLID, 1);
            if (model == NULL) {
                PRINTF(("Error: in link2D_create_camera\n"));
                return NULL;
            }
            model->header.kind = OBJ_KIND_SOLID;
            model->AModel      = (unsigned int) &D_80063740 + ANIME_KIND_CAMERA;
            model->sx = model->sy = model->sz = 1.0f;
            model->header.pri                 = draw_list;
            break;
    }
    return &D_80063740;
}

void func_800115B8(YamamotoWork *obj, int dx, int dy)
{
    YamamotoPos *pos = &obj->pos;

    if (obj != NULL) {
        // clang-format off
        pos->x = pos->x + dx; pos->y = pos->y + dy;
        // clang-format on
    }
}

void func_800115E0(int *p, int a, int b)
{
    int *q = p + 0x20;

    if (p != NULL) {
        q[0] = a;
        q[1] = b;
    }
}

void func_800115F8(int *p, int a, int b)
{
    int *q = p + 0x17;

    if (p != NULL) {
        q[2] = a;
        q[3] = b;
    }
}

void func_80011610(YamamotoWork *obj, YamamotoWork *src)
{
    if (obj != NULL) {
        if (src == NULL) {
            obj->pos.parent = NULL;
        } else {
            obj->pos.parent = &src->pos;
        }
    }
}

void func_80011634(YamamotoObj *obj, unsigned short id)
{
    if (obj != NULL) {
        if (obj->next != NULL && id < obj->next->priority) {
            func_80011634(obj->next, id);
        }
        if (obj->sub.destroy != NULL) {
            obj->sub.destroy(obj);
        }
        func_80034EF8(obj);
    }
}

int func_800116AC(YamamotoObj *obj)
{
    if (obj == NULL) {
        return 0;
    }
    func_80011634(obj, obj->priority);
    return 0;
}

void func_800116DC(YamamotoObj *obj, int unused)
{
    YamamotoSub *sub = &obj->sub;

    if ((g_sys->controller[0].button_held_down & (A_BUTTON | B_BUTTON | START_BUTTON)) == 0) {
        func_8003521C(sub->exec);
        sub->exec = NULL;
    }
}

void func_80011734(YamamotoWork *obj, int val)
{
    if (obj != NULL) {
        obj->pos.exec = val;
        func_8003521C(func_800116DC);
    }
}

int func_80011760(Task *task)
{
    float       x;
    float       y;
    float       z;
    Link3DWork *link = LINK3D_WORK(task);
    Obj        *node;
    Link3DWork *parent = link->parent;
    ObjSolid   *model;

    if (parent != NULL) {
        link->rx = (parent->rx + link->offset_rx) & ANGLE_MASK;
        link->ry = (parent->ry + link->offset_ry) & ANGLE_MASK;
        link->rz = (parent->rz + link->offset_rz) & ANGLE_MASK;
        x        = link->offset_x;
        y        = link->offset_y;
        z        = link->offset_z;
        func_80033898(parent->rx, parent->ry, parent->rz, &x, &y, &z);
        link->x = parent->x + x;
        link->y = parent->y + y;
        link->z = parent->z + z;
    } else {
        link->x  = link->offset_x;
        link->y  = link->offset_y;
        link->z  = link->offset_z;
        link->rx = link->offset_rx;
        link->ry = link->offset_ry;
        link->rz = link->offset_rz;
    }
    for (node = task->obj_head; node != NULL; node = node->next) {
        switch (node->kind) {
            case OBJ_KIND_2D:
                break;
            case OBJ_KIND_SOLID:
                model     = (ObjSolid *) node;
                model->tx = link->x;
                model->ty = link->y;
                model->tz = link->z;
                if (model->rx != ANGLE_BILLBOARD) {
                    model->rx = link->rx;
                }
                if (model->ry != ANGLE_BILLBOARD) {
                    model->ry = link->ry;
                }
                if (model->rz != ANGLE_BILLBOARD) {
                    model->rz = link->rz;
                }
                break;
        }
    }
}

void func_80011908(YamamotoObj *obj, float x, float y, float z)
{
    YamamotoSub *sub = &obj->sub;

    if (obj != NULL) {
        sub->offset_x = x;
        sub->offset_y = y;
        sub->offset_z = z;
    }
}

void func_80011934(YamamotoObj *obj, unsigned short a, unsigned short b, unsigned short c)
{
    YamamotoSub *sub = &obj->sub;

    if (obj != NULL) {
        sub->offset_rx = a;
        sub->offset_ry = b;
        sub->offset_rz = c;
    }
}

void func_80011968(YamamotoWork *obj, YamamotoWork *src)
{
    if (obj != NULL) {
        if (src == NULL) {
            obj->pos.parent = NULL;
        } else {
            obj->pos.parent = &src->pos;
        }
    }
}

void connect_magicfix(void)
{
    PRINTF(("connect_magicfix: in \n"));
    func_80013B14(FILE_60);
    func_80001EB0(FILE_60, func_800141C4(FILE_60));
    (*func_080026B8_71FE88)(g_task_list.head);
    PRINTF(("connect_magicfix: out \n"));
}

ObjSolid *func_800119D4(void *arg0, int pri)
{
    ObjSolid *solid = func_80035DFC(arg0, OBJ_KIND_SOLID, 1);

    if (solid == NULL) {
        return NULL;
    }
    solid->header.kind = OBJ_KIND_SOLID;
    solid->AModel      = (unsigned int) D_80063930 + ANIME_KIND_MODEL;
    solid->header.pri  = pri;
    solid->disabled    = 0;
    return solid;
}

ObjSolid *func_80011A38(void *arg0, int pri)
{
    ObjSolid *solid = func_80035EEC(arg0, OBJ_KIND_SOLID, 1);

    if (solid == NULL) {
        return NULL;
    }
    solid->header.kind = OBJ_KIND_SOLID;
    solid->AModel      = (unsigned int) D_80063930 + ANIME_KIND_MODEL;
    solid->header.pri  = pri;
    solid->disabled    = 0;
    return solid;
}

void func_80011A9C(void)
{
    Task        *task;
    Obj         *obj;
    ObjSolid    *solid;
    unsigned int kind;

    PRINTF(("\n -- dbprint solid --\n"));
    for (task = g_task_list.head; task != NULL; task = task->next) {
        for (obj = task->obj_head; obj != NULL; obj = obj->next) {
            if (obj->kind & OBJ_HIDDEN) {
                continue;
            }
            if (obj->kind == OBJ_KIND_SOLID) {
                solid = (ObjSolid *) obj;
                if (solid->hidden != 1) {
                    PRINTF(("%d:%8X->%08X", task->priority, task, obj));
                    kind = solid->AModel & ANIME_KIND_MASK;
                    if (kind == ANIME_KIND_DEMO) {
                        PRINTF(("[Demo   ]"));
                    }
                    if (kind == ANIME_KIND_ANIME) {
                        PRINTF(("[Anime  ]"));
                    }
                    if (kind == ANIME_KIND_CAMERA) {
                        PRINTF(("[Camera ]"));
                    }
                    if (kind == ANIME_KIND_LIGHT) {
                        PRINTF(("[Light  ]"));
                    }
                    if (kind == ANIME_KIND_MODEL) {
                        PRINTF(("[Ambient]"));
                    }
                    if (kind == ANIME_KIND_AMBIENT) {
                        PRINTF(("[Model  ]"));
                    }
                    if (kind == ANIME_KIND_JCHAR) {
                        PRINTF(("[Jchar  ]"));
                    }
                    if (kind == ANIME_KIND_JMODEL) {
                        PRINTF(("[Jmodel ]"));
                    }
                    PRINTF(("pri[%02d]", obj->s_pri));
                    if ((unsigned int) solid->init_glist & ANIME_GLIST_LOOKAT) {
                        PRINTF(("[L]"));
                    } else {
                        PRINTF(("[l]"));
                    }
                    PRINTF(("a[%08X]i[%08X]w[%d]", solid->init_glist, solid->AModel, task->wave.wave_no));
                    PRINTF(("\n"));
                }
            } else {
                PRINTF(("%d:%8X->%08X", task->priority, task, obj));
                switch (obj->kind) {
                    default:
                        PRINTF(("[Unknown Type]"));
                        break;
                    case OBJ_KIND_2D:
                        PRINTF(("[CLS_2D ]"));
                        break;
                    case OBJ_KIND_MOJI:
                        PRINTF(("[CLS_MOJI]"));
                        break;
                    case OBJ_KIND_BG:
                        PRINTF(("[CLS_BG ]"));
                        break;
                    case OBJ_KIND_GBG:
                        PRINTF(("[CLS_GBG]"));
                        break;
                }
                PRINTF(("pri[%02d]", obj->s_pri));
                PRINTF(("\n"));
            }
        }
    }
}

void func_80011B58(ObjSolid *obj)
{
    PRINTF(("next[%08X] kind[%02X] pri[%d] s_pri[%d]\n", obj->header.next, obj->header.kind, obj->header.pri, obj->header.s_pri));
    PRINTF(("tx[%4.4f] ty[%4.4f] tz[%4.4f]\n", obj->tx, obj->ty, obj->tz));
    PRINTF(("rx[%04X] ry[%04X] rz[%04X]\n", obj->rx, obj->ry, obj->rz));
    PRINTF(("sx[%4.4f] sy[%4.4f] sz[%4.4f]\n", obj->sx, obj->sy, obj->sz));
    PRINTF(("time[%4.4f] AModel[%08X] init_glist[%08X]\n", obj->time, obj->AModel, obj->init_glist));
}
