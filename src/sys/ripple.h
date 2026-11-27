#ifndef RIPPLE_H
#define RIPPLE_H

#include "common.h"
#include "structs.h"

void           func_80024160(Task *task, Obj *obj);
RippleSurface *func_80024670(void);
void           func_800246BC(RippleSurface *grid);
void           func_80024888(Task *task);
void           func_80025B38(Task *task, Obj *obj);
void           func_80026114(Task *task);
float          func_80026AAC(ColHit *ray, Task *task);

#endif // RIPPLE_H
