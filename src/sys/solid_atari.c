#include "sys/solid_atari.h"
#include "common.h"
#include "sys/math.h"

#pragma intrinsic(sqrtf)

unsigned char  func_80032DC4(unsigned short track, Task *task, unsigned char *out, float a, float b, int c);
int            func_800334EC(Task *self, Task *task);
void           func_80033688(ObjSolid *src_solid, ObjSolid *dst_solid, Task *src, Task *dst);
void           func_80033404(ObjSolid *node, Task *self, Task *task);
void           func_80033590(ColShape *shape);
int            func_80033BDC(float width, float height, float x, float y, float z, float radius, float *out, ObjSolid *solid);
void           func_80033D40(float width, float height, float x, float y, float z, float *out, ObjSolid *solid);
unsigned short func_80033F24(unsigned short track);
short          func_800340FC(unsigned short track);
unsigned short func_80034268(unsigned short pos, int frame_a, unsigned short *out_a, int frame_b);

// clang-format off

// <<<<< bss >>>>>
unsigned int  D_80168F70;
unsigned char *D_80168F74;
float         D_80168F78;
float         D_80168F7C;
float         D_80168F80;
float         D_80168F84;
float         D_80168F88;
float         D_80168F8C;
unsigned char D_80168F90[32];

// clang-format on

int func_80032B20(Task *task, unsigned char *out, float a, float b, int c)
{
    unsigned int   *data;
    ObjSolid       *solid;
    int             count;
    unsigned short *keys;
    unsigned int    header;
    int             i;

    data = (unsigned int *) task->anim_events;
    if (data == NULL) {
        return 0;
    }

    solid = (ObjSolid *) task->obj_head;
    if (solid == NULL) {
        for (i = 0; i < 4; i++) { *out++ = 0; }
        return 0;
    }

    D_80168F70 = (unsigned int) data & ANIME_REF_MASK;
    data       = (unsigned int *) SOLID_SEG_ADDR(solid, D_80168F70);
    header     = *data;
    if (header != 0) {
        count      = ANIME_HDR_ROOTS(header);
        D_80168F78 = ANIME_HDR_FRAMES(header);
        D_80168F7C = solid->time;
        data++;
        D_80168F70 = *data;
        D_80168F74 = (unsigned char *) SOLID_SEG_ADDR(solid, D_80168F70);
        data++;
        D_80168F70 = *data;
        keys       = (unsigned short *) SOLID_SEG_ADDR(solid, D_80168F70);
        for (i = 0; i < count; i++) {
            if (!(*keys & ANIME_TRACK_FIXED)) {
                if ((unsigned int) func_80032DC4(*keys, task, out, a, b, c) < 0) {
                    PRINTF_DEAD(("TMM WORK CLEAR!!\n"));
                }
            } else {
                *out = 0;
            }
            keys++;
            out++;
        }
    }
}

unsigned char func_80032DC4(unsigned short track, Task *task, unsigned char *out, float a, float b, int c)
{
    ObjSolid      *solid      = (ObjSolid *) task->obj_head;
    float          from_frame = (int) (solid->time - a - b);
    float          now_frame  = (int) solid->time;
    unsigned short value      = 0;
    unsigned short v;
    int            i;

#ifdef JAPAN_0
    if (ABS(solid->time - a - b) < 1e-5 || solid->time - a <= b) {
#else
    if (ABS(solid->time - a - b) < 1e-7 || solid->time - a <= b) {
#endif
        value = func_80034268(track, -1, NULL, 0);
    } else if (now_frame == from_frame) {
        *out = 0;
        return 0;
    } else if (D_80168F78 <= now_frame && !c) {
        value = func_80034268(track, -1, NULL, D_80168F78 - 1.0f);
    } else if (now_frame - from_frame == 1.0f) {
        value = func_80034268(track, -1, NULL, now_frame);
    } else {
        if (ABS(from_frame - (solid->time - a - b)) < 1e-5) {
            i = from_frame;
        } else {
            i = (int) from_frame + 1;
        }
        for (; i <= (int) now_frame; i++) {
            v = func_80034268(track, -1, NULL, i);
            if (v >= value) {
                value = v;
            }
        }
    }
    if (value >= 0x800) {
        *out = 1;
    } else {
        *out = 0;
    }
    return *out;
}

void func_80033024(Task *list, Task *other)
{
    int            pad[3];
    unsigned short key;
    ObjSolid      *solid;
    unsigned int   ref;
    unsigned int   hdr;
    unsigned int   shapes;
    int            count;
    unsigned short i;

    key = list->priority;

    while (list != NULL) {
        solid = (ObjSolid *) list->obj_head;
        if (solid != NULL && solid->header.kind == OBJ_KIND_SOLID && (ref = list->hit_ref) != 0) {
            if (ref == -1) {
                if (list->hit_by == NULL && (list->hit_flags & 2)) {
                    D_80168F8C    = (unsigned int) list->attack_radius;
                    D_80168F80    = 0.0f;
                    D_80168F84    = list->attack_offset_y;
                    D_80168F88    = list->attack_offset_z;
                    D_80168F90[0] = 1;
                    func_80033404(solid, list, other);
                }
            } else {
                D_80168F70 = ref & ANIME_REF_MASK;
                ref        = SOLID_SEG_ADDR(solid, D_80168F70);
                if (ref < WAVE_SEGMENT_ADDR) {
                    PRINTF(("**** WARNING in solid_atari.c : solid_init error ****\n"));
                    list = list->next;
                    if (list == NULL || key >= list->priority) {
                        return;
                    }
                    continue;
                }

                if (list->hit_by == NULL && (list->hit_flags & 2)) {
                    hdr = *(unsigned int *) ref;
                    if (hdr != 0) {
                        count      = ANIME_HDR_ROOTS(hdr);
                        D_80168F78 = ANIME_HDR_FRAMES(hdr);
                        D_80168F7C = solid->time;
                        D_80168F70 = *(unsigned int *) (ref += 4);
                        D_80168F74 = (unsigned char *) SOLID_SEG_ADDR(solid, D_80168F70);
                        D_80168F70 = *(unsigned int *) (ref += 4);
                        shapes     = SOLID_SEG_ADDR(solid, D_80168F70);
                        for (i = 0; i < count; i++) {
                            func_80033590((ColShape *) shapes);
                            D_80168F90[0] = i + 1;
                            func_80033404(solid, list, other);
                            shapes += 8;
                        }
                    }
                }
            }
        }
        list = list->next;
        if (list == NULL || key >= list->priority) {
            break;
        }
    }
}

void func_80033404(ObjSolid *node, Task *self, Task *task)
{
    unsigned short depth = task->priority;
    ObjSolid      *other;

    while (task != NULL) {
        if (self->hit != 0) {
            return;
        }
        other = (ObjSolid *) task->obj_head;
        if (other != NULL && func_800334EC(self, task) != 0 && other != node && other->header.kind == OBJ_KIND_SOLID &&
            task->hit_by == 0 && task->width != 0) {
            func_80033688(node, other, self, task);
        }
        if (task->next == NULL || task->next->priority <= depth) {
            return;
        }
        task = task->next;
    }
}

int func_800334EC(Task *self, Task *task)
{
    int kinds[4] = { 7, 8, 9, -1 };
    int found    = 0;
    int i        = 0;

    while (kinds[i] != -1) {
        if (self->hit_kind == (unsigned char) kinds[i++]) {
            found = 1;
            break;
        }
    }
    if (task->hit_flags & 4) {
        return found;
    }
    if (task->hit_flags & 1) {
        return 1;
    }
    return 0;
}

void func_80033590(ColShape *shape)
{
    D_80168F8C = (float) (unsigned int) func_80033F24(shape->size) * 0.00390625;
    D_80168F80 = (float) func_800340FC(shape->x) * 0.03125;
    D_80168F84 = (float) func_800340FC(shape->y) * 0.03125;
    D_80168F88 = (float) func_800340FC(shape->z) * 0.03125;
}

void func_80033688(ObjSolid *src_solid, ObjSolid *dst_solid, Task *src, Task *dst)
{
    float x, y, z;

    x = src_solid->sx * D_80168F80;
    y = src_solid->sy * D_80168F84;
    z = src_solid->sz * D_80168F88;
    func_80033898(src_solid->rx & ANGLE_MASK, src_solid->ry & ANGLE_MASK, src_solid->rz & ANGLE_MASK, &x, &y, &z);

    x += src_solid->tx;
    y += src_solid->ty;
    z += src_solid->tz;

    x -= dst_solid->tx;
    y -= dst_solid->ty;
    z -= dst_solid->tz;
    func_80033A3C(dst_solid->rx & ANGLE_MASK, dst_solid->ry & ANGLE_MASK, dst_solid->rz & ANGLE_MASK, &x, &y, &z);

    y -= dst->offset_y * dst_solid->sy;
    z -= dst->offset_z * dst_solid->sz;

    if (func_80033BDC((float) (unsigned int) dst->width * dst_solid->sx, (float) (unsigned int) dst->height * dst_solid->sy, x, y, z,
            src_solid->sx * D_80168F8C, src->contact, dst_solid)) {
        src->hit       = dst;
        dst->hit_by    = src;
        dst->hit_index = D_80168F90[0];
    }
}

void func_80033898(unsigned short rot_x, unsigned short rot_y, unsigned short rot_z, float *x, float *y, float *z)
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
}

void func_80033A3C(unsigned short rot_x, unsigned short rot_y, unsigned short rot_z, float *x, float *y, float *z)
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
    new_x      = cos_y * cos_z * *x + cos_y * sin_z * *y + *z * -sin_y;
    new_y      = (sin_xsin_y * cos_z - cos_x * sin_z) * *x + (sin_xsin_y * sin_z + cos_x * cos_z) * *y + *z * (sin_x * cos_y);
    new_z      = (cos_xsin_y * cos_z + sin_x * sin_z) * *x + (cos_xsin_y * sin_z - sin_x * cos_z) * *y + *z * (cos_x * cos_y);
    *x         = new_x;
    *y         = new_y;
    *z         = new_z;
}

int func_80033BDC(float width, float height, float x, float y, float z, float radius, float *out, ObjSolid *solid)
{
    float zero = 0.0f;

    if (height == zero) {
        if ((width + radius) * (width + radius) < x * x + y * y + z * z) {
            return 0;
        }
        func_80033D40(width, height, x, y, z, out, solid);
        return 1;
    }

    if ((width + radius) * (width + radius) < z * z + x * x) {
        return 0;
    }
    if (height < y - radius || y + radius < zero) {
        return 0;
    }
    func_80033D40(width, height, x, y, z, out, solid);
    return 1;
}

void func_80033D10(Task *task)
{
    float *p;
    int    i;

    p = task->contact;
    if (p != NULL) {
        for (i = 0; i < 3; i++) {
            *p++ = 0.0f;
        }
    }
}

void func_80033D40(float width, float height, float x, float y, float z, float *out, ObjSolid *solid)
{
    float  px;
    float  py;
    float  pz;
    float  dist;
    float  t;
    float  lim;
    float *point = out;

    if (out != NULL) {
        if (height == 0.0f) {
            t  = width / sqrtf(x * x + y * y + z * z);
            pz = t * x;
            px = t * z;
            py = t * y;
        } else {
            if (0.0f <= y || y <= height) {
                py   = y;
                dist = sqrtf(z * z + x * x);
                pz   = z / dist * width;
                px   = x / dist * width;
            } else {
                lim = (0.0f < y) ? height : 0.0;
                t   = (lim - y) / (height / 2 - y);
                pz  = t * (0.0 - z) + z;
                px  = t * (0.0 - x) + x;
                py  = lim;
            }
            func_80033898(solid->rx & ANGLE_MASK, solid->ry & ANGLE_MASK, solid->rz & ANGLE_MASK, &px, &py, &pz);
        }
        *point++ = solid->tx + px;
        *point++ = solid->ty + py;
        *point   = solid->tz + pz;
    }
}

unsigned short func_80033F24(unsigned short track)
{
    unsigned short cur;
    unsigned short next;
    int            pad;
    float          frac;
    int            frame;

    track &= ANIME_TRACK_MASK;

    if (track > ANIME_TRACK_CONST_MIN) {
        return track - ANIME_TRACK_CONST_BIAS;
    }

    if (track & ANIME_TRACK_FIXED) {
        track = track & ANIME_TRACK_INDEX_MASK;
        frac  = 0.0f;
        frame = 0;
    } else {
        frame = D_80168F7C;
        frac  = D_80168F7C - frame;
    }

    if (frac == 0.0f) {
        return func_80034268(track, -1, NULL, frame);
    }

    if (D_80168F78 - 1.0f <= frame) {
        cur = func_80034268(track, 0, (short *) &next, frame);
    } else {
        next = func_80034268(track, frame, (short *) &cur, frame + 1);
    }

    return cur + (unsigned short) ((next - cur) * frac);
}

short func_800340FC(unsigned short track)
{
    short cur;
    short next;
    int   pad;
    float frac;
    int   frame;

    track &= ANIME_TRACK_MASK;

    if (track > ANIME_TRACK_CONST_MIN) {
        return track - ANIME_TRACK_CONST_BIAS;
    }

    if (track & ANIME_TRACK_FIXED) {
        track = track & ANIME_TRACK_INDEX_MASK;
        frac  = 0.0f;
        frame = 0;
    } else {
        frame = D_80168F7C;
        frac  = D_80168F7C - frame;
    }

    if (frac == 0.0f) {
        return func_80034268(track, -1, NULL, frame);
    }

    if (D_80168F78 - 1.0f <= frame) {
        cur = func_80034268(track, 0, &next, frame);
    } else {
        next = func_80034268(track, frame, &cur, frame + 1);
    }

    return cur + (short) ((next - cur) * frac);
}

unsigned short func_80034268(unsigned short pos, int frame_a, unsigned short *value_a, int frame_b)
{
    unsigned char  op;
    unsigned char  hi;
    unsigned short n;
    unsigned short rep;

    hi = 0;
    while (1) {
        op = D_80168F74[pos];
        pos++;
        if (op < 0x78) {
            if (op >= 0x60) {
                hi = D_80168F74[pos++];
            } else if (op >= 0x40) {
                hi++;
            } else if (op >= 0x20) {
                hi--;
            }
            n = op & 0x1F;
            if (frame_a >= 0) {
                if (!n || frame_a < n) {
                    *value_a = D_80168F74[pos + frame_a] + (hi << 8);
                    frame_a  = -1;
                } else {
                    frame_a -= n;
                }
            }
            if (!n || frame_b < n) {
                return D_80168F74[pos + frame_b] + (hi << 8);
            }
            frame_b -= n;
            pos += n;
        } else if (op < 0xF0) {
            rep = op - 0x78;
            if (op >= 0xD8) {
                hi = D_80168F74[pos++];
            } else if (op >= 0xB8) {
                hi++;
            } else if (op >= 0x98) {
                hi--;
            }
            n = rep & 0x1F;
            if (n != 0) {
                n += 2;
            }
            if (frame_a >= 0) {
                if (!n || frame_a < n) {
                    *value_a = D_80168F74[pos] + (hi << 8);
                    frame_a  = -1;
                } else {
                    frame_a -= n;
                }
            }
            if (!n || frame_b < n) {
                return D_80168F74[pos] + (hi << 8);
            }
            frame_b -= n;
            pos++;
        } else {
            n = op & 0xF;
            if (frame_a >= 0) {
                if (!n || frame_a < n) {
                    *value_a = (D_80168F74[pos + frame_a * 2] << 8) + D_80168F74[pos + frame_a * 2 + 1];
                    frame_a  = -1;
                } else {
                    frame_a -= n;
                }
            }
            if (!n || frame_b < n) {
                return (D_80168F74[pos + frame_b * 2] << 8) + D_80168F74[pos + frame_b * 2 + 1];
            }
            frame_b -= n;
            hi = D_80168F74[pos + n * 2 - 2];
            pos += n * 2;
        }
    }
}

int func_8003454C(Task *task, int index, short delta, short limit)
{
    unsigned short *u = NULL;
    short          *s = NULL;

    if (index < 0 || index >= 7) {
        PRINTF(("Adm_morph error\n"));
        return -1;
    }

    switch (index) {
        case 0:
            u = &task->width;
            break;
        case 1:
            u = &task->height;
            break;
        case 2:
            s = &task->offset_y;
            break;
        case 3:
            s = &task->offset_z;
            break;
        case 4:
            u = &task->attack_radius;
            break;
        case 5:
            s = &task->attack_offset_y;
            break;
        case 6:
            s = &task->attack_offset_z;
            break;
    }

    if (u != NULL) {
        *u += delta;
        if (delta > 0) {
            if (*u > limit) {
                *u = limit;
                return 1;
            }
        } else if (*u < limit) {
            *u = limit;
            return 1;
        }
    } else {
        *s += delta;
        if (delta > 0) {
            if (*s > limit) {
                *s = limit;
                return 1;
            }
        } else if (*s < limit) {
            *s = limit;
            return 1;
        }
    }

    return 0;
}
