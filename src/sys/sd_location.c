#include "sys/sd_location.h"
#include "sys/sd_main.h"
#include "sys/task.h"
#include "sys/math.h"
#include "sys/okutani.h"
#include "sys/gfx_util.h"

void func_8000F924(Task *task, Obj *obj);
void func_8000F2EC(unsigned short id, float screen_x);
void func_8000FC94(unsigned short, AnimeCamera *, float, float, float);
void func_8000F2EC(unsigned short, float);
void func_8000F730(unsigned short, float, float);

void func_8000F240(unsigned short id, AnimeCamera *camera, ObjSolid *obj)
{
    func_8000F280(id, camera, obj->tx, obj->ty, obj->tz);
}

void func_8000F280(unsigned short id, AnimeCamera *camera, float x, float y, float z)
{
    float screen_x;
    float screen_y;

    if (func_8001CC38(camera, x, y, z, &screen_x, &screen_y) >= 0.0f) {
        func_8000F2EC(id, screen_x);
    }
}

void func_8000F2EC(unsigned short id, float screen_x)
{
    unsigned short pan = screen_x / 320.0f * 128.0f;

    if (pan <= 0) {
        pan = 1;
    }
    if (pan >= 128) {
        pan = 127;
    }
    func_80038BF8(id, pan);
}

void func_8000F3D8(unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range)
{
    func_8000F5F8(id, camera, obj->tx, obj->ty, obj->tz, range);
}

void func_8000F420(unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range)
{
    func_8000F6E8(id, camera, obj->tx, obj->ty, obj->tz, range);
}

void func_8000F468(unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range)
{
    float screen_x;
    float screen_y;

    if (func_8001CC38(camera, obj->tx, obj->ty, obj->tz, &screen_x, &screen_y) >= 0.0f) {
        if (!(screen_x < 0.0f) && !(320.0f < screen_x) && !(screen_y < 0.0f) && !(240.0f < screen_y)) {
            func_8000F420(id, camera, obj, range);
        }
    }
}

void func_8000F52C(unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range)
{
    float screen_x;
    float screen_y;

    if (func_8001CC38(camera, obj->tx, obj->ty, obj->tz, &screen_x, &screen_y) >= 0.0f) {
        if (!(screen_x < -100.0f) && !(420.0f < screen_x) && !(screen_y < -100.0f) && !(340.0f < screen_y)) {
            func_8000F420(id, camera, obj, range);
        }
    }
}

void func_8000F5F8(unsigned short id, AnimeCamera *camera, float x, float y, float z, float range)
{
    float dx       = x - camera->eye[0];
    float dy       = y - camera->eye[1];
    float dz       = z - camera->eye[2];
    float distance = sqrtf(dx * dx + dy * dy + dz * dz) / range;
    float screen_x;
    float screen_y;

    if (func_8001CC38(camera, x, y, z, &screen_x, &screen_y) >= 0.0f) {
        if (screen_x < 0.0f) {
            screen_x = 0.0f;
        }
        if (320.0f < screen_x) {
            screen_x = 320.0f;
        }
        func_8000F730(id, screen_x, distance);
    }
}

void func_8000F6E8(unsigned short id, AnimeCamera *camera, float x, float y, float z, float range)
{
    func_8000FE1C(id, camera, x, y, z, range);
}

void func_8000F730(unsigned short id, float screen_x, float distance)
{
    unsigned char volume;
    float         pan;

    if (distance < 0.0f) {
        distance = 0.0f;
    }
    if (distance > 1.0) {
        distance = 1.0f;
    }
    volume = 255.0f - distance * 159.0f;
    if (volume >= 0x30) {
        pan = screen_x / 320.0f * 128.0f;
        if (pan < 1.0f) {
            pan = 1.0f;
        }
        if (127.0f < pan) {
            pan = 127.0f;
        }
        func_80038C30(id, pan, volume);
    }
}

void func_8000F924(Task *task, Obj *obj)
{
    SoundTaskWork *source   = SOUND_TASK_WORK(task);
    float          dx       = source->solid->tx - source->camera->eye[0];
    float          dy       = source->solid->ty - source->camera->eye[1];
    float          dz       = source->solid->tz - source->camera->eye[2];
    float          distance = sqrtf(dx * dx + dy * dy + dz * dz) / source->range;
    float          volume;
    float          pan;
    unsigned short angle;
    unsigned short view_yaw;

    if (distance < 0.0f) {
        distance = 0.0f;
    }
    if (distance > 1.0) {
        distance = 1.0f;
    }
    view_yaw = func_8000E28C(source->camera->at[0], source->camera->at[2], source->camera->eye[0], source->camera->eye[2]);
    angle    = (func_8000E28C(source->solid->tx, source->solid->tz, source->camera->eye[0], source->camera->eye[2]) - view_yaw) &
               ANGLE_MASK;
    pan      = func_80003E10(angle) * 64.0f + 64.0f;
    volume   = 255.0f - distance * 159.0f;
    if (pan < 1.0f) {
        pan = 1.0f;
    }
    if (127.0f < pan) {
        pan = 127.0f;
    }
    func_80038D94(source->sound_id, volume, pan);
}

int func_8000FBA8(Task *task)
{
    func_80038B98(SOUND_TASK_WORK(task)->sound_id | 0x8000);
    func_80034EF8(task);
    return 0;
}

Task *func_8000FBE0(Task *parent, unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range)
{
    Task *task = func_80034E08(parent, func_8000F924, 0);

    if (task == NULL) {
        return NULL;
    }
    SOUND_TASK_WORK(task)->sound_id = id;
    SOUND_TASK_WORK(task)->camera   = camera;
    SOUND_TASK_WORK(task)->solid    = obj;
    SOUND_TASK_WORK(task)->range    = range;
    func_80038B98(SOUND_TASK_WORK(task)->sound_id);
    return task;
}

void func_8000FC54(unsigned short id, AnimeCamera *camera, ObjSolid *obj)
{
    func_8000FC94(id, camera, obj->tx, obj->ty, obj->tz);
}

void func_8000FC94(unsigned short id, AnimeCamera *camera, float x, float y, float z)
{
    int            yaw;
    int            diff;
    float          sine;
    float          pan;
    unsigned short angle;
    unsigned short view_yaw;

    view_yaw = func_8000E28C(camera->at[0], camera->at[2], camera->eye[0], camera->eye[2]);
    yaw      = func_8000E28C(x, z, camera->eye[0], camera->eye[2]);
    diff     = yaw - view_yaw;
    angle    = diff & ANGLE_MASK;
    sine     = func_80003E10(angle);
    pan      = sine * 64.0f + 64.0f;
    if (pan < 1.0f) {
        pan = 1.0f;
    }
    if (127.0f < pan) {
        pan = 127.0f;
    }
    func_80038BF8(id, pan);
}

void func_8000FDD4(unsigned short id, AnimeCamera *camera, ObjSolid *obj, float range)
{
    func_8000FE1C(id, camera, obj->tx, obj->ty, obj->tz, range);
}

void func_8000FE1C(unsigned short id, AnimeCamera *camera, float x, float y, float z, float range)
{
    float          dx       = x - camera->eye[0];
    float          dy       = y - camera->eye[1];
    float          dz       = z - camera->eye[2];
    float          distance = sqrtf(dx * dx + dy * dy + dz * dz) / range;
    float          volume;
    float          pan;
    unsigned short angle;
    unsigned short view_yaw;

    if (distance < 0.0f) {
        distance = 0.0f;
    }
    if (distance > 1.0) {
        distance = 1.0f;
    }
    volume   = 255.0f - distance * 159.0f;
    view_yaw = func_8000E28C(camera->at[0], camera->at[2], camera->eye[0], camera->eye[2]);
    angle    = (func_8000E28C(x, z, camera->eye[0], camera->eye[2]) - view_yaw) & ANGLE_MASK;
    pan      = func_80003E10(angle) * 64.0f + 64.0f;
    if (pan < 1.0f) {
        pan = 1.0f;
    }
    if (127.0f < pan) {
        pan = 127.0f;
    }
    if (angle > ANGLE_QUARTER && angle < ANGLE_FULL - ANGLE_QUARTER) {
        volume = 255 - (unsigned char) (distance * 1.1 * 159.0);
    }
    func_80038C30(id, pan, volume);
}
