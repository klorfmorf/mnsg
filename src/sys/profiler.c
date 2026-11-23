#include "sys/profiler.h"

void func_80006430(float arg0);

// clang-format off

// <<<<< data >>>>>
int D_8005B230 = 3;

float D_8005B234 = 45720360.0f;

// <<<<< bss >>>>>
OSTime             D_801673C0;
OSTime             D_801673C8;
OSTime             D_801673D0;
OSTime             D_801673D8;
OSTime             D_801673E0;
OSTime             D_801673E8;
OSTime             D_801673F0;
OSTime             D_801673F8;
OSTime             D_80167400;
OSTime             D_80167408;
OSTime             D_80167410;
OSTime             D_80167418;
float              D_80167420;
float              D_80167424;
float              D_80167428;
float              D_8016742C;
float              D_80167430;
float              D_80167434;
float              D_80167438;
float              D_8016743C;
float              D_80167440;
float              D_80167444;
float              D_80167448[2];
unsigned long long D_80167450[128];

// clang-format on

void func_80006350(OSMesgQueue *mq)
{
    unsigned int start;
    unsigned int end;
    double       ticks;
    double       rate;

    if (mq->validCount >= mq->msgCount) {
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    start = osGetCount();
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    end = osGetCount();
    if (osTvType == 0) {
        rate = 50.0;
    } else {
        rate = 60.0;
    }
    ticks = end - start;
    func_80006430((float) (rate * ticks));
}

void func_80006430(float arg0)
{
    D_8005B234 = arg0;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/profiler/func_8000643C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/profiler/func_80006568.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/profiler/func_8000693C.s")

void func_80006B44(Gfx **arg0, float arg1)
{
    int i;

    gDPPipeSync((*arg0)++);
    gDPSetFillColor((*arg0)++, 0x00010001);
    for (i = 0; i <= D_8005B230; i++) {
        gDPFillRectangle((*arg0)++, (int) arg1 * i + 0x28, 210, (int) arg1 * i + 0x28, 220);
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/profiler/func_80006BF8.s")
