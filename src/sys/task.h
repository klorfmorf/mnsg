#ifndef TASK_H
#define TASK_H

#include "common.h"
#include "structs.h"

void  func_80034734(void);
void  func_8003488C(char *arg0);
Task *func_80034DD8(void (*exec)(Task *, Obj *), unsigned short priority);
Task *func_80034E08(Task *prev, void (*exec)(Task *, Obj *), unsigned short priority);
void  func_80034ED4(void);
Task *func_800358E8(Task *prev, void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1);
void  func_80034680(ObjSolid *solid, unsigned int model, unsigned int glist, float sx, float sy, float sz, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, unsigned short wave0, unsigned short wave1, unsigned short wave2);
void  func_80034EF8(Task *task);
Task *func_80035690(Task *prev, void (*exec)(Task *, Obj *), unsigned int model, unsigned int glist, float tx, float ty, float tz, unsigned short rx, unsigned short ry, unsigned short rz, float sx, float sy, float sz, unsigned short wave0, unsigned short wave1, unsigned short priority);
void  func_80035214(Task *task, void (*exec)(Task *, Obj *));
#ifndef NO_PROTO_func_8003521C
void func_8003521C(void (*exec)(Task *, Obj *));
#endif
void  func_8003522C(Task *task, void (*exec)(Task *, Obj *));
void  func_80035234(void (*exec)(Task *, Obj *));
void  func_80035244(Task *task, void (*exec)(Task *, Obj *));

extern void          *D_8006D320;
extern TaskList       g_task_list;
extern unsigned short D_8016DAB0;
extern unsigned short D_8016DAB2;
extern Task          *D_8016DAB4;

#endif // TASK_H
