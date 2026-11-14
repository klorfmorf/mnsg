#ifndef PIC_H
#define PIC_H


#include "common.h"

#define PIC_NO_COLOR 0x80000000

typedef struct Pic {
    /* 0x00 */ int             width;
    /* 0x04 */ int             height;
    /* 0x08 */ int             bits;
    /* 0x0C */ int             size;
    /* 0x10 */ int             type;
    /* 0x14 */ int             transparent;
    /* 0x18 */ unsigned char  *data;
    /* 0x1C */ void           *image;
    /* 0x20 */ unsigned short *palette;
} Pic; // size = 0x24

typedef enum PicType {
    PIC_TYPE_DIRECT,
    PIC_TYPE_PALETTE,
    PIC_TYPE_NO_PALETTE
} PicType;

typedef struct ColorCacheEntry {
    /* 0x00 */ short color;
    /* 0x02 */ short next;
    /* 0x04 */ short prev;
} ColorCacheEntry; // size = 0x6

Pic  *picOpen(unsigned char *data, Pic *pic);
Pic  *picDecode(int arg0, void *buf, Pic *pic);
void *picDecode8(int arg0, void *buf, Pic *pic);
void *picDecode4(int arg0, void *buf, Pic *pic);
void  picReadPalette(int n, Pic *pic);
void  picReadHeader(Pic *pic);
void  picExpand16(Pic *pic);
void  picExpandChain16(Pic *pic, int x, int y, int c);
void  picExpand8(Pic *pic);
void  picExpand4(Pic *pic);
int   picReadLenIndexed(Pic *pic);
void  picExpandChain8(Pic *pic, int x, int y, int c);
void  picExpandChain4(Pic *pic, int x, int y, int c);
int   picReadLen(void);
int   picReadColor(Pic *pic);
void  picColorCacheInit(void);
int   picNewColor(Pic *pic, int c);
int   picGetColor(Pic *pic, int idx);
int   picPoint(int x, int y);
void  picPset(Pic *pic, int x, int y, int c);
void  picReset(int x, int y);
void  picUnused(void);
void  picPset8(int x, int y, int c);
int   picPoint4(int x, int y);
void  picPset4(int x, int y, int c);
int   picParseHex(unsigned char *s);
void  picClearTransparent(Pic *pic);
void  picFlagSet(unsigned char *bits, int i);
void  picFlagClear(unsigned char *bits, int i);
int   picFlagTest(unsigned char *bits, int i);

#endif // PIC_H
