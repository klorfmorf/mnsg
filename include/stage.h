#ifndef STAGE_H
#define STAGE_H


#include "common.h"

typedef struct CameraRegion {
    /* 0x00 */ short         type;
    /* 0x02 */ unsigned char unk_2;
    /* 0x03 */ unsigned char unk_3;
    /* 0x04 */ int           max_x;
    /* 0x08 */ int           min_x;
    /* 0x0C */ int           max_y;
    /* 0x10 */ int           min_y;
    /* 0x14 */ int           max_z;
    /* 0x18 */ int           min_z;
    /* 0x1C */ int           rail_x;
    /* 0x20 */ int           rail_y;
    /* 0x24 */ int           rail_z;
} CameraRegion; // size = 0x28

typedef struct RoomEntry {
    /* 0x00 */ unsigned short camera_yaw_step;
    /* 0x02 */ short          x;
    /* 0x04 */ short          y;
    /* 0x06 */ short          z;
    /* 0x08 */ unsigned short facing;
} RoomEntry; // size = 0xA

void func_8000B2A0(void);
void func_8000B364(void);
void func_8000B3E4(void);

#endif // STAGE_H
