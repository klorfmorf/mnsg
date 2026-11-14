#ifndef FILE_REQUEST_H
#define FILE_REQUEST_H


#include "common.h"

typedef struct WaveReq {
    /* 0x00 */ int            wave_no;
    /* 0x04 */ unsigned char *data;
} WaveReq; // size = 0x8

unsigned char *func_80005A20(WaveReq *req);
void           func_80005A64(void);

#endif // FILE_REQUEST_H
