#include "sys/vram.h"
#include "sys/ride.h"
#include "sys/solid_atari.h"
#include "sys/xvram.h"
#include "sys/wave_uty.h"
#include "unk.h"

void           func_80027A7C(float x, float y, float z, float move_x, float move_y, float move_z, float scale, ColPlane *arg7, ColNode *head, ColHit *hit);
ColHit         func_80028BC0(float x, float y, float z, float move_x, float move_y, float move_z);
ColHit         func_80029560(float x, float y, float z, float move_y);
int            func_8002A168(float origin_x, float origin_y, float origin_z);
ColHit         func_8002A750(float x, float y, float z, unsigned short length);
unsigned short func_80029E58(float origin_x, float origin_y, float origin_z, float scale, void *p, void *n);
void           func_80027B38(float x, float y, float z, float move_x, float move_y, float move_z, float scale, ColPlane *mesh_planes, ColNode *mesh_nodes, ColHit *ray);
void           func_800283E8(float x, float y, float z, float move_y, float scale, ColPlane *planes, ColNode *nodes, ColHit *ray);

// clang-format off

// <<<<< bss >>>>>
ColPlane *D_80168F60;
ColNode  *D_80168F64;

// clang-format on

float func_800273E0(ColHit *hit, Task *task, unsigned char arg2, float arg3)
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

    hit->result = 0;
    if (!arg2) {
        arg3 = 0.0f;
    }

    base  = func_800141C4(*D_80236984[ENEMY_WORK(task)->type2]->wave_no);
    entry = &D_80236984[ENEMY_WORK(task)->type2]->entries[ENEMY_WORK(task)->col_entry];
    head  = entry->nodes;
    data2 = entry->planes;
    data2 = (void *) ((unsigned int) data2 - WAVE_SEGMENT_ADDR + base);
    head  = (ColHead *) ((unsigned int) head - WAVE_SEGMENT_ADDR + base);
    range = head->range;

    hit->obj   = task;
    solid      = (ObjSolid *) task->obj_head;
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

    func_80033A3C(solid->rx & ANGLE_MASK, solid->ry & ANGLE_MASK, solid->rz & ANGLE_MASK, &x, &y, &z);
    func_80033A3C(solid->rx & ANGLE_MASK, solid->ry & ANGLE_MASK, solid->rz & ANGLE_MASK, &move_x, &move_y, &move_z);

    if (!arg2) {
        func_80027A7C(x, y, z, move_x, move_y, move_z, scale, data2, (ColNode *) head, hit);
    } else {
        func_8002CC94(x, y, z, move_x, move_y, move_z, scale, data2, head, hit, arg3);
    }

    if (hit->result == COL_HIT) {
        func_80033898(solid->rx & ANGLE_MASK, solid->ry & ANGLE_MASK, solid->rz & ANGLE_MASK, &hit->hit_x, &hit->hit_y, &hit->hit_z);
        func_80033898(solid->rx & ANGLE_MASK, solid->ry & ANGLE_MASK, solid->rz & ANGLE_MASK, &hit->normal_x, &hit->normal_y, &hit->normal_z);
        return hit->hit_x * hit->hit_x + hit->hit_y * hit->hit_y + hit->hit_z * hit->hit_z;
    }

    return 0.0f;
}

unsigned short func_800277C0(float x, float y, float z, Task *task)
{
    unsigned int base;
    ColEntry    *mesh;
    float        scale;
    unsigned int reach;
    void        *planes;
    ColHead     *nodes;
    ObjSolid    *model;

    base   = func_800141C4(*D_80236984[ENEMY_WORK(task)->type2]->wave_no);
    mesh   = &D_80236984[ENEMY_WORK(task)->type2]->entries[ENEMY_WORK(task)->col_entry];
    nodes  = mesh->nodes;
    planes = mesh->planes;
    planes = (void *) ((unsigned int) planes - WAVE_SEGMENT_ADDR + base);
    nodes  = (ColHead *) ((unsigned int) nodes - WAVE_SEGMENT_ADDR + base);
    reach  = nodes->range;
    model  = (ObjSolid *) task->obj_head;
    scale  = model->sx;
    x -= model->tx;
    y -= model->ty;
    z -= model->tz;
    if (reach == 0 || scale == 0.0f) {
        reach = 0;
    } else {
        reach *= scale;
    }
    if (reach < ABS(x) || reach < ABS(y) || reach < ABS(z)) {
        return 0;
    }
    func_80033A3C(model->rx & ANGLE_MASK, model->ry & ANGLE_MASK, model->rz & ANGLE_MASK, &x, &y, &z);
    return func_80029E58(x, y, z, scale, planes, nodes);
}

void func_80027A7C(float x, float y, float z, float move_x, float move_y, float move_z, float scale, ColPlane *arg7, ColNode *head, ColHit *hit)
{
    if (move_x == 0.0 && move_z == 0.0) {
        func_800283E8(x, y, z, move_y, scale, arg7, head, hit);
    } else {
        func_80027B38(x, y, z, move_x, move_y, move_z, scale, arg7, head, hit);
    }
}

void func_80027B38(float x, float y, float z, float move_x, float move_y, float move_z, float scale, ColPlane *mesh_planes, ColNode *mesh_nodes, ColHit *ray)
{
    ColPlane      *planes;
    ColNode       *nodes;
    unsigned short node;
    unsigned short next;
    unsigned short tree;
    unsigned short count;
    short          child;
    short          found;
    unsigned char  flags;
    unsigned char  hit_flags;
    unsigned char  kind;
    unsigned short index;
    ColPlane      *plane;
    float          nx;
    float          ny;
    float          nz;
    float          d;
    float          cx;
    float          cy;
    float          cz;
    float          hit_nx;
    float          hit_ny;
    float          hit_nz;
    float          hit_d;
    float          t;
    float          hit_dist;
    float          prev_nx;
    float          prev_ny;
    float          prev_nz;
    float          prev_d;
    float          prev_dist;
    float          dist;
    float          best_t;
    float          denom;
    float          move;
    unsigned short group;
    float          best;

    planes    = mesh_planes;
    nodes     = mesh_nodes;
    node      = 0;
    hit_flags = 0xFF;
    kind      = 0xFF;
    best      = 20000.0f;
    prev_nx   = 100000.0f;
    move_x    = -move_x;
    move_y    = -move_y;
    move_z    = -move_z;
    for (cy = y, cx = x, cz = z;;) {
        next = nodes[node].index;
        while (nodes[node + 1].x * scale < x || x < nodes[node + 2].x * scale ||
               nodes[node + 1].y * scale < y || y < nodes[node + 2].y * scale ||
               nodes[node + 1].z * scale < z || z < nodes[node + 2].z * scale) {
            if (next == COL_LIST_END) {
                return;
            }
            node = next;
            next = nodes[node].index;
        }
        best_t = 2000.0f;
        group  = nodes[node].group;
        node += 3;
        tree      = node;
        found     = 0;
        count     = 20;
        prev_dist = -1.0f;
        while (1) {
            index = nodes[node].index;
            plane = (ColPlane *) ((unsigned char *) planes + index * sizeof(ColPlane));
            nx    = plane->normal_x;
            ny    = plane->normal_y;
            nz    = plane->normal_z;
            d     = plane->distance * scale;
            flags = plane->type;
            dist  = cx * nx + cy * ny + cz * nz + d;
            PRINTF_DEAD(("Vram Hosen ride Error %f,%f,%f \n", move_x, move_y, move_z));
            if (flags == 0 || dist < 0.0) {
                denom = nx * move_x + ny * move_y + nz * move_z;
                if (denom == 0.0) {
                    t = 2000.0f;
                } else {
                    t = (-d - (cx * nx + cy * ny + cz * nz)) / denom;
                }
                if (flags == 0) {
                    if (best_t != 2000.0 && t < 1e-05 && t > -1e-05) {
                        t    = 0.0f;
                        dist = (cx + move_x) * nx + (cy + move_y) * ny + (cz + move_z) * nz + d;
                    }
                    if (found && t == 0.0 && prev_dist > 0.0 && prev_nx == nx && prev_ny == ny && prev_nz == nz &&
                        prev_d == d) {
                        dist = -1.0f;
                    }
                }
                if (t > 0.0 && t <= best_t) {
                    best_t    = t;
                    hit_nx    = nx;
                    hit_ny    = ny;
                    hit_nz    = nz;
                    hit_d     = d;
                    hit_dist  = dist;
                    hit_flags = flags;
                }
            }
            if (dist < 0.0) {
                child = nodes[node].back;
                if (child == 0) {
                    float step_x;
                    float step_y;
                    float step_z;

                    found = COL_HIT;
                    node  = tree;
                    move  = ABS(step_x = move_x * best_t);
                    if (move < 1e-05 && move_x != 0.0) {
                        step_x = (step_x >= 0.0) ? 1e-05f : -1e-05f;
                    }
                    move = ABS(step_y = move_y * best_t);
                    if (move < 1e-05 && move_y != 0.0) {
                        step_y = (step_y >= 0.0) ? 1e-05f : -1e-05f;
                    }
                    move = ABS(step_z = move_z * best_t);
                    if (move < 1e-05 && move_z != 0.0) {
                        step_z = (step_z >= 0.0) ? 1e-05f : -1e-05f;
                    }
                    cx     = step_x + cx;
                    cy     = step_y + cy;
                    cz     = step_z + cz;
                    best_t = 2000.0f;
                    if (--count == 0) {
                        ray->result = 2;
                        return;
                    }
                    kind      = hit_flags;
                    prev_nx   = hit_nx;
                    prev_ny   = hit_ny;
                    prev_nz   = hit_nz;
                    prev_d    = hit_d;
                    prev_dist = hit_dist;
                } else {
                    node = child;
                }
            } else {
                child = nodes[node].front;
                if (child == 0) {
                    node = next;
                    if (found == COL_HIT) {
                        float dx;
                        float dy;
                        float dz;
                        float dist_sq;

                        if (kind == 0) {
                            prev_nx = hit_nx;
                            prev_ny = hit_ny;
                            prev_nz = hit_nz;
                            prev_d  = hit_d;
                            kind    = hit_flags;
                        }
                        dx      = cx - x;
                        dy      = cy - y;
                        dz      = cz - z;
                        dist_sq = dx * dx + dy * dy + dz * dz;
                        if (best < dist_sq || best == 20000.0) {
                            best                = dist_sq;
                            ray->dist_sq        = best;
                            ray->result         = COL_HIT;
                            ray->hit_x          = dx;
                            ray->hit_y          = dy;
                            ray->hit_z          = dz;
                            ray->normal_x       = prev_nx;
                            ray->normal_y       = prev_ny;
                            ray->normal_z       = prev_nz;
                            ray->plane_distance = prev_d;
                            ray->plane_type     = kind;
                            ray->group          = group;
                        }
                    }
                    if (next == COL_LIST_END) {
                        return;
                    }

                    cx = x;
                    cy = y;
                    cz = z;
                    break;
                } else {
                    node = child;
                }
            }
        }
    }
}

void func_800283E8(float x, float y, float z, float move_y, float scale, ColPlane *mesh_planes, ColNode *mesh_nodes, ColHit *ray)
{
    ColPlane      *planes;
    ColNode       *nodes;
    unsigned short node;
    unsigned short next;
    unsigned short tree;
    unsigned short count;
    short          child;
    unsigned short found;
    unsigned short hit = COL_HIT;
    unsigned char  flags;
    unsigned char  hit_flags;
    unsigned char  kind;
    unsigned short index;
    ColPlane      *plane;
    float          nx;
    float          ny;
    float          nz;
    float          d;
    float          cy;
    float          hit_nx;
    float          hit_ny;
    float          hit_nz;
    float          hit_d;
    float          t;
    float          hit_dist;
    float          prev_nx;
    float          prev_ny;
    float          prev_nz;
    float          prev_d;
    float          prev_dist;
    float          dist;
    float          best_t;
    float          move;
    float          denom;
    unsigned short group;
    float          best;

    node      = 0;
    best      = 20000.0f;
    prev_nx   = 100000.0f;
    hit_flags = 0xFF;
    kind      = 0xFF;
    planes    = mesh_planes;
    nodes     = mesh_nodes;
    if (move_y < 0.0) {
        move_y = 1.0f;
    } else {
        move_y = -1.0f;
    }
    cy = y;
    // The constant local puts found first in the compare of the front leaf.
    while (1) {
        next = nodes[node].index;
        while (nodes[node + 1].x * scale < x || x < nodes[node + 2].x * scale ||
               nodes[node + 1].y * scale < y || y < nodes[node + 2].y * scale ||
               nodes[node + 1].z * scale < z || z < nodes[node + 2].z * scale) {
            if (next == COL_LIST_END) {
                return;
            }
            node = next;
            next = nodes[node].index;
        }
        best_t = 2000.0f;
        group  = nodes[node].group;
        node += 3;
        tree      = node;
        found     = 0;
        count     = 20;
        prev_dist = -1.0f;
        while (1) {
            index = nodes[node].index;

            plane = (ColPlane *) ((unsigned char *) planes + index * sizeof(ColPlane));

            nx = plane->normal_x;
            ny = plane->normal_y;
            nz = plane->normal_z;
            d  = plane->distance * scale;

            flags = plane->type;

            dist = x * nx + cy * ny + z * nz + d;

            PRINTF_DEAD(("Vram Hosen ride Error 0.0,%f,0.0 \n", move_y));
            if (flags == 0 || dist < 0.0) {

                denom = ny * move_y;
                if (denom == 0.0) {
                    t = 2000.0f;
                } else {
                    t = (-d - (x * nx + cy * ny + z * nz)) / denom;
                }
                if (flags == 0) {
                    if (best_t != 2000.0 && t < 1e-05 && t > -1e-05) {
                        t    = 0.0f;
                        dist = x * nx + (cy + move_y) * ny + z * nz + d;
                    }
                    if (found && t == 0.0 && prev_dist > 0.0 && prev_nx == nx && prev_ny == ny && prev_nz == nz &&
                        prev_d == d) {
                        dist = -1.0f;
                    }
                }
                if (t > 0.0 && t <= best_t) {
                    best_t    = t;
                    hit_nx    = nx;
                    hit_ny    = ny;
                    hit_nz    = nz;
                    hit_d     = d;
                    hit_dist  = dist;
                    hit_flags = flags;
                }
            }
            if (dist < 0.0) {
                child = nodes[node].back;
                if (child == 0) {
                    float step;

                    found = COL_HIT;
                    node  = tree;
                    move  = ABS(step = move_y * best_t);
                    if (move < 1e-05 && move_y != 0.0) {
                        step = (step >= 0.0) ? 1e-05f : -1e-05f;
                    }
                    cy     = step + cy;
                    best_t = 2000.0f;
                    if (--count == 0) {
                        ray->result = 2;
                        return;
                    }
                    kind      = hit_flags;
                    prev_nx   = hit_nx;
                    prev_ny   = hit_ny;
                    prev_nz   = hit_nz;
                    prev_d    = hit_d;
                    prev_dist = hit_dist;
                } else {
                    node = child;
                }
            } else {
                child = nodes[node].front;
                if (child == 0) {
                    if (hit == found) {
                        float dx;
                        float dy;
                        float dz;
                        float dist_sq;

                        if (kind == 0) {
                            prev_nx = hit_nx;
                            prev_ny = hit_ny;
                            prev_nz = hit_nz;
                            prev_d  = hit_d;
                            kind    = hit_flags;
                        }
                        dx      = 0.0f;
                        dy      = cy - y;
                        dz      = 0.0f;
                        dist_sq = dy * dy;
                        if (best < dist_sq || best == 20000.0) {
                            best                = dist_sq;
                            ray->dist_sq        = best;
                            ray->result         = COL_HIT;
                            ray->hit_y          = dy;
                            ray->hit_x          = dx;
                            ray->hit_z          = dz;
                            ray->normal_x       = prev_nx;
                            ray->normal_y       = prev_ny;
                            ray->normal_z       = prev_nz;
                            ray->plane_distance = prev_d;
                            ray->plane_type     = kind;
                            ray->group          = group;
                        }
                    }
                    if (next == COL_LIST_END) {
                        return;
                    }
                    node = next;
                    cy   = y;
                    break;
                } else {
                    node = child;
                }
            }
        }
    }
}

ColHit func_80028B28(float x, float y, float z, float move_x, float move_y, float move_z)
{
    if (move_x == 0.0 && move_z == 0.0) {
        return func_80029560(x, y, z, move_y);
    }

    return func_80028BC0(x, y, z, move_x, move_y, move_z);
}

ColHit func_80028BC0(float x, float y, float z, float dir_x, float dir_y, float dir_z)
{
    ColPlane      *planes;
    ColNode       *nodes;
    unsigned short node;
    unsigned short next;
    unsigned short tree;
    unsigned short count;
    short          child;
    unsigned short found;
    unsigned char  flags;
    unsigned char  hit_flags;
    unsigned char  kind;
    unsigned short index;
    ColPlane      *plane;
    float          nx;
    float          ny;
    float          nz;
    float          d;
    float          hit_nx;
    float          hit_ny;
    float          hit_nz;
    float          hit_d;
    float          t;
    float          hit_dist;
    float          prev_nx;
    float          prev_ny;
    float          prev_nz;
    float          prev_d;
    float          prev_dist;
    float          cx;
    float          cy;
    float          cz;
    float          dist;
    float          best_t;
    float          denom;
    float          move;
    unsigned short group;
    float          step_y;
    float          step_z;
    ColHit         ray;
    ColHit         task_ray;
    float          best;

    ray.normal_x       = 0.0f;
    ray.normal_y       = 0.0f;
    ray.normal_z       = 0.0f;
    ray.plane_distance = 0.0f;
#ifndef JAPAN_0
    hit_nx = hit_nz = prev_nz = node = 0;
    hit_ny = prev_ny = 1.0f;
#endif
    ray.result = 0;
    if (D_80168F60 == NULL) {
        return ray;
    }
    best      = 20000.0f;
    prev_nx   = 100000.0f;
    hit_flags = 0xFF;
    kind      = 0xFF;
    planes    = D_80168F60;
    nodes     = D_80168F64;
    dir_x     = -dir_x;
    dir_y     = -dir_y;
    dir_z     = -dir_z;
    while (1) {
        cx   = x;
        cy   = y;
        cz   = z;
        next = nodes[node].index;
        while (nodes[node + 1].x < cx || cx < nodes[node + 2].x || nodes[node + 1].z < cz ||
               cz < nodes[node + 2].z || nodes[node + 1].y < cy ||
               cy + 10.0f < nodes[node + 2].y) {
            if (next == COL_LIST_END) {
                return ray;
            }
            node = next;
            next = nodes[node].index;
        }
        best_t = 2000.0f;
        group  = nodes[node].group;
        node += 3;
        tree      = node;
        found     = 0;
        count     = 20;
        prev_dist = -1.0f;
        while (1) {
            index = nodes[node].index;
            plane = (ColPlane *) ((unsigned char *) planes + index * sizeof(ColPlane));
            nx    = plane->normal_x;
            ny    = plane->normal_y;
            nz    = plane->normal_z;
            d     = plane->distance;
            flags = plane->type;
            dist  = cx * nx + cy * ny + cz * nz + d;
            if (flags == 0 || dist < 0.0) {
                denom = nx * dir_x + ny * dir_y + nz * dir_z;
                if (denom == 0.0) {
                    t = 2000.0f;
                } else {
                    t = (-d - (cx * nx + cy * ny + cz * nz)) / denom;
                }
                if (flags == 0) {
                    if (best_t != 2000.0 && t < 1e-05 && t > -1e-05) {
                        t    = 0.0f;
                        dist = (cx + dir_x) * nx + (cy + dir_y) * ny + (cz + dir_z) * nz + d;
                    }
                    if (found && t == 0.0 && prev_dist > 0.0 && prev_nx == nx && prev_ny == ny && prev_nz == nz &&
                        prev_d == d) {
                        dist = -1.0f;
                    }
                }
                if (t > 0.0 && t <= best_t) {
                    best_t    = t;
                    hit_nx    = nx;
                    hit_ny    = ny;
                    hit_nz    = nz;
                    hit_d     = d;
                    hit_dist  = dist;
                    hit_flags = flags;
                }
            }
            if (dist < 0.0) {
                child = nodes[node].back;
                if (child == 0) {
                    float step_x;

                    found = COL_HIT;
                    node  = tree;
                    move  = ABS(step_x = dir_x * best_t);
                    if (move < 1e-05 && dir_x != 0.0) {
                        step_x = (step_x >= 0.0) ? 1e-05f : -1e-05f;
                    }
                    move = ABS(step_y = dir_y * best_t);
                    if (move < 1e-05 && dir_y != 0.0) {
                        step_y = (step_y >= 0.0) ? 1e-05f : -1e-05f;
                    }
                    move = ABS(step_z = dir_z * best_t);
                    if (move < 1e-05 && dir_z != 0.0) {
                        step_z = (step_z >= 0.0) ? 1e-05f : -1e-05f;
                    }
                    cx     = step_x + cx;
                    cy     = step_y + cy;
                    cz     = step_z + cz;
                    best_t = 2000.0f;
                    if (--count == 0) {
                        PRINTF(("Vram Hosen Error %f,%f,%f \n", dir_x, dir_y, dir_z));
                        ray.result = 2;
                        return ray;
                    }
                    kind      = hit_flags;
                    prev_nx   = hit_nx;
                    prev_ny   = hit_ny;
                    prev_nz   = hit_nz;
                    prev_d    = hit_d;
                    prev_dist = hit_dist;
                } else {
                    node = child;
                }
            } else {
                child = nodes[node].front;
                if (child == 0) {
                    if (found == COL_HIT) {
                        float dx;
                        float dy;
                        float dz;
                        float dist_sq;

                        if (kind == 0) {
                            prev_nx = hit_nx;
                            prev_ny = hit_ny;
                            prev_nz = hit_nz;
                            prev_d  = hit_d;
                            kind    = hit_flags;
                        }
                        dx      = cx - x;
                        dy      = cy - y;
                        dz      = cz - z;
                        dist_sq = dx * dx + dy * dy + dz * dz;
                        if (best < dist_sq || best == 20000.0) {
                            ray.result         = COL_HIT;
                            best               = dist_sq;
                            ray.dist_sq        = best;
                            ray.hit_x          = dx;
                            ray.hit_y          = dy;
                            ray.hit_z          = dz;
                            ray.plane_type     = kind;
                            ray.normal_x       = prev_nx;
                            ray.normal_y       = prev_ny;
                            ray.normal_z       = prev_nz;
                            ray.plane_distance = prev_d;
                            ray.group          = group;
                        }
                    }
                    if (next == COL_LIST_END) {
                        return ray;
                    }
                    node = next;
                    break;
                } else {
                    node = child;
                }
            }
        }
    }
}

ColHit func_80029560(float x, float y, float z, float dir_y)
{
    ColPlane      *planes;
    ColNode       *nodes;
    unsigned short node;
    unsigned short next;
    unsigned short tree;
    unsigned short count;
    short          child;
    unsigned short found;
    unsigned int   flags;
    unsigned char  hit_flags;
    unsigned char  kind;
    unsigned short index;
    ColPlane      *plane;
    float          nx;
    float          ny;
    float          nz;
    float          d;
    float          hit_nx;
    float          hit_ny;
    float          hit_nz;
    float          hit_d;
    float          t;
    float          hit_dist;
    float          prev_nx;
    float          prev_ny;
    float          prev_nz;
    float          prev_d;
    float          prev_dist;
    float          cy;
    float          dist;
    float          best_t;
    float          denom;
    float          move;
    unsigned short group;
    unsigned short inside;
    ColHit         ray;
    ColHit         task_ray;
    float          best;

    hit_nx = hit_nz = prev_nz = node = 0;
    hit_ny = prev_ny = 1.0f;
    if (dir_y == 0.0) {
        inside             = func_80029E08(x, y, z);
        ray.result         = inside;
        ray.plane_type     = 0;
        ray.group          = 0;
        ray.hit_x          = 0.0f;
        ray.hit_y          = 0.0f;
        ray.hit_z          = 0.0f;
        ray.normal_x       = 0.0f;
        ray.normal_y       = 0.0f;
        ray.normal_z       = 0.0f;
        ray.plane_distance = 0.0f;
        ray.dist_sq        = 0.0f;
        return ray;
    }
    ray.result = 0;
    if (D_80168F60 == NULL) {
        return ray;
    }
    best      = 20000.0f;
    prev_nx   = 100000.0f;
    hit_flags = 0xFF;
    kind      = 0xFF;
    planes    = D_80168F60;
    nodes     = D_80168F64;
    if (dir_y < 0.0) {
        dir_y = 1.0f;
    } else {
        dir_y = -1.0f;
    }
    cy = y;
    while (1) {
        next = nodes[node].index;
        while (nodes[node + 1].x < x || x < nodes[node + 2].x || nodes[node + 1].z < z ||
               z < nodes[node + 2].z || nodes[node + 1].y < cy || cy + 10.0f < nodes[node + 2].y) {
            if (next == COL_LIST_END) {
                return ray;
            }
            node = next;
            next = nodes[node].index;
        }
        best_t = 2000.0f;
        group  = nodes[node].group;
        node += 3;
        tree      = node;
        found     = 0;
        count     = 20;
        prev_dist = -1.0f;
        while (1) {
            index = nodes[node].index;
            plane = (ColPlane *) ((unsigned char *) planes + index * sizeof(ColPlane));
            nx    = plane->normal_x;
            ny    = plane->normal_y;
            nz    = plane->normal_z;
            d     = plane->distance;
            flags = plane->type;
            dist  = x * nx + cy * ny + z * nz + d;
            if (flags == 0 || dist < 0.0) {
                denom = ny * dir_y;
                if (denom == 0.0) {
                    t = 2000.0f;
                } else {
                    t = (-d - (x * nx + cy * ny + z * nz)) / denom;
                }
                if (flags == 0) {
                    if (best_t != 2000.0 && t < 1e-05 && t > -1e-05) {
                        t    = 0.0f;
                        dist = x * nx + (cy + dir_y) * ny + z * nz + d;
                    }
                    if (found && t == 0.0 && prev_dist > 0.0 && prev_nx == nx && prev_ny == ny && prev_nz == nz &&
                        prev_d == d) {
                        dist = -1.0f;
                    }
                }
                if (t > 0.0 && t <= best_t) {
                    best_t    = t;
                    hit_nx    = nx;
                    hit_ny    = ny;
                    hit_nz    = nz;
                    hit_d     = d;
                    hit_dist  = dist;
                    hit_flags = plane->type;
                }
            }
            if (dist < 0.0) {
                child = nodes[node].back;
                if (child == 0) {
                    float step;

                    found = COL_HIT;
                    node  = tree;
                    move  = ABS(step = dir_y * best_t);
                    if (move < 1e-05 && dir_y != 0.0) {
                        step = (step >= 0.0) ? 1e-05f : -1e-05f;
                    }
                    cy     = step + cy;
                    best_t = 2000.0f;
                    if (--count == 0) {
                        PRINTF(("Vram Hosen Error 0,%f,0 \n", dir_y));
                        ray.result = 2;
                        return ray;
                    }
                    kind      = hit_flags;
                    prev_nx   = hit_nx;
                    prev_ny   = hit_ny;
                    prev_nz   = hit_nz;
                    prev_d    = hit_d;
                    prev_dist = hit_dist;
                } else {
                    node = child;
                }
            } else {
                child = nodes[node].front;
                if (child == 0) {
                    if (found == COL_HIT) {
                        float dx;
                        float dy;
                        float dz;
                        float dist_sq;

                        if (kind == 0) {
                            prev_nx = hit_nx;
                            prev_ny = hit_ny;
                            prev_nz = hit_nz;
                            prev_d  = hit_d;
                            kind    = hit_flags;
                        }
                        dx      = 0.0f;
                        dy      = cy - y;
                        dz      = 0.0f;
                        dist_sq = dy * dy;
                        if (best < dist_sq || best == 20000.0) {
                            ray.result         = COL_HIT;
                            best               = dist_sq;
                            ray.dist_sq        = best;
                            ray.hit_y          = dy;
                            ray.hit_x          = dx;
                            ray.hit_z          = dz;
                            ray.normal_x       = prev_nx;
                            ray.normal_y       = prev_ny;
                            ray.normal_z       = prev_nz;
                            ray.plane_distance = prev_d;
                            ray.plane_type     = kind;
                            ray.group          = group;
                        }
                    }
                    if (next == COL_LIST_END) {
                        return ray;
                    }
                    node = next;
                    cy   = y;
                    break;
                } else {
                    node = child;
                }
            }
        }
    }
}

int func_80029E08(float x, float y, float z)
{
    if (func_8003266C(x, y, z) == COL_HIT) {
        return COL_HIT;
    }

    return func_8002A168(x, y, z);
}

unsigned short func_80029E58(float origin_x, float origin_y, float origin_z, float scale, void *p, void *n)
{
    int TERMINATE = COL_LIST_END;

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
                    return COL_HIT;
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
    int TERMINATE = COL_LIST_END;

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
                    return COL_HIT;
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
        hit.result         = func_80029E08(x, y, z);
        hit.plane_type     = 0;
        hit.group          = 0;
        hit.obj            = 0;
        hit.solid          = 0;
        hit.hit_x          = 0.0f;
        hit.hit_y          = 0.0f;
        hit.hit_z          = 0.0f;
        hit.normal_x       = 0.0f;
        hit.normal_y       = 0.0f;
        hit.normal_z       = 0.0f;
        hit.plane_distance = 0.0f;
        hit.dist_sq        = 0.0f;
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

    flag  = hit.result;
    flag2 = hit2.result;

    if (flag == 0 && flag2 == 0) {
        return hit2;
    }
    if (flag == COL_HIT && flag2 == COL_HIT) {
        if (hit.dist_sq < hit2.dist_sq) {
            return hit2;
        }
        return hit;
    }
    if (flag == COL_HIT) {
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

void func_8002A7BC(ColHit *ray, Task *task)
{
    ObjSolid      *model;
    ColStage      *mesh;
    float          x;
    float          y;
    float          z;
    float          dir_x;
    float          dir_y;
    float          dir_z;
    float          scale;
    unsigned short i;

    ray->result = 0;
    if (task == NULL) {
        return;
    }
    ray->obj   = task;
    model      = (ObjSolid *) task->obj_head;
    ray->solid = model;
    x          = ray->x - model->tx;
    y          = ray->y - model->ty;
    z          = ray->z - model->tz;
    dir_x      = ray->move_x;
    dir_y      = ray->move_y;
    dir_z      = ray->move_z;
    func_80033A3C(model->rx & ANGLE_MASK, model->ry & ANGLE_MASK, model->rz & ANGLE_MASK, &x, &y, &z);
    func_80033A3C(model->rx & ANGLE_MASK, model->ry & ANGLE_MASK, model->rz & ANGLE_MASK, &dir_x, &dir_y, &dir_z);
    scale = model->sx;
    for (i = 0; i < 3 && D_8020EEE0_63A2C0[i].planes != NULL; i++) {
        mesh       = &D_8020EEE0_63A2C0[i];
        D_80168F60 = mesh->planes;
        D_80168F64 = mesh->nodes;
        if (D_80168F60 == NULL || D_80168F64 == NULL) {
            return;
        }
        func_80027A7C(x, y, z, dir_x, dir_y, dir_z, scale, D_80168F60, D_80168F64, ray);
        if (ray->result == COL_HIT) {
            func_80033898(model->rx & ANGLE_MASK, model->ry & ANGLE_MASK, model->rz & ANGLE_MASK, &ray->hit_x, &ray->hit_y, &ray->hit_z);
            func_80033898(model->rx & ANGLE_MASK, model->ry & ANGLE_MASK, model->rz & ANGLE_MASK, &ray->normal_x, &ray->normal_y, &ray->normal_z);
            return;
        }
    }
}
