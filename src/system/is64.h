#ifndef IS64_H
#define IS64_H


#include "common.h"

#define IS_DEBUG_BUFFER      ((IsDebug *) 0xB1FF0000)
#define IS_DEBUG_MAGIC       0x49533634
#define IS_DEBUG_BUFFER_SIZE 0xFFE0
#define KMC_DEBUG_ADDR       ((int *) 0xBFF00000)

typedef struct IsDebug {
    /* 0x0000 */ unsigned int  magic;
    /* 0x0004 */ unsigned int  get;
    /* 0x0008 */ unsigned char unk_08[12];
    /* 0x0014 */ unsigned int  put;
    /* 0x0018 */ unsigned char unk_18[8];
    /* 0x0020 */ unsigned char data[0xFFE0];
} IsDebug; // size = 0x10000

void  func_80001810(void);
void  func_8000186C(void);
void  func_80001928(unsigned int *func, unsigned int jump);
void  func_80001980(const char *fmt, ...);
void  func_800019C0(const char *fmt, ...);
void  func_80001A00(const char *fmt, ...);
char *func_80001A40(char *arg, const char *str, int count);

#endif // IS64_H
