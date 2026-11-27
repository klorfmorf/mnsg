#include "sys/gfx_util.h"
#include "sys/math.h"
#include "sys/anime.h"
#include "sys/atan2.h"

#pragma intrinsic(sqrtf)

void func_8001DE74(unsigned short *rot, float y, float length, float z_sin, float z_cos, float sin1, float cos1, float sin2, float cos2, float sin3, float cos3);
void func_8001DF94(unsigned short *rot, float y, float length, float z_sin, float z_cos, float sin1, float cos1, float sin2, float cos2, float sin3, float cos3);
void func_8001E0BC(unsigned short *rot, float y, float length, float z_sin, float z_cos, float sin1, float cos1, float sin2, float cos2, float sin3, float cos3, float *dir, float dir_length, float sign);
void func_8001E9B0(float m[4][4], float x, float y, float z, unsigned short rot_x, unsigned short rot_y, unsigned short rot_z, float scale_x, float scale_y, float scale_z);
void func_8001EC04(float m[4][4], float x, float y, float z, unsigned short rot_x, unsigned short rot_y, unsigned short rot_z, float scale_x, float scale_y, float scale_z);
void func_8001F19C(unsigned short *rot_x, unsigned short *rot_y, unsigned short *rot_z, float length, float m[4][4]);
void func_8001F6C8(unsigned short *x, unsigned short *y, unsigned short *z, unsigned short tx, unsigned short ty, unsigned short tz);

// clang-format off

// <<<<< bss >>>>>
unsigned short D_801689F0;
unsigned short D_801689F2;
unsigned short D_801689F4;
int            D_801689F8;

// clang-format on

void func_8001C970(ObjSolid *dst, ObjSolid *src)
{
    dst->tx = src->tx;
    dst->ty = src->ty;
    dst->tz = src->tz;
    dst->rx = src->rx;
    dst->ry = src->ry;
    dst->rz = src->rz;
    dst->sx = src->sx;
    dst->sy = src->sy;
    dst->sz = src->sz;
}

void func_8001C9BC(ObjSolid *dst, ObjSolid *src)
{
    dst->tx = src->tx;
    dst->ty = src->ty;
    dst->tz = src->tz;
}

void func_8001C9D8(ObjSolid *dst, ObjSolid *src)
{
    dst->tx += src->tx;
    dst->ty += src->ty;
    dst->tz += src->tz;
}

unsigned short func_8001CA0C(float y, float x)
{
    float angle = func_800166E0(y, x);

    while (angle < 0) {
        angle += 6.283185307179586;
    }
    while (angle > 6.283185307179586) {
        angle -= 6.283185307179586;
    }
    return (float) (angle * 512.0f / 3.141592653589793);
}

float func_8001CB40(AnimeCamera *camera, float x, float y, float z, float *view_x, float *view_y)
{
    float dir[3];
    float rel[3];
    float view[3];
    float scale;

    dir[0] = camera->eye[0] - camera->at[0];
    dir[1] = camera->eye[1] - camera->at[1];
    dir[2] = camera->eye[2] - camera->at[2];
    rel[0] = x - camera->eye[0];
    rel[1] = y - camera->eye[1];
    rel[2] = z - camera->eye[2];
    func_8001D394((Vec3f *) dir);
    func_8001D460((Vec3f *) rel, (Vec3f *) view, (Vec3f *) dir);
    scale = -view[2] * func_80003DC0(camera->fovy);
    if (scale < 0.0f) {
        return scale;
    }
    *view_x = view[0] / scale;
    *view_y = view[1] / scale;
    return scale;
}

float func_8001CC38(AnimeCamera *camera, float x, float y, float z, float *screen_x, float *screen_y)
{
    Vp   *vp    = &g_anime_default_vp;
    float depth = func_8001CB40(camera, x, y, z, screen_x, screen_y);

    if (depth < 0.0f) {
        return depth;
    }
    if (camera->vp != NULL) {
        vp = camera->vp;
    }
    *screen_x = (*screen_x * vp->vp.vscale[0] * 0.75f + vp->vp.vtrans[0]) * 0.25;
    *screen_y = (-*screen_y * vp->vp.vscale[1] + vp->vp.vtrans[1]) * 0.25;
    return depth;
}

unsigned short func_8001CD4C(Vec3f *out, Vec3f *v, Vec3f *dir, Vec3f *target, float scale)
{
    Vec3f result;
    Vec3f target_local;
    float target_length;
    Vec3f local;
    float length;
    int   v_heading;
    int   heading;
    int   angle;
    float sin;
    float cos;

    func_8001D898(v, &local, dir);
    v_heading = func_800040A8(local.z, local.x);
    local.x *= scale;
    local.z *= scale;
    length = sqrtf(local.z * local.z + local.x * local.x);
    if (((length < 0.0f) ? -length : length) < 1e-05) {
        out->x = out->y = out->z = 0.0f;
        return 0;
    }
    func_8001D898(target, &target_local, dir);
    target_length = sqrtf(target_local.z * target_local.z + target_local.x * target_local.x);
    if (((target_length < 0.0f) ? -target_length : target_length) < 1e-05) {
        out->x = out->y = out->z = 0.0f;
        return 0;
    }
    heading = func_800040A8(target_local.z, target_local.x);
    angle   = (v_heading - heading) & ANGLE_MASK;
    if (angle & ANGLE_HALF) {
        if (angle & ANGLE_QUARTER) {
            angle += ANGLE_QUARTER;
        } else {
            angle = -ANGLE_QUARTER - angle;
        }
        heading -= 240;
    } else {
        if (angle & ANGLE_QUARTER) {
            angle -= ANGLE_QUARTER;
        } else {
            angle = ANGLE_QUARTER - angle;
        }
        heading += 240;
    }
    angle &= ANGLE_MASK;
    length   = func_80003EA0(angle) * length;
    sin      = func_80003F30(heading, &cos);
    result.x = length * cos;
    result.y = 0.0f;
    result.z = length * sin;
    func_8001D718(&result, out, dir);
    return angle | 0x400;
}

int func_8001CF5C(Vec3f *out, Vec3f *v, Vec3f *dir, Vec3f *target, float scale)
{
    Vec3f        saved;
    float        scaled;
    float        length_sq;
    float        new_length = 0.0f;
    float        length;
    Vec3f        local;
    float        new_length_sq;
    Vec3f        turned;
    Vec3f        moved;
    unsigned int zero = 0;

    saved.x = v->x;
    saved.y = v->y;
    saved.z = v->z;
    func_8001D898(v, &local, dir);
    length_sq = local.z * local.z + local.x * local.x;
    length    = sqrtf(length_sq);
    if (((length < 0.0f) ? -length : length) < 1e-05) {
        out->x = out->y = out->z = 0.0f;
        return 0;
    }
    func_8001D898(v, &local, target);
    local.y       = 0.0f;
    new_length_sq = local.z * local.z + local.x * local.x;
    new_length    = sqrtf(new_length_sq);
    if (((new_length < 0.0f) ? -new_length : new_length) < 1e-05) {
        out->x = out->y = out->z = 0.0f;
        return 0;
    }
    scaled     = length * scale;
    new_length = scaled / new_length;
    local.x *= new_length;
    local.z *= new_length;
    func_8001D718(&local, out, target);
    moved.x = out->x;
    moved.y = out->y;
    moved.z = out->z;
    func_8001D394(&saved);
    func_8001D394(&moved);
    func_8001D898(&moved, &turned, &saved);
    if (turned.z < zero) {
        out->x = out->y = out->z = 0.0f;
        return 0;
    }
    return 1;
}

int func_8001D14C(ObjSolid *obj, Vec3f *dir, float x, float y, float z)
{
    Vec3f rel;
    Vec3f local;
    float abs_x;
    float abs_z;

    rel.x = x - obj->tx;
    rel.y = y - obj->ty;
    rel.z = z - obj->tz;
    func_8001D898(&rel, &local, dir);
    if ((abs_x = (local.x < 0.0f) ? -local.x : local.x) < 1e-05 &&
        (abs_z = (local.z < 0.0f) ? -local.z : local.z) < 1e-05) {
        return 0x400;
    }
    return func_800040A8(local.x, local.z);
}

int func_8001D230(Vec3f *v, float x, float y, float z, unsigned short angle)
{
    Vec3f          vec;
    Vec3f          t;
    float          len;
    unsigned short rot;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    func_8001D898(v, &t, &vec);
    len = sqrtf(t.z * t.z + t.x * t.x);
    if (((len < 0.0f) ? -len : len) < 1e-5) {
        v->x = t.x;
        v->y = t.y;
        v->z = t.z;
        return 1;
    }
    rot = func_800040A8(t.y, len);
    if (0.0f <= t.y) {
        rot = (rot + angle) & ANGLE_MASK;
        if (rot > ANGLE_QUARTER) {
            rot = ANGLE_QUARTER;
        }
    } else {
        rot = (rot - angle) & ANGLE_MASK;
        if (rot < ANGLE_FULL - ANGLE_QUARTER) {
            rot = ANGLE_FULL - ANGLE_QUARTER;
        }
    }
    len = func_80003EA0(rot) / len;
    t.y = func_80003E10(rot);
    t.x *= len;
    t.z *= len;
    func_8001D718(&t, v, &vec);
    func_8001D394(v);
    return 0;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gfx_util/func_8001D394.s")

int func_8001D460(Vec3f *in, Vec3f *out, Vec3f *dir)
{
    float rotated[3];
    float horizontal = sqrtf(dir->z * dir->z + dir->x * dir->x);

    if (((horizontal < 0.0f) ? -horizontal : horizontal) < 1e-05) {
        out->x = in->x;
        if (dir->y > 0.0f) {
            out->y = -in->z;
            out->z = in->y;
        } else {
            out->y = in->z;
            out->z = -in->y;
        }
        return 0;
    }
    rotated[0] = (in->x * dir->z - dir->x * in->z) / horizontal;
    rotated[1] = in->y * horizontal + -(in->x * dir->x + in->z * dir->z) * dir->y / horizontal;
    rotated[2] = dir->z * in->z + (in->x * dir->x + in->y * dir->y);
    out->x     = rotated[0];
    out->y     = rotated[1];
    out->z     = rotated[2];
    return 1;
}

int func_8001D5B8(Vec3f *in, Vec3f *out, Vec3f *dir)
{
    float rotated[3];
    float horizontal = sqrtf(dir->z * dir->z + dir->x * dir->x);

    if (((horizontal < 0.0f) ? -horizontal : horizontal) < 1e-05) {
        out->x = in->x;
        if (dir->y > 0.0f) {
            out->y = in->z;
            out->z = -in->y;
        } else {
            out->y = -in->z;
            out->z = in->y;
        }
        return 0;
    }
    rotated[0] = dir->x * in->z + (in->x * dir->z - in->y * dir->x * dir->y) / horizontal;
    rotated[1] = dir->y * in->z + in->y * horizontal;
    rotated[2] = dir->z * in->z + -(in->x * dir->x + in->y * dir->z * dir->y) / horizontal;
    out->x     = rotated[0];
    out->y     = rotated[1];
    out->z     = rotated[2];
    return 1;
}

int func_8001D718(Vec3f *in, Vec3f *out, Vec3f *dir)
{
    float length = sqrtf(dir->y * dir->y + dir->x * dir->x);
    float sign   = (dir->y >= 0.0f) ? 1.0f : -1.0f;

    if (((length < 0.0f) ? -length : length) < 1e-05) {
        out->x = in->x;
        if (dir->z > 0.0f) {
            out->y = -in->z;
            out->z = in->y;
        } else {
            out->y = in->z;
            out->z = -in->y;
        }
        return 0;
    }
    out->x = dir->x * in->y + (in->x * dir->y - in->z * dir->z * dir->x) / length * sign;
    out->y = dir->y * in->y + (-in->x * dir->x - in->z * dir->z * dir->y) / length * sign;
    out->z = in->z * length * sign + in->y * dir->z;
    return 1;
}

int func_8001D898(Vec3f *in, Vec3f *out, Vec3f *dir)
{
    float length = sqrtf(dir->y * dir->y + dir->x * dir->x);
    float sign   = (dir->y >= 0.0f) ? 1.0f : -1.0f;

    if (((length < 0.0f) ? -length : length) < 1e-05) {
        out->x = in->x;
        if (dir->z > 0.0f) {
            out->y = in->z;
            out->z = -in->y;
        } else {
            out->y = -in->z;
            out->z = in->y;
        }
        return 0;
    }
    out->x = (in->x * dir->y - dir->x * in->y) / length * sign;
    out->y = dir->z * in->z + (in->x * dir->x + in->y * dir->y);
    out->z = (in->z * length + (-in->x * dir->z * dir->x - in->y * dir->z * dir->y) / length) * sign;
    return 1;
}

unsigned short func_8001DA08(int range)
{
    float value;

    D_801689F8 = (D_801689F8 * 23 + 2345) % 4535;
    value      = D_801689F8 * (1.0 / 4536) * range;
    return value;
}

void func_8001DB04(unsigned short *rot, float *dir, unsigned short angle_x, unsigned short angle_y, unsigned short angle_z)
{
    float          length;
    float          sign;
    float          x_sin;
    float          x_cos;
    float          y_sin;
    float          y_cos;
    float          z_sin;
    float          z_cos;
    float          y;
    float          side_length;
    float          cos_ysin_z;
    float          cos_ycos_z;
    float          side_sin;
    float          side_cos;
    float          down_y;
    float          up_length;
    float          neg_sin_y;
    float          neg_cos_y;
    float          down_length;
    unsigned short old[3];

    length = sqrtf(dir[0] * dir[0] + dir[1] * dir[1]);
    sign   = (dir[1] >= 0.0f) ? 1.0f : -1.0f;
    old[0] = rot[0];
    old[1] = rot[1];
    old[2] = rot[2];
    rot[0] = ANGLE_HALF;
    x_sin  = func_80003F30(angle_x, &x_cos);
    y_sin  = func_80003F30(angle_y, &y_cos);
    z_sin  = func_80003F30(angle_z, &z_cos);
    if (((length < 0.0f) ? -length : length) < 1e-05) {
        if (dir[2] > 0.0f) {
            cos_ysin_z = y_cos * z_sin;
            cos_ycos_z = y_cos * z_cos;
            up_length  = sqrtf(y_sin * y_sin + cos_ycos_z * cos_ycos_z);
            func_8001DE74(rot, cos_ysin_z, up_length, y_sin, cos_ycos_z, x_sin, x_cos, y_sin, y_cos, z_sin, z_cos);
            func_8001F6C8(rot, rot + 1, rot + 2, old[0], old[1], old[2]);
        } else {
            cos_ycos_z  = y_cos * z_cos;
            neg_sin_y   = -y_sin;
            neg_cos_y   = -y_cos;
            down_length = sqrtf(neg_sin_y * neg_sin_y + cos_ycos_z * cos_ycos_z);
            down_y      = neg_cos_y * z_sin;
            func_8001DF94(rot, down_y, down_length, neg_sin_y, cos_ycos_z, x_sin, x_cos, y_sin, y_cos, z_sin, z_cos);
            func_8001F6C8(rot, rot + 1, rot + 2, old[0], old[1], old[2]);
        }
    } else {
        cos_ysin_z  = y_cos * z_sin;
        y           = -(dir[2] * cos_ysin_z - y_sin * length * sign);
        cos_ycos_z  = y_cos * z_cos;
        side_cos    = (cos_ycos_z * dir[1] + y_sin * dir[2] * dir[0]) / length * sign + dir[0] * cos_ysin_z;
        neg_cos_y   = -y_cos;
        side_sin    = (neg_cos_y * z_cos * dir[0] + y_sin * dir[2] * dir[1]) / length * sign + dir[1] * cos_ysin_z;
        side_length = sqrtf(side_sin * side_sin + side_cos * side_cos);
        func_8001E0BC(rot, y, side_length, side_sin, side_cos, x_sin, x_cos, y_sin, y_cos, z_sin, z_cos, dir, length, sign);
        func_8001F6C8(rot, rot + 1, rot + 2, old[0], old[1], old[2]);
    }
}

void func_8001DE74(unsigned short *rot, float y, float length, float z_sin, float z_cos, float sin1, float cos1, float sin2, float cos2, float sin3, float cos3)
{
    rot[1] = func_800040A8(y, length);
    if (((length < 0.0f) ? -length : length) < 1e-05) {
#ifdef JAPAN_0
        if (length > 0.0f || (length == 0.0f && (rot[0] & ANGLE_HALF))) {
            rot[0] = 0;
            rot[2] = func_800040A8(sin1 * sin2 * cos3 - cos1 * sin3, -sin1 * cos2);
        } else {
            rot[0] = ANGLE_HALF;
            rot[2] = func_800040A8(-(sin1 * sin2 * cos3 - cos1 * sin3), -(-sin1 * cos2));
        }
#else
        rot[0] = 0;
        rot[2] = func_800040A8(-(sin1 * sin2 * cos3 - cos1 * sin3), -sin1 * cos2);
#endif
    } else {
        rot[0] = func_800040A8((sin1 * sin2 * sin3 + cos1 * cos3) / length,
            (cos1 * sin2 * sin3 - sin1 * cos3) / length);
        rot[2] = func_800040A8(z_sin / length, z_cos / length);
    }
}

void func_8001DF94(unsigned short *rot, float y, float length, float z_sin, float z_cos, float sin1, float cos1, float sin2, float cos2, float sin3, float cos3)
{
    rot[1] = func_800040A8(y, length);
    if (((length < 0.0f) ? -length : length) < 1e-05) {
#ifdef JAPAN_0
        if (length > 0.0f || (length == 0.0f && (rot[0] & ANGLE_HALF))) {
            rot[0] = 0;
            rot[2] = func_800040A8(sin1 * sin2 * cos3 - cos1 * sin3, sin1 * cos2);
        } else {
            rot[0] = ANGLE_HALF;
            rot[2] = func_800040A8(-(sin1 * sin2 * cos3 - cos1 * sin3), -(sin1 * cos2));
        }
#else
        rot[0] = 0;
        rot[2] = func_800040A8(-(sin1 * sin2 * cos3 - cos1 * sin3), sin1 * cos2);
#endif
    } else {
        rot[0] = func_800040A8((-sin1 * sin2 * sin3 - cos1 * cos3) / length,
            (-cos1 * sin2 * sin3 + sin1 * cos3) / length);
        rot[2] = func_800040A8(z_sin / length, z_cos / length);
    }
}

#ifdef NON_MATCHING
void func_8001E0BC(unsigned short *rot, float y, float length, float z_sin, float z_cos, float sin1, float cos1, float sin2, float cos2,
    float sin3, float cos3, float *dir, float dir_length, float sign)
{
    float sine;
    float cosine;

    rot[1] = func_800040A8(y, length);
    if (((length < 0.0f) ? -length : length) < 1e-05) {
        sine   = dir[0] * (sin1 * sin2 * sin3 + cos1 * cos3) +
                 ((sin1 * sin2 * cos3 - cos1 * sin3) * dir[1] - sin1 * cos2 * dir[2] * dir[0]) / dir_length * sign;
        cosine = dir[1] * (sin1 * sin2 * sin3 + cos1 * cos3) +
                 (-(sin1 * sin2 * cos3 - cos1 * sin3) * dir[0] - sin1 * cos2 * dir[2] * dir[1]) / dir_length * sign;
#ifdef JAPAN_0
        if (length > 0.0f || (length == 0.0f && (rot[0] & ANGLE_HALF))) {
            rot[0] = 0;
            rot[2] = func_800040A8(sine, cosine);
        } else {
            rot[0] = ANGLE_HALF;
            rot[2] = func_800040A8(-sine, -cosine);
        }
#else
        rot[0] = 0;
        rot[2] = func_800040A8(-sine, cosine);
#endif
    } else {
        sine   = dir[2] * (sin1 * sin2 * sin3 + cos1 * cos3) + sin1 * cos2 * dir_length * sign;
        cosine = dir[2] * (cos1 * sin2 * sin3 - sin1 * cos3) + cos1 * cos2 * dir_length * sign;
        rot[0] = func_800040A8(sine / length, cosine / length);
        rot[2] = func_800040A8(z_sin / length, z_cos / length);
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/gfx_util/func_8001E0BC.s")
#endif

void func_8001E2BC(float m[4][4], ObjSolid *obj)
{
    D_801689F0 = ((obj->rx) == ANGLE_BILLBOARD ? 0 : (obj->rx));
    D_801689F2 = ((obj->ry) == ANGLE_BILLBOARD ? 0 : (obj->ry));
    D_801689F4 = ((obj->rz) == ANGLE_BILLBOARD ? 0 : (obj->rz));
    func_8001E9B0(m, obj->tx, obj->ty, obj->tz, obj->rx, obj->ry, obj->rz, obj->sx, obj->sy,
        obj->sz);
}

void func_8001E380(float m[4][4], ObjSolid *obj)
{
    func_8001EC04(m, obj->tx, obj->ty, obj->tz, obj->rx, obj->ry, obj->rz, obj->sx, obj->sy,
        obj->sz);
}

void func_8001E3E4(float m[4][4], float x, float y, float z)
{
    m[0][0] = x;
    m[1][1] = y;
    m[2][2] = z;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    m[1][0] = 0.0f;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

void func_8001E444(float m[4][4], float x, float y, float z)
{
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = m[2][0] = m[2][1] = m[2][3] = 0.0f;
    m[3][0]                                                                                 = x;
    m[3][1]                                                                                 = y;
    m[3][2]                                                                                 = z;
}

void func_8001E4A4(float (*mf)[4], unsigned short rx, unsigned short ry, unsigned short rz)
{
    float sx, cx, sy, cy, sz, cz;
    float cxsy, sxsy;
    int   pad[4];

    rx       = (rx == ANGLE_BILLBOARD) ? 0 : rx;
    ry       = (ry == ANGLE_BILLBOARD) ? 0 : ry;
    rz       = (rz == ANGLE_BILLBOARD) ? 0 : rz;
    sx       = func_80003F30(rx, &cx);
    sy       = func_80003F30(ry, &cy);
    sz       = func_80003F30(rz, &cz);
    cxsy     = cx * sy;
    sxsy     = sx * sy;
    mf[0][0] = cy * cz;
    mf[0][1] = cy * sz;
    mf[0][2] = -sy;
    mf[1][0] = sxsy * cz - cx * sz;
    mf[1][1] = sxsy * sz + cx * cz;
    mf[1][2] = sx * cy;
    mf[2][0] = cxsy * cz + sx * sz;
    mf[2][1] = cxsy * sz - sx * cz;
    mf[2][2] = cx * cy;
    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;
}

void func_8001E634(float (*mf)[4], unsigned short rx, unsigned short ry, unsigned short rz)
{
    float sx, cx, sy, cy, sz, cz;
    float cxsy, sxsy;
    int   pad[4];

    rx       = (rx == ANGLE_BILLBOARD) ? 0 : rx;
    ry       = (ry == ANGLE_BILLBOARD) ? 0 : ry;
    rz       = (rz == ANGLE_BILLBOARD) ? 0 : rz;
    sx       = func_80003F30(rx, &cx);
    sy       = func_80003F30(ry, &cy);
    sz       = func_80003F30(rz, &cz);
    cxsy     = cx * sy;
    sxsy     = sx * sy;
    mf[0][0] = cy * cz;
    mf[1][0] = cy * sz;
    mf[2][0] = -sy;
    mf[0][1] = sxsy * cz - cx * sz;
    mf[1][1] = sxsy * sz + cx * cz;
    mf[2][1] = sx * cy;
    mf[0][2] = cxsy * cz + sx * sz;
    mf[1][2] = cxsy * sz - sx * cz;
    mf[2][2] = cx * cy;
    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][0] = 0.0f;
    mf[3][1] = 0.0f;
    mf[3][2] = 0.0f;
    mf[3][3] = 1.0f;
}

void func_8001E7C4(float m[4][4], unsigned short angle)
{
    float sin;
    float cos;

    angle   = ((angle) == ANGLE_BILLBOARD ? 0 : (angle));
    sin     = func_80003F30(angle, &cos);
    m[1][1] = cos;
    m[1][2] = sin;
    m[2][1] = -sin;
    m[2][2] = cos;
    m[0][1] = m[0][2] = m[1][0] = m[2][0] = m[0][3] = m[1][3] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
    m[0][0] = m[3][3] = 1.0f;
}

void func_8001E868(float m[4][4], unsigned short angle)
{
    float sin;
    float cos;

    angle   = ((angle) == ANGLE_BILLBOARD ? 0 : (angle));
    sin     = func_80003F30(angle, &cos);
    m[0][0] = cos;
    m[0][2] = -sin;
    m[2][0] = sin;
    m[2][2] = cos;
    m[0][1] = m[1][0] = m[1][2] = m[2][1] = m[0][3] = m[1][3] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
    m[1][1] = m[3][3] = 1.0f;
}

void func_8001E90C(float m[4][4], unsigned short angle)
{
    float sin;
    float cos;

    angle   = ((angle) == ANGLE_BILLBOARD ? 0 : (angle));
    sin     = func_80003F30(angle, &cos);
    m[0][0] = cos;
    m[0][1] = sin;
    m[1][0] = -sin;
    m[1][1] = cos;
    m[0][2] = m[1][2] = m[2][0] = m[2][1] = m[0][3] = m[1][3] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
    m[2][2] = m[3][3] = 1.0f;
}

void func_8001E9B0(float m[4][4], float x, float y, float z, unsigned short rot_x, unsigned short rot_y, unsigned short rot_z, float scale_x, float scale_y,
    float scale_z)
{
    float sin_x;
    float cos_x;
    float sin_y;
    float cos_y;
    float sin_z;
    float cos_z;
    float cos_xsin_y;
    float sin_xsin_y;

    rot_x      = ((rot_x) == ANGLE_BILLBOARD ? 0 : (rot_x));
    rot_y      = ((rot_y) == ANGLE_BILLBOARD ? 0 : (rot_y));
    rot_z      = ((rot_z) == ANGLE_BILLBOARD ? 0 : (rot_z));
    sin_x      = func_80003F30(rot_x, &cos_x);
    sin_y      = func_80003F30(rot_y, &cos_y);
    sin_z      = func_80003F30(rot_z, &cos_z);
    cos_xsin_y = cos_x * sin_y;
    sin_xsin_y = sin_x * sin_y;
    m[0][0]    = cos_y * cos_z;
    m[0][1]    = cos_y * sin_z;
    m[0][2]    = -sin_y;
    m[1][0]    = sin_xsin_y * cos_z - cos_x * sin_z;
    m[1][1]    = sin_xsin_y * sin_z + cos_x * cos_z;
    m[1][2]    = sin_x * cos_y;
    m[2][0]    = cos_xsin_y * cos_z + sin_x * sin_z;
    m[2][1]    = cos_xsin_y * sin_z - sin_x * cos_z;
    m[2][2]    = cos_x * cos_y;
    m[3][0]    = x;
    m[3][1]    = y;
    m[3][2]    = z;
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3]                     = 1.0f;
    if (scale_x != 1.0f) {
        m[0][0] *= scale_x;
        m[0][1] *= scale_x;
        m[0][2] *= scale_x;
    }
    if (scale_y != 1.0f) {
        m[1][0] *= scale_y;
        m[1][1] *= scale_y;
        m[1][2] *= scale_y;
    }
    if (scale_z != 1.0f) {
        m[2][0] *= scale_z;
        m[2][1] *= scale_z;
        m[2][2] *= scale_z;
    }
}

void func_8001EC04(float m[4][4], float x, float y, float z, unsigned short rot_x, unsigned short rot_y, unsigned short rot_z, float scale_x, float scale_y,
    float scale_z)
{
    float sin_x;
    float cos_x;
    float sin_y;
    float cos_y;
    float sin_z;
    float cos_z;
    float cos_xsin_y;
    float sin_xsin_y;

    rot_x      = (rot_x == ANGLE_BILLBOARD) ? 0 : ANGLE_FULL - rot_x;
    rot_y      = (rot_y == ANGLE_BILLBOARD) ? 0 : ANGLE_FULL - rot_y;
    rot_z      = (rot_z == ANGLE_BILLBOARD) ? 0 : ANGLE_FULL - rot_z;
    sin_x      = func_80003F30(rot_x, &cos_x);
    sin_y      = func_80003F30(rot_y, &cos_y);
    sin_z      = func_80003F30(rot_z, &cos_z);
    cos_xsin_y = cos_x * sin_y;
    sin_xsin_y = sin_x * sin_y;
    m[0][0]    = cos_y * cos_z;
    m[0][1]    = sin_xsin_y * cos_z + cos_x * sin_z;
    m[0][2]    = -cos_xsin_y * cos_z + sin_x * sin_z;
    m[1][0]    = -cos_y * sin_z;
    m[1][1]    = -sin_xsin_y * sin_z + cos_x * cos_z;
    m[1][2]    = cos_xsin_y * sin_z + sin_x * cos_z;
    m[2][0]    = sin_y;
    m[2][1]    = -sin_x * cos_y;
    m[2][2]    = cos_x * cos_y;
    m[3][0]    = x * m[0][0] + y * m[1][0] + m[2][0] * z;
    m[3][1]    = x * m[0][1] + y * m[1][1] + m[2][1] * z;
    m[3][2]    = x * m[0][2] + y * m[1][2] + m[2][2] * z;
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3]                     = 1.0f;

    if (scale_x != 1.0f) {
        scale_x = 1.0f / scale_x;
        m[0][0] *= scale_x;
        m[1][0] *= scale_x;
        m[2][0] *= scale_x;
        m[3][0] *= scale_x;
    }
    if (scale_y != 1.0f) {
        scale_y = 1.0f / scale_y;
        m[0][1] *= scale_y;
        m[1][1] *= scale_y;
        m[2][1] *= scale_y;
        m[3][1] *= scale_y;
    }
    if (scale_z != 1.0f) {
        scale_z = 1.0f / scale_z;
        m[0][2] *= scale_z;
        m[1][2] *= scale_z;
        m[2][2] *= scale_z;
        m[3][2] *= scale_z;
    }
}

void func_8001EEF4(float *x, float *y, float *z, unsigned short *rot_x, unsigned short *rot_y, unsigned short *rot_z, float *scale_x, float *scale_y, float *scale_z,
    float m[4][4])
{
    float          tmp_x;
    float          tmp_y;
    float          tmp_z;
    float          tmp_scale_x;
    float          tmp_scale_y;
    float          tmp_scale_z;
    unsigned short tmp_rot_x;
    unsigned short tmp_rot_y;
    unsigned short tmp_rot_z;
    float          length;
    unsigned short old[3];

    if (x == NULL) {
        x = &tmp_x;
    }
    if (y == NULL) {
        y = &tmp_y;
    }
    if (z == NULL) {
        z = &tmp_z;
    }
    if (rot_x == NULL) {
        rot_x = &tmp_rot_x;
    }
    if (rot_y == NULL) {
        rot_y = &tmp_rot_y;
    }
    if (rot_z == NULL) {
        rot_z = &tmp_rot_z;
    }
    if (scale_x == NULL) {
        scale_x = &tmp_scale_x;
    }
    if (scale_y == NULL) {
        scale_y = &tmp_scale_y;
    }
    if (scale_z == NULL) {
        scale_z = &tmp_scale_z;
    }
    old[0]   = *rot_x;
    old[1]   = *rot_y;
    old[2]   = *rot_z;
    *rot_x   = ANGLE_HALF;
    *x       = m[3][0];
    *y       = m[3][1];
    *z       = m[3][2];
    *scale_x = sqrtf(m[0][0] * m[0][0] + m[0][1] * m[0][1] + m[0][2] * m[0][2]);
    *scale_y = sqrtf(m[1][0] * m[1][0] + m[1][1] * m[1][1] + m[1][2] * m[1][2]);
    *scale_z = sqrtf(m[2][0] * m[2][0] + m[2][1] * m[2][1] + m[2][2] * m[2][2]);
    if (*scale_x != 0.0f) {
        m[0][0] /= *scale_x;
        m[0][1] /= *scale_x;
        m[0][2] /= *scale_x;
    }
    if (*scale_y != 0.0f) {
        m[1][0] /= *scale_y;
        m[1][1] /= *scale_y;
        m[1][2] /= *scale_y;
    }
    if (*scale_z != 0.0f) {
        m[2][0] /= *scale_z;
        m[2][1] /= *scale_z;
        m[2][2] /= *scale_z;
    }
    length = sqrtf(m[0][0] * m[0][0] + m[0][1] * m[0][1]);
    func_8001F19C(rot_x, rot_y, rot_z, length, m);
    func_8001F6C8(rot_x, rot_y, rot_z, old[0], old[1], old[2]);
}

void func_8001F19C(unsigned short *rot_x, unsigned short *rot_y, unsigned short *rot_z, float length, float m[4][4])
{
    *rot_y = func_800040A8(-m[0][2], length);
    if (((length < 0.0f) ? -length : length) < 1e-05) {
        if (length > 0.0f || (length == 0.0f && (*rot_x & ANGLE_HALF))) {
            *rot_x = 0;
            *rot_z = func_800040A8(-m[1][0], m[1][1]);
        } else {
            *rot_x = ANGLE_HALF;
            *rot_z = func_800040A8(m[1][0], -m[1][1]);
        }
    } else {
        *rot_x = func_800040A8(m[1][2] / length, m[2][2] / length);
        *rot_z = func_800040A8(m[0][1] / length, m[0][0] / length);
    }
}

void func_8001F2D8(float a[4][4], float b[4][4])
{
    float m[4][4];

    m[0][0] = a[0][0] * b[0][0] + a[1][0] * b[0][1] + a[2][0] * b[0][2];
    m[0][1] = a[0][1] * b[0][0] + a[1][1] * b[0][1] + a[2][1] * b[0][2];
    m[0][2] = a[0][2] * b[0][0] + a[1][2] * b[0][1] + a[2][2] * b[0][2];
    m[1][0] = a[0][0] * b[1][0] + a[1][0] * b[1][1] + a[2][0] * b[1][2];
    m[1][1] = a[0][1] * b[1][0] + a[1][1] * b[1][1] + a[2][1] * b[1][2];
    m[1][2] = a[0][2] * b[1][0] + a[1][2] * b[1][1] + a[2][2] * b[1][2];
    m[2][0] = a[0][0] * b[2][0] + a[1][0] * b[2][1] + a[2][0] * b[2][2];
    m[2][1] = a[0][1] * b[2][0] + a[1][1] * b[2][1] + a[2][1] * b[2][2];
    m[2][2] = a[0][2] * b[2][0] + a[1][2] * b[2][1] + a[2][2] * b[2][2];
    m[3][0] = a[0][0] * b[3][0] + a[1][0] * b[3][1] + a[2][0] * b[3][2] + a[3][0] * b[3][3];
    m[3][1] = a[0][1] * b[3][0] + a[1][1] * b[3][1] + a[2][1] * b[3][2] + a[3][1] * b[3][3];
    m[3][2] = a[0][2] * b[3][0] + a[1][2] * b[3][1] + a[2][2] * b[3][2] + a[3][2] * b[3][3];
    b[0][0] = m[0][0];
    b[0][1] = m[0][1];
    b[0][2] = m[0][2];
    b[1][0] = m[1][0];
    b[1][1] = m[1][1];
    b[1][2] = m[1][2];
    b[2][0] = m[2][0];
    b[2][1] = m[2][1];
    b[2][2] = m[2][2];
    b[3][0] = m[3][0];
    b[3][1] = m[3][1];
    b[3][2] = m[3][2];
    b[0][3] = b[1][3] = b[2][3] = 0.0f;
    b[3][3]                     = 1.0f;
}

void func_8001F5F8(float mf[4][4], Mtx *m)
{
    int   i;
    int   e1;
    int   e2;
    long *ai;
    long *af;

    ai = &m->m[0][0];
    af = &m->m[2][0];
    for (i = 0; i < 4; i++) {
        e1      = FTOFIX32(mf[i][0]);
        e2      = FTOFIX32(mf[i][1]);
        *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
        *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
        e1      = FTOFIX32(mf[i][2]);
        e2      = FTOFIX32(mf[i][3]);
        *(ai++) = (e1 & 0xFFFF0000) | ((e2 >> 16) & 0xFFFF);
        *(af++) = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF);
    }
}

void func_8001F6C8(unsigned short *x, unsigned short *y, unsigned short *z, unsigned short tx, unsigned short ty, unsigned short tz)
{
    unsigned short dist;
    unsigned short alt;
    unsigned short diff;
    unsigned short alt_x;
    unsigned short alt_y;
    unsigned short alt_z;

    diff = (((((*x) - (tx)) & ANGLE_HALF) ? ((tx) - (*x)) : ((*x) - (tx))) & ANGLE_MASK);
    dist = diff;
    diff = (((((*y) - (ty)) & ANGLE_HALF) ? ((ty) - (*y)) : ((*y) - (ty))) & ANGLE_MASK);
    dist += diff;
    diff = (((((*z) - (tz)) & ANGLE_HALF) ? ((tz) - (*z)) : ((*z) - (tz))) & ANGLE_MASK);
    dist += diff;
    alt_x = *x;
    alt_y = *y;
    alt_z = *z;
    func_8001F878(&alt_x, &alt_y, &alt_z);
    diff = (((((alt_x) - (tx)) & ANGLE_HALF) ? ((tx) - (alt_x)) : ((alt_x) - (tx))) & ANGLE_MASK);
    alt  = diff;
    diff = (((((alt_y) - (ty)) & ANGLE_HALF) ? ((ty) - (alt_y)) : ((alt_y) - (ty))) & ANGLE_MASK);
    alt += diff;
    diff = (((((alt_z) - (tz)) & ANGLE_HALF) ? ((tz) - (alt_z)) : ((alt_z) - (tz))) & ANGLE_MASK);
    alt += diff;
    if (alt <= dist) {
        *x = alt_x;
        *y = alt_y;
        *z = alt_z;
    }
}

void func_8001F878(unsigned short *x, unsigned short *y, unsigned short *z)
{
    *y = (ANGLE_HALF - *y) & ANGLE_MASK;
    *x = (*x + ANGLE_HALF) & ANGLE_MASK;
    *z = (*z + ANGLE_HALF) & ANGLE_MASK;
}
