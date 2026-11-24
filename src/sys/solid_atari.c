#include "sys/solid_atari.h"
#include "common.h"
#include "sys/anime.h"

unsigned char  func_80032DC4(unsigned short track, ColObj *obj, unsigned char *out, float a, float b, int c);
void           func_80033404(ObjSolid *solid, ColObj *obj, ColObj *other);
void           func_80033590(ColShape *shape);
int            func_80033BDC(float width, float height, float x, float y, float z, float radius, float *out, ObjSolid *solid);
void           func_80033D40(float width, float height, float x, float y, float z, float *out, ObjSolid *solid);
unsigned short func_80033F24(unsigned short track);
short          func_800340FC(unsigned short track);
unsigned short func_80034268(unsigned short pos, int frame_a, short *out_a, int frame_b);

#pragma intrinsic(sqrtf)

// clang-format off

// <<<<< data >>>>>
unsigned int D_8006D310[4] = {
    0x00000007, 0x00000008, 0x00000009, 0xFFFFFFFF,
};

// <<<<< rodata >>>>>
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/solid_atari/D_8007C690.s")

// <<<<< bss >>>>>
unsigned char D_80168F70[4];
int           D_80168F74;
float         D_80168F78;
float         D_80168F7C;
float         D_80168F80;
float         D_80168F84;
float         D_80168F88;
float         D_80168F8C;
unsigned char D_80168F90[32];

// clang-format on

#ifdef NON_MATCHING
int func_80032B20(ColObj *obj, unsigned char *out, float a, float b, int c)
{
    ObjSolid       *solid;
    unsigned int    ref;
    unsigned int    hdr;
    unsigned short *tracks;
    int             count;
    int             i;

    ref = obj->script;
    if (ref == 0) {
        return 0;
    }

    solid = obj->solid;
    if (solid == NULL) {
        out[0] = 0;
        out[1] = 0;
        out[2] = 0;
        out += 3;
        *out = 0;
        return 0;
    }

    ref = ANIME_REF_SOLID(solid, ref & 0x8FFFFFFE);
    hdr = *(unsigned int *) ref;
    if (hdr != 0) {
        count        = (hdr >> 8) & 0x7FFF;
        D_80168F78   = hdr & 0xFF;
        D_80168F7C   = solid->time;
        s_anime_keys = (unsigned char *) ANIME_REF_SOLID(solid, *(unsigned int *) (ref += 4));
        tracks       = (unsigned short *) ANIME_REF_SOLID(solid, *(unsigned int *) (ref += 4));
        for (i = 0; i < count; i++) {
            if (!(*tracks & 0x8000)) {
                func_80032DC4(*tracks, obj, out, a, b, c);
            } else {
                *out = 0;
            }
            tracks++;
            out++;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/solid_atari/func_80032B20.s")
#endif

#ifdef NON_MATCHING
unsigned char func_80032DC4(unsigned short track, ColObj *obj, unsigned char *out, float a, float b, int c)
{
    ObjSolid      *solid;
    float          time, rem, diff, step, key, delta;
    unsigned short best;
    int            i, end;

    solid = obj->solid;
    time  = solid->time;
    rem   = time - a;
    time  = (int) time;
    diff  = rem - b;
    key   = diff;
    key   = (int) key;
    best  = 0;

    delta = rem < b ? -diff : diff;
    if (delta < 0.0000001 || rem <= b) {
        best = func_80034268(track, -1, 0, 0);
    } else if (time == key) {
        *out = 0;
        return 0;
    } else if (D_80168F78 <= time && c == 0) {
        best = func_80034268(track, -1, 0, (int) (D_80168F78 - 1.0f));
    } else if (1.0f == time - key) {
        best = func_80034268(track, -1, 0, (int) time);
    } else {
        step = key < diff ? -(key - diff) : key - diff;
        end  = (int) time;
        if (step < 0.00001) {
            i = (int) key;
        } else {
            i = (int) key + 1;
        }
        for (; i <= end; i++) {
            int prev = best;
            int v    = func_80034268(track, -1, 0, i);
            if (v >= prev) {
                best = v;
            }
        }
    }

    if (best >= 0x800) {
        *out = 1;
    } else {
        *out = 0;
    }
    return *out;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/solid_atari/func_80032DC4.s")
#endif

#ifdef NON_MATCHING
void func_80033024(ColObj *list, ColObj *other)
{
    int            pad[3];
    unsigned short key;
    ObjSolid      *solid;
    unsigned int   ref;
    unsigned int   hdr;
    unsigned int   shapes;
    int            count;
    unsigned short i;

    key = list->unk_20;

    while (list != NULL) {
        solid = list->solid;
        if (solid != NULL && solid->header.kind == 2 && (ref = list->ref) != 0) {
            if (ref == -1) {
                if (list->hit_by == NULL && (list->flags & 2)) {
                    D_80168F8C    = (unsigned int) list->unk_4E;
                    D_80168F80    = 0.0f;
                    D_80168F84    = list->unk_50;
                    D_80168F88    = list->unk_52;
                    D_80168F90[0] = 1;
                    func_80033404(solid, list, other);
                }
            } else {
                ref = ANIME_REF_SOLID(solid, ref & 0x8FFFFFFE);
                if (ref < 0x08000000) {
                    list = list->next;
                    if (list == NULL || key >= list->unk_20) {
                        return;
                    }
                    continue;
                }

                if (list->hit_by == NULL && (list->flags & 2)) {
                    hdr = *(unsigned int *) ref;
                    if (hdr != 0) {
                        count        = (hdr >> 8) & 0x7FFF;
                        D_80168F78   = hdr & 0xFF;
                        D_80168F7C   = solid->time;
                        s_anime_keys = (unsigned char *) ANIME_REF_SOLID(solid, *(unsigned int *) (ref += 4));
                        shapes       = ANIME_REF_SOLID(solid, *(unsigned int *) (ref += 4));
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
        if (list == NULL || key >= list->unk_20) {
            break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/solid_atari/func_80033024.s")
#endif

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/solid_atari/func_80033404.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/solid_atari/func_800334EC.s")

void func_80033590(ColShape *shape)
{
    D_80168F8C = (float) (unsigned int) func_80033F24(shape->size) * 0.00390625;
    D_80168F80 = (float) func_800340FC(shape->x) * 0.03125;
    D_80168F84 = (float) func_800340FC(shape->y) * 0.03125;
    D_80168F88 = (float) func_800340FC(shape->z) * 0.03125;
}

void func_80033688(ObjSolid *src_solid, ObjSolid *dst_solid, ColObj *src, ColObj *dst)
{
    float x, y, z;

    x = src_solid->sx * D_80168F80;
    y = src_solid->sy * D_80168F84;
    z = src_solid->sz * D_80168F88;
    func_80033898(src_solid->rx & 0x3FF, src_solid->ry & 0x3FF, src_solid->rz & 0x3FF, &x, &y, &z);

    x += src_solid->tx;
    y += src_solid->ty;
    z += src_solid->tz;

    x -= dst_solid->tx;
    y -= dst_solid->ty;
    z -= dst_solid->tz;
    func_80033A3C(dst_solid->rx & 0x3FF, dst_solid->ry & 0x3FF, dst_solid->rz & 0x3FF, &x, &y, &z);

    y -= dst->offset_y * dst_solid->sy;
    z -= dst->offset_z * dst_solid->sz;

    if (func_80033BDC((float) (unsigned int) dst->width * dst_solid->sx, (float) (unsigned int) dst->height * dst_solid->sy, x, y, z,
            src_solid->sx * D_80168F8C, src->contact, dst_solid)) {
        src->hit       = dst;
        dst->hit_by    = src;
        dst->hit_index = D_80168F90[0];
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/solid_atari/func_80033898.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/solid_atari/func_80033A3C.s")

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

void func_80033D10(ColObj *obj)
{
    float *p;
    int    i;

    p = obj->contact;
    if (p != NULL) {
        for (i = 0; i < 3; i++) {
            *p++ = 0.0f;
        }
    }
}

#ifdef NON_MATCHING
void func_80033D40(float width, float height, float x, float y, float z, float *out, ObjSolid *solid)
{
    float px, py, pz;
    float scale, len, cap, t;

    if (out != NULL) {
        if (height == 0.0f) {
            scale = width / sqrtf(x * x + y * y + z * z);
            pz    = scale * x;
            px    = scale * z;
            py    = scale * y;
        } else {
            if (y >= 0.0f || y <= height) {
                py  = y;
                len = sqrtf(z * z + x * x);
                pz  = z / len * width;
                px  = x / len * width;
            } else {
                cap = y > 0.0f ? height : 0.0;
                py  = cap;
                t   = (cap - y) / (height / 2 - y);
                pz  = t * (0.0 - z) + z;
                px  = t * (0.0 - x) + x;
            }
            func_80033898(solid->rx & 0x3FF, solid->ry & 0x3FF, solid->rz & 0x3FF, &px, &py, &pz);
        }
        out[0] = solid->tx + px;
        out[1] = solid->ty + py;
        out[2] = solid->tz + pz;
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/solid_atari/func_80033D40.s")
#endif

unsigned short func_80033F24(unsigned short track)
{
    unsigned short cur;
    unsigned short next;
    int            pad;
    float          frac;
    int            frame;

    track &= 0xBFFF;

    if (track > 0xA000) {
        return track - 0xB000;
    }

    if (track & 0x8000) {
        track = track & 0x7FFF;
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

    track &= 0xBFFF;

    if (track > 0xA000) {
        return track - 0xB000;
    }

    if (track & 0x8000) {
        track = track & 0x7FFF;
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

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/solid_atari/func_80034268.s")

int func_8003454C(ColObj *obj, int index, short delta, short limit)
{
    unsigned short *u = NULL;
    short          *s = NULL;

    if (index < 0 || index >= 7) {
        return -1;
    }

    switch (index) {
        case 0:
            u = &obj->width;
            break;
        case 1:
            u = &obj->height;
            break;
        case 2:
            s = &obj->offset_y;
            break;
        case 3:
            s = &obj->offset_z;
            break;
        case 4:
            u = &obj->unk_4E;
            break;
        case 5:
            s = &obj->unk_50;
            break;
        case 6:
            s = &obj->unk_52;
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
