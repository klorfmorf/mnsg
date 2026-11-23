#include <stdarg.h>

#include "structs.h"
#include "system/main.h"
#include "unk.h"

void  func_80001928(unsigned int *func, unsigned int jump);
void  func_800019C0(const char *fmt, ...);
void  func_80001A00(const char *fmt, ...);
char *func_80001A40(char *arg, const char *str, int count);

// libultra
int _Printf(char *(*prout)(char *, const char *, int), char *arg, const char *fmt, va_list args);

// clang-format off

// <<<<< data >>>>>
void *D_80054900[4] = {
    osSyncPrintf, rmonPrintf, NULL, NULL,
};
// clang-format on

void func_80001810(void)
{
    if (*KMC_DEBUG_ADDR != 0x4B4D4300) {
        osPiWriteIo((unsigned int) &IS_DEBUG_BUFFER->put, 0);
        osPiWriteIo((unsigned int) &IS_DEBUG_BUFFER->get, 0);
        osPiWriteIo((unsigned int) &IS_DEBUG_BUFFER->magic, IS_DEBUG_MAGIC);
    }
}

void func_8000186C(void)
{
    unsigned short i;

    if (*KMC_DEBUG_ADDR != 0x4B4D4300) {
        func_80001640(0, &D_80304000[0x000], 0x100);
        func_80001640(0x01000000, &D_80304000[0x100], 0x100);

        for (i = 0; i < 0x100; i++) {
            if (D_80304000[i] != D_80304000[i + 0x100]) {
                func_80001928((unsigned int *) rmonPrintf, (unsigned int) func_800019C0);
                func_80001928((unsigned int *) osSyncPrintf, (unsigned int) func_80001A00);
                return;
            }
        }
    }
}

void func_80001928(unsigned int *func, unsigned int jump)
{
    func[0] = 0x3C190000 + (unsigned short) (jump >> 16);
    func[1] = 0x27390000 + (unsigned short) jump;
    func[2] = 0x03200008;
    func[3] = 0;
    osWritebackDCache(func, 16);
}

void func_80001980(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    _Printf(func_80001A40, 0, fmt, args);
    va_end(args);
}

void func_800019C0(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    _Printf(func_80001A40, 0, fmt, args);
    va_end(args);
}

void func_80001A00(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    _Printf(func_80001A40, 0, fmt, args);
    va_end(args);
}

char *func_80001A40(char *arg, const char *str, int count)
{
    unsigned long data;
    int           pos;
    int           start;
    int           end;
    unsigned int  addr;
    int           shift;

    osPiReadIo((unsigned int) &IS_DEBUG_BUFFER->magic, &data);

    if (data != IS_DEBUG_MAGIC) {
        return (char *) 1;
    }

    osPiReadIo((unsigned int) &IS_DEBUG_BUFFER->get, &data);
    pos = data;

    osPiReadIo((unsigned int) &IS_DEBUG_BUFFER->put, &data);
    start = data;
    end   = start + count;

    if (end >= IS_DEBUG_BUFFER_SIZE) {
        end -= IS_DEBUG_BUFFER_SIZE;
        if (pos < end || start < pos) {
            return (char *) 1;
        }
    } else {
        if (start < pos && pos < end) {
            return (char *) 1;
        }
    }

    while (count) {
        addr  = (unsigned int) &IS_DEBUG_BUFFER->data + (start & 0x0FFFFFFC);
        shift = (3 - (start & 3)) * 8;

        if (*str) {
            osPiReadIo(addr, &data);
            osPiWriteIo(addr, (*str << shift) | (data & ~(0xFF << shift)));
            start++;

            if (start >= IS_DEBUG_BUFFER_SIZE) {
                start -= IS_DEBUG_BUFFER_SIZE;
            }
        }

        count--;
        str++;
    }

    osPiWriteIo((unsigned int) &IS_DEBUG_BUFFER->put, start);

    return (char *) 1;
}
