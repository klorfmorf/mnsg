#ifndef OBJ_ALLOC_H
#define OBJ_ALLOC_H

#include "common.h"
#include "structs.h"

void      func_80035B50(void);
void     *func_80035DFC(Task *task, short kind, unsigned char count);
void     *func_80035EEC(Task *task, short kind, unsigned char count);
int       func_80036260(Task *task);
Obj      *func_800362DC(Task *task);
int       func_80036388(ObjSolid *solid, ObjSolid *node);
int       func_800363F4(ObjSolid *solid, ObjSolid *node);
ObjSolid *func_80036448(ObjSolid *solid);
int       func_800364FC(ObjSolid *solid);
void      func_80036660(ObjSolid *solid);
int       func_8003674C(ObjSolid *solid);
int       func_80036798(ObjSolid *solid);
void      func_800367E4(ObjSolid *solid);

#endif // OBJ_ALLOC_H
