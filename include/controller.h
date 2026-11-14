#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "common.h"

typedef struct Controller {
    /* 0x00 */ unsigned short status;
    /* 0x02 */ unsigned short button_held_down;
    /* 0x04 */ unsigned short button_pressed;
    /* 0x06 */ short          stick_raw_x;
    /* 0x08 */ short          stick_raw_y;
    /* 0x0C */ float          stick_magnitude;
    /* 0x10 */ float          stick_x;
    /* 0x14 */ float          stick_y;
} Controller; // size = 0x18

void func_80004910(void);
void func_800049D0(void);
void func_80004AF8(void);

#endif // CONTROLLER_H
