#ifndef HEAP_H
#define HEAP_H


#include "common.h"
#include "system/object.h"

void      func_80035B50(void);
ObjSolid *func_80035EEC(void *arg0, int arg1, int arg2);
void      func_80036388(ObjSolid *solid, ObjSolid *node);
void      func_800363F4(ObjSolid *solid, ObjSolid *node);
ObjSolid *func_80036448(ObjSolid *solid);
void      func_800364FC(ObjSolid *solid);
void      func_8003674C(ObjSolid *solid);
void      func_80036798(ObjSolid *solid);
void      func_800367E4(ObjSolid *solid);

#endif // HEAP_H
