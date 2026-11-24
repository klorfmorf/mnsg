#include "sys/obj_sort.h"
#include "sys/atan2.h"
#include "sys/sys.h"
#include "sys/task.h"
#include "unk.h"

unsigned char func_8000AFA8(ObjSolid *solid, AnimeCamera *cam, float x, float y, float z, float a, float b);
void          func_8000AD08(ObjSolid *solid, AnimeCamera *cam);

extern float  D_8007AAF0;
extern double D_8007AAF8;

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

#ifdef NON_MATCHING
void func_8000A74C(ObjLayer *layer, unsigned short *arg1, int arg2)
{
    int            top;
    int            l;
    int            r;
    int            lo[32];
    int            hi[32];
    int            i;
    int            j;
    unsigned short pivot;
    unsigned short tmp;
    Obj           *obj;

    r   = arg2 - 1;
    l   = 0;
    top = 0;
    for (;;) {
        if (r - l < 11) {
            if (top == 0) {
                break;
            }
            top--;
            l = lo[top];
            r = hi[top];
        }
        pivot = arg1[(l + r) / 2];
        i     = l;
        j     = r;
        for (;;) {
            while (arg1[i] < pivot) {
                i++;
            }
            while (pivot < arg1[j]) {
                j--;
            }
            if (i >= j) {
                break;
            }
            tmp               = arg1[i];
            arg1[i]           = arg1[j];
            arg1[j]           = tmp;
            obj               = layer->objects[i];
            layer->objects[i] = layer->objects[j];
            layer->objects[j] = obj;
            i++;
            j--;
        }
        if (r - j < i - l) {
            if (i - l >= 11) {
                lo[top] = l;
                hi[top] = i - 1;
                top++;
            }
            l = j + 1;
        } else {
            if (r - j >= 11) {
                lo[top] = j + 1;
                hi[top] = r;
                top++;
            }
            r = i - 1;
        }
    }
    func_8000A680(layer, arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_sort/func_8000A74C.s")
#endif

int func_8000A918(ObjLayer *layer, unsigned short *keys)
{
    short i;
    Obj  *obj;
    int   count;
    int   size;

    for (i = 0, size = count = layer->size; i < size; i++, keys++) {
        obj = layer->objects[i];
        if (!(obj->kind & 0x80)) {
            if (layer->unk_371 & 0x80) {
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

    if (layer->unk_371 & 0x1) {
        if ((count = func_8000A918(layer, D_80167A80)) >= 2) {
            func_8000A74C(layer, D_80167A80, count);
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
            }
            prev = NULL;
        }
        if (D_8016DAB4->status & g_sys_real.task_disabled_status & 0xD0) {
            prev = D_8016DAB4;
            continue;
        }
        obj = D_8016DAB4->obj_head;
        while (obj != NULL) {
            if (!(obj->kind & 0x80)) {
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
    func_800041E0(dst, 0x2970);
}

void func_8000AB30(void)
{
    short i;

    for (i = 0; i < 12; i++) {
        g_sys_real.layers[i].unk_371 = 0;
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
                if (solid->header.kind == 2) {
                    switch (solid->AModel & 0x70000000) {
                        case 0x20000000:
                            if (solid->hidden == 0) {
                                cam = (AnimeCamera *) (solid->AModel & 0x8FFFFFFE);
                                count++;
                            }
                            break;
                        case 0x0:
                        case 0x10000000:
                        case 0x40000000:
                        case 0x60000000:
                        case 0x70000000:
                            if (count != 0) {
                                func_8000AD08(solid, cam);
                            }
                            break;
                        case 0x30000000:
                        case 0x50000000:
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
        solid->disabled = func_8000AFA8(solid, cam, ux, uy, uz, D_8007AAF0, solid->scratch_f[0]);
        if (solid->disabled >= 0) {
            vz              = dy * ux - dx * uy;
            solid->disabled = func_8000AFA8(solid, cam, dz * uy - dy * uz, dx * uz - dz * ux, vz, 1.0f, solid->scratch_f[1]);
        }
    }
}

#ifdef NON_MATCHING
unsigned char func_8000AFA8(ObjSolid *solid, AnimeCamera *cam, float x, float y, float z, float a, float b)
{
    float tx;
    float ty;
    float tz;
    float dot;
    float len2;
    float t;
    float dx;
    float dy;
    float dz;
    float span;
    float phi;
    float ratio;
    float s1;
    float theta;
    float dlen;
    float cosv;
    float s2;
    float vlen;
    float vx;
    float vy;
    float ey;
    float vz;
    float vlen2;

    tx    = solid->tx;
    ty    = solid->ty;
    tz    = solid->tz;
    dx    = cam->at[0] - cam->eye[0];
    ey    = cam->eye[1];
    dy    = cam->at[1] - ey;
    dz    = cam->at[2] - cam->eye[2];
    dot   = x * (cam->eye[0] - tx) + y * (cam->eye[1] - ty) + z * (cam->eye[2] - tz);
    len2  = x * x + y * y + z * z;
    t     = dot / len2;
    vx    = tx + x * t - cam->eye[0];
    vy    = ty + y * t - cam->eye[1];
    vz    = tz + z * t - cam->eye[2];
    vlen2 = vx * vx + vy * vy + vz * vz;
    ratio = b / _nsqrtf(vlen2);
    if (ratio > 1.0f) {
        return 0xFF;
    }
    if (ratio * ratio >= 1.0f) {
        s1 = 0.0f;
    } else {
        s1 = _nsqrtf(1.0f - ratio * ratio);
    }
    theta = func_800166E0(ratio, s1);
    vlen  = _nsqrtf(vlen2);
    dlen  = _nsqrtf(dx * dx + dy * dy + dz * dz);
    cosv  = (vx * dx + vy * dy + vz * dz) / (dlen * vlen);
    if (cosv > 1.0f) {
        phi = 0.0f;
    } else {
        if (cosv * cosv >= 1.0f) {
            s2 = 0.0f;
        } else {
            s2 = _nsqrtf(1.0f - cosv * cosv);
        }
        phi = func_800166E0(s2, cosv);
    }
    span = (cam->fovy * (float) 2) * D_8007AAF8 / 65536.0 * a;
    if (span < phi - theta) {
        return 0xFF;
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/obj_sort/func_8000AFA8.s")
#endif
