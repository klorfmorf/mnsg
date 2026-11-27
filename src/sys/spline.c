#include "sys/spline.h"
#include "common.h"
#include "structs.h"

void func_800376B0(Vec3f *out, Vec3f *points, float tension, float t)
{
    float t2;
    float s;
    float t3;
    float h0;
    float h1;
    float h2;
    float u;

    u      = t;
    t2     = u * u;
    s      = tension;
    t3     = t2 * u;
    h0     = (2.0f * t2 - t3 - u) * s;
    h1     = (2.0f - s) * t3 + (s - 3.0f) * t2 + 1.0f;
    h2     = (s - 2.0f) * t3 + (3.0f - 2.0f * s) * t2 + s * u;
    out->x = points[0].x * h0 + points[1].x * h1 + points[2].x * h2 + points[3].x * ((t3 - t2) * tension);
    out->y = points[0].y * h0 + points[1].y * h1 + points[2].y * h2 + points[3].y * ((t3 - t2) * tension);
    out->z = points[0].z * h0 + points[1].z * h1 + points[2].z * h2 + points[3].z * ((t3 - t2) * tension);
}

void func_800377F4(Vec3f *out, SplinePath *path, float t)
{
    short  index;
    Vec3f *p;

    if (t < 0.0f || t > 1.0f) {
        return;
    }
    if (t < 1.0f) {
        t *= path->count - 1;
        index = t;
        t -= index;
        switch (path->type) {
            case 0:
                p      = &path->points[index];
                out->x = (p[1].x - p[0].x) * t + p[0].x;
                out->y = (p[1].y - p[0].y) * t + p[0].y;
                out->z = (p[1].z - p[0].z) * t + p[0].z;
                break;
            case 1:
                func_800376B0(out, &path->points[index], path->tension, t);
                break;
        }
    } else {
        index = path->count - 1;
        switch (path->type) {
            case 0:
                p    = &path->points[index];
                *out = *p;
                break;
            case 1:
                p    = &path->points[index + 1];
                *out = *p;
                break;
        }
    }
}
