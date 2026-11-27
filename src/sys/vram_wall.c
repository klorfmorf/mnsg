#include "sys/vram_wall.h"
#include "common.h"
#include "structs.h"

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/vram_wall/func_8002EB10.s")

void func_80030688(float *max_a, float *min_a, float *max_b, float *min_b, ColHit *ray)
{
    if (ray->hit_x > 0.0f) {
        if (*max_a < ray->hit_x) {
            *max_a = ray->hit_x;
        }
    } else if (ray->hit_x < *min_a) {
        *min_a = ray->hit_x;
    }
    if (ray->hit_z > 0.0f) {
        if (*max_b < ray->hit_z) {
            *max_b = ray->hit_z;
        }
    } else if (ray->hit_z < *min_b) {
        *min_b = ray->hit_z;
    }
}
