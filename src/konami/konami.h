#ifndef KONAMI_H
#define KONAMI_H


#include "common.h"

typedef struct KonamiLogoKey {
    /* 0x00 */ float a[3];
    /* 0x0C */ float b[3];
    /* 0x18 */ float c;
} KonamiLogoKey; // size = 0x1C

typedef struct KonamiLogoMtx {
    /* 0x000 */ Mtx proj;
    /* 0x040 */ Mtx view;
    /* 0x080 */ Mtx ident;
    /* 0x0C0 */ Mtx obj[3];
} KonamiLogoMtx; // size = 0x180

typedef struct KonamiLogoMap {
    /* 0x00 */ unsigned short  enabled;
    /* 0x02 */ unsigned short  unk_2;
    /* 0x04 */ unsigned char  *cells;
    /* 0x08 */ unsigned short *tiles;
    /* 0x0C */ unsigned short *offsets;
    /* 0x10 */ unsigned char  *image;
    /* 0x14 */ unsigned char  *palette;
    /* 0x18 */ unsigned short unk_18;
    /* 0x1A */ unsigned char  format;
    /* 0x1B */ unsigned char  unk_1b;
    /* 0x1C */ short          cols;
    /* 0x1E */ short          rows;
    /* 0x20 */ short          cell_w;
    /* 0x22 */ short          cell_h;
} KonamiLogoMap; // size = 0x24

typedef union KonamiLogoFade {
    int           amount;
    unsigned char byte[4];
} KonamiLogoFade;

typedef struct KonamiLogoSteps {
    void (*fn[2])(void);
} KonamiLogoSteps; // size = 0x8

void func_801CB460_69E080(void);
void func_801CB4BC_69E0DC(void);
void func_801CB53C_69E15C(void);
void func_801CB610_69E230(void);
Gfx *func_801CB668_69E288(int buf, Gfx *dl);
void func_801CB95C_69E57C(unsigned char alpha);
void func_801CB9CC_69E5EC(void);
void func_801CBAF8_69E718(Gfx *dl, Mtx *mtx, KonamiLogoKey *keys, int frame, float t);
void func_801CBC8C_69E8AC(KonamiLogoMtx *m, KonamiLogoKey *keys, int frame, float t);
void func_801CBF5C_69EB7C(KonamiLogoMap *map);
void func_801CBF98_69EBB8(void);
void func_801CC0C4_69ECE4(KonamiLogoMap *map);

extern KonamiLogoSteps D_801D6C30_6A9850;
extern KonamiLogoMap   D_801D5348_6A7F68;
extern KonamiLogoMap   D_801D536C_6A7F8C;
extern Gfx             D_801D5390_6A7FB0[];
extern Gfx             D_801D5430_6A8050[];
extern Gfx             D_801D54B8_6A80D8[];
extern Gfx             D_801D5E48_6A8A68[];
extern Gfx             D_801D67D8_6A93F8[];
extern Gfx             D_801D6C48_6A9868[];
extern Vp              D_801D6C38_6A9858;
extern KonamiLogoKey   D_801CC7E0_69F400[];
extern KonamiLogoKey   D_801CCA80_69F6A0[];
extern KonamiLogoKey   D_801CCD20_69F940[];
extern KonamiLogoKey   D_801CCFC0_69FBE0[];

extern int            D_801D6D00_6A9920;
extern KonamiLogoMtx  D_801D6D08_6A9928[2];
extern int            D_801D7008_6A9C28;
extern int            D_801D700C_6A9C2C;
extern int            D_801D7010_6A9C30;
extern float          D_801D7014_6A9C34;
extern int            D_801D7018_6A9C38;
extern Gfx           *D_801D701C_6A9C3C;
extern int            D_801D7020_6A9C40;
extern int            D_801D7024_6A9C44;
extern int            D_801D7028_6A9C48;
extern KonamiLogoFade D_801D702C_6A9C4C;
extern KonamiLogoMap  D_801D7030_6A9C50;
extern unsigned char *D_801D7044_6A9C64;

#endif // KONAMI_H
