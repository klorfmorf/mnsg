#include "sys/dracam.h"
#include "common.h"
#include "macros.h"
#include "structs.h"
#include "sys/sys.h"
#include "sys/amem.h"
#include "sys/task.h"
#include "sys/obj_alloc.h"
#include "sys/yamamoto.h"
#include "sys/gfx_util.h"
#include "sys/spline.h"
#include "douchu/587B50.h"

void func_80011B60(void)
{
    if (D_801FC624_5B8534 != NULL && D_801FC628_5B8538 != NULL) {
        D_801FC624_5B8534->status |= TASK_STATUS_SUSPEND_UPDATE | TASK_STATUS_SUSPEND_DRAW;
        D_801FC628_5B8538->hidden = 1;
        D_801FC628_5B8538->header.kind |= OBJ_HIDDEN;
    }
}

void func_80011BB4(void)
{
    if (D_801FC624_5B8534 != NULL && D_801FC628_5B8538 != NULL) {
        D_801FC624_5B8534->status &= ~(TASK_STATUS_SUSPEND_UPDATE | TASK_STATUS_SUSPEND_DRAW);
        D_801FC628_5B8538->hidden = 0;
        D_801FC628_5B8538->header.kind &= ~OBJ_HIDDEN;
    }
}

void func_80011C04(void)
{
    if (g_sys->stage_lighting_task != NULL) {
        g_sys->stage_lighting_task->status |= TASK_STATUS_SUSPEND_UPDATE | TASK_STATUS_SUSPEND_DRAW;
        g_sys->stage_lighting_task->obj_head->kind |= OBJ_HIDDEN;
    }
}

void func_80011C58(void)
{
    if (g_sys->stage_lighting_task != NULL) {
        g_sys->stage_lighting_task->status &= ~(TASK_STATUS_SUSPEND_UPDATE | TASK_STATUS_SUSPEND_DRAW);
        g_sys->stage_lighting_task->obj_head->kind &= ~OBJ_HIDDEN;
    }
}

void func_80011CAC(Task *task, Obj *obj)
{
    DracamWork *move = DRACAM_WORK(task);
    Vec3f       eye;

    DRACAM_STEP(move->fovy, move->fovy_target, move->fovy_speed);
    if (move->path_frame < move->path_frames) {
        func_800377F4(&eye, move->path, (float) move->path_frame / move->path_frames);
        func_80012518(task, eye.x, eye.y, eye.z);
        move->path_frame++;
    }
    DRACAM_STEP(move->eye_x, move->eye_x_target, move->eye_x_speed);
    DRACAM_STEP(move->eye_y, move->eye_y_target, move->eye_y_speed);
    DRACAM_STEP(move->eye_z, move->eye_z_target, move->eye_z_speed);
    DRACAM_STEP(move->at_x, move->at_x_target, move->at_x_speed);
    DRACAM_STEP(move->at_y, move->at_y_target, move->at_y_speed);
    DRACAM_STEP(move->at_z, move->at_z_target, move->at_z_speed);
    move->camera->fovy   = move->fovy + 0.5;
    move->camera->eye[0] = move->eye_x;
    move->camera->eye[1] = move->eye_y;
    move->camera->eye[2] = move->eye_z;
    move->camera->at[0]  = move->at_x;
    move->camera->at[1]  = move->at_y;
    move->camera->at[2]  = move->at_z;
    if (move->shake_period) {
        if (move->shake_period < move->shake_timer) {
            if (move->shake_timer <= move->shake_period * 2) {
                move->camera->at[0] += move->shake_x;
                move->camera->eye[0] += move->shake_x;
                move->camera->at[1] += move->shake_y;
                move->camera->eye[1] += move->shake_y;
                move->camera->at[2] += move->shake_z;
                move->camera->eye[2] += move->shake_z;
            } else {
                move->shake_timer = 0;
            }
        }
        move->shake_timer++;
    }
    if (DRACAM_DIST(move->camera->at[0], move->camera->eye[0]) < 1.0f &&
        DRACAM_DIST(move->camera->at[2], move->camera->eye[2]) < 1.0f) {
        move->camera->at[2] += 1.0f;
    }
}

Task *func_80012304(Task *task)
{
    DracamWork *move = DRACAM_WORK(task);

    PRINTF(("dracam_destroy: in \n"));
    if (move->camera != NULL) {
        amemFree(g_sys->memory_blocks, move->camera);
    }
    if (move->path != NULL) {
        amemFree(g_sys->memory_blocks, move->path);
    }
    func_80034EF8(task);
    PRINTF(("dracam_destroy: out \n"));
    return NULL;
}

// Debug print of an unidentified function.
const char D_8007B070[] = "Error: _type_=%d \n";

int func_80012380(Task *task)
{
    DracamWork *move   = DRACAM_WORK(task);
    int         moving = 0;

    if ((1e-05) < move->fovy_speed) {
        moving = DRACAM_MOVING_FOVY;
    }
    if ((1e-05) < move->eye_x_speed) {
        moving |= DRACAM_MOVING_EYE_X;
    }
    if ((1e-05) < move->eye_y_speed) {
        moving |= DRACAM_MOVING_EYE_Y;
    }
    if ((1e-05) < move->eye_z_speed) {
        moving |= DRACAM_MOVING_EYE_Z;
    }
    if ((1e-05) < move->at_x_speed) {
        moving |= DRACAM_MOVING_AT_X;
    }
    if ((1e-05) < move->at_y_speed) {
        moving |= DRACAM_MOVING_AT_Y;
    }
    if ((1e-05) < move->at_z_speed) {
        moving |= DRACAM_MOVING_AT_Z;
    }
    return moving;
}

void func_80012470(Task *task)
{
    DRACAM_WORK(task)->fovy_speed  = 0.0f;
    DRACAM_WORK(task)->eye_x_speed = 0.0f;
    DRACAM_WORK(task)->eye_y_speed = 0.0f;
    DRACAM_WORK(task)->eye_z_speed = 0.0f;
    DRACAM_WORK(task)->at_x_speed  = 0.0f;
    DRACAM_WORK(task)->at_y_speed  = 0.0f;
    DRACAM_WORK(task)->at_z_speed  = 0.0f;
    DRACAM_WORK(task)->path_frame = DRACAM_WORK(task)->path_frames = 0;
}

void func_800124A0(Task *task, float steps)
{
    DRACAM_WORK(task)->steps = steps;
}

void func_800124AC(Task *task, float target)
{
    DracamWork *move = DRACAM_WORK(task);

    move->fovy_target = target;
    move->fovy_speed  = DRACAM_DIST(move->fovy_target, move->fovy) / move->steps;
}

void func_80012500(Task *task, int value)
{
    DRACAM_WORK(task)->fovy_speed = 0.0f;
    DRACAM_WORK(task)->fovy       = value;
}

void func_80012518(Task *task, float x, float y, float z)
{
    DracamWork *move = DRACAM_WORK(task);

    move->eye_x_target = x;
    move->eye_y_target = y;
    move->eye_z_target = z;
    move->eye_x_speed  = DRACAM_DIST(move->eye_x_target, move->eye_x) / move->steps;
    move->eye_y_speed  = DRACAM_DIST(move->eye_y_target, move->eye_y) / move->steps;
    move->eye_z_speed  = DRACAM_DIST(move->eye_z_target, move->eye_z) / move->steps;
}

void func_800125D0(Task *task, int period, float x, float y, float z)
{
    DRACAM_WORK(task)->shake_period = period;
    DRACAM_WORK(task)->shake_x      = x;
    DRACAM_WORK(task)->shake_y      = y;
    DRACAM_WORK(task)->shake_z      = z;
}

void func_800125F0(Task *task, int count, Vec3f *points, float tension, short steps)
{
    DRACAM_WORK(task)->path->type    = 1;
    DRACAM_WORK(task)->path->count   = count;
    DRACAM_WORK(task)->path->tension = tension;
    DRACAM_WORK(task)->path->points  = points;
    DRACAM_WORK(task)->path_frame    = 0;
    DRACAM_WORK(task)->path_frames   = steps;
}

void func_80012628(Task *task, float x, float y, float z)
{
    DracamWork *move = DRACAM_WORK(task);

    move->at_x_target = x;
    move->at_y_target = y;
    move->at_z_target = z;
    move->at_x_speed  = DRACAM_DIST(move->at_x_target, move->at_x) / move->steps;
    move->at_y_speed  = DRACAM_DIST(move->at_y_target, move->at_y) / move->steps;
    move->at_z_speed  = DRACAM_DIST(move->at_z_target, move->at_z) / move->steps;
}

void func_800126E0(Task *task, float x, float z)
{
    DracamWork *move = DRACAM_WORK(task);

    move->at_x_target = x;
    move->at_z_target = z;
    move->at_x_speed  = DRACAM_DIST(move->at_x_target, move->at_x) / move->steps;
    move->at_z_speed  = DRACAM_DIST(move->at_z_target, move->at_z) / move->steps;
}

void func_80012764(Task *task, float y)
{
    DracamWork *move = DRACAM_WORK(task);

    move->at_y_target = y;
    move->at_y_speed  = DRACAM_DIST(move->at_y_target, move->at_y) / move->steps;
}

void func_800127B8(Task *task, float x, float y, float z)
{
    DRACAM_WORK(task)->eye_z_speed = DRACAM_WORK(task)->eye_y_speed = DRACAM_WORK(task)->eye_x_speed = 0.0f;
    DRACAM_WORK(task)->eye_x                                                                         = x;
    DRACAM_WORK(task)->eye_y                                                                         = y;
    DRACAM_WORK(task)->eye_z                                                                         = z;
}

void func_800127E8(Task *task, float y)
{
    DRACAM_WORK(task)->eye_y       = y;
    DRACAM_WORK(task)->eye_y_speed = 0.0f;
}

void func_800127FC(Task *task, float *x, float *y, float *z)
{
    *x = DRACAM_WORK(task)->eye_x;
    *y = DRACAM_WORK(task)->eye_y;
    *z = DRACAM_WORK(task)->eye_z;
}

void func_80012818(Task *task, float x, float y, float z)
{
    DRACAM_WORK(task)->at_z_speed = DRACAM_WORK(task)->at_y_speed = DRACAM_WORK(task)->at_x_speed = 0.0f;
    DRACAM_WORK(task)->at_x                                                                       = x;
    DRACAM_WORK(task)->at_y                                                                       = y;
    DRACAM_WORK(task)->at_z                                                                       = z;
}

void func_80012848(Task *task, float y)
{
    DRACAM_WORK(task)->at_y       = y;
    DRACAM_WORK(task)->at_y_speed = 0.0f;
}

void func_8001285C(Task *task, float *x, float *y, float *z)
{
    *x = DRACAM_WORK(task)->at_x;
    *y = DRACAM_WORK(task)->at_y;
    *z = DRACAM_WORK(task)->at_z;
}

void func_80012878(Task *task, AnimeCamera *key)
{
    *DRACAM_WORK(task)->camera = *key;
    func_800127B8(task, key->eye[0], key->eye[1], key->eye[2]);
    func_80012818(task, key->at[0], key->at[1], key->at[2]);
    func_80012500(task, key->fovy);
}

void func_80012900(Task *task, AnimeCamera *out)
{
    *out = *DRACAM_WORK(task)->camera;
}

AnimeCamera *func_80012938(Task *task)
{
    return DRACAM_WORK(task)->camera;
}

Task *func_80012940(Task *task, int draw_list)
{
    Task       *cam = func_80034E08(task, func_80011CAC, 0);
    DracamWork *move;
    ObjSolid   *node;

    PRINTF(("dracam_create\n"));
    if (cam == NULL) {
        return NULL;
    }
    move         = DRACAM_WORK(cam);
    move->camera = amemAlloc(g_sys->memory_blocks, sizeof(AnimeCamera));
    if (move->camera == NULL) {
        PRINTF(("Error: out of memory in dracam_create\n"));
        func_80012304(cam);
        return NULL;
    }
    *move->camera = D_80063740;
    move->path    = amemAlloc(g_sys->memory_blocks, sizeof(SplinePath));
    if (move->path == NULL) {
        PRINTF(("Error: out of memory in dracam_create\n"));
        func_80012304(cam);
        return NULL;
    }
    node = func_80035EEC(cam, OBJ_KIND_SOLID, 1);
    if (node == NULL) {
        PRINTF(("Error: in dracam_create\n"));
        return NULL;
    }
    node->header.kind = OBJ_KIND_SOLID;
    node->AModel      = (unsigned int) move->camera + ANIME_KIND_CAMERA;
    node->sx = node->sy = node->sz = 1.0f;
    node->header.pri               = draw_list;
    move->eye_z = move->eye_y = 100.0f;
    move->eye_x               = 0.0f;
    move->at_z = move->at_y = move->at_x = 0.0f;
    move->fovy                           = 2560.0f;
    move->steps                          = 20.0f;
    PRINTF(("dracam_create end\n"));
    return cam;
}

void func_80012AD8(Task *task, Obj *obj)
{
    DraligWork *move = DRALIG_WORK(task);
    Vec3f       dir;

    DRACAM_STEP(move->dir_x, move->dir_x_target, move->dir_x_speed);
    DRACAM_STEP(move->dir_y, move->dir_y_target, move->dir_y_speed);
    DRACAM_STEP(move->dir_z, move->dir_z_target, move->dir_z_speed);
    DRACAM_STEP(move->r, move->r_target, move->r_speed);
    DRACAM_STEP(move->g, move->g_target, move->g_speed);
    DRACAM_STEP(move->b, move->b_target, move->b_speed);
    DRACAM_STEP(move->ambient_r, move->ambient_r_target, move->ambient_r_speed);
    DRACAM_STEP(move->ambient_g, move->ambient_g_target, move->ambient_g_speed);
    DRACAM_STEP(move->ambient_b, move->ambient_b_target, move->ambient_b_speed);
    dir.x = move->dir_x;
    dir.y = move->dir_y;
    dir.z = move->dir_z;
    if ((dir.x < 0.0f ? -dir.x : dir.x) < 0.01 && (dir.y < 0.0f ? -dir.y : dir.y) < 0.01 &&
        (dir.z < 0.0f ? -dir.z : dir.z) < 0.01) {
        dir.z = 1.0f;
    }
    func_8001D394(&dir);
    move->light_dir[0]   = dir.x * 125.0f;
    move->light_dir[1]   = dir.y * 125.0f;
    move->light_dir[2]   = dir.z * 125.0f;
    move->light_col[0]   = move->r;
    move->light_col[1]   = move->g;
    move->light_col[2]   = move->b;
    move->ambient_col[0] = move->ambient_r;
    move->ambient_col[1] = move->ambient_g;
    move->ambient_col[2] = move->ambient_b;
}

void func_800133D4(Task *task, float steps)
{
    DRALIG_WORK(task)->steps = steps;
}

void func_800133E0(Task *task, float x, float y, float z)
{
    DRALIG_WORK(task)->dir_x = x;
    DRALIG_WORK(task)->dir_y = y;
    DRALIG_WORK(task)->dir_z = z;
}

void func_80013400(Task *task, unsigned char r, unsigned char g, unsigned char b)
{
    DRALIG_WORK(task)->r = r;
    DRALIG_WORK(task)->g = g;
    DRALIG_WORK(task)->b = b;
}

void func_80013484(Task *task, unsigned char r, unsigned char g, unsigned char b)
{
    DRALIG_WORK(task)->ambient_r = r;
    DRALIG_WORK(task)->ambient_g = g;
    DRALIG_WORK(task)->ambient_b = b;
}

void func_80013508(Task *task)
{
    task->obj_tail->kind |= OBJ_HIDDEN;
}

void func_8001351C(Task *task, float x, float y, float z)
{
    DraligWork *move = DRALIG_WORK(task);

    move->dir_x_target = x;
    move->dir_y_target = y;
    move->dir_z_target = z;
    move->dir_x_speed  = DRACAM_DIST(move->dir_x_target, move->dir_x) / move->steps;
    move->dir_y_speed  = DRACAM_DIST(move->dir_y_target, move->dir_y) / move->steps;
    move->dir_z_speed  = DRACAM_DIST(move->dir_z_target, move->dir_z) / move->steps;
}

void func_800135D4(Task *task, unsigned char r, unsigned char g, unsigned char b)
{
    DraligWork *move = DRALIG_WORK(task);

    move->r_target = r;
    move->g_target = g;
    move->b_target = b;
    move->r_speed  = DRACAM_DIST(move->r_target, move->r) / move->steps;
    move->g_speed  = DRACAM_DIST(move->g_target, move->g) / move->steps;
    move->b_speed  = DRACAM_DIST(move->b_target, move->b) / move->steps;
}

void func_800136F8(Task *task, unsigned char r, unsigned char g, unsigned char b)
{
    DraligWork *move = DRALIG_WORK(task);

    move->ambient_r_target = r;
    move->ambient_g_target = g;
    move->ambient_b_target = b;
    move->ambient_r_speed  = DRACAM_DIST(move->ambient_r_target, move->ambient_r) / move->steps;
    move->ambient_g_speed  = DRACAM_DIST(move->ambient_g_target, move->ambient_g) / move->steps;
    move->ambient_b_speed  = DRACAM_DIST(move->ambient_b_target, move->ambient_b) / move->steps;
}

// Debug print of an unidentified function.
const char D_8007B114[] = "Error: _type_=%d \n";

Task *func_8001381C(Task *task, int draw_list)
{
    Task       *light = func_80034E08(task, func_80012AD8, 0);
    DraligWork *move;
    ObjSolid   *node;

    if (light == NULL) {
        return NULL;
    }
    move            = DRALIG_WORK(light);
    move->dir_x     = 100.0f;
    move->dir_y     = 100.0f;
    move->dir_z     = 100.0f;
    move->r         = 255.0f;
    move->g         = 255.0f;
    move->b         = 255.0f;
    move->ambient_r = 96.0f;
    move->ambient_g = 96.0f;
    move->ambient_b = 96.0f;
    move->steps     = 20.0f;
    node            = func_80035EEC(light, OBJ_KIND_SOLID, 1);
    if (node == NULL) {
        PRINTF(("Error: in atlas_create\n"));
        return NULL;
    }
    node->header.kind = OBJ_KIND_SOLID;
    node->AModel      = (unsigned int) move->light_dir + ANIME_KIND_LIGHT;
    node->header.pri  = draw_list;
    node              = func_80035EEC(light, OBJ_KIND_SOLID, 1);
    if (node == NULL) {
        PRINTF(("Error: in atlas_create\n"));
        return NULL;
    }
    node->header.kind = OBJ_KIND_SOLID;
    node->AModel      = (unsigned int) move->ambient_col + ANIME_KIND_AMBIENT;
    node->header.pri  = draw_list;
    PRINTF(("dralig_create end\n"));
    return light;
}
