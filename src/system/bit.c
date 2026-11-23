#include "system/bit.h"

// clang-format off

// <<<<< data >>>>>
int D_8006ADC0 = 0;
int D_8006ADC4 = 0;
int D_8006ADC8 = 8;
int D_8006ADCC = 0;

// <<<<< bss >>>>>
unsigned char *D_80168160;
// clang-format on

void bitInit(unsigned char *arg0)
{
    D_8006ADC0 = 0;
    D_8006ADC4 = 0;
    D_8006ADC8 = 8;
    D_8006ADCC = 0;
    D_80168160 = arg0;
}

int bitRead1(void)
{
    if (--D_8006ADC4 >= 0) {
        return ((unsigned int) D_8006ADCC >> D_8006ADC4) & 1;
    }
    D_8006ADC4 = 7;
    D_8006ADCC = *D_80168160++;

    return ((unsigned int) D_8006ADCC >> 7) & 1;
}

int bitRead(int n)
{
    int x = 0;

    while (n > D_8006ADC4) {
        n -= D_8006ADC4;
        x |= (D_8006ADCC & ((1 << D_8006ADC4) - 1)) << n;
        D_8006ADCC = *D_80168160++;
        D_8006ADC4 = 8;
    }
    D_8006ADC4 -= n;

    return (((unsigned int) D_8006ADCC >> D_8006ADC4) & ((1 << n) - 1)) | x;
}
