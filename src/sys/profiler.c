#include "sys/profiler.h"

void func_80006430(float arg0);
void func_80006B44(Gfx **arg0, float arg1);
void func_80006BF8(Gfx **gfxp, unsigned int color, float x, float width, int row);

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
float              D_80167448;
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

void func_8000643C(void)
{
    D_801673C0 = D_801673C8 = D_801673D0 = D_801673D8 = D_801673E0 = D_801673E8 = D_801673F0 = D_801673F8 =
        D_80167400 = D_80167408 = D_80167410 = D_80167418 = 0;
    D_80167424 = D_80167428 = D_8016742C = D_80167430 = D_80167434 = D_80167438 = 0.0f;
    D_8016743C = D_80167440 = D_80167444 = D_80167448 = 0.0f;
}

void func_80006568(unsigned int event)
{
    switch (event) {
        case 0:
            D_801673C0 = osGetTime();
            break;
        case 1:
            D_801673C8 = osGetTime();
            D_8016743C += (float) (D_801673C8 - D_801673C0);
            D_801673F0 = osGetTime();
            break;
        case 2:
            D_8016743C = 0.0f;
            D_801673C0 = osGetTime();
            break;
        case 3:
            if (D_801673F0 == 0) {
                D_801673F0 = osGetTime();
            }
            break;
        case 4:
            D_801673F8 = osGetTime();
            D_80167440 = D_801673F8 - D_801673F0;
            D_801673F0 = 0;
            break;
        case 5:
            D_80167440 = 0.0f;
            D_801673F0 = osGetTime();
            break;
        case 6:
            D_80167400 = osGetTime();
            break;
        case 7:
            D_80167408 = osGetTime();
            D_80167444 += (float) (D_80167408 - D_80167400);
            break;
        case 8:
            if (D_801673D0 == 0) {
                D_801673D0 = osGetTime();
            }
            break;
        case 9:
            D_801673D8 = osGetTime();
            D_80167430 = D_801673D8 - D_801673D0;
            D_80167434 = D_80167448;
            D_80167448 = 0.0f;
            D_801673D0 = 0;
            break;
        case 10:
            D_80167410 = osGetTime();
            break;
        case 11:
            D_80167418 = osGetTime();
            D_80167448 += (float) (D_80167418 - D_80167410);
            break;
        case 12:
            D_801673E0 = osGetTime();
            D_80167420 = D_801673E0 - D_801673E8;
            D_801673E8 = D_801673E0;
            break;
        case 13:
            D_80167424 = D_8016743C;
            D_80167428 = D_80167440;
            D_8016742C = D_80167444;
            D_8016743C = D_80167440 = D_80167444 = 0.0f;
            break;
    }
}

void func_8000693C(Gfx **gfxp)
{
    float scale;
    float first;
    float second;
    float third;
    float x;

    scale = 240 / D_8005B230;
    gDPPipeSync((*gfxp)++);
    gDPSetCycleType((*gfxp)++, G_CYC_FILL);
    gSPClearGeometryMode((*gfxp)++, G_ZBUFFER);
    gDPSetRenderMode((*gfxp)++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    first = D_8016742C / D_80167420 * scale;
    func_80006BF8(gfxp, ((GPACK_RGBA5551(120, 0, 0, 1) << 16) | GPACK_RGBA5551(120, 0, 0, 1)), 40, first, 0);
    second = D_80167424 / D_80167420 * scale;
    x      = 40 + first;
    func_80006BF8(gfxp, ((GPACK_RGBA5551(0, 120, 0, 1) << 16) | GPACK_RGBA5551(0, 120, 0, 1)), x, second, 0);
    third = D_80167428 / D_80167420 * scale;
    func_80006BF8(gfxp, ((GPACK_RGBA5551(0, 0, 120, 1) << 16) | GPACK_RGBA5551(0, 0, 120, 1)), x + second, third, 0);
    second = D_80167430 / D_80167420 * scale;
    func_80006BF8(gfxp, ((GPACK_RGBA5551(0, 0, 120, 1) << 16) | GPACK_RGBA5551(0, 0, 120, 1)), 40, second, 4);
    func_80006B44(gfxp, scale);
    gDPPipeSync((*gfxp)++);
}

void func_80006B44(Gfx **arg0, float arg1)
{
    int i;

    gDPPipeSync((*arg0)++);
    gDPSetFillColor((*arg0)++, 0x00010001);
    for (i = 0; i <= D_8005B230; i++) {
        gDPFillRectangle((*arg0)++, (int) arg1 * i + 0x28, 210, (int) arg1 * i + 0x28, 220);
    }
}

void func_80006BF8(Gfx **gfxp, unsigned int color, float x, float width, int row)
{
    gDPPipeSync((*gfxp)++);
    if (width < 240) {
        gDPSetFillColor((*gfxp)++, color);
        gDPFillRectangle((*gfxp)++, x, row + 210, x + width, row + 210 + 3);
    } else {
        gDPSetFillColor((*gfxp)++, ((GPACK_RGBA5551(120, 0, 0, 1) << 16) | GPACK_RGBA5551(120, 0, 0, 1)));
        gDPFillRectangle((*gfxp)++, 40, row + 210, 40 + 240, row + 210 + 3);
    }
}
