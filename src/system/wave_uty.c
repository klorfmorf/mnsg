#define NO_PROTO_func_80001DF4

#include "system/wave_uty.h"
#include "system/data_load.h"
#include "system/main.h"
#include "system/pic.h"
#include "task.h"
#include "unk.h"

void func_80013940(void)
{
    int i;

    for (i = 0; i < WAVE_DECODE_MAX; i++) { D_80167FC0[i].data = D_80167FC0[i].wave_no = 0; }

    D_80167FC0[0].data    = (int) &D_80304000;
    D_80167FC0[0].wave_no = 0;
}

void func_800139A4(unsigned short i)
{
    if (i < WAVE_DECODE_MAX) { D_80167FC0[i++].wave_no = 0; }

    while (i++ < WAVE_DECODE_MAX) {
        D_80167FC0[i].data = D_80167FC0[i].wave_no = 0;
    }
}

void func_80013A24(unsigned short wave_no)
{
    int found;
    int i;

    for (i = 0; i < WAVE_DECODE_MAX && wave_no != D_80167FC0[i].wave_no; i++) {}

    if (i < WAVE_DECODE_MAX) { 
        D_80167FC0[i].wave_no = 0; 
    }

    for (; i++ < WAVE_DECODE_MAX;) {
        D_80167FC0[i].data = D_80167FC0[i].wave_no = 0;
        i++;
    }
}

int func_80013AC4(unsigned short *wave_no_list)
{
    int sp24;

    while (*wave_no_list != 0) {
        sp24 = func_80013B14(*wave_no_list++);
    }

    return sp24;
}

int func_80001DF4(unsigned short);
int func_80013B14(unsigned short arg0) {
    int sp24;
    int var_a1;
    Wave* var_s0;

    var_s0 = D_80167FC0;

    while (var_s0->wave_no != 0) {
        if (arg0 == var_s0->wave_no) {
            var_s0++;
            return var_s0->data;
        }

        var_s0++;

        if (var_s0 >= &D_80167FC0[WAVE_DECODE_MAX]) {
            return 0;
        }
    }

    var_a1 = var_s0->data;
    var_s0->wave_no = arg0;

    if (func_80001DF4(arg0) != 0) {
        var_a1 = (var_a1 + 0xFFF) & ~0xFFF;
        var_s0->data = var_a1 | 0x40000000;
    }

    sp24 = func_80001C00(var_s0->wave_no, var_a1);
    sp24 = (sp24 + 0x3F) & ~0x3F;

    func_800142BC(var_s0->wave_no, var_a1);

    var_s0++;
    var_s0->wave_no = 0;
    var_s0->data = sp24;

    return sp24;
}

void func_80013C0C(unsigned short arg0)
{
    Wave *temp_v0;
    int   temp_t8;

    temp_v0 = &D_80167FC0[arg0];
    temp_t8 = temp_v0->data & 0xBFFFFFFF;
    func_80001C00(temp_v0->wave_no, temp_t8);
    func_800142BC(temp_v0->wave_no, temp_t8);
}

void func_80013C70(unsigned short *arg0)
{
    func_80013C90(arg0, 4);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/wave_uty/func_80013C90.s")

int func_800141C4(unsigned int wave_no)
{
    Wave *entry = (Wave *) &D_80167FC0;

    if (wave_no == 0) {
        return 0;
    }

    while (entry->wave_no != 0) {
        if (entry->wave_no == wave_no) {
            return entry->data;
        }

        entry++;
    }

    return -1;
}

int func_80014218(ObjSolid *solid)
{
    int result = 0;
    int i;

    for (i = 0; i < 6; i++) {
        if (solid->SegWave[i].wave_no == 0) { continue; }

        if (i + 8 == func_80001E50(solid->SegWave[i].wave_no)) {
            solid->SegWave[i].data = func_800141C4(solid->SegWave[i].wave_no) & 0xBFFFFFFF;
        } else {
            func_80001E50(solid->SegWave[i].wave_no);
            result = -1;
        }
    }

    return result;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/wave_uty/func_800142BC.s")

#ifdef NON_MATCHING
unsigned char *func_800144E8(unsigned int id, unsigned char *src, unsigned char *dst)
{
    unsigned char *end;
    Pic            pic;
    unsigned char *buf = dst;
    unsigned int   i;
    unsigned char *p;

    end = func_800145B4(id, src);

    if (src[0] == 'P' && src[1] == 'I' && src[2] == 'C') {
        picOpen(src, &pic);
        picDecode(src, dst, &pic);
        dst += pic.size;
    } else {
        if (end != src) {
            p = src;
            i = 0;
            do {
                i += 1;
                p += 1;
                dst += 1;
                dst[-1] = p[-1];
            } while (i < end - src);
        }
    }

    osWritebackDCache(buf, dst - buf);
    return dst;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/wave_uty/func_800144E8.s")
#endif

unsigned char *func_800145B4(unsigned int id, unsigned char *data)
{
    int            rom;
    unsigned int   size;
    unsigned char  busy;
    unsigned char *end;
    unsigned short i;

    if (id >= 0x8770) { return data; }

    if (id >= 0x8000) {
        size = func_80014698(id, &rom);
        end  = data + size;

        if (size != 0) {
            busy       = D_8015C5D4;
            D_8015C5D4 = 1;
            func_80001640(rom, data, size);
            D_8015C5D4 = busy;

            if (id == 0x818D) {
                for (i = 0; i < size; i++) {}
            }
        }
        return end;
    }

    return (unsigned char *) func_80001C00(id, (int) data);
}

#ifdef NON_MATCHING
short func_80014698(unsigned int id, int *rom)
{
    int          i;
    int          start;
    int          end;
    int          size;
    unsigned int first;
    unsigned int next;

    if (id >= 0x8770) {
        if (rom != 0) { *rom = 0; }
        return 0;
    }

    if (id >= 0x8000) {
        for (i = 0; D_80063940[i] != 0 && id >= D_80063940[i]; i += 2) {}
        i -= 2;

        start = func_80001D68(D_80063940[i + 1]);
        end   = func_80001D94(D_80063940[i + 1]);
        first = D_800639D4[id - 0x8000];
        next  = D_800639D4[id - 0x8000 + 1];

        size = (next != 0 && (D_80063940[i + 2] == 0 || id + 1 < D_80063940[i + 2])) ? next - first : end - ((first & 0xFFFFFF) + start);

        if (rom != 0) { *rom = (first & 0xFFFFFF) + start; }
        return size;
    }

    if (rom != 0) { *rom = func_80001D68(id & 0xFFFF); }
    return func_80001D94(id & 0xFFFF) - func_80001D68(id & 0xFFFF);
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/system/wave_uty/func_80014698.s")
#endif

void func_8001481C(struct Task *task)
{
    int data = task->wave.data;
    
    func_80001EB0(task->wave.wave_no, data);
}

int func_80014840(int arg0, unsigned int wave_no)
{
    int data;

    if (arg0 > 0) {
        data = func_800141C4(wave_no);

        if (data == -1) {
            *(int *) -1 = 0;
        }

        data = data & 0xBFFFFFFF;

        return (arg0 - (func_80001E50(wave_no) << 24)) + data;
    }

    return arg0;
}

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
    AmemBlock *cur;
    AmemBlock *prev;
    AmemBlock *last;
    char      *start;
    char      *heap;
    unsigned int heap_size;
    char      *p;
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
        cur->next = arg0->next;
        cur->up   = 0;
        arg0->next = cur;
    } else {
        cur->next = prev->next;
        cur->up   = prev;
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
        cur        = (AmemBlock *) (heap + heap_size - 0x10);
        start      = heap + heap_size - n;
        cur->pt    = start;
        cur->size  = n;
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

        cur        = (AmemBlock *) (blk->pt - 0x10);
        start      = blk->pt - n;
        cur->pt    = start;
        cur->size  = n;
        blk->up    = cur;
    }

    if (last == 0) {
        cur->next = arg0->next;
        cur->up   = 0;
        arg0->next = cur;
    } else {
        cur->next = last->next;
        cur->up   = last;
        last->next = cur;
    }

    p = start;
    while (p < (char *) cur) { *p++ = 0; }

    return cur->pt;
}

void *amemFree(AmemBlock *arg0, char *arg1)
{
    AmemBlock *blk;
    AmemBlock *prev;
    AmemBlock *next;
    int          n;
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

    var_v0 = arg0->next;

    while (var_v0 != 0) {
        var_v0 = var_v0->next;
    }
}
