#ifndef XPRINTF_H
#define XPRINTF_H


#include "common.h"
#include <stdarg.h>

int _Printf(char *(*prout)(char *, const char *, int), char *arg, const char *fmt, va_list args);

#endif // XPRINTF_H
