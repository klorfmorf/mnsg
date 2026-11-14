#include "system/anime.h"
#include "gbi.h"
#include "gfx_util.h"
#include "heap.h"
#include "math_util.h"
#include "sys.h"

extern Gfx D_9002410[];

Vp g_anime_default_vp = { { { 640, 480, G_MAXZ / 2, 0 }, { 640, 480, G_MAXZ / 2, 0 } } };

AnimeCamera s_anime_default_camera = {
    { 0.0f, 0.0f, 400.0f },
    { 0.0f, 0.0f, 0.0f },
    0,
    0x80,
    100.0f,
    5000.0f,
    { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    32, 32, 0, 0,
    &g_anime_default_vp,
    3,
    0, 0, 320, 240,
    -160.0f, -120.0f, 160.0f, 120.0f
};

Gfx    *s_anime_proxy_dlists[] = { D_9002410, NULL };
Lights7 s_anime_default_lights = { 0 };
Gfx     s_anime_gfx_end        = gsSPEndDisplayList();
Gfx     s_anime_gfx_branch     = gsSPBranchList(NULL);

ObjSolid      *g_anime_solid;
AnimeCamera   *s_anime_camera;
Lights7       *s_anime_lights;
int            D_801684AC;
float          s_anime_mtx[4][4];
unsigned int   s_anime_ref;
unsigned char  s_anime_vp_count;
int            s_anime_light_next;
int            s_anime_light_count;
Vp            *s_anime_vp_pool;
Mtx           *s_anime_mtx_pool;
LookAt        *s_anime_lookat_pool;
Hilite        *s_anime_hilite_pool;
float          s_anime_frame;
float          s_anime_blend;
float          s_anime_frame_total;
int            s_anime_local;
unsigned char *s_anime_keys;
int            s_anime_solid_ready;
Gfx           *s_anime_init_glist;
unsigned char  s_anime_proxy;
unsigned char  s_anime_rsp_mtx;
float (*s_anime_mtx_top)[4][4];
int            D_80168534;
float          s_anime_mtx_stack[16][4][4];
float          s_anime_world_mtx[4][4];
Mtx           *s_anime_proxy_mtx;
ObjSolid      *s_anime_found_solid;
float          s_anime_view_x;
float          s_anime_view_y;
float          s_anime_view_z;
unsigned short s_anime_view_roll;
AnimeJoint    *s_anime_path_joint[10];
ObjSolid      *s_anime_path_solid[10];
int            s_anime_root_countdown;
int            s_anime_joint_countdown;

extern unsigned short D_801689F0;
extern unsigned short D_801689F2;
extern unsigned short D_801689F4;

extern Gfx D_8005588[];
extern Gfx D_8006DFF8[];
extern Gfx D_8006E020[];
extern Gfx D_9004958[];
extern Gfx D_9004A88[];
extern Gfx D_9004AA8[];
extern Gfx D_90050F8[];
extern Gfx D_90056E8[];

void anime_init_frame(void)
{
    g_sys->clear_depth_buffer = 1;
    s_anime_light_count = s_anime_light_next = 0;
    s_anime_init_glist                       = NULL;
    s_anime_camera                           = NULL;
    s_anime_vp_count                         = 0;
    s_anime_mtx_pool                         = g_sys->graphics_buffer[g_sys->current_graphics_pool].matrices;
    s_anime_vp_pool                          = g_sys->graphics_buffer[g_sys->current_graphics_pool].viewports;
    s_anime_lights                           = g_sys->graphics_buffer[g_sys->current_graphics_pool].lights;
    s_anime_lookat_pool                      = g_sys->graphics_buffer[g_sys->current_graphics_pool].look_ats;
    s_anime_hilite_pool                      = g_sys->graphics_buffer[g_sys->current_graphics_pool].hilites;
    *s_anime_lights                          = s_anime_default_lights;
}

void anime_commit_lights(void)
{
    int i;

    if (s_anime_camera == NULL) {
        func_8001E444(s_anime_mtx, 0, 0, 0);
        anime_camera(&s_anime_default_camera, s_anime_mtx);
    }

    if (s_anime_light_next >= 0) {
        if (s_anime_light_next == 0) {
            s_anime_light_next++;
        }

        s_anime_light_count = s_anime_light_next;

        gDPPipeSync(D_8015C5CC++);
        gSPSetGeometryMode(D_8015C5CC++, G_LIGHTING);
        gSPNumLights(D_8015C5CC++, s_anime_light_count);

        for (i = 0; i < s_anime_light_count; i++) {
            gSPLight(D_8015C5CC++, &s_anime_lights->l[i], i + 1);
        }

        gSPLight(D_8015C5CC++, &s_anime_lights->a, s_anime_light_count + 1);
    }

    s_anime_light_next = -1;
}

int anime_draw(ObjSolid *solid)
{
    unsigned int script;
    unsigned int hdr;
    unsigned int kind;
    unsigned int camera_keys;
    unsigned int light_keys;
    unsigned int root;
    unsigned int jchar_root;
    unsigned int cameras_left;
    unsigned int lights_left;
    unsigned int roots_left;
    unsigned int camera_count;

    if (solid->hidden & 1) {
        return 0;
    }

    if (solid->disabled < 0) {
        return 0;
    }

    g_anime_solid = solid;

    if (solid->rx != 0x8000) {
        solid->rx &= 0x3FF;
    }

    if (solid->ry != 0x8000) {
        solid->ry &= 0x3FF;
    }

    if (solid->rz != 0x8000) {
        solid->rz &= 0x3FF;
    }

    script = g_anime_solid->AModel;

    if (script == 0 || (script & 0x8FFFFFFE) == 0) {
        if (g_anime_solid->sibling != NULL || g_anime_solid->child != NULL) {
            func_800364FC(g_anime_solid);
        }

        return 0;
    }

    kind = script & 0x70000000;

    s_anime_rsp_mtx     = 1;
    s_anime_solid_ready = 0;
    s_anime_proxy       = script & 1;

    if (s_anime_proxy) {
        s_anime_rsp_mtx = 0;
    }

    switch (kind) {
        case ANIME_KIND_DEMO:
        case ANIME_KIND_ANIME:
            script = ANIME_REF(script & 0x8FFFFFFE);

            hdr = *(unsigned int *) script;

            if (hdr == 0) {
                return 0;
            }

            script += 4;

            s_anime_local       = (hdr / 0x80000000) & 1;
            s_anime_frame_total = hdr & 0xFF;
            s_anime_frame       = g_anime_solid->time;
            s_anime_keys        = (unsigned char *) ANIME_REF(*(unsigned int *) script);

            script += 4;

            camera_count = (hdr >> 28) & 7;

            if (camera_count != 0) {
                func_8001E380(s_anime_mtx, g_anime_solid);

                for (cameras_left = camera_count; cameras_left--;) {
                    camera_keys = ANIME_REF(*(unsigned int *) script);
                    script += 4;

                    if (camera_keys == 0) {
                        return 0;
                    }

                    anime_camera_keys((AnimeCameraKeys *) camera_keys, s_anime_mtx);
                }
            }

            if ((hdr >> 24) & 0xF) {
                for (lights_left = (hdr >> 24) & 0xF; lights_left--;) {
                    light_keys = ANIME_REF(*(unsigned int *) script);
                    script += 4;

                    if (light_keys == 0) {
                        return 0;
                    }

                    anime_light_keys((AnimeLightKeys *) light_keys);
                }
            }

            if ((hdr >> 8) & 0x7FFF) {
                anime_commit_lights();
                anime_push_solid(g_anime_solid);

                for (roots_left = (hdr >> 8) & 0x7FFF; roots_left--;) {
                    root = ANIME_REF(*(unsigned int *) script);
                    script += 4;

                    if (root != 0) {
                        anime_draw_root((AnimeJoint *) root, kind);
                    }
                }

                gSPPopMatrix(D_8015C5CC++, G_MTX_MODELVIEW);
            }

            break;

        case ANIME_KIND_CAMERA:
            func_8001E380(s_anime_mtx, g_anime_solid);
            anime_camera((AnimeCamera *) (script & 0x8FFFFFFE), s_anime_mtx);
            anime_set_view((AnimeCamera *) ANIME_REF(script & 0x8FFFFFFE));
            break;

        case ANIME_KIND_AMBIENT:
            anime_ambient((AnimeAmbient *) ANIME_REF(script & 0x8FFFFFFE));
            break;

        case ANIME_KIND_LIGHT:
            anime_light((AnimeLight *) ANIME_REF(script & 0x8FFFFFFE));
            break;

        case ANIME_KIND_MODEL:
            anime_commit_lights();
            anime_push_solid(g_anime_solid);
            anime_model(g_anime_solid->AModel & 0x8FFFFFFE);
            gSPPopMatrix(D_8015C5CC++, G_MTX_MODELVIEW);
            break;

        case ANIME_KIND_JCHAR:
            script = ANIME_REF(script & 0x8FFFFFFE);
            hdr    = *(unsigned int *) script;

            if (hdr == 0) {
                return 0;
            }

            script += 4;

            s_anime_local       = (hdr / 0x80000000) & 1;
            s_anime_frame_total = hdr & 0xFF;
            s_anime_frame       = g_anime_solid->time;
            s_anime_blend       = g_anime_solid->blend;

            script += 4;

            s_anime_keys = (unsigned char *) ANIME_REF(((unsigned int *) script)[-1]);

            anime_commit_lights();
            anime_push_solid(g_anime_solid);

            if (s_anime_local != 0) {
                jchar_root = ANIME_REF(*(unsigned int *) script);
                anime_jchar((AnimeJoint *) jchar_root, kind, g_anime_solid->child);
            } else {
                PRINTF(("anime.c: This isn't Local Model!!\n"));
            }

            if (g_anime_solid->blend != 0.0f) {
                g_anime_solid->blend -= 1.0f;
            }

            gSPPopMatrix(D_8015C5CC++, G_MTX_MODELVIEW);
            break;

        case ANIME_KIND_JMODEL:
            break;
    }

    return 1;
}

void anime_camera_keys(AnimeCameraKeys *keys, float (*mf)[4])
{
    unsigned short roll;
    unsigned short persp_norm;
    Mtx           *projection;
    Mtx           *look;
    Mtx           *ident;
    Mtx           *world;

    projection = s_anime_mtx_pool++;
    look       = s_anime_mtx_pool++;
    ident      = s_anime_mtx_pool++;
    world      = s_anime_mtx_pool++;

    roll = anime_key_angle(keys->roll);

    if (s_anime_camera == NULL) {
        s_anime_camera = &s_anime_default_camera;
    }

    if (s_anime_camera->vp != NULL) {
        s_anime_vp_pool[s_anime_vp_count] = *s_anime_camera->vp;
        gSPViewport(D_8015C5CC++, &s_anime_vp_pool[s_anime_vp_count]);
        s_anime_vp_count++;

        if (s_anime_vp_count >= 5) {
            PRINTF(("ERROR!! out of buffer Tvp in lt_sys.h\n"));
        }
    } else {
        gSPViewport(D_8015C5CC++, &g_anime_default_vp);
    }

    if (!(s_anime_camera->flags & 1)) {
        guPerspective(projection, &persp_norm, (2 * (float) (unsigned int) anime_key_angle(keys->fovy) * 180.0f) / 32768.0f, 1.3333334f,
            (float) (unsigned int) anime_key_u16(keys->near), (float) (unsigned int) anime_key_u16(keys->far), 1.0f);
        gSPPerspNormalize(D_8015C5CC++, persp_norm);
    } else {
        guOrtho(projection, s_anime_camera->left, s_anime_camera->right, s_anime_camera->bottom, s_anime_camera->top, s_anime_camera->near,
            s_anime_camera->far, 1.0f);
    }

    gSPMatrix(D_8015C5CC++, (char *) projection + 0x80000000, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    if (!(s_anime_camera->flags & 1)) {
        guLookAtHilite(look, s_anime_lookat_pool++, s_anime_hilite_pool++,
            (float) anime_key_s16(keys->eye[0]) * 0.03125, (float) anime_key_s16(keys->eye[1]) * 0.03125, (float) anime_key_s16(keys->eye[2]) * 0.03125,
            (float) (short) anime_key_s16(keys->at[0]) * 0.03125, (float) (short) anime_key_s16(keys->at[1]) * 0.03125, (float) (short) anime_key_s16(keys->at[2]) * 0.03125,
            func_80003E10(roll), func_80003EA0(roll), 0.0f,
            s_anime_camera->light[0], s_anime_camera->light[1], s_anime_camera->light[2],
            s_anime_camera->light[3], s_anime_camera->light[4], s_anime_camera->light[5],
            (s8) s_anime_camera->tex_w, (s8) s_anime_camera->tex_h);
        gSPMatrix(D_8015C5CC++, (char *) look + 0x80000000, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    }

    guMtxF2L(mf, world);
    gSPMatrix(D_8015C5CC++, (char *) world + 0x80000000, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    guMtxIdent(ident);
    gSPMatrix(D_8015C5CC++, (unsigned int) ident & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (s_anime_camera->clip != 0) {
        gMoveWd(D_8015C5CC++, G_MW_CLIP, G_MWO_CLIP_RNX, s_anime_camera->clip);
        gMoveWd(D_8015C5CC++, G_MW_CLIP, G_MWO_CLIP_RNY, s_anime_camera->clip);
        gMoveWd(D_8015C5CC++, G_MW_CLIP, G_MWO_CLIP_RPX, 0x10000 - s_anime_camera->clip);
        gMoveWd(D_8015C5CC++, G_MW_CLIP, G_MWO_CLIP_RPY, 0x10000 - s_anime_camera->clip);
    }

    if (s_anime_camera->scissor0 | s_anime_camera->scissor1 | s_anime_camera->scissor2 | s_anime_camera->scissor3) {
        gDPSetScissor(D_8015C5CC++, G_SC_NON_INTERLACE, s_anime_camera->scissor0, s_anime_camera->scissor1, s_anime_camera->scissor2, s_anime_camera->scissor3);
    }
}

void anime_camera(AnimeCamera *cam, float (*mf)[4])
{
    unsigned short roll;
    unsigned short persp_norm;
    Mtx           *projection;
    Mtx           *look;
    Mtx           *ident;
    Mtx           *world;

    projection = s_anime_mtx_pool++;
    look       = s_anime_mtx_pool++;
    ident      = s_anime_mtx_pool++;
    world      = s_anime_mtx_pool++;

    roll = cam->roll;

    s_anime_camera = cam;

    anime_model(0);

    if (s_anime_camera->vp != NULL) {
        s_anime_vp_pool[s_anime_vp_count] = *s_anime_camera->vp;
        gSPViewport(D_8015C5CC++, &s_anime_vp_pool[s_anime_vp_count]);
        s_anime_vp_count++;

        if (s_anime_vp_count >= 5) {
            PRINTF(("ERROR!! out of buffer Tvp in lt_sys.h\n"));
        }
    } else {
        gSPViewport(D_8015C5CC++, &g_anime_default_vp);
    }

    if (!(s_anime_camera->flags & 1)) {
        guPerspective(projection, &persp_norm, (2 * (float) s_anime_camera->fovy * 180.0f) / 32768.0f, 1.3333334f, s_anime_camera->near,
            s_anime_camera->far, 1.0f);
        gSPPerspNormalize(D_8015C5CC++, persp_norm);
    } else {
        guOrtho(projection, s_anime_camera->left, s_anime_camera->right, s_anime_camera->bottom, s_anime_camera->top, s_anime_camera->near,
            s_anime_camera->far, 1.0f);
    }

    gSPMatrix(D_8015C5CC++, (char *) projection + 0x80000000, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    if (!(s_anime_camera->flags & 1)) {
        guLookAtHilite(look, s_anime_lookat_pool++, s_anime_hilite_pool++,
            s_anime_camera->eye[0], s_anime_camera->eye[1], s_anime_camera->eye[2],
            s_anime_camera->at[0], s_anime_camera->at[1], s_anime_camera->at[2],
            func_80003E10(roll), func_80003EA0(roll), 0.0f,
            s_anime_camera->light[0], s_anime_camera->light[1], s_anime_camera->light[2],
            s_anime_camera->light[3], s_anime_camera->light[4], s_anime_camera->light[5],
            (s8) s_anime_camera->tex_w, (s8) s_anime_camera->tex_h);
        gSPMatrix(D_8015C5CC++, (char *) look + 0x80000000, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    }

    guMtxF2L(mf, world);
    gSPMatrix(D_8015C5CC++, (char *) world + 0x80000000, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    guMtxIdent(ident);
    gSPMatrix(D_8015C5CC++, (unsigned int) ident & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (s_anime_camera->clip != 0) {
        gMoveWd(D_8015C5CC++, G_MW_CLIP, G_MWO_CLIP_RNX, s_anime_camera->clip);
        gMoveWd(D_8015C5CC++, G_MW_CLIP, G_MWO_CLIP_RNY, s_anime_camera->clip);
        gMoveWd(D_8015C5CC++, G_MW_CLIP, G_MWO_CLIP_RPX, 0x10000 - s_anime_camera->clip);
        gMoveWd(D_8015C5CC++, G_MW_CLIP, G_MWO_CLIP_RPY, 0x10000 - s_anime_camera->clip);
    }

    if (s_anime_camera->scissor0 | s_anime_camera->scissor1 | s_anime_camera->scissor2 | s_anime_camera->scissor3) {
        gDPSetScissor(D_8015C5CC++, G_SC_NON_INTERLACE, s_anime_camera->scissor0, s_anime_camera->scissor1, s_anime_camera->scissor2, s_anime_camera->scissor3);
    }
}

void anime_light_keys(AnimeLightKeys *keys)
{
    s_anime_lights->l[s_anime_light_next].l.col[0]  = anime_key_s16(keys->col[0]);
    s_anime_lights->l[s_anime_light_next].l.col[1]  = anime_key_s16(keys->col[1]);
    s_anime_lights->l[s_anime_light_next].l.col[2]  = anime_key_s16(keys->col[2]);
    s_anime_lights->l[s_anime_light_next].l.pad1    = 0;
    s_anime_lights->l[s_anime_light_next].l.colc[0] = s_anime_lights->l[s_anime_light_next].l.col[0];
    s_anime_lights->l[s_anime_light_next].l.colc[1] = s_anime_lights->l[s_anime_light_next].l.col[1];
    s_anime_lights->l[s_anime_light_next].l.colc[2] = s_anime_lights->l[s_anime_light_next].l.col[2];
    s_anime_lights->l[s_anime_light_next].l.pad2    = 0;
    s_anime_lights->l[s_anime_light_next].l.dir[0]  = (signed char) (int) (func_80003EA0(anime_key_angle(keys->dir[0])) * 127.0f);
    s_anime_lights->l[s_anime_light_next].l.dir[1]  = (signed char) (int) (func_80003EA0(anime_key_angle(keys->dir[1])) * 127.0f);
    s_anime_lights->l[s_anime_light_next].l.dir[2]  = (signed char) (int) (func_80003EA0(anime_key_angle(keys->dir[2])) * 127.0f);
    s_anime_lights->l[s_anime_light_next].l.pad3    = 0;
    s_anime_light_next++;
}

void anime_ambient(AnimeAmbient *ambient)
{
    if (s_anime_light_next < 0) {
        if (ambient->keep == 0) {
            s_anime_lights[1]  = s_anime_lights[0];
            s_anime_light_next = s_anime_light_count;
        } else {
            s_anime_lights[1]  = s_anime_default_lights;
            s_anime_light_next = 0;
        }

        s_anime_lights++;
    }

    s_anime_lights->a.l.col[0] = s_anime_lights->a.l.colc[0] = ambient->col[0];
    s_anime_lights->a.l.col[1] = s_anime_lights->a.l.colc[1] = ambient->col[1];
    s_anime_lights->a.l.col[2] = s_anime_lights->a.l.colc[2] = ambient->col[2];

    anime_model(0);
}

void anime_light(AnimeLight *light)
{
    s_anime_lights->l[s_anime_light_next].l.col[0]  = light->col[0];
    s_anime_lights->l[s_anime_light_next].l.col[1]  = light->col[1];
    s_anime_lights->l[s_anime_light_next].l.col[2]  = light->col[2];
    s_anime_lights->l[s_anime_light_next].l.pad1    = 0;
    s_anime_lights->l[s_anime_light_next].l.colc[0] = s_anime_lights->l[s_anime_light_next].l.col[0];
    s_anime_lights->l[s_anime_light_next].l.colc[1] = s_anime_lights->l[s_anime_light_next].l.col[1];
    s_anime_lights->l[s_anime_light_next].l.colc[2] = s_anime_lights->l[s_anime_light_next].l.col[2];
    s_anime_lights->l[s_anime_light_next].l.pad2    = 0;
    s_anime_lights->l[s_anime_light_next].l.dir[0]  = light->dir[0];
    s_anime_lights->l[s_anime_light_next].l.dir[1]  = light->dir[1];
    s_anime_lights->l[s_anime_light_next].l.dir[2]  = light->dir[2];
    s_anime_lights->l[s_anime_light_next].l.pad3    = 0;
    s_anime_light_next++;

    anime_model(0);
}

void anime_draw_root(AnimeJoint *joint, unsigned int kind)
{
    AnimeJoint  *subtree;
    unsigned int ref;

    if (kind == ANIME_KIND_DEMO) {
        anime_push_joint(joint, NULL);
    }

    if (!(joint->model & ANIME_KIND_ANIME)) {
        if (joint->model & 0x8FFFFFFF) {
            ref = joint->model & 0x8FFFFFFF;
            anime_model(ref);
        }
    } else {
        ref     = ANIME_REF(joint->model);
        subtree = (AnimeJoint *) (ref & 0x8FFFFFFF);

        if (subtree->model != 0) {
            anime_model(subtree->model);
            anime_pop_joint();
        }

        if (subtree->child != 0) {
            anime_draw_joint(JOINT_AT(subtree, subtree->child));
        }

        if (subtree->sibling != 0) {
            anime_draw_joint(JOINT_AT(subtree, subtree->sibling));
        }
    }

    if (kind == ANIME_KIND_DEMO && ((joint->rx | joint->ry | joint->rz) & 0x4000)) {
        anime_pop_joint();
    }

    if (joint->child) {
        anime_draw_joint(JOINT_AT(joint, joint->child));
    }

    if (joint->sibling) {
        anime_draw_joint(JOINT_AT(joint, joint->sibling));
    }

    if (kind == ANIME_KIND_DEMO) {
        anime_pop_joint();
    }
}

void anime_draw_joint(AnimeJoint *joint)
{
    unsigned int model;
    int          ref;
    AnimeJoint  *subtree;

    anime_push_joint(joint, NULL);

    model = joint->model;

    if (!(model & 0x10000000)) {
        if (model & 0x8FFFFFFF) {
            ref = model & 0x8FFFFFFF;
            anime_model(ref);
        }
    } else {
        ref     = ANIME_REF(model);
        subtree = (AnimeJoint *) (ref & 0x8FFFFFFF);

        if (subtree->model != 0) {
            anime_model(subtree->model);
        }

        if (subtree->child != 0) {
            anime_draw_joint(JOINT_AT(subtree, subtree->child));
        }

        if (subtree->sibling != 0) {
            anime_draw_joint(JOINT_AT(subtree, subtree->sibling));
        }
    }

    if ((joint->rx | joint->ry | joint->rz) & 0x4000) {
        anime_pop_joint();
    }

    if (s_anime_local != 0) {
        if (joint->child != 0) {
            anime_draw_joint(JOINT_AT(joint, joint->child));
        }

        anime_pop_joint();
    } else {
        anime_pop_joint();

        if (joint->child != 0) {
            anime_draw_joint(JOINT_AT(joint, joint->child));
        }
    }

    if (joint->sibling != 0) {
        anime_draw_joint(JOINT_AT(joint, joint->sibling));
    }
}

void anime_jchar(AnimeJoint *joint, unsigned int kind, ObjSolid *model_node)
{
    ObjSolid    *next;
    unsigned int model;

    if (model_node == NULL) {
        model_node           = func_80036448(g_anime_solid);
        model_node->parent   = NULL;
        g_anime_solid->child = model_node;
    } else if (joint->model != model_node->AModel & 0x8FFFFFFE) {
        func_800364FC(g_anime_solid);
        model_node           = func_80036448(g_anime_solid);
        model_node->parent   = NULL;
        g_anime_solid->child = model_node;
    }

    model              = joint->model;
    model_node->AModel = model;

    if (model != 0) {
        anime_model(joint->model);
    }

    if (joint->child != 0) {
        next = anime_child_node(joint, model_node);

        if (next != NULL) {
            anime_draw_jchar_joint(JOINT_AT(joint, joint->child), next);
        }
    } else {
        next = model_node->child;

        if (next != NULL) {
            func_8003674C(model_node);
        }
    }

    if (joint->sibling != 0) {
        next = anime_sibling_node(joint, model_node);

        if (next != NULL) {
            anime_draw_jchar_joint(JOINT_AT(joint, joint->sibling), next);
        }
    } else {
        next = model_node->sibling;

        if (next != NULL) {
            func_80036798(model_node);
        }
    }
}

void anime_draw_jchar_joint(AnimeJoint *joint, ObjSolid *solid)
{
    ObjSolid    *saved_solid;
    ObjSolid    *node;
    ObjSolid    *sibling;
    unsigned int model;
    int          ref;
    AnimeJoint  *subtree;

    saved_solid = g_anime_solid;

    if (solid->init_glist != 0) {
        s_anime_solid_ready = 0;
        g_anime_solid       = solid;
    }

    anime_push_joint(joint, solid);

    model = joint->model;

    if (!(model & 0x10000000)) {
        if (model & 0x8FFFFFFF) {
            ref = model & 0x8FFFFFFF;
            anime_model(ref);
        }
    } else {
        ref     = ANIME_REF(model);
        subtree = (AnimeJoint *) (ref & 0x8FFFFFFF);

        if (subtree->model != 0) {
            anime_model(subtree->model);
        }

        if (subtree->child != 0) {
            anime_draw_jchar_joint(JOINT_AT(subtree, subtree->child), solid);
        }

        if (subtree->sibling != 0) {
            anime_draw_jchar_joint(JOINT_AT(subtree, subtree->sibling), solid);
        }
    }

    if ((joint->rx | joint->ry | joint->rz) & 0x4000) {
        anime_pop_joint();
    }

    if (saved_solid != g_anime_solid) {
        s_anime_solid_ready = 0;
        g_anime_solid       = saved_solid;
    }

    if (joint->child != 0) {
        node = anime_child_node(joint, solid);

        if (node != NULL) {
            anime_draw_jchar_joint(JOINT_AT(joint, joint->child), node);
        }
    } else {
        node = solid->child;

        if (node != NULL) {
            func_8003674C(solid);
        }
    }

    anime_pop_joint();

    if (joint->sibling != 0) {
        node = anime_sibling_node(joint, solid);

        if (node != NULL) {
            anime_draw_jchar_joint(JOINT_AT(joint, joint->sibling), node);
        }
    } else {
        sibling = solid->sibling;

        if (sibling != NULL) {
            func_80036798(solid);
        }
    }
}

ObjSolid *anime_child_node(AnimeJoint *joint, ObjSolid *solid)
{
    unsigned int model;
    ObjSolid    *node;
    ObjSolid    *first;

    node  = solid->child;
    model = joint[joint->child].model & 0x8FFFFFFF;

    if (node == NULL || model != (node->AModel & 0x8FFFFFFE)) {
        first = node;

        if (node != NULL) {
            node = node->sibling;

            while (node != NULL && model != (node->AModel & 0x8FFFFFFE)) {
                node = node->sibling;
            }
        }

        if (node != NULL) {
            func_80036388(solid, node);
        } else {
            anime_delete_model_node(solid, model + ANIME_KIND_JMODEL);
            node         = func_80036448(solid);
            node->parent = solid;
            node->AModel = model + ANIME_KIND_JMODEL;
            solid->child = node;

            if (first != NULL) {
                node->sibling = first;
            }
        }
    }

    return node;
}

ObjSolid *anime_sibling_node(AnimeJoint *joint, ObjSolid *solid)
{
    unsigned int model;
    ObjSolid    *node;
    ObjSolid    *first;

    node  = solid->sibling;
    model = joint[joint->sibling].model & 0x8FFFFFFF;

    if (node == NULL || model != (node->AModel & 0x8FFFFFFE)) {
        first = node;

        if (node != NULL) {
            node = node->sibling;

            while (node != NULL && model != (node->AModel & 0x8FFFFFFE)) {
                node = node->sibling;
            }
        }

        if (node != NULL) {
            func_800363F4(solid, node);
        } else {
            anime_delete_model_node(solid->parent, model + ANIME_KIND_JMODEL);
            node           = func_80036448(solid);
            node->parent   = solid->parent;
            node->AModel   = model + ANIME_KIND_JMODEL;
            solid->sibling = node;

            if (first != NULL) {
                node->sibling = first;
            }
        }
    }

    return node;
}

int anime_delete_model_node(ObjSolid *solid, unsigned int model)
{
    ObjSolid *parent;
    ObjSolid *sibling;

    for (;;) {
        parent = solid->parent;

        if (parent == NULL) {
            return 0;
        }

        sibling = solid->sibling;

        if (sibling != NULL && anime_delete_model_in(sibling, model)) {
            return 1;
        }

        solid = parent;
    }
}

int anime_delete_model_in(ObjSolid *solid, unsigned int model)
{
    ObjSolid *prev = solid->parent;
    ObjSolid *first;
    ObjSolid *next;
    ObjSolid *node;

    if (prev == NULL) {
        return 0;
    }

    if (model == solid->AModel) {
        func_8003674C(solid);

        node = solid->sibling;

        if (node != NULL) {
            first = prev->child;

            if (solid == first) {
                prev->child = node;
            } else {
                next = first->sibling;
                prev = first;

                while (solid != next) {
                    prev = next;
                    next = next->sibling;
                }

                prev->sibling = node;
            }
        } else {
            prev->child = NULL;
        }

        func_800367E4(solid);
        return 1;
    }

    node = solid->child;

    if (node != NULL && anime_delete_model_in(node, model)) {
        return 1;
    }

    node = solid->sibling;

    if (node != NULL && anime_delete_model_in(node, model)) {
        return 1;
    }

    return 0;
}

void anime_push_joint(AnimeJoint *joint, ObjSolid *solid)
{
    Mtx *joint_mtx;
    Mtx *billboard_mtx;
    Mtx *align_mtx;
    float (*parent)[4][4];
    float (*cur)[4][4];
    float (*billboard)[4][4];
    float align_mf[4][4];

    if (s_anime_mtx_top > s_anime_mtx_stack) {
        parent = s_anime_mtx_top - 1;
    } else {
        parent = NULL;
    }

    cur = s_anime_mtx_top++;

    anime_joint_mtx(*cur, joint, solid);

    if (s_anime_rsp_mtx) {
        joint_mtx = s_anime_mtx_pool++;
        func_8001F5F8(*cur, joint_mtx);
        gSPMatrix(D_8015C5CC++, (unsigned int) joint_mtx & 0x1FFFFFFF, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    } else {
        if (parent != NULL) {
            func_8001F2D8(*parent, *cur);
        }

        *(AnimeMtx *) s_anime_world_mtx = *(AnimeMtx *) cur;
    }

    if ((joint->rx | joint->ry | joint->rz) & 0x4000) {
        billboard = s_anime_mtx_top++;

        func_8001E634(*billboard,
            (joint->rx & 0x4000) ? D_801689F0 : 0,
            (joint->ry & 0x4000) ? D_801689F2 : 0,
            (joint->rz & 0x4000) ? D_801689F4 : 0);

        guAlignF(align_mf, 0,
            ((joint->ry & 0x4000) || (joint->rz & 0x4000)) ? -s_anime_view_x : 0.0f,
            ((joint->rz & 0x4000) || (joint->rx & 0x4000)) ? -s_anime_view_y : 0.0f,
            ((joint->rx & 0x4000) || (joint->ry & 0x4000)) ? -s_anime_view_z : 0.0f);

        if (s_anime_rsp_mtx) {
            billboard_mtx = s_anime_mtx_pool++;
            func_8001F5F8(*billboard, billboard_mtx);
            gSPMatrix(D_8015C5CC++, (unsigned int) billboard_mtx & 0x1FFFFFFF, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

            align_mtx = s_anime_mtx_pool++;
            func_8001F5F8(align_mf, align_mtx);
            gSPMatrix(D_8015C5CC++, (unsigned int) align_mtx & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            return;
        }

        func_8001F2D8(*cur, *billboard);
        func_8001F2D8(*billboard, align_mf);
        *(AnimeMtx *) s_anime_world_mtx = *(AnimeMtx *) align_mf;
    }
}

void anime_mtx_set_scale(float (*mf)[4], float scale)
{
    mf[0][1] = mf[0][2] = mf[0][3] = mf[1][0] = mf[1][2] = mf[1][3] = mf[2][0] = mf[2][1] = mf[2][3] = 0.0f;
    mf[0][0] = mf[1][1] = mf[2][2] = scale;
    mf[3][3]                       = 1.0f;
}

void anime_pop_joint(void)
{
    s_anime_mtx_top--;

    if (s_anime_rsp_mtx) {
        gSPPopMatrix(D_8015C5CC++, G_MTX_MODELVIEW);
    }
}

void anime_model(unsigned int dlist)
{
    Gfx          end    = s_anime_gfx_end;
    Gfx          branch = s_anime_gfx_branch;
    unsigned int start  = 0;
    unsigned int stop   = 0;
    Gfx         *patch  = NULL;
    Gfx         *copy   = NULL;
    int          seg;
    float        scale;

    if ((dlist & 0x0FFFFF00) == 0x0FFFFF00) {
        return;
    }

    seg = -1;
    if (s_anime_solid_ready == 0) {
        while (++seg < 6) {
            if (g_anime_solid->SegWave[seg].data != 0) {
                gSPSegment(D_8015C5CC++, seg + 8, (char *) g_anime_solid->SegWave[seg].data + 0x80000000);
            }
        }

        if ((g_anime_solid->init_glist & 0x40000000) || (g_anime_solid->init_glist & 0x8FFFFFFF) != (unsigned int) s_anime_init_glist) {
            if ((g_anime_solid->init_glist & 0x8FFFFFFF) != 0) {
                s_anime_init_glist = (Gfx *) (g_anime_solid->init_glist & 0x8FFFFFFF);

                if (g_anime_solid->init_glist & 0x20000000) {
                    for (; end.force_structure_alignment != s_anime_init_glist->force_structure_alignment; D_8015C5CC++, s_anime_init_glist++) {
                        *D_8015C5CC = *s_anime_init_glist;

                        if (branch.words.w0 == s_anime_init_glist->words.w0) {
                            start = (unsigned int) s_anime_init_glist;
                            patch = D_8015C5CC;
                            stop  = s_anime_init_glist->words.w1;
                        }

                        if (stop != 0 && stop == (unsigned int) s_anime_init_glist) {
                            copy = D_8015C5CC;
                            gSPBranchList(patch, D_8015C5CC);
                        }

                        if (copy != NULL && *(signed char *) s_anime_init_glist == G_VTX) {
                            if (s_anime_init_glist->words.w1 >= start && s_anime_init_glist->words.w1 < stop) {
                                D_8015C5CC->words.w1 = D_8015C5CC->words.w1 + (unsigned int) patch - start;
                            }
                        }
                    }
                } else {
                    gSPDisplayList(D_8015C5CC++, s_anime_init_glist);
                }
            } else {
                gDPPipeSync(D_8015C5CC++);
            }
        } else {
            gDPPipeSync(D_8015C5CC++);
        }

        if (g_anime_solid->init_glist & 0x10000000) {
            gSPLookAtX(D_8015C5CC++, s_anime_lookat_pool - 1);
            gSPLookAtY(D_8015C5CC++, (char *) s_anime_lookat_pool - 0x10);
        }
    } else {
        gDPPipeSync(D_8015C5CC++);
    }

    if (dlist == 0) {
        return;
    }

    s_anime_solid_ready = 1;

    if (s_anime_rsp_mtx) {
        gSPDisplayList(D_8015C5CC++, dlist);
    } else if (s_anime_mtx_top > s_anime_mtx_stack) {
        scale = 1.0f;

        if ((D_801FC61C_5B852C == g_anime_solid && D_801FC604_5B8514 != NULL && ((D_801FC604_5B8514->unk_60 == 0 && dlist == (unsigned int) D_90050F8) || (D_801FC604_5B8514->unk_60 == 1 && dlist == (unsigned int) D_90056E8) || (D_801FC604_5B8514->unk_60 == 2 && dlist == (unsigned int) D_9004AA8) || (D_801FC604_5B8514->unk_60 == 3 && dlist == (unsigned int) D_9004A88))) || (g_anime_solid->SegWave[0].wave_no == 0x4D9 && dlist == (unsigned int) D_8005588) || dlist == (unsigned int) D_8006DFF8) {
            scale = 2.5f;
        } else if ((D_801FC61C_5B852C == g_anime_solid && D_801FC604_5B8514 != NULL && D_801FC604_5B8514->unk_60 == 3 && dlist == (unsigned int) D_9004958) || dlist == (unsigned int) D_8006E020) {
            scale = 2.0f;
        }

        s_anime_proxy_mtx = s_anime_mtx_pool++;

        if (s_anime_proxy) {
            anime_mtx_set_scale(s_anime_world_mtx, scale);
        }

        func_8001F5F8(s_anime_world_mtx, s_anime_proxy_mtx);
        gSPMatrix(D_8015C5CC++, (unsigned int) s_anime_proxy_mtx & 0x1FFFFFFF, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gSPDisplayList(D_8015C5CC++, s_anime_proxy_dlists[g_anime_solid->work[0x13]]);
        gSPPopMatrix(D_8015C5CC++, G_MTX_MODELVIEW);
    } else {
        gSPDisplayList(D_8015C5CC++, s_anime_proxy_dlists[g_anime_solid->work[0x13]]);
    }

    if (g_anime_solid->init_glist & 0x40000000) {
        gSPNumLights(D_8015C5CC++, s_anime_light_count);
        gSPLight(D_8015C5CC++, &s_anime_lights->a, s_anime_light_count + 1);
    }
}

void anime_push_solid(ObjSolid *solid)
{
    float mf[4][4];
    Mtx  *mtx;

    func_8001E2BC(mf, solid);

    mtx = s_anime_mtx_pool++;
    func_8001F5F8(mf, mtx);
    gSPMatrix(D_8015C5CC++, (unsigned int) mtx & 0x1FFFFFFF, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (solid->rx == 0x8000 || solid->ry == 0x8000 || solid->rz == 0x8000) {
        mtx = s_anime_mtx_pool++;

        guAlign(mtx, 0, NEG_IF_HALF_TURN(solid->ry, solid->rz, s_anime_view_x), NEG_IF_HALF_TURN(solid->rx, solid->rz, s_anime_view_y), NEG_IF_HALF_TURN(solid->rx, solid->ry, s_anime_view_z));
        gSPMatrix(D_8015C5CC++, (unsigned int) mtx & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    }

    s_anime_mtx_top = s_anime_mtx_stack;
}

void anime_joint_mtx(float (*mf)[4], AnimeJoint *joint, ObjSolid *solid)
{
    float          sin_x, cos_x;
    float          sin_y, cos_y;
    float          sin_z, cos_z;
    float          step;
    unsigned short delta;
    float          sx, sy, sz;
    unsigned short rot[3];
    float          sinxsiny;
    float          cosxsiny;

    mf[0][3] = 0.0f;
    mf[1][3] = 0.0f;
    mf[2][3] = 0.0f;
    mf[3][3] = 1.0f;
    mf[3][0] = (float) anime_key_s16(joint->tx) * 0.03125;
    mf[3][1] = (float) anime_key_s16(joint->ty) * 0.03125;
    mf[3][2] = (float) anime_key_s16(joint->tz) * 0.03125;

    anime_key_rot(joint, rot);

    sx = (float) (unsigned int) anime_key_u16(joint->sx) * 0.00390625;
    sy = (float) (unsigned int) anime_key_u16(joint->sy) * 0.00390625;
    sz = (float) (unsigned int) anime_key_u16(joint->sz) * 0.00390625;

    if (solid != NULL) {
        if (s_anime_blend > 0.0f) {
            delta = (rot[0] - solid->rx) & 0x3FF;
            if (delta > 0x198 && delta < 0x268) {
                func_8001F878(&solid->rx, &solid->ry, &solid->rz);
                delta = rot[0] - solid->rx;
            }

            if (!(delta & 0x200)) {
                step = (delta & 0x3FF) / (s_anime_blend + 1.0f);
            } else {
                step = (unsigned short) (0x400 - (unsigned short) (((0x400 - delta) & 0x3FF) / (s_anime_blend + 1.0f))) & 0x3FF;
            }
            rot[0] = (unsigned short) step + solid->rx;

            if (!((rot[1] - solid->ry) & 0x200)) {
                step = ((rot[1] - solid->ry) & 0x3FF) / (s_anime_blend + 1.0f);
            } else {
                step = (unsigned short) (0x400 - (unsigned short) (((solid->ry - rot[1]) & 0x3FF) / (s_anime_blend + 1.0f))) & 0x3FF;
            }
            rot[1] = (unsigned short) step + solid->ry;

            if (!((rot[2] - solid->rz) & 0x200)) {
                step = ((rot[2] - solid->rz) & 0x3FF) / (s_anime_blend + 1.0f);
            } else {
                step = (unsigned short) (0x400 - (unsigned short) (((solid->rz - rot[2]) & 0x3FF) / (s_anime_blend + 1.0f))) & 0x3FF;
            }
            rot[2] = (unsigned short) step + solid->rz;

            // clang-format off
            rot[0] &= 0x3FF; rot[1] &= 0x3FF; rot[2] &= 0x3FF;
            // clang-format on

            mf[3][0] = (mf[3][0] - solid->tx) / (s_anime_blend + 1.0f) + solid->tx;
            mf[3][1] = (mf[3][1] - solid->ty) / (s_anime_blend + 1.0f) + solid->ty;
            mf[3][2] = (mf[3][2] - solid->tz) / (s_anime_blend + 1.0f) + solid->tz;

            sx = solid->sx + (sx - solid->sx) / (s_anime_blend + 1.0f);
            sy = solid->sy + (sy - solid->sy) / (s_anime_blend + 1.0f);
            sz = solid->sz + (sz - solid->sz) / (s_anime_blend + 1.0f);
        }

        sin_x    = func_80003F30(rot[0], &cos_x);
        sin_y    = func_80003F30(rot[1], &cos_y);
        sin_z    = func_80003F30(rot[2], &cos_z);
        sinxsiny = sin_x * sin_y;
        cosxsiny = cos_x * sin_y;
        mf[0][0] = cos_y * cos_z;
        mf[0][1] = cos_y * sin_z;
        mf[0][2] = -sin_y;
        mf[1][0] = sinxsiny * cos_z - cos_x * sin_z;
        mf[1][1] = sinxsiny * sin_z + cos_x * cos_z;
        mf[1][2] = sin_x * cos_y;
        mf[2][0] = cosxsiny * cos_z + sin_x * sin_z;
        mf[2][1] = cosxsiny * sin_z - sin_x * cos_z;
        mf[2][2] = cos_x * cos_y;

        solid->rx = rot[0];
        solid->ry = rot[1];
        solid->rz = rot[2];
        solid->sx = sx;
        solid->sy = sy;
        solid->sz = sz;
        solid->tx = mf[3][0];
        solid->ty = mf[3][1];
        solid->tz = mf[3][2];
    } else {
        sin_x    = func_80003F30(rot[0], &cos_x);
        sin_y    = func_80003F30(rot[1], &cos_y);
        sin_z    = func_80003F30(rot[2], &cos_z);
        sinxsiny = sin_x * sin_y;
        cosxsiny = cos_x * sin_y;
        mf[0][0] = cos_y * cos_z;
        mf[0][1] = cos_y * sin_z;
        mf[0][2] = -sin_y;
        mf[1][0] = sinxsiny * cos_z - cos_x * sin_z;
        mf[1][1] = sinxsiny * sin_z + cos_x * cos_z;
        mf[1][2] = sin_x * cos_y;
        mf[2][0] = cosxsiny * cos_z + sin_x * sin_z;
        mf[2][1] = cosxsiny * sin_z - sin_x * cos_z;
        mf[2][2] = cos_x * cos_y;
    }

    if (sx != 1.0) {
        mf[0][0] *= sx;
        mf[0][1] *= sx;
        mf[0][2] *= sx;
    }
    if (sy != 1.0) {
        mf[1][0] *= sy;
        mf[1][1] *= sy;
        mf[1][2] *= sy;
    }
    if (sz != 1.0) {
        mf[2][0] *= sz;
        mf[2][1] *= sz;
        mf[2][2] *= sz;
    }
}

unsigned short anime_key_u16(unsigned short track)
{
    unsigned short cur;
    unsigned short next;
    float          frac;
    int            frame;

    track &= 0xBFFF;

    if (track > 0xA000) {
        return track - 0xB000;
    }

    if (track & 0x8000) {
        track = track & 0x7FFF;
        frac  = 0.0f;
        frame = 0;
    } else {
        frame = s_anime_frame;
        frac  = s_anime_frame - frame;
    }

    if (frac == 0.0f) {
        return anime_key_decode(track, -1, NULL, frame);
    }

    if (s_anime_frame_total - 1.0f <= frame) {
        cur = anime_key_decode(track, 0, (short *) &next, frame);
    } else {
        next = anime_key_decode(track, frame, (short *) &cur, frame + 1);
    }

    return cur + (unsigned short) ((next - cur) * frac);
}

short anime_key_s16(unsigned short track)
{
    short cur;
    short next;
    float frac;
    int   frame;

    track &= 0xBFFF;

    if (track > 0xA000) {
        return track - 0xB000;
    }

    if (track & 0x8000) {
        track = track & 0x7FFF;
        frac  = 0.0f;
        frame = 0;
    } else {
        frame = s_anime_frame;
        frac  = s_anime_frame - frame;
    }

    if (frac == 0.0f) {
        return anime_key_decode(track, -1, NULL, frame);
    }

    if (s_anime_frame_total - 1.0f <= frame) {
        cur = anime_key_decode(track, 0, &next, frame);
    } else {
        next = anime_key_decode(track, frame, &cur, frame + 1);
    }

    return cur + (short) ((next - cur) * frac);
}

unsigned short anime_key_angle(unsigned short track)
{
    unsigned short cur;
    unsigned short next;
    short          delta;
    float          frac;
    int            frame;

    track &= 0xBFFF;

    if (track > 0xA000) {
        return track - 0xB000;
    }

    if (track & 0x8000) {
        track = track & 0x7FFF;
        frac  = 0.0f;
        frame = 0;
    } else {
        frame = s_anime_frame;
        frac  = s_anime_frame - frame;
    }

    if (frac == 0.0f) {
        return anime_key_decode(track, -1, NULL, frame);
    }

    if (s_anime_frame_total - 1.0f <= frame) {
        cur = anime_key_decode(track, 0, (short *) &next, frame);
    } else {
        next = anime_key_decode(track, frame, (short *) &cur, frame + 1);
    }

    delta = (unsigned short) ((next - cur) & 0x3FF);

    while (delta > 0x200) {
        delta -= 0x400;
    }

    return (short) ((short) cur + (short) (delta * frac)) & 0x3FF;
}

void anime_key_rot(AnimeJoint *joint, unsigned short *rot)
{
    int            track_frame;
    float          frac;
    float          track_frac;
    int            frame;
    unsigned short cur_rot;
    short          delta;
    unsigned short next_rot[3];
    unsigned short track[3];

    track[0]    = joint->rx;
    track[1]    = joint->ry;
    track[2]    = joint->rz;
    frame       = s_anime_frame;
    frac        = s_anime_frame - frame;
    track_frame = frame;
    track_frac  = frac;

    track[0] &= 0xBFFF;
    if (track[0] > 0xA000) {
        rot[0] = next_rot[0] = track[0] - 0xB000;
    } else {
        if (track[0] & 0x8000) {
            track_frac = 0.0f;
            track[0] &= 0x7FFF;
            track_frame = 0;
        }
        if (!(track_frac != 0.0f)) {
            rot[0] = next_rot[0] = anime_key_decode(track[0], -1, NULL, track_frame);
        } else if (s_anime_frame_total - 1.0f <= track_frame) {
            rot[0] = anime_key_decode(track[0], 0, (short *) &next_rot[0], track_frame);
        } else {
            next_rot[0] = anime_key_decode(track[0], track_frame, (short *) &rot[0], track_frame + 1);
        }
        track_frame = frame;
        track_frac  = frac;
    }

    track[1] &= 0xBFFF;
    if (track[1] > 0xA000) {
        rot[1] = next_rot[1] = track[1] - 0xB000;
    } else {
        if (track[1] & 0x8000) {
            track_frac = 0.0f;
            track[1] &= 0x7FFF;
            track_frame = 0;
        }
        if (!(track_frac != 0.0f)) {
            rot[1] = next_rot[1] = anime_key_decode(track[1], -1, NULL, track_frame);
        } else if (s_anime_frame_total - 1.0f <= track_frame) {
            rot[1] = anime_key_decode(track[1], 0, (short *) &next_rot[1], track_frame);
        } else {
            next_rot[1] = anime_key_decode(track[1], track_frame, (short *) &rot[1], track_frame + 1);
        }
        track_frame = frame;
        track_frac  = frac;
    }

    track[2] &= 0xBFFF;
    if (track[2] > 0xA000) {
        rot[2] = next_rot[2] = track[2] - 0xB000;
    } else {
        if (track[2] & 0x8000) {
            track_frac = 0.0f;
            track[2] &= 0x7FFF;
            track_frame = 0;
        }
        if (track_frac == 0.0f) {
            rot[2] = next_rot[2] = anime_key_decode(track[2], -1, NULL, track_frame);
        } else if (s_anime_frame_total - 1.0f <= track_frame) {
            rot[2] = anime_key_decode(track[2], 0, (short *) &next_rot[2], track_frame);
        } else {
            next_rot[2] = anime_key_decode(track[2], track_frame, (short *) &rot[2], track_frame + 1);
        }
        track_frame = frame;
        track_frac  = frac;
    }

    if (frac != 0.0f) {
        if (rot[0] != next_rot[0]) {
            delta = (next_rot[0] - rot[0]) & 0x3FF;
            if (delta > 0x198 && delta < 0x268) {
                func_8001F878(&rot[0], &rot[1], &rot[2]);
            }
            delta = (next_rot[0] - rot[0]) & 0x3FF;
            while (delta > 0x200) {
                delta -= 0x400;
            }
            rot[0] = (short) ((short) rot[0] + (short) (delta * frac)) & 0x3FF;
        }
        if (rot[1] != next_rot[1]) {
            delta = (next_rot[1] - rot[1]) & 0x3FF;
            while (delta > 0x200) {
                delta -= 0x400;
            }
            rot[1] = (short) ((short) rot[1] + (short) (delta * frac)) & 0x3FF;
        }
        if (rot[2] != next_rot[2]) {
            delta = (next_rot[2] - rot[2]) & 0x3FF;
            while (delta > 0x200) {
                delta -= 0x400;
            }
            rot[2] = (short) ((short) rot[2] + (short) (delta * frac)) & 0x3FF;
        }
    }
}

unsigned short anime_key_decode(unsigned short pos, int frame_a, short *out_a, int frame_b)
{
    unsigned char  code;
    unsigned char  hi;
    unsigned short len;

    hi = 0;

    for (;;) {
        code = KEY(pos++);

        if (code < 0x78) {
            if (code >= 0x60) {
                hi = KEY(pos++);
            } else if (code >= 0x40) {
                hi++;
            } else if (code >= 0x20) {
                hi--;
            }

            len = code & 0x1F;

            if (frame_a >= 0) {
                if (!len || frame_a < len) {
                    *out_a  = (hi << 8) + KEY(pos + frame_a);
                    frame_a = -1;
                } else {
                    frame_a -= len;
                }
            }

            if (!len || frame_b < len) {
                return (hi << 8) + KEY(pos + frame_b);
            }

            frame_b -= len;
            pos += len;
        } else if (code < 0xF0) {
            if (code >= 0xD8) {
                hi = KEY(pos++);
            } else if (code >= 0xB8) {
                hi++;
            } else if (code >= 0x98) {
                hi--;
            }

            len = code - 0x78;
            len &= 0x1F;

            if (len != 0) {
                len += 2;
            }

            if (frame_a >= 0) {
                if (!len || frame_a < len) {
                    *out_a  = (hi << 8) + KEY(pos);
                    frame_a = -1;
                } else {
                    frame_a -= len;
                }
            }

            if (!len || frame_b < len) {
                return (hi << 8) + KEY(pos);
            }

            frame_b -= len;
            pos++;
        } else {
            len = code & 0xF;

            if (frame_a >= 0) {
                if (!len || frame_a < len) {
                    *out_a  = (KEY(pos + frame_a * 2) << 8) + KEY(pos + frame_a * 2 + 1);
                    frame_a = -1;
                } else {
                    frame_a -= len;
                }
            }

            if (!len || frame_b < len) {
                return (KEY(pos + frame_b * 2) << 8) + KEY(pos + frame_b * 2 + 1);
            }

            frame_b -= len;
            hi = KEY(pos + len * 2 - 2);
            pos += len * 2;
        }
    }
}

float anime_frame_count(ObjSolid *solid)
{
    unsigned int kind;
    unsigned int ref;
    unsigned int hdr;

    kind = solid->AModel & 0x70000000;
    ref  = solid->AModel & 0x8FFFFFFE;

    switch (kind) {
        case ANIME_KIND_DEMO:
        case ANIME_KIND_ANIME:
        case ANIME_KIND_JCHAR:
            break;

        default:
            return 0.0f;
    }

    if (ref == 0) {
        return 0.0f;
    }

    hdr = *(unsigned int *) ANIME_REF_SOLID(solid, ref);

    return hdr & 0xFF;
}

void anime_set_default_ambient(unsigned char r, unsigned char g, unsigned char b)
{
    s_anime_default_lights.a.l.col[0] = s_anime_default_lights.a.l.colc[0] = r;
    s_anime_default_lights.a.l.col[1] = s_anime_default_lights.a.l.colc[1] = g;
    s_anime_default_lights.a.l.col[2] = s_anime_default_lights.a.l.colc[2] = b;
}

void anime_set_view(AnimeCamera *cam)
{
    s_anime_view_x    = cam->eye[0] - cam->at[0];
    s_anime_view_y    = cam->eye[1] - cam->at[1];
    s_anime_view_z    = cam->eye[2] - cam->at[2];
    s_anime_view_roll = cam->roll;

    anime_view_to_local(g_anime_solid);
}

int anime_spawn_parts(void *arg0, ObjSolid *src)
{
    ObjSolid   *part;
    int         i;
    ObjSolid    pose;
    int         model;
    signed char count;

    count = 0;

    pose = *src;

    *(int *) &pose = 0;
    pose.rx        = 0;
    pose.ry        = 0;
    pose.rz        = 0;

    model = anime_locate_joint(&pose, src, 0xF0000001);

    while (model != 0) {
        part = func_80035EEC(arg0, 2, 1);

        if (part == NULL) {
            return count;
        }

        func_8001C970(part, &pose);
        part->AModel     = model + ANIME_KIND_MODEL;
        part->header.pri = src->header.pri;
        part->init_glist = src->init_glist;

        for (i = 0; i < 6; i++) {
            part->SegWave[i] = src->SegWave[i];
        }

        count++;

        pose.rx = 0;
        pose.ry = 0;
        pose.rz = 0;

        model = anime_locate_joint(&pose, src, count + 0xF0000001);
    }

    return count;
}

int anime_locate_joint(ObjSolid *out, ObjSolid *solid, int target)
{
    return anime_locate_joint_at(out, solid, solid->AModel, solid->time, solid->blend, target);
}

int anime_locate_joint_at(ObjSolid *out, ObjSolid *solid, unsigned int model, float frame, float blend, int target)
{
    ObjSolid      pose;
    AnimeJoint   *joint;
    ObjSolid     *child;
    ObjSolid     *right;
    ObjSolid     *path_solid;
    unsigned int *script;
    unsigned int  hdr;
    AnimeJoint   *last_root;
    unsigned int  joint_id;
    int           found;
    int           roots_left;
    unsigned char i;
    unsigned char depth;
    unsigned char have_parent;

    s_anime_found_solid = NULL;
    s_anime_frame       = frame;
    s_anime_blend       = blend;
    child               = NULL;
    have_parent         = 0;
    g_anime_solid       = solid;

    if ((model & 0x70000000) != ANIME_KIND_JCHAR) {
        right = NULL;
    } else {
        right = g_anime_solid->child;
    }

    script = (unsigned int *) ANIME_REF(model & 0x8FFFFFFE);
    hdr    = *script++;

    if (!hdr) {
        return 0;
    }

    joint               = NULL;
    s_anime_local       = (hdr / 0x80000000) & 1;
    roots_left          = (hdr >> 8) & 0x7FFF;
    s_anime_frame_total = hdr & 0xFF;
    // clang-format off
    s_anime_keys = (unsigned char *) ANIME_REF(*script); script += ((hdr >> 28) & 7) + ((hdr >> 24) & 0xF) + 1;
    // clang-format on
    depth = 0;

    if ((target & 0xF0000000) == 0xF0000000) {
        s_anime_joint_countdown = target - 0xF0000000;
    } else {
        s_anime_joint_countdown = 0;
    }
    if ((target & 0xF0000000) == 0xE0000000) {
        s_anime_root_countdown = target - 0xE0000000;
    } else {
        s_anime_root_countdown = 0;
    }

    for (;;) {
        if (!joint) {
            if (roots_left--) {
            } else {
                break;
            }

            joint = last_root = (AnimeJoint *) ANIME_REF(*script);
            script++;

            if ((model & 0x70000000) == ANIME_KIND_DEMO) {
                s_anime_path_joint[depth] = joint;
                s_anime_path_solid[depth] = NULL;
                depth                     = 1;
            }

            if (s_anime_root_countdown && --s_anime_root_countdown == 0) {
                break;
            }
        } else if ((model & 0x70000000) == ANIME_KIND_DEMO) {
            s_anime_path_joint[depth] = joint;
            s_anime_path_solid[depth] = NULL;
            depth                     = 1;
        }

        if (!joint) {
            depth = 0;
            continue;
        }

        joint_id = joint->model & 0x8FFFFFFF;

        if (target == joint_id || (joint_id && s_anime_joint_countdown && --s_anime_joint_countdown == 0)) {
            break;
        }

        if (joint->child) {
            if (right) {
                child = anime_child_node(joint, right);
                if (!child && right->child) {
                    func_8003674C(right);
                }
            }

            if (!right || child) {
                found = anime_find_joint_path(JOINT_AT(joint, joint->child), target, depth, child);
                depth = found;
                if (found) {
                    break;
                }
            }
        }

        depth = 0;

        if (right && !anime_sibling_node(joint, right) && right->sibling) {
            func_80036798(right);
        }

        if (joint->sibling) {
            joint = JOINT_AT(joint, joint->sibling);
        } else {
            joint = NULL;
        }
    }

    if (out) {
        if (depth) {
            if ((solid->tx != 0.0f) | (solid->ty != 0.0f) | (solid->tz != 0.0f) | solid->rx | solid->ry | solid->rz |
                (solid->sx != 1.0f) | (solid->sy != 1.0f) | (solid->sz != 1.0f)) {
                func_8001E2BC(s_anime_mtx_stack[have_parent++], solid);
            }

            for (i = 0; i < depth; i++) {
                path_solid = s_anime_path_solid[i];

                if (path_solid) {
                    pose.tx = path_solid->tx;
                    pose.ty = path_solid->ty;
                    pose.tz = path_solid->tz;
                    pose.rx = path_solid->rx;
                    pose.ry = path_solid->ry;
                    pose.rz = path_solid->rz;
                    pose.sx = path_solid->sx;
                    pose.sy = path_solid->sy;
                    pose.sz = path_solid->sz;
                    anime_joint_mtx(s_anime_mtx_stack[have_parent], s_anime_path_joint[i], &pose);
                } else {
                    anime_joint_mtx(s_anime_mtx_stack[have_parent], s_anime_path_joint[i], NULL);
                }

                if (have_parent) {
                    func_8001F2D8(s_anime_mtx_stack[0], s_anime_mtx_stack[1]);
                    *(AnimeMtx *) s_anime_mtx_stack[0] = *(AnimeMtx *) s_anime_mtx_stack[1];
                } else {
                    have_parent = 1;
                }
            }

            joint = s_anime_path_joint[depth - 1];
            func_8001EEF4(&out->tx, &out->ty, &out->tz, &out->rx, &out->ry, &out->rz, &out->sx, &out->sy,
                &out->sz, s_anime_mtx_stack[0]);
        } else {
            if (!last_root || target != (last_root->model & 0x8FFFFFFF)) {
                return 0;
            }

            joint = (AnimeJoint *) ANIME_REF(*script);
            func_8001C970(out, solid);
        }

        if (joint->rx & 0x4000) {
            out->rx = 0x8000;
        }
        if (joint->ry & 0x4000) {
            out->ry = 0x8000;
        }
        if (joint->rz & 0x4000) {
            out->rz = 0x8000;
        }
    } else if (depth) {
        joint = s_anime_path_joint[depth - 1];
    } else {
        joint = last_root;
        if (!last_root || target != (last_root->model & 0x8FFFFFFF)) {
            return 0;
        }
    }

    if (s_anime_found_solid) {
        return (int) s_anime_found_solid;
    }

    return joint->model;
}

int anime_find_joint_path(AnimeJoint *joint, unsigned int target, int depth, ObjSolid *solid)
{
    ObjSolid    *sibling;
    ObjSolid    *child;
    unsigned int model;
    int          found;

    s_anime_path_joint[depth] = joint;
    sibling                   = NULL;
    child                     = NULL;
    s_anime_path_solid[depth] = solid;
    model                     = joint->model & 0x8FFFFFFF;

    if (target == model || (model != 0 && s_anime_joint_countdown != 0 && --s_anime_joint_countdown == 0)) {
        s_anime_found_solid = solid;
        return (depth + 1) & 0xFF;
    }

    if (joint->child != 0) {
        if (solid != NULL) {
            child = anime_child_node(joint, solid);

            if (child == NULL && solid->child != NULL) {
                func_8003674C(solid);
            }
        }

        if (solid == NULL || child != NULL) {
            found = anime_find_joint_path(JOINT_AT(joint, joint->child), target, s_anime_local != 0 ? depth + 1 : depth, child);

            if (found != 0) {
                return found & 0xFF;
            }
        }
    }

    if (joint->sibling != 0) {
        if (solid != NULL) {
            sibling = anime_sibling_node(joint, solid);

            if (sibling == NULL && solid->sibling != NULL) {
                func_80036798(solid);
            }
        }

        if (solid == NULL || sibling != NULL) {
            found = anime_find_joint_path(JOINT_AT(joint, joint->sibling), target, depth, sibling);

            if (found != 0) {
                return found & 0xFF;
            }
        }
    }

    return 0;
}

int anime_swap_models(ObjSolid *target_solid, unsigned int model, unsigned int *table)
{
    ObjSolid     *right;
    unsigned int *script;
    unsigned int  hdr;
    unsigned int  ref;
    AnimeJoint   *joint;
    ObjSolid     *solid;
    int           spare;
    unsigned int  roots_left;

    g_anime_solid = target_solid;

    if (g_anime_solid != NULL && model == 0) {
        model = target_solid->AModel;
    }

    if ((model & 0x70000000) != ANIME_KIND_JCHAR) {
        right = NULL;
    } else {
        right = g_anime_solid->child;
    }

    script = (unsigned int *) ANIME_REF_SOLID(g_anime_solid, model & 0x8FFFFFFE);
    hdr    = *script++;

    if (hdr == 0) {
        return 0;
    }

    s_anime_local       = (hdr / 0x80000000) & 1;
    roots_left          = (hdr >> 8) & 0x7FFF;
    s_anime_frame_total = hdr & 0xFF;
    s_anime_keys        = (unsigned char *) ANIME_REF_SOLID(g_anime_solid, *script);

    if (script == NULL) {
        PRINTF(("WAWAWAWAWAWAWAWAWA!!!!!!!\n"));
        PRINTF(("NANI YATONNJYA !!!!!!!!!!\n"));
        PRINTF(("!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
        PRINTF(("!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
        PRINTF(("!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
        PRINTF(("!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
        PRINTF(("!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
        PRINTF(("!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
        PRINTF(("!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
    }

    script += ((hdr >> 28) & 7) + ((hdr >> 24) & 0xF) + 1;

    for (;;) {
        if (roots_left-- == 0) {
            break;
        }

        joint = (AnimeJoint *) ANIME_REF(*script);
        script++;

        if (joint != 0) {
            anime_swap_joint_models(joint, table, right);
        } else {
            PRINTF(("TRANS DAME "));
            PRINTF((""));
        }
    }

    return 1;
}

int anime_swap_joint_models(AnimeJoint *joint, unsigned int *table, ObjSolid *solid)
{
    ObjSolid *sibling;
    ObjSolid *child;
    int       i;

    child   = NULL;
    sibling = NULL;

    for (i = 0; table[i] != 0; i += 2) {
        if ((joint->model & 0x8FFFFFFF) == table[i]) {
            joint->model = table[i + 1];

            if (solid != NULL && (solid->AModel & 0x8FFFFFFE) == table[i]) {
                solid->AModel = table[i + 1];
            }
        }
    }

    if (joint->child != 0) {
        if (solid != NULL) {
            child = anime_child_node(joint, solid);

            if (child == NULL && solid->child != NULL) {
                func_8003674C(solid);
            }
        }

        anime_swap_joint_models(JOINT_AT(joint, joint->child), table, child);
    }

    if (joint->sibling != 0) {
        if (solid != NULL) {
            sibling = anime_sibling_node(joint, solid);

            if (sibling == NULL && solid->sibling != NULL) {
                func_80036798(solid);
            }
        }

        anime_swap_joint_models(JOINT_AT(joint, joint->sibling), table, sibling);
    }

    return 0;
}

void anime_view_to_local(ObjSolid *solid)
{
    unsigned short rx;
    unsigned short ry;
    unsigned short rz;
    float          sin_x;
    float          cos_x;
    float          sin_y;
    float          cos_y;
    float          sin_z;
    float          cos_z;
    float          sinxsiny;
    float          cosxsiny;
    float          x;
    float          y;
    float          z;

    rx    = solid->rx;
    ry    = solid->ry;
    rz    = solid->rz;
    sin_x = func_80003F30(rx, &cos_x);
    sin_y = func_80003F30(ry, &cos_y);
    sin_z = func_80003F30(rz, &cos_z);

    sinxsiny = sin_x * sin_y;
    cosxsiny = cos_x * sin_y;

    x              = (cos_y * cos_z * s_anime_view_x) + (((sinxsiny * cos_z) - (cos_x * sin_z)) * s_anime_view_y) + (((cosxsiny * cos_z) + (sin_x * sin_z)) * s_anime_view_z);
    y              = (cos_y * sin_z * s_anime_view_x) + (((sinxsiny * sin_z) + (cos_x * cos_z)) * s_anime_view_y) + (((cosxsiny * sin_z) - (sin_x * cos_z)) * s_anime_view_z);
    z              = (-sin_y * s_anime_view_x) + (sin_x * cos_y * s_anime_view_y) + (cos_x * cos_y * s_anime_view_z);
    s_anime_view_x = x;
    s_anime_view_y = y;
    s_anime_view_z = z;
}
