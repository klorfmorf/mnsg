#ifndef COMMON_H
#define COMMON_H

#include <ultra64.h>

typedef struct WAVE_W {
    unsigned short wave_no;
    int            data;
} WAVE_W;

typedef struct AMEM_W {
    char*          pt;
    unsigned int   size;
    struct AMEM_W* next;
    struct AMEM_W* up;
} AMEM_W;

typedef struct TASK_W {
    struct TASK_W* next;
    struct TASK_W* unk_4;
    void          (*functions[3])(struct TASK_W*, void*);
    void          (*previous_function)(struct TASK_W*, void*);
    void*          unk_14;
    void*          unk_1c;
    unsigned short priority;
    unsigned short unk_22;
    unsigned short timer;
    WAVE_W         wave;
    unsigned char  unk_30;
    unsigned char  unk_31;
    unsigned char  unk_32;
    unsigned char  unk_33;
    unsigned int   unk_34;
    unsigned int   unk_38;
    unsigned short unk_3c;
    unsigned short unk_3e;
    unsigned short unk_40;
    unsigned short unk_42;
    unsigned char  unk_44;
    unsigned char  unk_45;
    unsigned char  unk_46;
    unsigned char  unk_47;
    unsigned int   unk_48;
    unsigned char  unk_4c;
    unsigned char  unk_4d;
    unsigned short unk_4e;
    unsigned short unk_50;
    unsigned short unk_52;
    unsigned int   unk_54;
    unsigned int   unk_58;
} TASK_W;

#endif // COMMON_H
