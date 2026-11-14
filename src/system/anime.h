#ifndef ANIME_H
#define ANIME_H


#include "common.h"
#include "system/object.h"
#include "unk.h"

#define ANIME_REF_SOLID(solid, v)                                                                           \
    ((s_anime_ref = (v))                                                                                    \
            ? ((s_anime_ref & 0x80000000) ? s_anime_ref                                                     \
                  : (s_anime_ref > 0x08000000)                                                              \
                      ? (solid)->SegWave[((s_anime_ref >> 24) & 0xF) - 8].data + (s_anime_ref & 0x80FFFFFF) \
                      : (solid)->SegWave[0].data + (s_anime_ref & 0x80FFFFFF))                              \
            : 0)

#define ANIME_REF(v) ANIME_REF_SOLID(g_anime_solid, v)

#define KEY(i) (s_anime_keys[i])

#define JOINT_AT(j, i) ((AnimeJoint *) ((int) (j) + (i) * 0x18))

#define NEG_IF_HALF_TURN(ra, rb, c) ((ra) == 0x8000 || (rb) == 0x8000 ? -(c) : 0.0f)

typedef enum AnimeKind {
    ANIME_KIND_DEMO    = 0x00000000,
    ANIME_KIND_ANIME   = 0x10000000,
    ANIME_KIND_CAMERA  = 0x20000000,
    ANIME_KIND_LIGHT   = 0x30000000,
    ANIME_KIND_MODEL   = 0x40000000,
    ANIME_KIND_AMBIENT = 0x50000000,
    ANIME_KIND_JCHAR   = 0x60000000,
    ANIME_KIND_JMODEL  = 0x70000000
} AnimeKind;

typedef struct AnimeCamera {
    /* 0x00 */ float          eye[3];
    /* 0x0C */ float          at[3];
    /* 0x18 */ unsigned short roll;
    /* 0x1A */ unsigned short fovy;
    /* 0x1C */ float          near;
    /* 0x20 */ float          far;
    /* 0x24 */ float          light[6];
    /* 0x3C */ unsigned char  tex_w;
    /* 0x3D */ unsigned char  tex_h;
    /* 0x3E */ unsigned char  flags;
    /* 0x3F */ unsigned char  unk_3f;
    /* 0x40 */ Vp            *vp;
    /* 0x44 */ int            clip;
    /* 0x48 */ short          scissor0;
    /* 0x4A */ short          scissor1;
    /* 0x4C */ short          scissor2;
    /* 0x4E */ short          scissor3;
    /* 0x50 */ float          left;
    /* 0x54 */ float          top;
    /* 0x58 */ float          right;
    /* 0x5C */ float          bottom;
} AnimeCamera; // size = 0x60

typedef struct AnimeCameraKeys {
    /* 0x00 */ unsigned short eye[3];
    /* 0x06 */ unsigned short at[3];
    /* 0x0C */ unsigned short roll;
    /* 0x0E */ unsigned short fovy;
    /* 0x10 */ unsigned short near;
    /* 0x12 */ unsigned short far;
} AnimeCameraKeys; // size = 0x14

typedef struct AnimeAmbient {
    /* 0x00 */ unsigned char col[3];
    /* 0x03 */ unsigned char keep;
} AnimeAmbient; // size = 0x4

typedef struct AnimeLight {
    /* 0x00 */ signed char   dir[3];
    /* 0x03 */ unsigned char col[3];
} AnimeLight; // size = 0x6

typedef struct AnimeLightKeys {
    /* 0x00 */ unsigned short dir[3];
    /* 0x06 */ unsigned short col[3];
} AnimeLightKeys; // size = 0xC

typedef struct AnimeJoint {
    /* 0x00 */ unsigned int   model;
    /* 0x04 */ signed char    child;
    /* 0x05 */ signed char    sibling;
    /* 0x06 */ unsigned short sx, sy, sz;
    /* 0x0C */ unsigned short rx, ry, rz;
    /* 0x12 */ unsigned short tx, ty, tz;
} AnimeJoint; // size = 0x18

typedef struct AnimeMtx {
    /* 0x00 */ float m[4][4];
} AnimeMtx; // size = 0x40

void anime_init_frame(void);
void anime_commit_lights(void);
int  anime_draw(ObjSolid *solid);

void           anime_camera_keys(AnimeCameraKeys *keys, float (*mf)[4]);
void           anime_camera(AnimeCamera *cam, float (*mf)[4]);
void           anime_light_keys(AnimeLightKeys *keys);
void           anime_ambient(AnimeAmbient *ambient);
void           anime_light(AnimeLight *light);
void           anime_draw_root(AnimeJoint *joint, unsigned int kind);
void           anime_draw_joint(AnimeJoint *joint);
void           anime_jchar(AnimeJoint *joint, unsigned int kind, ObjSolid *model_node);
void           anime_draw_jchar_joint(AnimeJoint *joint, ObjSolid *solid);
ObjSolid      *anime_child_node(AnimeJoint *joint, ObjSolid *solid);
ObjSolid      *anime_sibling_node(AnimeJoint *joint, ObjSolid *solid);
int            anime_delete_model_node(ObjSolid *solid, unsigned int model);
int            anime_delete_model_in(ObjSolid *solid, unsigned int model);
void           anime_push_joint(AnimeJoint *joint, ObjSolid *solid);
void           anime_mtx_set_scale(float (*mf)[4], float scale);
void           anime_pop_joint(void);
void           anime_model(unsigned int dlist);
void           anime_push_solid(ObjSolid *solid);
void           anime_joint_mtx(float (*mf)[4], AnimeJoint *joint, ObjSolid *solid);
unsigned short anime_key_u16(unsigned short track);
short          anime_key_s16(unsigned short track);
unsigned short anime_key_angle(unsigned short track);
void           anime_key_rot(AnimeJoint *joint, unsigned short *rot);
unsigned short anime_key_decode(unsigned short pos, int frame_a, short *out_a, int frame_b);
float          anime_frame_count(ObjSolid *solid);
void           anime_set_default_ambient(unsigned char r, unsigned char g, unsigned char b);
void           anime_set_view(AnimeCamera *cam);
int            anime_spawn_parts(void *arg0, ObjSolid *src);
int            anime_locate_joint(ObjSolid *out, ObjSolid *solid, int target);
int            anime_locate_joint_at(ObjSolid *out, ObjSolid *solid, unsigned int model, float frame, float blend, int target);
int            anime_find_joint_path(AnimeJoint *joint, unsigned int target, int depth, ObjSolid *solid);
int            anime_swap_models(ObjSolid *target_solid, unsigned int model, unsigned int *table);
int            anime_swap_joint_models(AnimeJoint *joint, unsigned int *table, ObjSolid *solid);
void           anime_view_to_local(ObjSolid *solid);

extern ObjSolid *g_anime_solid;

#endif // ANIME_H
