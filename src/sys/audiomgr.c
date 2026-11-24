#include "structs.h"
#include "sys/main.h"
#include "sys/sched.h"
#include "unk.h"

static void      __amMain(void *arg);
static int       __amDMA(int addr, int len, void *state);
static ALDMAproc __amDmaNew(AMDMAState **state);
static int       __amHandleFrameMsg(AudioInfo *info, AudioInfo *next);
static void      __amHandleDoneMsg(AudioInfo *info);
static void      __clearAudioDMA(void);

// clang-format off

// <<<<< data >>>>>
unsigned int audFrameCt = 0;

unsigned int nextDMA = 0;

unsigned int curAcmdList = 0;

// <<<<< bss >>>>>
AMAudioMgr    __am;
static unsigned long long audioStack[AUDIO_STACKSIZE / sizeof(unsigned long long)];
AMDMAState    dmaState;
AMDMABuffer   dmaBuffs[32];
unsigned int  minFrameSize;
unsigned int  frameSize;
unsigned int  maxFrameSize;
unsigned int  maxRSPCmds;
OSIoMesg      audDMAIOMesgBuf[64];
OSMesgQueue   audDMAMessageQ;
OSMesg        audDMAMessageBuf[64];

// clang-format on

void amCreateAudioMgr(ALSynConfig *c, int pri, amConfig *amc)
{
    unsigned int i;
    float        fsize;

    c->dmaproc    = __amDmaNew;
    c->outputRate = osAiSetFrequency(amc->outputRate);

    for (i = 16; i != 0; i--) {
    }

    fsize     = (float) amc->framesPerField * c->outputRate / 60.0f;
    frameSize = (int) fsize;
    if (frameSize < fsize) {
        frameSize++;
    }
    if (frameSize & 0xF) {
        frameSize = (frameSize & ~0xF) + 0x10;
    }
    minFrameSize = frameSize - 16;
    maxFrameSize = frameSize + 0x100;

    alInit(&__am.g, c);

    dmaBuffs[0].prev = 0;
    dmaBuffs[0].next = 0;
    for (i = 0; i < 31; i++) {
        alLink((ALLink *) &dmaBuffs[i + 1], (ALLink *) &dmaBuffs[i]);
        dmaBuffs[i].ptr = alHeapDBAlloc(0, 0, c->heap, 1, 0xC00);
    }
    dmaBuffs[i].ptr = alHeapDBAlloc(0, 0, c->heap, 1, 0xC00);

    for (i = 0; i < 2; i++) {
        __am.ACMDList[i] = alHeapDBAlloc(0, 0, c->heap, 1, amc->maxACMDSize * 8);
    }

    maxRSPCmds = amc->maxACMDSize;

    for (i = 0; i < 3; i++) {
        __am.audioInfo[i]                = alHeapDBAlloc(0, 0, c->heap, 1, 0x90);
        __am.audioInfo[i]->msg.done.type = 2;
        __am.audioInfo[i]->msg.done.info = __am.audioInfo[i];
        __am.audioInfo[i]->data          = alHeapDBAlloc(0, 0, c->heap, 1, maxFrameSize * 4);
    }

    osCreateMesgQueue(&__am.audioReplyMsgQ, __am.audioReplyMsgBuf, 64);
    osCreateMesgQueue(&__am.audioFrameMsgQ, __am.audioFrameMsgBuf, 64);
    osCreateMesgQueue(&audDMAMessageQ, audDMAMessageBuf, 64);

    osCreateThread(&__am.thread, 3, __amMain, NULL, (void *) (audioStack + AUDIO_STACKSIZE / sizeof(unsigned long long)), pri);
    osStartThread(&__am.thread);
}

static void __amMain(void *arg)
{
    int          pad;
    unsigned int done;
    AudioMsg    *msg;
    AudioInfo   *prev;
    OSScClient   client;

    done = 0;
    prev = NULL;
    osScAddClient((OSSched *) D_8008A9F0, &client, &__am.audioFrameMsgQ);
    while (!done) {
        osRecvMesg(&__am.audioFrameMsgQ, (OSMesg *) &msg, 1);
        switch (msg->gen.type) {
            case 4:
                break;
            case 1:
                if (__amHandleFrameMsg(__am.audioInfo[audFrameCt % 3], prev) != 0) {
                    osRecvMesg(&__am.audioReplyMsgQ, (OSMesg *) &msg, 1);
                    __amHandleDoneMsg(msg->done.info);
                    prev = msg->done.info;
                }
                break;
            case 32:
                done = 1;
                break;
        }
    }
    alClose(&__am.g);
}

static int __amHandleFrameMsg(AudioInfo *info, AudioInfo *next)
{
    short *buf;
    int    pad;
    int    cmdLen;
    int    pad2;
    Acmd  *cmds;

    __clearAudioDMA();
    buf = (short *) osVirtualToPhysical(info->data);
    if (next != NULL) {
        osAiSetNextBuffer(next->data, next->frameSamples * 4);
    }
    info->frameSamples = (frameSize - (osAiGetLength() >> 2) + 0x100) & 0xFFF0;
    if (info->frameSamples < minFrameSize) {
        info->frameSamples = minFrameSize;
    }
    cmds = alAudioFrame(__am.ACMDList[curAcmdList], &cmdLen, buf, info->frameSamples);
    if (cmdLen == 0) {
        return 0;
    }
    info->task.next                   = NULL;
    info->task.msgQ                   = &__am.audioReplyMsgQ;
    info->task.msg                    = &info->msg;
    info->task.flags                  = 2;
    info->task.list.t.data_ptr        = (unsigned long long *) __am.ACMDList[curAcmdList];
    info->task.list.t.data_size       = (cmds - __am.ACMDList[curAcmdList]) * sizeof(Acmd);
    info->task.list.t.type            = 2;
    info->task.list.t.ucode_boot      = D_800525B0;
    info->task.list.t.ucode_boot_size = (unsigned int) D_80052680 - (unsigned int) D_800525B0;
    info->task.list.t.flags           = 0;
    info->task.list.t.ucode           = D_80053AB0;
    info->task.list.t.ucode_data      = D_8007DD60;
    info->task.list.t.ucode_data_size = 0x800;
    info->task.list.t.yield_data_ptr  = NULL;
    info->task.list.t.yield_data_size = 0;
    osSendMesg(D_8008CCB0, &info->task, 1);
    curAcmdList ^= 1;
    return 1;
}

static void __amHandleDoneMsg(AudioInfo *info)
{
    int        samplesLeft;
    static int firstTime = 1;

    samplesLeft = osAiGetLength() >> 2;
    if (samplesLeft == 0 && !firstTime) {
        firstTime = 0;
    }
}

static int __amDMA(int addr, int len, void *state)
{
    unsigned char *foundBuffer;
    int            delta;
    int            addrEnd;
    int            buffEnd;
    AMDMABuffer   *dmaPtr;
    AMDMABuffer   *lastDmaPtr;

    lastDmaPtr = NULL;
    dmaPtr     = dmaState.firstUsed;
    addrEnd    = addr + len;
    while (dmaPtr != NULL) {
        buffEnd = dmaPtr->startAddr + 0xC00;
        if (addr < dmaPtr->startAddr) {
            break;
        } else if (addrEnd <= buffEnd) {
            dmaPtr->lastFrame = audFrameCt;
            foundBuffer       = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr     = dmaPtr->next;
    }
    dmaPtr             = dmaState.firstFree;
    dmaState.firstFree = dmaPtr->next;
    alUnlink((ALLink *) dmaPtr);
    if (lastDmaPtr != NULL) {
        alLink((ALLink *) dmaPtr, (ALLink *) lastDmaPtr);
    } else if (dmaState.firstUsed != NULL) {
        lastDmaPtr         = dmaState.firstUsed;
        dmaState.firstUsed = dmaPtr;
        dmaPtr->next       = lastDmaPtr;
        dmaPtr->prev       = NULL;
        lastDmaPtr->prev   = dmaPtr;
    } else {
        dmaState.firstUsed = dmaPtr;
        dmaPtr->next       = NULL;
        dmaPtr->prev       = NULL;
    }
    foundBuffer = dmaPtr->ptr;
    delta       = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = audFrameCt;
    osPiStartDma(&audDMAIOMesgBuf[nextDMA++], 0, 0, addr, foundBuffer, 0xC00, &audDMAMessageQ);
    return osVirtualToPhysical(foundBuffer) + delta;
}

static ALDMAproc __amDmaNew(AMDMAState **state)
{
    if (dmaState.initialized == 0) {
        dmaState.firstUsed   = NULL;
        dmaState.firstFree   = &dmaBuffs[0];
        dmaState.initialized = 1;
    }
    *state = &dmaState;
    return __amDMA;
}

static void __clearAudioDMA(void)
{
    unsigned int i;
    void        *msg;
    AMDMABuffer *buf;
    AMDMABuffer *next;

    i = 0;
    if (nextDMA != 0) {
        do {
            osRecvMesg(&audDMAMessageQ, &msg, 0);
            i++;
        } while (i < nextDMA);
    }
    for (buf = dmaState.firstUsed; buf != NULL; buf = next) {
        next = buf->next;
        if (buf->lastFrame + 1 < audFrameCt) {
            if (buf == dmaState.firstUsed) {
                dmaState.firstUsed = buf->next;
            }
            alUnlink((ALLink *) buf);
            if (dmaState.firstFree != NULL) {
                alLink((ALLink *) buf, (ALLink *) dmaState.firstFree);
            } else {
                dmaState.firstFree = buf;
                buf->next          = NULL;
                buf->prev          = NULL;
            }
        }
    }
    nextDMA = 0;
    audFrameCt++;
}
