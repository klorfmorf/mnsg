#include "sys/amem.h"

void func_800148C0(AmemBlock *arg0, char *arg1, unsigned int arg2)
{
    char        *data;
    unsigned int i;

    i = 0;

    if (arg2 != 0) {
        data = arg1;

        do {
            i += 1;
            *data = 0;
            data += 1;
        } while (i < arg2);
    }

    arg0->pt   = arg1;
    arg0->size = arg2;
    arg0->next = 0;
}

void *amemAlloc(AmemBlock *arg0, int size)
{
    AmemBlock   *cur;
    AmemBlock   *prev;
    AmemBlock   *last;
    char        *start;
    char        *heap;
    unsigned int heap_size;
    char        *p;
    unsigned int n;

    heap      = arg0->pt;
    heap_size = arg0->size;
    start     = heap;
    prev      = 0;
    cur       = arg0->next;
    last      = 0;

    if (cur != 0) {
        do {
            last = cur;
            if ((unsigned int) (cur->pt - start) >= ((unsigned int) (size + 0x4F) >> 6 << 6)) { break; }
            prev  = cur;
            start = (char *) (cur + 1);
            cur   = cur->next;
        } while (cur != 0);
    }

    n = (unsigned int) (size + 0x4F) >> 6 << 6;

    if (cur == 0) {
        cur = (AmemBlock *) (start + n - 0x10);
        if (arg0->next != 0) {
            start = (char *) (prev + 1);
        } else {
            start = heap;
        }
        if ((unsigned int) (heap + heap_size - start) < n) { return 0; }
        cur->pt   = start;
        cur->size = n;
    } else {
        cur       = (AmemBlock *) (start + n - 0x10);
        cur->pt   = start;
        cur->size = n;
        last->up  = cur;
    }

    if (prev == 0) {
        cur->next  = arg0->next;
        cur->up    = 0;
        arg0->next = cur;
    } else {
        cur->next  = prev->next;
        cur->up    = prev;
        prev->next = cur;
    }

    p = start;
    while (p < (char *) cur) { *p++ = 0; }

    return cur->pt;
}

void *func_80014A28(AmemBlock *arg0, int size)
{
    AmemBlock   *cur;
    AmemBlock   *last;
    AmemBlock   *blk;
    char        *start;
    char        *heap;
    unsigned int heap_size;
    char        *p;
    unsigned int n;

    heap      = arg0->pt;
    heap_size = arg0->size;
    start     = heap;
    last      = 0;

    for (cur = arg0->next; cur != 0; cur = cur->next) {
        last  = cur;
        start = (char *) (cur + 1);
    }

    n = (unsigned int) (size + 0x4F) >> 6 << 6;

    if ((unsigned int) heap + heap_size - (unsigned int) start >= n) {
        cur       = (AmemBlock *) (heap + heap_size - 0x10);
        start     = heap + heap_size - n;
        cur->pt   = start;
        cur->size = n;
    } else {
        if (last == 0) { return 0; }

        blk = last;
        while (blk != 0) {
            last = blk->up;
            if (last == 0) {
                start = heap;
            } else {
                start = (char *) (last + 1);
            }
            if ((unsigned int) (blk->pt - start) >= n) { break; }
            blk = last;
        }

        if (blk == 0) { return 0; }

        cur       = (AmemBlock *) (blk->pt - 0x10);
        start     = blk->pt - n;
        cur->pt   = start;
        cur->size = n;
        blk->up   = cur;
    }

    if (last == 0) {
        cur->next  = arg0->next;
        cur->up    = 0;
        arg0->next = cur;
    } else {
        cur->next  = last->next;
        cur->up    = last;
        last->next = cur;
    }

    p = start;
    while (p < (char *) cur) { *p++ = 0; }

    return cur->pt;
}

void *amemFree(AmemBlock *arg0, void *arg1)
{
    AmemBlock *blk;
    AmemBlock *prev;
    AmemBlock *next;
    int        n;
    char      *p;

    for (blk = arg0->next; blk != 0; blk = blk->next) {
        if (arg1 == blk->pt) { break; }
    }

    if (blk == 0) { return 0; }

    prev = blk->up;
    next = blk->next;

    if (blk == arg0->next) {
        arg0->next = next;
    } else {
        prev->next = next;
    }

    if (next != 0) { next->up = prev; }

    p = blk->pt;
    n = blk->size;

    while (n--) { *p++ = 0; }

    return arg1;
}

void func_80014C00(AmemBlock *arg0)
{
    AmemBlock *var_v0;
    int        i;

    PRINTF(("DEBUG amem = %p (%x)\n", arg0->pt, arg0->size));
    for (i = 0, var_v0 = arg0->next; var_v0 != 0; i++, var_v0 = var_v0->next) {
        PRINTF(("DEBUG AMhed[%d]%p { pt=%p size=%x next=%p up=%p}\n", i, var_v0, var_v0->pt, var_v0->size, var_v0->next,
            var_v0->up));
    }
}
