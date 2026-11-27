#ifndef COMMON_H
#define COMMON_H

#include <ultra64.h>

#ifdef __clang__
#define PRINTF(args) ((void) sizeof(osSyncPrintf args))
#else
#define PRINTF(args) ((void) (args))
#endif

// Some functions only match with this form.
#define PRINTF_DEAD(args) \
    if (0) { osSyncPrintf args; }

#endif // COMMON_H
