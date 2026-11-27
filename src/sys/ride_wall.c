#include "common.h"
#include "sys/ride.h"

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/ride_wall/func_80030730.s")

void func_800322A8(ColHit *ray, float x, float y, float z, float dir_x, float dir_y, float dir_z, float length)
{
    ray->x      = x;
    ray->y      = y;
    ray->z      = z;
    ray->move_x = dir_x;
    ray->move_y = dir_y;
    ray->move_z = dir_z;
    func_80032320(ray, 1, length + 2.0f);
}
