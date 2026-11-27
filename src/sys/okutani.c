#include "sys/okutani.h"
#include "common.h"
#include "sys/math.h"
#include "sys/wave_uty.h"
#include "sys/gfx_util.h"
#include "sys/obj_alloc.h"
#include "sys/sys.h"
#include "sys/task.h"
#include "unk.h"

void func_8000EFD0(Task *, ObjSolid *);
void func_8000F178(Task *, unsigned char);

// clang-format off

// <<<<< data >>>>>
unsigned int D_800636D0[4] = {
    0x00000003, 0x00000004, 0x00000005, 0x00000000,
};

Gfx D_800636E0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x01),
    gsDPSetPrimColor(0, 0, 0xFF, 0xFF, 0xFF, 0x00),
    gsSPEndDisplayList(),
};

// <<<<< bss >>>>>
int D_80167C60[4];

// clang-format on

ObjSolid *func_8000DBF0(Task *task, unsigned int id, Gfx *gfx, float x, float y, float z,
    unsigned short rot_x, unsigned short rot_y, unsigned short rot_z, float scale_x, float scale_y, float scale_z,
    unsigned short file0, unsigned short file1)
{
    ObjSolid *obj = (ObjSolid *) func_80035EEC(task, OBJ_KIND_SOLID, 1);

    if (task != NULL && obj != NULL) {
        obj->AModel     = id;
        obj->init_glist = (unsigned int) gfx;
        obj->tx         = x;
        obj->ty         = y;
        obj->tz         = z;
        obj->rx         = rot_x;
        obj->ry         = rot_y;
        obj->rz         = rot_z;
        obj->sx         = scale_x;
        obj->sy         = scale_y;
        obj->sz         = scale_z;
        obj->hidden     = 0;
        obj->disabled   = 0;
        obj->sibling    = NULL;
        obj->child      = NULL;
        obj->param      = 0;
        obj->param_fx8  = 0;
        obj->time = obj->scratch_f[0] = obj->scratch_f[1] = obj->blend = 0.0f;
        obj->SegWave[0].wave_no                                        = file0;
        obj->SegWave[1].wave_no                                        = file1;
        obj->SegWave[2].wave_no                                        = g_sys->common_wave_no;
        obj->SegWave[3].wave_no                                        = 0;
        obj->SegWave[4].wave_no                                        = 0;
        obj->SegWave[5].wave_no                                        = 0;
        func_80014218(obj);
        return obj;
    }
    return NULL;
}

void func_8000DD04(ObjSolid *src, ObjSolid *dst)
{
    dst->tx     = src->tx;
    dst->ty     = src->ty;
    dst->tz     = src->tz;
    dst->rx     = src->rx;
    dst->ry     = src->ry;
    dst->rz     = src->rz;
    dst->sx     = src->sx;
    dst->sy     = src->sy;
    dst->sz     = src->sz;
    dst->hidden = src->hidden;
}

int func_8000DD58(int range)
{
    float value;

    D_80167C60[0] = (D_80167C60[0] * 23 + 2345) % 4535;
    value         = 0.0002204585537918871 * D_80167C60[0] * range;
    return value;
}

int func_8000DDC0(void)
{
    if (func_8000DD58(100) >= 50) {
        return 1;
    }
    return 0;
}

Gfx *func_8000DDF0(Task *task, Gfx *dl, int r, int g, int b, int a)
{
    Gfx *list = (Gfx *) FLASH_WORK(task)->first_glist;
    Gfx *gfx  = list;

    gSPDisplayList(gfx++, dl);
    gDPSetPrimColor(gfx++, 0, 0, r, g, b, a);
    gSPEndDisplayList(gfx++);
    osWritebackDCache(list, (unsigned char *) gfx - (unsigned char *) list);
    return list;
}

Gfx *func_8000DE80(Task *task, Gfx *dl, int r, int g, int b, int a)
{
    Gfx *list = (Gfx *) FLASH_WORK(task)->second_glist;
    Gfx *gfx  = list;

    gSPDisplayList(gfx++, dl);
    gDPSetPrimColor(gfx++, 0, 0, r, g, b, a);
    gSPEndDisplayList(gfx++);
    osWritebackDCache(list, (unsigned char *) gfx - (unsigned char *) list);
    return list;
}

Gfx *func_8000DF10(Task *task, Gfx *dl, int r, int g, int b, int a)
{
    Gfx *list = (Gfx *) FLASH_WORK(task)->first_glist;
    Gfx *gfx  = list;

    gSPDisplayList(gfx++, dl);
    gDPSetEnvColor(gfx++, r, g, b, a);
    gSPEndDisplayList(gfx++);
    osWritebackDCache(list, (unsigned char *) gfx - (unsigned char *) list);
    return list;
}

Gfx *func_8000DFA0(Task *task, Gfx *dl, int r, int g, int b, int a)
{
    Gfx *list = (Gfx *) FLASH_WORK(task)->second_glist;
    Gfx *gfx  = list;

    gSPDisplayList(gfx++, dl);
    gDPSetEnvColor(gfx++, r, g, b, a);
    gSPEndDisplayList(gfx++);
    osWritebackDCache(list, (unsigned char *) gfx - (unsigned char *) list);
    return list;
}

Gfx *func_8000E030(Task *task, Gfx *dl, int prim_r, int prim_g, int prim_b, int prim_a, int env_r, int env_g,
    int env_b, int env_a)
{
    Gfx *list = (Gfx *) TINT_WORK(task)->glist;
    Gfx *gfx  = list;

    gSPDisplayList(gfx++, dl);
    gDPSetPrimColor(gfx++, 0, 0, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gfx++, env_r, env_g, env_b, env_a);
    gSPEndDisplayList(gfx++);
    osWritebackDCache(list, (unsigned char *) gfx - (unsigned char *) list);
    return list;
}

void func_8000E100(ObjSolid *obj, unsigned int id, unsigned char frame_count, unsigned short file_id)
{
    obj->AModel             = id;
    obj->time               = 0.0f;
    obj->frame_count        = frame_count;
    obj->SegWave[0].wave_no = file_id;
    func_80014218(obj);
}

void func_8000E160(ObjSolid *obj, unsigned int *images, int i)
{
    unsigned int image = images[0];

    obj->work[0xC + i]               = 0;
    obj->work[0x10 + i]              = 0;
    obj->SegWave[D_800636D0[i]].data = obj->SegWave[0].data + image - WAVE_SEGMENT_ADDR;
}

int func_8000E1A0(ObjSolid *obj, unsigned int *images, int i, unsigned char count, unsigned char delay)
{
    int           wrapped = 0;
    unsigned char frame;
    unsigned int  image;

    if (++obj->work[0xC + i] > delay) {
        frame = ++obj->work[0x10 + i];
        if (frame >= count) {
            wrapped = 1;
            frame = obj->work[0x10 + i] = 0;
        }
        image                            = images[frame];
        obj->work[0xC + i]               = 0;
        obj->SegWave[D_800636D0[i]].data = obj->SegWave[0].data + image - WAVE_SEGMENT_ADDR;
    }
    return wrapped;
}

void func_8000E23C(ObjSolid *obj, unsigned int *images, int i, unsigned char frame)
{
    unsigned int image;

    obj->work[0xC + i]               = 0;
    obj->work[0x10 + i]              = frame;
    image                            = images[obj->work[0x10 + i]];
    obj->SegWave[D_800636D0[i]].data = obj->SegWave[0].data + image - WAVE_SEGMENT_ADDR;
}

unsigned short func_8000E28C(float x1, float y1, float x2, float y2)
{
    return func_800040A8(y1 - y2, x1 - x2) & ANGLE_MASK;
}

int func_8000E2D4(float speed, unsigned short pitch, unsigned short yaw, Task *task)
{
    float horizontal;

    VELOCITY_WORK(task)->vel_y = ((speed < 0.0f) ? -speed : speed) * func_80003E10(pitch);
    horizontal                 = ((speed < 0.0f) ? -speed : speed) * func_80003EA0(pitch);
    VELOCITY_WORK(task)->vel_x = func_80003E10(yaw) * horizontal;
    VELOCITY_WORK(task)->vel_z = func_80003EA0(yaw) * horizontal;
    return 1;
}

int func_8000E39C(float length, float x, float y, float z, Task *task)
{
    float     dx;
    float     dy;
    float     dz;
    float     dy2;
    float     dz2;
    float     length2;
    float     dist2;
    ObjSolid *obj = (ObjSolid *) task->obj_head;

    dx                         = x - obj->tx;
    dy                         = y - obj->ty;
    dz                         = z - obj->tz;
    dy2                        = dy * dy;
    dz2                        = dz * dz;
    length2                    = length * length;
    dist2                      = dx * dx + dy2 + dz2;
    VELOCITY_WORK(task)->vel_x = _nsqrtf(dx * dx * length2 / dist2);
    if (dx < 0.0f) {
        VELOCITY_WORK(task)->vel_x = -VELOCITY_WORK(task)->vel_x;
    }
    VELOCITY_WORK(task)->vel_y = _nsqrtf(dy2 * length2 / dist2);
    if (dy < 0.0f) {
        VELOCITY_WORK(task)->vel_y = -VELOCITY_WORK(task)->vel_y;
    }
    VELOCITY_WORK(task)->vel_z = _nsqrtf(dz2 * length2 / dist2);
    if (dz < 0.0f) {
        VELOCITY_WORK(task)->vel_z = -VELOCITY_WORK(task)->vel_z;
    }
    return 1;
}

int func_8000E4E4(float length, float x, float y, float z, float *out_x, float *out_y, float *out_z)
{
    float dx      = x - *out_x;
    float dy      = y - *out_y;
    float dz      = z - *out_z;
    float dy2     = dy * dy;
    float dz2     = dz * dz;
    float length2 = length * length;
    float dist2   = dx * dx + dy2 + dz2;

    *out_x = _nsqrtf(dx * dx * length2 / dist2);
    if (dx < 0.0f) {
        *out_x = -*out_x;
    }
    *out_y = _nsqrtf(dy2 * length2 / dist2);
    if (dy < 0.0f) {
        *out_y = -*out_y;
    }
    *out_z = _nsqrtf(dz2 * length2 / dist2);
    if (dz < 0.0f) {
        *out_z = -*out_z;
    }
    return 1;
}

int func_8000E630(float radius, unsigned short angle, float *out_cos, float *out_sin)
{
    *out_cos = func_80003EA0(angle) * radius;
    *out_sin = func_80003E10(angle) * radius;
    return 1;
}

int func_8000E68C(float radius, unsigned short yaw, unsigned short pitch, float *out_x, float *out_y, float *out_z)
{
    func_8000E630(radius, yaw, out_z, out_y);
    pitch = ANGLE_FULL - (pitch & ANGLE_MASK);
    func_8000E630(*out_z, pitch, out_x, out_z);
    return 1;
}

int func_8000E6F4(float radius, unsigned short yaw, unsigned short pitch, ObjSolid *obj)
{
    func_8000E630(radius, yaw, &obj->tz, &obj->ty);
    pitch = ANGLE_FULL - (pitch & ANGLE_MASK);
    func_8000E630(obj->tz, pitch, &obj->tx, &obj->tz);
    return 1;
}

int func_8000E764(unsigned short angle, float x, float z, float *out_x, float *out_z)
{
    angle &= ANGLE_MASK;
    *out_x = x * func_80003EA0(angle) + func_80003E10(angle) * z;
    *out_z = -(x * func_80003E10(angle)) + func_80003EA0(angle) * z;
    return 1;
}

int func_8000E808(unsigned short rot_x, unsigned short rot_y, unsigned short rot_z, float *x, float *y, float *z)
{
    float sin_x;
    float cos_x;
    float sin_y;
    float cos_y;
    float sin_z;
    float cos_z;
    float sin_xsin_y;
    float cos_xsin_y;
    float new_x;
    float new_y;
    float new_z;

    sin_x      = func_80003F30(rot_x, &cos_x);
    sin_y      = func_80003F30(rot_y, &cos_y);
    sin_z      = func_80003F30(rot_z, &cos_z);
    sin_xsin_y = sin_x * sin_y;
    cos_xsin_y = cos_x * sin_y;
    new_x      = cos_y * cos_z * *x + (sin_xsin_y * cos_z - cos_x * sin_z) * *y + *z * (cos_xsin_y * cos_z + sin_x * sin_z);
    new_y      = cos_y * sin_z * *x + (sin_xsin_y * sin_z + cos_x * cos_z) * *y + *z * (cos_xsin_y * sin_z - sin_x * cos_z);
    new_z      = -sin_y * *x + sin_x * cos_y * *y + *z * (cos_x * cos_y);
    *x         = new_x;
    *y         = new_y;
    *z         = new_z;
    return 1;
}

unsigned short func_8000E9B0(float y, float z, ObjSolid *obj)
{
    float dy = y - obj->ty;
    float dz = z - obj->tz;

    return (ANGLE_FULL - func_800040A8(dy, dz)) & ANGLE_MASK;
}

unsigned short func_8000E9F4(float x, float z, ObjSolid *obj)
{
    float dx = x - obj->tx;
    float dz = z - obj->tz;

    return func_800040A8(dx, dz) & ANGLE_MASK;
}

unsigned short func_8000EA34(float x, float y, ObjSolid *obj)
{
    float dx = x - obj->tx;
    float dy = y - obj->ty;

    return func_800040A8(dy, dx) & ANGLE_MASK;
}

unsigned short func_8000EA74(float x1, float y1, float x2, float y2)
{
    return func_800040A8(y1 - y2, x1 - x2) & ANGLE_MASK;
}

unsigned short func_8000EABC(float x1, float y1, float x2, float y2)
{
    return (ANGLE_FULL - func_800040A8(x1 - x2, y1 - y2)) & ANGLE_MASK;
}

unsigned short func_8000EB08(float x1, float y1, float x2, float y2)
{
    return func_800040A8(x1 - x2, y1 - y2) & ANGLE_MASK;
}

void func_8000EB50(float x, float y, float z, ObjSolid *obj)
{
    float dx   = x - obj->tx;
    float dy   = y - obj->ty;
    float dz   = z - obj->tz;
    float dist = _nsqrtf(dx * dx + dz * dz);

    obj->rx = (ANGLE_FULL - func_800040A8(dy, (dist < 0.0f) ? -dist : dist)) & ANGLE_MASK;
    obj->ry = func_800040A8(dx, dz);
}

void func_8000EC04(float x1, float y1, float z1, float x2, float y2, float z2, unsigned short *pitch, unsigned short *yaw)
{
    float dx   = x1 - x2;
    float dy   = y1 - y2;
    float dz   = z1 - z2;
    float dist = _nsqrtf(dx * dx + dz * dz);
    int   angle;

    angle  = func_800040A8(dy, (dist < 0.0f) ? -dist : dist);
    *pitch = (ANGLE_FULL - angle) & ANGLE_MASK;
    *yaw   = func_800040A8(dx, dz);
}

void func_8000ECB4(unsigned short *pitch, unsigned short *yaw)
{
    *yaw += ANGLE_HALF;
    if (*yaw >= ANGLE_FULL) {
        *yaw -= ANGLE_FULL;
    }
    *pitch = ANGLE_FULL - *pitch;
    if (*pitch >= ANGLE_FULL) {
        *pitch -= ANGLE_FULL;
    }
}

float func_8000ED00(Task *a, Task *b)
{
    ObjSolid *model_a = (ObjSolid *) a->obj_head;
    ObjSolid *model_b = (ObjSolid *) b->obj_head;
    float     dx      = model_b->tx - model_a->tx;
    float     dy      = model_b->ty - model_a->ty;
    float     dz      = model_b->tz - model_a->tz;

    return _nsqrtf(dx * dx + dy * dy + dz * dz);
}

float func_8000ED5C(ObjSolid *a, ObjSolid *b)
{
    float dx = b->tx - a->tx;
    float dy = b->ty - a->ty;
    float dz = b->tz - a->tz;

    return _nsqrtf(dx * dx + dy * dy + dz * dz);
}

float func_8000EDB0(ObjSolid *a, ObjSolid *b)
{
    float dx = b->tx - a->tx;
    float dz = b->tz - a->tz;

    return _nsqrtf(dx * dx + dz * dz);
}

float func_8000EDF4(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    float dz = z1 - z2;

    return _nsqrtf(dx * dx + dy * dy + dz * dz);
}

void func_8000EE50(ObjSolid *obj, float x, float y, float z, unsigned short roll)
{
    float dir[3];

    dir[0] = x;
    dir[1] = y;
    dir[2] = z;
    func_8001D394((Vec3f *) dir);
    func_8001DB04(&obj->rx, dir, 0, roll, 0);
}

int func_8000EEAC(Task *parent, float x, float y, float z, float growth, float scale, unsigned char draw_list, unsigned char draw_list2)
{
    Task     *task;
    ObjSolid *second;
    Obj      *head;

    task = func_800358E8(parent, (void (*)(Task *, Obj *)) func_8000EFD0, (unsigned int) D_8000048 + ANIME_KIND_ANIME, (unsigned int) D_800636E0, x, y,
        z, 0, 0, 0, scale, scale, scale, 0x4AE, 0);
    if (task != NULL) {
        head                         = task->obj_head;
        FLASH_WORK(task)->anim_speed = growth;
        head->pri                    = draw_list;
        second                       = func_8000DBF0(task, (unsigned int) D_8000170 + ANIME_KIND_MODEL, D_800636E0, x, y, z, ANGLE_BILLBOARD, ANGLE_BILLBOARD, ANGLE_BILLBOARD,
            scale, scale, scale, 0x4AE, 0);
        if (second != NULL) {
            second->header.pri = draw_list2;
        }
        func_8000F178(task, 0x20);
    }
}

void func_8000EFD0(Task *task, ObjSolid *obj)
{
    float alpha;

    obj->time += FLASH_WORK(task)->anim_speed;
    PRINTF(("KIRAN ANIME TIME = %f\n", obj->time));
    if (19.0f < obj->time) {
        func_80034ED4();
    } else {
        alpha = 255.0 * func_80003E10(obj->time * 25.6);
        func_8000F178(task, alpha);
    }
}

void func_8000F178(Task *task, unsigned char alpha)
{
    ObjSolid *first  = (ObjSolid *) task->obj_head;
    ObjSolid *second = (ObjSolid *) first->header.next;
    Gfx      *list;

    if (first != NULL) {
        list              = func_8000DF10(task, D_800636E0, 0x20, 0x20, 0xFF, alpha);
        first->init_glist = (unsigned int) list | ANIME_GLIST_RELOAD | ANIME_GLIST_COPY;
    }
    if (second != NULL) {
        list               = func_8000DFA0(task, D_800636E0, 0x60, 0x60, 0xFF, alpha);
        second->init_glist = (unsigned int) list | ANIME_GLIST_RELOAD | ANIME_GLIST_COPY;
    }
}
