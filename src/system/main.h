#ifndef MAIN_H
#define MAIN_H


#include "common.h"
#include "scheduler.h"

void func_80000450(void);
void func_800004AC(void *arg);
void func_80000580(void *arg);
void func_8000098C(void);
void func_80000AD8(void *arg);
void func_80000D00(void);
void func_800011A0(void);
void func_800012FC(void);
void func_80001328(void);
void func_80001498(void);
void func_80001614(void);
void func_80001640(u32 rom, void *dst, s32 size);
void func_800016E4(OSScTask *task, OSScMsg *msg, u64 *ucode, u64 *ucode_data, int done);

extern OSThread    D_80080020;
extern OSThread    D_800841D0;
extern OSThread    D_80088380;
extern OSMesgQueue D_8008A530;
extern OSMesg      D_8008A548[0xC8];
extern OSMesgQueue D_8008A868;

#endif // MAIN_H
