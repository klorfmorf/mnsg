#ifndef TASK_H
#define TASK_H

#include "common.h"
#include "structs.h"

void  func_80034734(void);
void  func_8003488C(char *arg0);
Task *func_80034DD8(void (*exec)(Task *, Obj *), unsigned short priority);
Task *func_80034E08(Task *prev, void (*exec)(Task *, Obj *), unsigned short priority);
void  func_80034ED4(void);
void  func_80034EF8(Task *task);
#ifndef NO_PROTO_func_8003521C
void func_8003521C(void (*exec)(Task *, Obj *));
#endif

extern void          *D_8006D320;
extern TaskList       g_task_list;
extern unsigned short D_8016DAB0;
extern unsigned short D_8016DAB2;
extern Task          *D_8016DAB4;

#endif // TASK_H
