#include "sys/save_flags.h"
#include "common.h"
#include "sys/sys.h"

// clang-format off

// <<<<< bss >>>>>
unsigned char D_80168E90[100];
unsigned char D_80168EF4[4];
unsigned char D_80168EF8[100];
unsigned char D_80168F5C[4];

// clang-format on

void func_80023DF0(int index)
{
    unsigned char byte;
    unsigned char bit;
    unsigned char mask;

    byte = index / 8;
    bit  = index % 8;
    mask = 1 << bit;
    D_80168E90[byte] |= mask;
}

void func_80023E40(int index)
{
    unsigned char byte;
    unsigned char bit;
    unsigned char mask;

    byte = index / 8;
    bit  = index % 8;
    mask = 1 << bit;
    D_80168E90[byte] &= ~mask;
}

unsigned char func_80023E94(int index)
{
    unsigned char byte;
    unsigned char bit;
    unsigned char mask;

    byte = index / 8;
    bit  = index % 8;
    mask = 1 << bit;
    return D_80168E90[byte] & mask;
}

void func_80023EE4(void)
{
    int i;

    for (i = 0; i < 100; i++) {
        D_80168E90[i] = 0;
    }
}

void func_80023F14(int index)
{
    unsigned char byte;
    unsigned char bit;
    unsigned char mask;

    byte = index / 8;
    bit  = index % 8;
    mask = 1 << bit;
    D_80168EF8[byte] |= mask;
}

void func_80023F64(int index)
{
    unsigned char byte;
    unsigned char bit;
    unsigned char mask;

    byte = index / 8;
    bit  = index % 8;
    mask = 1 << bit;
    D_80168EF8[byte] &= ~mask;
}

unsigned char func_80023FB8(int index)
{
    unsigned char byte;
    unsigned char bit;
    unsigned char mask;

    byte = index / 8;
    bit  = index % 8;
    mask = 1 << bit;
    return D_80168EF8[byte] & mask;
}

void func_80024008(void)
{
    int i;

    for (i = 0; i < 100; i++) {
        D_80168EF8[i] = 0;
    }
}

void func_80024038(int index)
{
    unsigned char byte;
    unsigned char bit;
    unsigned char mask;

    byte = index / 8;
    bit  = index % 8;
    mask = 1 << bit;
    D_8015C608.flags[byte] |= mask;
}

void func_80024088(int index)
{
    unsigned char byte;
    unsigned char bit;
    unsigned char mask;

    byte = index / 8;
    bit  = index % 8;
    mask = 1 << bit;
    D_8015C608.flags[byte] &= ~mask;
}

unsigned char func_800240DC(int index)
{
    unsigned char byte;
    unsigned char bit;
    unsigned char mask;

    byte = index / 8;
    bit  = index % 8;
    mask = 1 << bit;
    return D_8015C608.flags[byte] & mask;
}

void func_8002412C(void)
{
    int i;

    for (i = 0; i < 100; i++) {
        D_8015C608.flags[i] = 0;
    }
}
