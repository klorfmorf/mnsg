#include "sys/obj_sort.h"
#include "sys/atan2.h"
#include "sys/sys.h"
#include "sys/task.h"
#include "unk.h"

unsigned char func_8000AFA8(ObjSolid *solid, AnimeCamera *cam, float dir_x, float dir_y, float dir_z, float scale, float radius);
void          func_8000AD08(ObjSolid *solid, AnimeCamera *cam);

// clang-format off

// <<<<< bss >>>>>
unsigned short D_80167A80[224];

// clang-format on

void func_8000A680(Obj **objects, unsigned short *keys, int count)
{
    int            i;
    int            j;
    unsigned short key;
    Obj           *obj;

    for (i = 1; i < count; i++) {
        key = keys[i];
        obj = objects[i];
        for (j = i - 1; j >= 0 && key < keys[j]; j--) {
            keys[j + 1]    = keys[j];
            objects[j + 1] = objects[j];
        }
        keys[j + 1]    = key;
        objects[j + 1] = obj;
    }
}

void func_8000A74C(Obj **objects, unsigned short *keys, int count)
{
    int            lo = 0, hi = count - 1;
    int            i;
    int            j;
    int            sp;
    int            lo_stack[32];
    int            hi_stack[32];
    unsigned short pivot;
    unsigned short key;
    Obj           *obj;

    sp = 0;
    for (;;) {
        if (hi - lo <= 10) {
            if (sp == 0) {
                break;
            }
            sp--;
            lo = lo_stack[sp];
            hi = hi_stack[sp];
        }
        pivot = keys[(lo + hi) / 2];
        i     = lo;
        j     = hi;
        for (;;) {
            while (keys[i] < pivot) {
                i++;
            }
            while (pivot < keys[j]) {
                j--;
            }
            if (i >= j) {
                break;
            }
            key        = keys[i];
            keys[i]    = keys[j];
            keys[j]    = key;
            obj        = objects[i];
            objects[i] = objects[j];
            objects[j] = obj;
            i++;
            j--;
        }
        if (hi - j < i - lo) {
            if (i - lo > 10) {
                lo_stack[sp] = lo;
                hi_stack[sp] = i - 1;
                sp++;
            }
            lo = j + 1;
        } else {
            if (hi - j > 10) {
                lo_stack[sp] = j + 1;
                hi_stack[sp] = hi;
                sp++;
            }
            hi = i - 1;
        }
    }
    func_8000A680(objects, keys, count);
}

int func_8000A918(ObjLayer *layer, unsigned short *keys)
{
    short i;
    Obj  *obj;
    int   count;
    int   size;

    for (i = 0, size = count = layer->size; i < size; i++, keys++) {
        obj = layer->objects[i];
        if (!(obj->kind & OBJ_HIDDEN)) {
            if (layer->sort_flags & LAYER_SORT_REVERSE) {
                *keys = 0xFFFF - obj->s_pri;
            } else {
                *keys = obj->s_pri;
            }
            size = count = layer->size;
        }
    }
    return count;
}

void func_8000A99C(ObjLayer *layer)
{
    short count;

    if (layer->sort_flags & LAYER_SORT_ENABLE) {
        if ((count = func_8000A918(layer, D_80167A80)) >= 2) {
            func_8000A74C(layer->objects, D_80167A80, count);
        }
    }
}

#ifdef NON_MATCHING
void func_8000AA00(ObjLayer *layer)
{
    Task     *prev;
    Obj      *obj;
    ObjLayer *dst;

    prev = NULL;
    for (D_8016DAB4 = g_task_list.head; D_8016DAB4 != NULL; D_8016DAB4 = D_8016DAB4->next) {
        if (prev != NULL) {
            if (prev->priority < D_8016DAB4->priority) {
                continue;
            } else {
                prev = NULL;
            }
        }
        if (D_8016DAB4->status & g_sys_real.task_disabled_status & TASK_STATUS_DRAW_MASK) {
            prev = D_8016DAB4;
            continue;
        }
        obj = D_8016DAB4->obj_head;
        while (obj != NULL) {
            if (!(obj->kind & OBJ_HIDDEN)) {
                dst                     = &layer[obj->pri];
                dst->objects[dst->size] = obj;
                dst->size++;
            }
            obj = obj->next;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_sort/func_8000AA00.s")
#endif

void func_8000AAE8(ObjLayer *layers)
{
    short i;

    for (i = 0; i < 12; i++, layers++) {
        layers->size = 0;
    }
}

void func_8000AB10(void *dst)
{
    func_800041E0(dst, sizeof(ObjLayer) * 12);
}

void func_8000AB30(void)
{
    short i;

    for (i = 0; i < 12; i++) {
        g_sys_real.layers[i].sort_flags = 0;
    }
}

void func_8000AB74(void)
{
    int          i;
    int          j;
    int          size;
    int          count;
    AnimeCamera *cam;
    ObjSolid    *solid;
    int          pad;

    count = 0;
    for (i = 0; i < 12; i++) {
        if (g_sys_real.layers[i].size != 0) {
            for (j = 0, size = g_sys_real.layers[i].size; j < size; j++) {
                solid = (ObjSolid *) g_sys_real.layers[i].objects[j];
                if (solid->header.kind == OBJ_KIND_SOLID) {
                    switch (solid->AModel & ANIME_KIND_MASK) {
                        case ANIME_KIND_CAMERA:
                            if (solid->hidden == 0) {
                                cam = (AnimeCamera *) (solid->AModel & ANIME_REF_MASK);
                                count++;
                            }
                            break;
                        case ANIME_KIND_DEMO:
                        case ANIME_KIND_ANIME:
                        case ANIME_KIND_MODEL:
                        case ANIME_KIND_JCHAR:
                        case ANIME_KIND_JMODEL:
                            if (count != 0) {
                                func_8000AD08(solid, cam);
                            }
                            break;
                        case ANIME_KIND_LIGHT:
                        case ANIME_KIND_AMBIENT:
                            break;
                    }
                }
            }
        }
    }
}

void func_8000AD08(ObjSolid *solid, AnimeCamera *cam)
{
    float tx   = solid->tx;
    float ty   = solid->ty;
    float tz   = solid->tz;
    float ex   = cam->eye[0];
    float ey   = cam->eye[1];
    float ez   = cam->eye[2];
    float dx   = cam->at[0] - ex;
    float dy   = cam->at[1] - ey;
    float dz   = cam->at[2] - ez;
    float zero = 0.0f;
    float dist = (dx * tx + dy * ty + dz * tz) - (dx * ex + dy * ey + dz * ez);
    float len2 = dx * dx + dy * dy + dz * dz;
    float side;
    float vz;
    float k;
    float uz;
    float uy;
    float ux;

    if (dist < 0.0f) {
        dist = -dist;
    }
    if (zero != len2) {
        solid->header.s_pri = (int) (dist / _nsqrtf(len2));
    } else {
        solid->header.s_pri = 0;
    }
    side = dx * (tx - ex) + dy * (ty - ey) + dz * (tz - ez);
    if (side < 0.0f) {
        solid->header.s_pri = -solid->header.s_pri;
    }
    solid->header.s_pri += 0x8000;
    if (solid->disabled != 0) {
        k               = -(dy / len2);
        ux              = dx * k;
        uy              = dy * k + 1.0f;
        uz              = dz * k;
        solid->disabled = func_8000AFA8(solid, cam, ux, uy, uz, 4.0f / 3.0f, solid->scratch_f[0]);
        if (solid->disabled >= 0) {
            vz              = dy * ux - dx * uy;
            solid->disabled = func_8000AFA8(solid, cam, dz * uy - dy * uz, dx * uz - dz * ux, vz, 1.0f, solid->scratch_f[1]);
        }
    }
}

unsigned char func_8000AFA8(ObjSolid *solid, AnimeCamera *cam, float dir_x, float dir_y, float dir_z, float scale, float radius)
{
    float        px;
    float        py;
    float        pz;
    float        ax;
    float        ay;
    float        az;
    float        ex;
    float        ey;
    float        ez;
    float        t;
    float        length;
    float        limit;
    unsigned int half_angle;
    float        sin_r;
    float        cos_r;
    float        angle_r;
    float        sin_c;
    float        cos_c;
    float        angle_c;
    float        dist;

    px    = solid->tx;
    py    = solid->ty;
    pz    = solid->tz;
    ax    = cam->eye[0];
    ay    = cam->eye[1];
    az    = cam->eye[2];
    ex    = cam->at[0] - ax;
    ey    = cam->at[1] - ay;
    ez    = cam->at[2] - az;
    t     = ((ax - px) * dir_x + dir_y * (ay - py) + dir_z * (az - pz)) / (dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);
    sin_r = radius / _nsqrtf((dir_x * t + px - ax) * (dir_x * t + px - ax) + (dir_y * t + py - ay) * (dir_y * t + py - ay) + (dir_z * t + pz - az) * (dir_z * t + pz - az));
    if (1.0f < sin_r) {
        return 0xFF;
    }
    if (1.0f <= sin_r * sin_r) {
        cos_r = 0.0f;
    } else {
        cos_r = _nsqrtf(1.0f - sin_r * sin_r);
    }
    angle_r = func_800166E0(sin_r, cos_r);
    dist    = _nsqrtf((dir_x * t + px - ax) * (dir_x * t + px - ax) + (dir_y * t + py - ay) * (dir_y * t + py - ay) + (dir_z * t + pz - az) * (dir_z * t + pz - az));
    length  = _nsqrtf(ex * ex + ey * ey + ez * ez);
    cos_c   = ((dir_x * t + px - ax) * ex + (dir_y * t + py - ay) * ey + (dir_z * t + pz - az) * ez) / (length * dist);
    if (1.0f < cos_c) {
        angle_c = 0.0f;
    } else {
        if (1.0f <= cos_c * cos_c) {
            sin_c = 0.0f;
        } else {
            sin_c = _nsqrtf(1.0f - cos_c * cos_c);
        }
        angle_c = func_800166E0(sin_c, cos_c);
    }
    half_angle = cam->fovy & 0xFFFF;
    limit      = (float) half_angle * 2 * 3.1415 / 65536 * scale;
    if (limit < angle_c - angle_r) {
        return 0xFF;
    }
    return 1;
}
