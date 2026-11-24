#ifndef ANIME_H
#define ANIME_H

#include "common.h"
#include "structs.h"

void anime_init_frame(void);
int  anime_draw(ObjSolid *solid);

extern Vp             g_anime_default_vp;
extern ObjSolid      *g_anime_solid;
extern unsigned int   s_anime_ref;
extern unsigned char *s_anime_keys;

#endif // ANIME_H
