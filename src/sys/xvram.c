#include "sys/xvram.h"
#include "sys/vram.h"
#include "sys/ride.h"

ColHit func_8002B3B0(float, float, float, float, float, float, float);
ColHit func_8002AAD8(float, float, float, float, float, float, float);
ColHit func_8002BDEC(float, float, float, float, float, float, float);
void   func_8002D924(float, float, float, float, float, float, float, ColPlane *, ColHead *, ColHit *, float);
void   func_8002E2E8(float, float, float, float, float, float, float, ColPlane *, ColHead *, ColHit *, float);
void   func_8002CDB0(float, float, float, float, float, float, float, ColPlane *, ColHead *, ColHit *, float);

ColHit func_8002AA00(float x, float y, float z, float dir_x, float dir_y, float dir_z, float length)
{
    if (dir_y == 0.0f) {
        return func_8002B3B0(x, y, z, dir_x, dir_y, dir_z, length);
    }
    if (dir_x == 0.0f && dir_z == 0.0f) {
        return func_8002AAD8(x, y, z, dir_x, dir_y, dir_z, length);
    }
    return func_8002BDEC(x, y, z, dir_x, dir_y, dir_z, length);
}

ColHit func_8002AAD8(float x, float y, float z, float dir_x, float dir_y, float dir_z, float length)
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
    float          next_y;
    float          sum;
    ColHit         ray;
    ColHit         task_ray;
    float          best;

    node         = 0;
    ray.result   = 0;
    ray.normal_x = 0.0f;
    ray.normal_y = 0.0f;
    ray.normal_z = 0.0f;
    if (D_80168F60 == NULL) {
        return ray;
    }
    best      = 20000.0f;
    prev_nx   = 100000.0f;
    hit_flags = 0xFF;
    kind      = 0xFF;
    planes    = D_80168F60;
    nodes     = D_80168F64;
    while (1) {
        cx   = x;
        cy   = y;
        cz   = z;
        next = nodes[node].index;
        while (nodes[node + 1].x < cx || cx < nodes[node + 2].x || nodes[node + 1].z < cz ||
               cz < nodes[node + 2].z || (dir_y > 0.0f && nodes[node + 1].y < cy) ||
               (dir_y < 0.0f && cy < nodes[node + 2].y) || cy < nodes[node + 2].y - length ||
               nodes[node + 1].y + length < cy) {
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
        prev_dist = 1.0f;
        while (1) {
            index = nodes[node].index;
            plane = (ColPlane *) ((unsigned char *) planes + index * sizeof(ColPlane));
            nx    = plane->normal_x;
            ny    = plane->normal_y;
            nz    = plane->normal_z;
            d     = plane->distance;
            flags = plane->type;
            sum   = cx * nx + cy * ny + cz * nz;
            dist  = sum + d;
            if (flags == 0 || dist > 0.0) {
                denom = ny * dir_y;
                if (denom == 0.0) {
                    t = 2000.0f;
                } else {
                    t = (-d - sum) / denom;
                }
                if (flags == 0) {
                    if (t < 0.01 && t > -0.01) {
                        t      = 0;
                        next_y = cy + dir_y;
                        dist   = cx * nx + next_y * ny + cz * nz + d;
                    }
                    if (found && t == 0.0 && prev_dist <= 0.0 && prev_nx == nx && prev_ny == ny && prev_nz == nz &&
                        prev_d == d) {
                        dist = 1.0f;
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
            if (dist > 0.0) {
                child = nodes[node].front;
                if (child == 0) {
                    found = COL_HIT;
                    node  = tree;
                    if (best_t < length) {
                        float step;
                        float new_y;

                        move = ABS(step = dir_y * best_t);
                        if (move < 0.001 && dir_y != 0.0) {
                            step = (step >= 0.0) ? 0.001f : -0.001f;
                        }
                        new_y     = step + cy;
                        cy        = new_y;
                        kind      = hit_flags;
                        prev_nx   = hit_nx;
                        prev_ny   = hit_ny;
                        prev_nz   = hit_nz;
                        prev_d    = hit_d;
                        prev_dist = hit_dist;
                        best_t    = 2000.0f;
                        if (--count == 0) {
                            PRINTF(("XVram Hosen Error1 %f,%f,%f \n", dir_x, dir_y, dir_z));
                            ray.result = 2;
                            return ray;
                        }
                    } else {
                        if (next == COL_LIST_END) {
                            return ray;
                        }
                        node = next;
                        break;
                    }
                } else {
                    node = child;
                }
            } else {
                child = nodes[node].back;
                if (child == 0) {
                    if (found == COL_HIT) {
                        float dx;
                        float dy;
                        float dz;
                        float dist_sq;

                        if (kind == 0) {
                            prev_nx = hit_nx;
                            kind    = hit_flags;
                            prev_ny = hit_ny;
                            prev_nz = hit_nz;
                            prev_d  = hit_d;
                        }
                        dx      = 0.0f;
                        dy      = cy - y;
                        dz      = 0.0f;
                        dist_sq = dy * dy;
                        if (dist_sq < best) {
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
                    break;
                } else {
                    node = child;
                }
            }
        }
    }
}

ColHit func_8002B3B0(float x, float y, float z, float dir_x, float dir_y, float dir_z, float length)
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
    float          next_x;
    float          next_z;
    ColHit         ray;
    ColHit         task_ray;
    float          best;

    node         = 0;
    ray.result   = 0;
    ray.normal_x = 0.0f;
    ray.normal_y = 0.0f;
    ray.normal_z = 0.0f;
    if (D_80168F60 == NULL) {
        return ray;
    }
    best      = 20000.0f;
    prev_nx   = 100000.0f;
    hit_flags = 0xFF;
    kind      = 0xFF;
    planes    = D_80168F60;
    nodes     = D_80168F64;
    for (cx = x, cy = y, cz = z;;) {
        next = nodes[node].index;
        while ((dir_x > 0.0f && nodes[node + 1].x < cx) || (dir_x < 0.0f && cx < nodes[node + 2].x) ||
               cx < nodes[node + 2].x - length || nodes[node + 1].x + length < cx ||
               cz < nodes[node + 2].z - length || nodes[node + 1].z + length < cz ||
               (dir_z > 0 && nodes[node + 1].z < cz) || (dir_z < 0 && cz < nodes[node + 2].z) ||
               nodes[node + 1].y < y || y < nodes[node + 2].y) {
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
        prev_dist = 1.0f;
        while (1) {
            index = nodes[node].index;
            plane = (ColPlane *) ((unsigned char *) planes + index * sizeof(ColPlane));
            nx    = plane->normal_x;
            ny    = plane->normal_y;
            nz    = plane->normal_z;
            d     = plane->distance;
            flags = plane->type;
            dist  = cx * nx + cy * ny + cz * nz + d;
            if (flags == 0 || dist > 0.0) {
                denom = nx * dir_x + nz * dir_z;
                if (denom == 0.0) {
                    t = 2000.0f;
                } else {
                    t = (-d - (cx * nx + cy * ny + cz * nz)) / denom;
                }
                if (flags == 0) {
                    if (t < 0.01 && t > -0.01) {
                        t      = 0;
                        next_x = cx + dir_x;
                        next_z = cz + dir_z;
                        dist   = next_x * nx + cy * ny + next_z * nz + d;
                    }
                    if (found && t == 0.0 && prev_dist <= 0.0 && prev_nx == nx && prev_ny == ny && prev_nz == nz &&
                        prev_d == d) {
                        dist = 1.0f;
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
            if (dist > 0.0) {
                child = nodes[node].front;
                if (child == 0) {
                    found = COL_HIT;
                    node  = tree;
                    if (best_t < length) {
                        float step_x;
                        float step_z;

                        move = ABS(step_x = dir_x * best_t);
                        if (move < 0.001 && dir_x != 0.0) {
                            step_x = (step_x >= 0.0) ? 0.001f : -0.001f;
                        }
                        move = ABS(step_z = dir_z * best_t);
                        if (move < 0.001 && dir_z != 0.0) {
                            step_z = (step_z >= 0.0) ? 0.001f : -0.001f;
                        }
                        cx        = step_x + cx;
                        cz        = step_z + cz;
                        kind      = hit_flags;
                        prev_nx   = hit_nx;
                        prev_ny   = hit_ny;
                        prev_nz   = hit_nz;
                        prev_d    = hit_d;
                        prev_dist = hit_dist;
                        best_t    = 2000.0f;
                        if (--count == 0) {
                            PRINTF(("XVram Hosen Error2 %f,%f,%f \n", dir_x, dir_y, dir_z));
                            ray.result = 2;
                            return ray;
                        }
                    } else {
                        if (next == COL_LIST_END) {
                            return ray;
                        }
                        node = next;
                        cx   = x;
                        cy   = y;
                        cz   = z;
                        break;
                    }
                } else {
                    node = child;
                }
            } else {
                child = nodes[node].back;
                if (child == 0) {
                    if (found == COL_HIT) {
                        float dx;
                        float dy;
                        float dz;
                        float dist_sq;

                        if (kind == 0) {
                            prev_nx = hit_nx;
                            kind    = hit_flags;
                            prev_ny = hit_ny;
                            prev_nz = hit_nz;
                            prev_d  = hit_d;
                        }
                        dx      = cx - x;
                        dy      = 0.0f;
                        dz      = cz - z;
                        dist_sq = dx * dx + dz * dz;
                        if (dist_sq < best) {
                            ray.result         = COL_HIT;
                            best               = dist_sq;
                            ray.dist_sq        = best;
                            ray.hit_x          = dx;
                            ray.hit_y          = dy;
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
                    cx   = x;
                    cy   = y;
                    cz   = z;
                    break;
                } else {
                    node = child;
                }
            }
        }
    }
}

ColHit func_8002BDEC(float x, float y, float z, float dir_x, float dir_y, float dir_z, float length)
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
    float          sum;
    float          step_z;
    ColHit         ray;
    ColHit         task_ray;
    float          best;

    node         = 0;
    ray.result   = 0;
    ray.normal_x = 0;
    ray.normal_y = 0;
    ray.normal_z = 0;
    if (D_80168F60 == NULL) {
        return ray;
    }
    best      = 20000.0f;
    prev_nx   = 100000.0f;
    hit_flags = 0xFF;
    kind      = 0xFF;
    planes    = D_80168F60;
    nodes     = D_80168F64;
    while (1) {
        cx   = x;
        cy   = y;
        cz   = z;
        next = nodes[node].index;
        while ((dir_x > 0 && nodes[node + 1].x < cx) || (dir_x < 0 && cx < nodes[node + 2].x) ||
               cx < nodes[node + 2].x - length || nodes[node + 1].x + length < cx ||
               (dir_z > 0 && nodes[node + 1].z < cz) || (dir_z < 0 && cz < nodes[node + 2].z) ||
               cz < nodes[node + 2].z - length || nodes[node + 1].z + length < cz ||
               (dir_y > 0 && nodes[node + 1].y < cy) || (dir_y < 0 && cy < nodes[node + 2].y) ||
               cy < nodes[node + 2].y - length || nodes[node + 1].y + length < cy) {
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
        prev_dist = 1.0f;
        while (1) {
            index = nodes[node].index;
            plane = (ColPlane *) ((unsigned char *) planes + index * sizeof(ColPlane));
            nx    = plane->normal_x;
            ny    = plane->normal_y;
            nz    = plane->normal_z;
            d     = plane->distance;
            flags = plane->type;
            sum   = cx * nx + cy * ny + cz * nz;
            dist  = sum + d;
            if (flags == 0 || dist > 0.0) {
                denom = nx * dir_x + ny * dir_y + nz * dir_z;
                if (denom == 0.0) {
                    t = 2000.0f;
                } else {
                    t = (-d - sum) / denom;
                }
                if (flags == 0) {
                    if (t < 0.01 && t > -0.01) {
                        t    = 0;
                        dist = (cx + dir_x) * nx + (cy + dir_y) * ny + (cz + dir_z) * nz + d;
                    }
                    if (found && t == 0.0 && prev_dist <= 0.0 && prev_nx == nx && prev_ny == ny && prev_nz == nz &&
                        prev_d == d) {
                        dist = 1.0f;
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
            if (dist > 0.0) {
                child = nodes[node].front;
                if (child == 0) {
                    found = COL_HIT;
                    node  = tree;
                    if (best_t < length) {
                        float step_x;
                        float step_y;

                        move = ABS(step_x = dir_x * best_t);
                        if (move < 0.001 && dir_x != 0.0) {
                            step_x = (step_x >= 0.0) ? 0.001f : -0.001f;
                        }
                        move = ABS(step_y = dir_y * best_t);
                        if (move < 0.001 && dir_y != 0.0) {
                            step_y = (step_y >= 0.0) ? 0.001f : -0.001f;
                        }
                        move = ABS(step_z = dir_z * best_t);
                        if (move < 0.001 && dir_z != 0.0) {
                            step_z = (step_z >= 0.0) ? 0.001f : -0.001f;
                        }
                        cx        = step_x + cx;
                        cy        = step_y + cy;
                        cz        = step_z + cz;
                        kind      = hit_flags;
                        prev_nx   = hit_nx;
                        prev_ny   = hit_ny;
                        prev_nz   = hit_nz;
                        prev_d    = hit_d;
                        prev_dist = hit_dist;
                        best_t    = 2000.0f;
                        if (--count == 0) {
                            PRINTF(("XVram Hosen Error 3 %f,%f,%f \n", dir_x, dir_y, dir_z));
                            ray.result = 2;
                            return ray;
                        }
                    } else {
                        if (next == COL_LIST_END) {
                            return ray;
                        }
                        node = next;
                        break;
                    }
                } else {
                    node = child;
                }
            } else {
                child = nodes[node].back;
                if (child == 0) {
                    if (found == COL_HIT) {
                        float dx;
                        float dy;
                        float dz;
                        float dist_sq;

                        if (kind == 0) {
                            prev_nx = hit_nx;
                            kind    = hit_flags;
                            prev_ny = hit_ny;
                            prev_nz = hit_nz;
                            prev_d  = hit_d;
                        }
                        dx      = cx - x;
                        dy      = cy - y;
                        dz      = cz - z;
                        dist_sq = dx * dx + dy * dy + dz * dz;
                        if (dist_sq < best) {
                            ray.result         = COL_HIT;
                            best               = dist_sq;
                            ray.dist_sq        = best;
                            ray.hit_x          = dx;
                            ray.hit_y          = dy;
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
                    break;
                } else {
                    node = child;
                }
            }
        }
    }
}

ColHit func_8002C9D4(float x, float y, float z, float dir_x, float dir_y, float dir_z, float length)
{
    ColHit         stage_ray;
    ColHit         task_ray;
    unsigned short inside;

    if (dir_x == 0.0 && dir_y == 0.0 && dir_z == 0.0) {
        inside               = func_80029E08(x, y, z);
        stage_ray.result     = inside;
        stage_ray.plane_type = 0;
        stage_ray.group      = 0;
        stage_ray.obj        = NULL;
        stage_ray.solid      = NULL;
        stage_ray.hit_x      = 0.0f;
        stage_ray.hit_y      = 0.0f;
        stage_ray.hit_z      = 0.0f;
        stage_ray.normal_x   = 0.0f;
        stage_ray.normal_y   = 0.0f;
        stage_ray.normal_z   = 0.0f;
        stage_ray.dist_sq    = 0.0f;
        return stage_ray;
    }
    stage_ray       = func_8002AA00(x, y, z, dir_x, dir_y, dir_z, length);
    task_ray.x      = x;
    task_ray.y      = y;
    task_ray.z      = z;
    task_ray.move_x = dir_x;
    task_ray.move_y = dir_y;
    task_ray.move_z = dir_z;
    stage_ray.obj   = NULL;
    stage_ray.solid = NULL;
    func_80032320(&task_ray, 1, length);
    if (stage_ray.result == 0 && task_ray.result == 0) {
        return task_ray;
    }
    if (stage_ray.result == COL_HIT && task_ray.result == COL_HIT) {
        if (task_ray.dist_sq < stage_ray.dist_sq) {
            return task_ray;
        }
        return stage_ray;
    }
    if (stage_ray.result == COL_HIT) {
        return stage_ray;
    }
    return task_ray;
}

void func_8002CC94(float x, float y, float z, float dir_x, float dir_y, float dir_z, float scale, void *planes, ColHead *nodes, ColHit *ray, float length)
{
    if (dir_y == 0.0f) {
        func_8002D924(x, y, z, dir_x, dir_y, dir_z, scale, planes, nodes, ray, length);
    } else if (dir_x == 0.0f && dir_z == 0.0f) {
        func_8002E2E8(x, y, z, dir_x, dir_y, dir_z, scale, planes, nodes, ray, length);
    } else {
        func_8002CDB0(x, y, z, dir_x, dir_y, dir_z, scale, planes, nodes, ray, length);
    }
}

// Debug strings. They will be PRINTF calls once their functions match. The owner of "Error p" is not known.
const char D_8007C290[] = "XVram Hosen Error p %f,%f,%f \n";
const char D_8007C2B0[] = "XVram Hosen ride1 Error %f,%f,%f \n";

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/xvram/func_8002CDB0.s")

const char D_8007C2D4[] = "XVram Hosen ride2 Error %f,%f,%f \n";

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/xvram/func_8002D924.s")

const char D_8007C2F8[] = "XVram Hosen ride3 Error %f,%f,%f \n";

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/xvram/func_8002E2E8.s")
