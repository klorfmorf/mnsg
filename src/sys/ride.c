#include "sys/ride.h"
#include "sys/sys.h"
#include "sys/vram.h"

void func_80032320(ColHit *ray, unsigned char nearest, float length)
{
    ColHit        *probe;
    Task          *task;
    unsigned short depth;
    float          best;
    float          dist;
    ColHit         probe_ray;

    probe       = &probe_ray;
    ray->result = 0;
    if (g_sys->intended_stage_group >= 4 || ENEMY_MGR->parents[1] == NULL) {
        return;
    }
    *probe = *ray;
    if (!nearest) {
        best = 0.0f;
    } else {
        best = 2000.0f;
    }

    task  = ENEMY_MGR->parents[1];
    depth = task->priority;
    task  = task->next;
    while (task != NULL && depth < task->priority) {
        if (task->obj_head != NULL && (ENEMY_WORK(task)->flags_04 & 0x80000000) && task->obj_head->kind == OBJ_KIND_SOLID) {
            dist = func_800273E0(probe, task, nearest, length);
            if (probe->result == COL_HIT) {
                if (!nearest) {
                    if (best < dist) {
                        best = dist;
                        *ray = *probe;
                    }
                } else if (dist < best) {
                    best = dist;
                    *ray = *probe;
                }
            }
        }
        task = task->next;
    }
    if (ENEMY_MGR->parents[7] == NULL) {
        return;
    }
    task  = ENEMY_MGR->parents[7];
    depth = task->priority;
    task  = task->next;
    while (task != NULL && depth < task->priority) {
        if (task->obj_head != NULL && (ENEMY_WORK(task)->flags_04 & 0x80000000) && task->obj_head->kind == OBJ_KIND_SOLID) {
            dist = func_800273E0(probe, task, nearest, length);
            if (probe->result == COL_HIT) {
                if (!nearest) {
                    if (best < dist) {
                        best = dist;
                        *ray = *probe;
                    }
                } else if (dist < best) {
                    best = dist;
                    *ray = *probe;
                }
            }
        }
        task = task->next;
    }
    ray->dist_sq = best;
}

unsigned short func_8003266C(float x, float y, float z)
{
    Task          *task;
    unsigned short depth;

    if (g_sys->intended_stage_group >= 4) {
        return 0;
    }
    if (ENEMY_MGR->parents[1] == NULL) {
        return 0;
    }
    task  = ENEMY_MGR->parents[1];
    depth = task->priority;
    task  = task->next;
    while (task != NULL && depth < task->priority) {
        if (task->obj_head != NULL && (ENEMY_WORK(task)->flags_04 & 0x80000000) && task->obj_head->kind == OBJ_KIND_SOLID) {
            if (func_800277C0(x, y, z, task) == COL_HIT) {
                return COL_HIT;
            }
        }
        task = task->next;
    }
    if (ENEMY_MGR->parents[7] == NULL) {
        return 0;
    }
    task  = ENEMY_MGR->parents[7];
    depth = task->priority;
    task  = task->next;
    while (task != NULL && depth < task->priority) {
        if (task->obj_head != NULL && (ENEMY_WORK(task)->flags_04 & 0x80000000) && task->obj_head->kind == OBJ_KIND_SOLID) {
            if (func_800277C0(x, y, z, task) == COL_HIT) {
                return COL_HIT;
            }
        }
        task = task->next;
    }
    return 0;
}
