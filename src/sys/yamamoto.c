#include "structs.h"
#include "sys/anime.h"
#include "sys/window.h"
#include "sys/wave_uty.h"
#include "sys/rom_trans.h"
#include "sys/task.h"
#include "sys/sys.h"
#include "sys/obj_alloc.h"
#include "sys/pal.h"
#include "sys/sprite.h"
#include "unk.h"

void func_800102E0(int index);
void func_800105AC(int index);
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
    0, 0, 320, 240,
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

// <<<<< rodata >>>>>
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/D_8007ACA0.s")

// <<<<< bss >>>>>
unsigned short D_80167C70[4];
unsigned char  D_80167C78[8];
int            D_80167C80[158];
SpriteList     D_80167EF8[16];

// clang-format on

void func_80010180(int a, int b)
{
}

void func_8001018C(int a)
{
    int i;
    int j;

    for (i = 0; i < 16; i += 4) {
        for (j = 0; j < 4; j++) {
        }
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

#ifdef NON_MATCHING
int func_80010230(unsigned short a, unsigned short b, unsigned char c, unsigned char d, int e, unsigned short f)
{
    YamamotoEntry *tbl = (YamamotoEntry *) D_80167C78;
    unsigned int   i;

    i = 0;
    if (D_80167C80[0] != 0) {
        for (i = 0; i < 40; i++) {
            if (tbl[i].unk_08 == 0) {
                break;
            }
        }
    }
    if (i == 40) {
        return -1;
    }
    tbl[i].unk_02 = b;
    tbl[i].unk_04 = c;
    tbl[i].unk_05 = d;
    tbl[i].unk_00 = a;
    tbl[i].unk_08 = e;
    tbl[i].unk_0C = f;
    return i;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_80010230.s")
#endif

void func_800102E0(int index)
{
    YamamotoEntry *e;

    if (index != -1) {
        e         = &((YamamotoEntry *) D_80167C78)[index];
        e->unk_00 = 0;
        e->unk_02 = 0;
        e->unk_04 = 0;
        e->unk_05 = 0;
        e->unk_08 = 0;
        e->unk_0C = 0;
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
        D_80167EF8[list].unk_00 = 0;
    }
}

#ifdef NON_MATCHING
int func_800103DC(SpriteOwner *owner, unsigned int max, int pri)
{
    unsigned int list;
    ObjSprite   *sprite;

    for (list = 0; list < 16 && D_80167EF8[list].unk_00 != 0; list++) {
    }
    if (list == 16) {
        return -1;
    }
    if (D_80167EF8[list].parts != NULL) {
        return -1;
    }
    D_80167EF8[list].parts = amemAlloc(g_sys->memory_blocks, max * sizeof(SpriteList));
    if (D_80167EF8[list].parts == NULL) {
        return -1;
    }
    if (func_80035EEC(owner, 1, 1) == NULL) {
        func_80010374(list);
        func_80035044(owner);
        return -1;
    }
    D_80167EF8[list].unk_00 = 1;
    D_80167EF8[list].max    = max;
    func_80010358(list);
    sprite = owner->sprite;
    func_800086D8(sprite, D_80167EF8[list].parts);
    sprite->unk_8.scaled           = 0;
    sprite->unk_8.mode             = 1;
    sprite->header.kind            = 1;
    sprite->unk_2c                 = 1.0f;
    sprite->header.pri             = pri;
    sprite->unk_30                 = 1.0f;
    sprite->unk_8.tex_width_shift  = 0;
    sprite->unk_8.tex_height_shift = 0;
    sprite->unk_c                  = 0;
    sprite->unk_1c                 = 0;
    sprite->unk_20                 = 0;
    return list;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_800103DC.s")
#endif

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_800105AC.s")

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
        return -1;
    }
    part         = &D_80167EF8[list].parts[index];
    part->flags  = 0x4000 + tex;
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
        return -1;
    }
    part         = &sl->parts[index];
    part->flags  = 0x4000 + tex;
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
        return -1;
    }
    sl->parts[index].flags |= 0x2000;
    return index;
}

int func_80010864(int list, int index)
{
    SpriteList *sl = &D_80167EF8[list];

    if (index >= sl->max) {
        return -1;
    }
    sl->parts[index].flags &= ~0x2000;
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

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_80010C6C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_80010E9C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_8001110C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_8001136C.s")

#ifdef NON_MATCHING
void *func_800114B8(void *arg0, int arg1, int arg2)
{
    ObjSolid    *solid;
    ObjSolid    *solid1;
    ObjSolid    *solid2;
    AnimeCamera *cam;

    switch (arg1) {
        default:
            solid = func_80035EEC(arg0, 2, 1);
            if (solid == NULL) {
                return NULL;
            }
            solid->header.kind = 2;
            solid->AModel      = (unsigned int) D_800637A0 + 0x30000000;
            solid->header.pri  = arg2;
        case 1:
            solid1 = func_80035EEC(arg0, 2, 1);
            if (solid1 == NULL) {
                return NULL;
            }
            solid1->header.kind = 2;
            solid1->AModel      = (unsigned int) D_800637A8 + 0x50000000;
            solid1->header.pri  = arg2;
        case 0:
            solid2 = func_80035EEC(arg0, 2, 1);
            if (solid2 == NULL) {
                return NULL;
            }
            cam                 = &D_80063740;
            solid2->header.kind = 2;
            solid2->AModel      = (unsigned int) cam + 0x20000000;
            solid2->sz          = 1.0f;
            solid2->sy          = 1.0f;
            solid2->sx          = 1.0f;
            solid2->header.pri  = arg2;
            return cam;
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_800114B8.s")
#endif

void func_800115B8(YamamotoWork *obj, int dx, int dy)
{
    YamamotoPos *pos = &obj->pos;

    if (obj != NULL) {
        // clang-format off
        pos->x = pos->x + dx; pos->y = pos->y + dy; // IDO schedules by source line
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
            obj->pos.unk_00 = NULL;
        } else {
            obj->pos.unk_00 = &src->pos;
        }
    }
}

void func_80011634(YamamotoObj *obj, unsigned short id)
{
    if (obj != NULL) {
        if (obj->unk_00 != NULL && id < obj->unk_00->unk_20) {
            func_80011634(obj->unk_00, id);
        }
        if (obj->sub.unk_04 != NULL) {
            obj->sub.unk_04(obj);
        }
        func_80034EF8(obj);
    }
}

int func_800116AC(YamamotoObj *obj)
{
    if (obj == NULL) {
        return 0;
    }
    func_80011634(obj, obj->unk_20);
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
        obj->pos.unk_18 = val;
        func_8003521C(func_800116DC);
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_80011760.s")

void func_80011908(YamamotoObj *obj, float x, float y, float z)
{
    YamamotoSub *sub = &obj->sub;

    if (obj != NULL) {
        sub->unk_08 = x;
        sub->unk_0C = y;
        sub->unk_10 = z;
    }
}

void func_80011934(YamamotoObj *obj, unsigned short a, unsigned short b, unsigned short c)
{
    YamamotoSub *sub = &obj->sub;

    if (obj != NULL) {
        sub->unk_14 = a;
        sub->unk_16 = b;
        sub->unk_18 = c;
    }
}

void func_80011968(YamamotoWork *obj, YamamotoWork *src)
{
    if (obj != NULL) {
        if (src == NULL) {
            obj->pos.unk_00 = NULL;
        } else {
            obj->pos.unk_00 = &src->pos;
        }
    }
}

void func_8001198C(void)
{
    func_80013B14(0x3C);
    func_80001EB0(0x3C, func_800141C4(0x3C));
    (*func_080026B8_71FE88)(g_task_list.head);
}

ObjSolid *func_800119D4(void *arg0, int pri)
{
    ObjSolid *solid = func_80035DFC(arg0, 2, 1);

    if (solid == NULL) {
        return NULL;
    }
    solid->header.kind = 2;
    solid->AModel      = (unsigned int) D_80063930 + 0x40000000;
    solid->header.pri  = pri;
    solid->disabled    = 0;
    return solid;
}

ObjSolid *func_80011A38(void *arg0, int pri)
{
    ObjSolid *solid = func_80035EEC(arg0, 2, 1);

    if (solid == NULL) {
        return NULL;
    }
    solid->header.kind = 2;
    solid->AModel      = (unsigned int) D_80063930 + 0x40000000;
    solid->header.pri  = pri;
    solid->disabled    = 0;
    return solid;
}

#ifdef NON_MATCHING
void func_80011A9C(void)
{
    Task *task;
    Obj  *obj;

    for (task = g_task_list.head; task != NULL; task = task->next) {
        for (obj = task->obj_head; obj != NULL; obj = obj->next) {
            if (obj->kind & 0x80) {
                continue;
            }
            if (obj->kind == 2) {
                ObjSolid *solid = (ObjSolid *) obj;

                if (solid->hidden != 1 && (solid->init_glist & 0x10000000)) {
                }
            } else if (obj->kind != 1 && obj->kind != 3) {
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/yamamoto/func_80011A9C.s")
#endif

void func_80011B58(int a)
{
}
