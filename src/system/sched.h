#ifndef SCHED_H
#define SCHED_H

#include "common.h"
#include "structs.h"

void         osCreateScheduler(OSSched *sc, void *stack, OSPri priority, u8 mode, u8 numFields);
void         osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ);
OSMesgQueue *osScGetCmdQ(OSSched *sc);
OSMesgQueue *osScGetInterruptQ(OSSched *sc);

#endif // SCHED_H
