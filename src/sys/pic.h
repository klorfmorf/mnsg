#ifndef PIC_H
#define PIC_H

#include "common.h"
#include "structs.h"

Pic *picOpen(unsigned char *data, Pic *pic);
Pic *picDecode(unsigned char *arg0, void *buf, Pic *pic);

extern WaveReq D_8006ADD0;
extern WaveReq D_8006ADD8;

#endif // PIC_H
