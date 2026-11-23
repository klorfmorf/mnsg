#ifndef XVRAM_H
#define XVRAM_H

#include "common.h"
#include "structs.h"

ColHit func_8002C9D4(float x, float y, float z, float move_x, float move_y, float move_z, float length);
void   func_8002CC94(float x, float y, float z, float move_x, float move_y, float move_z, float scale, void *arg7, ColHead *head, ColHit *hit, float arg10);

#endif // XVRAM_H
