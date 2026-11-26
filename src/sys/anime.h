#ifndef ANIME_H
#define ANIME_H

#include "common.h"
#include "structs.h"

void anime_init_frame(void);
int  anime_draw(ObjSolid *solid);
float anime_frame_count(ObjSolid *solid);
int  anime_locate_joint(ObjSolid *out, ObjSolid *solid, int target);
int  anime_swap_models(ObjSolid *target_solid, unsigned int model, unsigned int *table);

extern Vp             g_anime_default_vp;
extern ObjSolid      *g_anime_solid;
extern unsigned int   s_anime_ref;
extern unsigned char *s_anime_keys;

#endif // ANIME_H
