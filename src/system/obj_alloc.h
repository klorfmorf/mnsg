#ifndef OBJ_ALLOC_H
#define OBJ_ALLOC_H

#include "common.h"
#include "structs.h"

void      func_80035B50(void);
void      func_80035DFC(void *arg0, short arg1, int arg2);
ObjSolid *func_80035EEC(void *arg0, int arg1, int arg2);
void      func_80036388(ObjSolid *solid, ObjSolid *node);
void      func_800363F4(ObjSolid *solid, ObjSolid *node);
ObjSolid *func_80036448(ObjSolid *solid);
int       func_800364FC(ObjSolid *solid);
void      func_80036660(ObjSolid *solid);
void      func_8003674C(ObjSolid *solid);
int       func_80036798(ObjSolid *solid);
void      func_800367E4(ObjSolid *solid);

#endif // OBJ_ALLOC_H
