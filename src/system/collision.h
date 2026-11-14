#ifndef COLLISION_H
#define COLLISION_H


#include "common.h"
#include "system/object.h"

typedef struct ColPlane {
    /* 0x00 */ float       normal_x;
    /* 0x04 */ float       normal_y;
    /* 0x08 */ float       normal_z;
    /* 0x0C */ float       distance;
    /* 0x10 */ signed char type;
} ColPlane; // size = 0x14

typedef struct ColTree {
    /* 0x00 */ unsigned short next_tree;
    /* 0x02 */ unsigned short type;
    /* 0x04 */ unsigned short scale;
    /* 0x06 */ short          box_max_x;
    /* 0x08 */ short          box_max_y;
    /* 0x0A */ short          box_max_z;
    /* 0x0C */ short          box_min_x;
    /* 0x0E */ short          box_min_y;
    /* 0x10 */ short          box_min_z;
} ColTree; // size = 0x12

typedef struct ColNode {
    /* 0x00 */ unsigned short a;
    /* 0x02 */ short          b;
    /* 0x04 */ short          c;
} ColNode; // size = 0x6

typedef struct ColHead {
    /* 0x00 */ short unk_0;
    /* 0x02 */ short unk_2;
    /* 0x04 */ short range;
} ColHead; // size = 0x6

typedef struct ColEntry {
    /* 0x00 */ ColHead *unk_0;
    /* 0x04 */ void    *unk_4;
} ColEntry; // size = 0x8

typedef struct ColFile {
    /* 0x00 */ unsigned short *wave_no;
    /* 0x04 */ int             unk_4;
    /* 0x08 */ int             unk_8;
    /* 0x0C */ ColEntry       *entries;
} ColFile; // size = 0x10

typedef struct ColObj {
    /* 0x00 */ struct ColObj *next;
    /* 0x04 */ unsigned char  unk_4[0x14];
    /* 0x18 */ ObjSolid      *solid;
    /* 0x1C */ unsigned char  unk_1C[0x42];
    /* 0x5E */ unsigned short file;
    /* 0x60 */ unsigned int   unk_60;
    /* 0x64 */ unsigned char  unk_64[8];
    /* 0x6C */ unsigned char  entry;
} ColObj; // size = 0x70

typedef struct ColHit {
    /* 0x00 */ float       x;
    /* 0x04 */ float       y;
    /* 0x08 */ float       z;
    /* 0x0C */ float       move_x;
    /* 0x10 */ float       move_y;
    /* 0x14 */ float       move_z;
    /* 0x18 */ float       unk_18;
    /* 0x1C */ float       unk_1C;
    /* 0x20 */ float       unk_20;
    /* 0x24 */ float       unk_24;
    /* 0x28 */ float       unk_28;
    /* 0x2C */ float       unk_2C;
    /* 0x30 */ float       unk_30;
    /* 0x34 */ signed char unk_34;
    /* 0x36 */ short       unk_36;
    /* 0x38 */ short       unk_38;
    /* 0x3C */ float       unk_3C;
    /* 0x40 */ ObjSolid   *solid;
    /* 0x44 */ ColObj     *obj;
} ColHit; // size = 0x48

float  func_800273E0(ColHit *hit, ColObj *obj, unsigned char arg2, float arg3);
void   func_80027A7C(float x, float y, float z, float move_x, float move_y, float move_z, float scale, void *arg7, ColHead *head, ColHit *hit);
ColHit func_80028B28(float x, float y, float z, float move_x, float move_y, float move_z);
short  func_80029E08(float x, float y, float z);
int    func_80029E58(float origin_x, float origin_y, float origin_z, float scale, void *p, void *n);
int    func_8002A168(float origin_x, float origin_y, float origin_z);
ColHit func_8002A458(float x, float y, float z, float move_x, float move_y, float move_z);

extern ColPlane *D_80168F60;
extern ColNode  *D_80168F64;
extern ColFile  *D_80236984[];

#endif // COLLISION_H
