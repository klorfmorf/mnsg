#ifndef TASK_H
#define TASK_H


#include "common.h"
#include "system/object.h"
#include "system/wave_uty.h"

#define TASK_STATUS_FIELD_UPDATE   0x01
#define TASK_STATUS_MENU_UPDATE    0x02
#define TASK_STATUS_SUSPEND_UPDATE 0x04
#define TASK_STATUS_SUSPEND_DRAW   0x10
#define TASK_STATUS_MENU_DRAW      0x40
#define TASK_STATUS_FIELD_DRAW     0x80
#define TASK_STATUS_UPDATE_MASK    0x07
#define TASK_STATUS_DRAW_MASK      0xD0

typedef struct Task {
    /* 0x00 */ struct Task *next;
    /* 0x04 */ struct Task *unk_4;
    /* 0x08 */ void (*exec[3])(struct Task *, struct Obj *);
    /* 0x14 */ void (*prev_exec)(struct Task *, struct Obj *);
    /* 0x18 */ void          *unk_18;
    /* 0x1C */ void          *unk_1c;
    /* 0x20 */ unsigned short priority;
    /* 0x22 */ unsigned short status;
    /* 0x24 */ unsigned short timer;
    /* 0x28 */ Wave           wave;
    /* 0x30 */ unsigned char  unk_30;
    /* 0x31 */ unsigned char  unk_31;
    /* 0x32 */ unsigned char  unk_32;
    /* 0x33 */ unsigned char  unk_33;
    /* 0x34 */ unsigned int   unk_34;
    /* 0x38 */ unsigned int   unk_38;
    /* 0x3C */ unsigned short unk_3c;
    /* 0x3E */ unsigned short unk_3e;
    /* 0x40 */ unsigned short unk_40;
    /* 0x42 */ unsigned short unk_42;
    /* 0x44 */ unsigned char  unk_44;
    /* 0x45 */ unsigned char  unk_45;
    /* 0x46 */ unsigned char  unk_46;
    /* 0x47 */ unsigned char  unk_47;
    /* 0x48 */ unsigned int   unk_48;
    /* 0x4C */ unsigned char  unk_4c;
    /* 0x4D */ unsigned char  unk_4d;
    /* 0x4E */ unsigned short unk_4e;
    /* 0x50 */ unsigned short unk_50;
    /* 0x52 */ unsigned short unk_52;
    /* 0x54 */ unsigned int   unk_54;
    /* 0x58 */ unsigned int   unk_58;
} Task; // size = 0x5C

void func_80034734(void);
void func_8003488C(char *arg0);

#endif // TASK_H
