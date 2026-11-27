#include "sys/ride_floor.h"
#include "common.h"
#include "sys/sys.h"
#include "sys/vram.h"
#include "sys/ripple.h"

ColHit func_80032850(float x, float y, float z)
{
    ColHit        *probe;
    Task          *task;
    Obj           *head;
    float          dist;
    float          best;
    ColHit         ray;
    unsigned short depth;
    ColHit         probe_ray;
    int            pad;

    probe         = &probe_ray;
    probe->result = ray.result = 0;
    if (g_sys->intended_stage_group >= 4) {
        return ray;
    }
    if (ENEMY_MGR->parents[3] == NULL) {
        return ray;
    }
    ray.x      = x;
    ray.y      = y;
    ray.z      = z;
    ray.move_x = 0.0f;
    ray.move_y = -1.0f;
    ray.move_z = 0.0f;
    *probe     = ray;

    task = ENEMY_MGR->parents[3];
    best = dist = 0.0f;
    depth       = task->priority;
    task        = task->next;
    while (task != NULL && depth < task->priority) {
        unsigned int flags;
        head = task->obj_head;
        if (head != NULL) {
            flags = RIPPLE_WORK(task)->flags_08;
            if ((flags & 0x80) && head->kind == OBJ_KIND_SOLID) {
                if (!(flags & 0x40)) {
                    dist = func_800273E0(probe, task, 0, 2000.0f);
                } else {
                    func_80026AAC(probe, task);
                    if (probe->result == COL_HIT) {
                        probe->obj   = task;
                        probe->solid = (ObjSolid *) task->obj_head;
                        dist         = probe->hit_y;
                    }
                }
                if (probe->result == COL_HIT && best < dist) {
                    best = dist;
                    ray  = *probe;
                }
            }
        }
        task = task->next;
    }
    ray.dist_sq = best;
    return ray;
}
