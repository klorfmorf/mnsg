#ifndef AMEM_H
#define AMEM_H

#include "common.h"
#include "structs.h"

void  func_800148C0(AmemBlock *arg0, char *arg1, unsigned int arg2);
void *amemAlloc(AmemBlock *arg0, int size);
void *amemFree(AmemBlock *arg0, void *arg1);

#endif // AMEM_H
