#include "system/vram.h"
#include "system/ride.h"
#include "system/solid_atari.h"
#include "system/xvram.h"
#include "system/wave_uty.h"
#include "unk.h"

void   func_80027A7C(float x, float y, float z, float move_x, float move_y, float move_z, float scale, void *arg7, ColHead *head, ColHit *hit);
ColHit func_80028BC0(float x, float y, float z, float move_x, float move_y, float move_z);
ColHit func_80029560(float x, float y, float z, float move_y);
int    func_8002A168(float origin_x, float origin_y, float origin_z);
ColHit func_8002A750(float x, float y, float z, unsigned short length);

// clang-format off

// <<<<< bss >>>>>
ColPlane *D_80168F60;
ColNode  *D_80168F64;
// clang-format on

float func_800273E0(ColHit *hit, ColObj *obj, unsigned char arg2, float arg3)
{
    int       base;
    ColEntry *entry;
    float     x;
    float     y;
    float     z;
    float     move_x;
    float     move_y;
    float     move_z;
    float     scale;
    int       range;
    ObjSolid *solid;
    void     *data2;
    ColHead  *head;

    hit->unk_38 = 0;
    if (!arg2) {
        arg3 = 0.0f;
    }

    base  = func_800141C4(*D_80236984[obj->file]->wave_no);
    entry = &D_80236984[obj->file]->entries[obj->entry];
    head  = entry->unk_0;
    data2 = entry->unk_4;
    data2 = (void *) ((unsigned int) data2 - 0x08000000 + base);
    head  = (ColHead *) ((unsigned int) head - 0x08000000 + base);
    range = head->range;

    hit->obj   = obj;
    solid      = obj->solid;
    hit->solid = solid;

    x      = hit->x - solid->tx;
    y      = hit->y - solid->ty;
    z      = hit->z - solid->tz;
    move_x = hit->move_x;
    move_y = hit->move_y;
    move_z = hit->move_z;
    scale  = solid->sx;

    if (range == 0 || scale == 0.0f) {
        range = 0;
    } else {
        range = ((range < 0) ? -range : range) * scale;
    }

    range = range + arg3;

    if (range < ((x < 0.0f) ? -x : x) || range < ((y < 0.0f) ? -y : y) || range < ((z < 0.0f) ? -z : z)) {
        return 0.0f;
    }

    func_80033A3C(solid->rx & 0x3FF, solid->ry & 0x3FF, solid->rz & 0x3FF, &x, &y, &z);
    func_80033A3C(solid->rx & 0x3FF, solid->ry & 0x3FF, solid->rz & 0x3FF, &move_x, &move_y, &move_z);

    if (!arg2) {
        func_80027A7C(x, y, z, move_x, move_y, move_z, scale, data2, head, hit);
    } else {
        func_8002CC94(x, y, z, move_x, move_y, move_z, scale, data2, head, hit, arg3);
    }

    if (hit->unk_38 == 0x7FFF) {
        func_80033898(solid->rx & 0x3FF, solid->ry & 0x3FF, solid->rz & 0x3FF, &hit->unk_18, &hit->unk_1C, &hit->unk_20);
        func_80033898(solid->rx & 0x3FF, solid->ry & 0x3FF, solid->rz & 0x3FF, &hit->unk_24, &hit->unk_28, &hit->unk_2C);
        return hit->unk_18 * hit->unk_18 + hit->unk_1C * hit->unk_1C + hit->unk_20 * hit->unk_20;
    }

    return 0.0f;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/vram/func_800277C0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/vram/func_80027A7C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/vram/func_80027B38.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/vram/func_800283E8.s")

ColHit func_80028B28(float x, float y, float z, float move_x, float move_y, float move_z)
{
    if (move_x == 0.0 && move_z == 0.0) {
        return func_80029560(x, y, z, move_y);
    }

    return func_80028BC0(x, y, z, move_x, move_y, move_z);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/vram/func_80028BC0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/vram/func_80029560.s")

int func_80029E08(float x, float y, float z)
{
    if (func_8003266C(x, y, z) == 0x7FFF) {
        return 0x7FFF;
    }

    return func_8002A168(x, y, z);
}

int func_80029E58(float origin_x, float origin_y, float origin_z, float scale, void *p, void *n)
{
    int TERMINATE = 0xFFFF;

    unsigned char *nodes;
    unsigned short node;
    long           next_tree;

    ColPlane *planes;
    int       plane;

    float normal_x;
    float normal_y;
    float normal_z;
    float distance;
    float dot_product;
    float signed_distance;

    short back;
    short front;

    node = 0;

    planes = (ColPlane *) p;
    nodes  = (unsigned char *) n;

    while (1) {
        next_tree = ((unsigned short *) ((unsigned char *) nodes + (node * 6)))[0];

        while ((((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_max_x * scale) < origin_x || origin_x < (((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_min_x * scale) ||
               (((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_max_z * scale) < origin_z || origin_z < (((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_min_z * scale) ||
               (((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_max_y * scale) < origin_y || origin_y < (((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_min_y * scale)) {
            if (next_tree == TERMINATE) {
                return 0;
            }

            node      = next_tree;
            next_tree = ((unsigned short *) ((unsigned char *) nodes + (next_tree * 6)))[0];
        }

        node += 3;

        while (1) {
            plane = ((unsigned short *) ((unsigned char *) nodes + (node * 6)))[0];

            normal_x = planes[plane].normal_x;
            normal_y = planes[plane].normal_y;
            normal_z = planes[plane].normal_z;
            distance = planes[plane].distance * scale;

            dot_product     = (origin_x * normal_x) + (origin_y * normal_y) + (origin_z * normal_z);
            signed_distance = dot_product + distance;

            if (signed_distance < 0.0) {
                back = ((short *) ((unsigned char *) nodes + (node * 6)))[1];

                if (back == 0) {
                    return 0x7FFF;
                } else {
                    node = back;
                }
            } else {
                front = ((short *) ((unsigned char *) nodes + (node * 6)))[2];

                if (front == 0) {
                    if (next_tree == TERMINATE) {
                        return 0;
                    }

                    node = next_tree;
                    break;
                } else {
                    node = front;
                }
            }
        }
    }
}

int func_8002A168(float origin_x, float origin_y, float origin_z)
{
    int TERMINATE = 0xFFFF;

    unsigned char *nodes;
    unsigned short node;
    long           next_tree;

    ColPlane *planes;
    int       plane;

    float normal_x;
    float normal_y;
    float normal_z;
    float distance;
    float dot_product;
    float signed_distance;

    short back;
    short front;

    node = 0;

    if (D_80168F60 == 0) {
        return 0;
    }

    planes = (ColPlane *) D_80168F60;
    nodes  = (unsigned char *) D_80168F64;

    while (1) {
        next_tree = ((unsigned short *) ((unsigned char *) nodes + (node * 6)))[0];

        while (((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_max_x < origin_x || origin_x < ((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_min_x ||
               ((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_max_y < origin_y || (origin_y + 10.0f) < ((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_min_y ||
               ((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_max_z < origin_z || origin_z < ((ColTree *) ((unsigned char *) nodes + node * sizeof(ColNode)))->box_min_z) {
            if (next_tree == TERMINATE) {
                return 0;
            }

            node      = next_tree;
            next_tree = ((unsigned short *) ((unsigned char *) nodes + (next_tree * 6)))[0];
        }

        node += 3;

        while (1) {
            plane = ((unsigned short *) ((unsigned char *) nodes + (node * 6)))[0];

            normal_x = planes[plane].normal_x;
            normal_y = planes[plane].normal_y;
            normal_z = planes[plane].normal_z;
            distance = planes[plane].distance;

            dot_product     = (origin_x * normal_x) + (origin_y * normal_y) + (origin_z * normal_z);
            signed_distance = dot_product + distance;

            if (signed_distance < 0.0) {
                back = ((short *) ((unsigned char *) nodes + (node * 6)))[1];

                if (back == 0) {
                    return 0x7FFF;
                } else {
                    node = back;
                }
            } else {
                front = ((short *) ((unsigned char *) nodes + (node * 6)))[2];

                if (front == 0) {
                    if (next_tree == TERMINATE) {
                        return 0;
                    }

                    node = next_tree;
                    break;
                } else {
                    node = front;
                }
            }
        }
    }
}

ColHit func_8002A458(float x, float y, float z, float move_x, float move_y, float move_z)
{
    ColHit hit;
    ColHit hit2;
    short  flag;
    short  flag2;

    if (move_x == 0.0 && move_y == 0.0 && move_z == 0.0) {
        hit.unk_38 = func_80029E08(x, y, z);
        hit.unk_34 = 0;
        hit.unk_36 = 0;
        hit.obj    = 0;
        hit.solid  = 0;
        hit.unk_18 = 0.0f;
        hit.unk_1C = 0.0f;
        hit.unk_20 = 0.0f;
        hit.unk_24 = 0.0f;
        hit.unk_28 = 0.0f;
        hit.unk_2C = 0.0f;
        hit.unk_30 = 0.0f;
        hit.unk_3C = 0.0f;
        return hit;
    }

    hit       = func_80028B28(x, y, z, move_x, move_y, move_z);
    hit.obj   = 0;
    hit.solid = 0;

    hit2.x      = x;
    hit2.y      = y;
    hit2.z      = z;
    hit2.move_x = move_x;
    hit2.move_y = move_y;
    hit2.move_z = move_z;
    func_80032320(&hit2, 0, 0.0f);

    flag  = hit.unk_38;
    flag2 = hit2.unk_38;

    if (flag == 0 && flag2 == 0) {
        return hit2;
    }
    if (flag == 0x7FFF && flag2 == 0x7FFF) {
        if (hit.unk_3C < hit2.unk_3C) {
            return hit2;
        }
        return hit;
    }
    if (flag == 0x7FFF) {
        return hit;
    }
    return hit2;
}

ColHit func_8002A718(float x, float y, float z)
{
    return func_8002A750(x, y, z, 100);
}

ColHit func_8002A750(float x, float y, float z, unsigned short length)
{
    return func_8002C9D4(x, y, z, 0.0f, -1.0f, 0.0f, length);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/vram/func_8002A7BC.s")
