#ifndef PRINT_TEXT_H
#define PRINT_TEXT_H


#include "common.h"

#define TEXT_LABEL_NONE        0
#define TEXT_LABEL_STRING      1
#define TEXT_LABEL_HEXADECIMAL 2

typedef struct TextureOffsets {
    /* 0x0 */ short s;
    /* 0x2 */ short t;
} TextureOffsets; // size = 0x4

void func_80004240(void);
void func_8000427C(short entry);
void func_800042AC(short entry, unsigned char *string, short x, short y);
void func_800042F4(short entry, unsigned int number, short x, short y);
void func_8000433C(void);

extern unsigned short D_8005B248[16];
extern TextureOffsets D_8005B270[];
extern TextureOffsets D_8005B39C[16];
extern Gfx            D_8006D508[];
extern unsigned char  D_80301000[];

#endif // PRINT_TEXT_H
