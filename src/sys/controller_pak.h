#ifndef CONTROLLER_PAK_H
#define CONTROLLER_PAK_H

#include "common.h"
#include "structs.h"

int          func_800231E0(void);
int          func_800232EC(void);
int          func_8002338C(void);
int          func_80023394(void);
int          func_80023410(void);
int          func_80023480(void);
int          func_800234D8(unsigned char *buffer, int slot);
int          func_80023560(unsigned char *buf);
int          func_80023610(unsigned char *buffer, int slot);
int          func_80023698(ContPakHeader *header);
int          func_80023788(void);
int          func_800237F0(void);
int          func_80023840(void);
int          func_80023880(void);
int          func_800238D0(void);
int          func_800239B8(int index);
unsigned int func_80023A1C(unsigned char *data, int size);

extern MemPak *D_80168E84;

#endif // CONTROLLER_PAK_H
