#include "sys/main.h"
#include "sys/sd_main.h"
#include "sys/joypad.h"
#include "sys/window.h"
#include "sys/controller_pak.h"
#include "sys/obj_sort.h"
#include "sys/vibration_pak.h"
#include "sys/scenario.h"
#include "sys/sched.h"
#include "structs.h"
#include "sys/sys.h"
#include "sys/anime.h"
#include "sys/rom_trans.h"
#include "sys/rom_queue.h"
#include "sys/step.h"
#include "sys/obj.h"
#include "sys/string.h"
#include "sys/gfx_data.h"
#include "sys/profiler.h"
#include "unk.h"

void func_800004AC(void *arg);
void func_80000580(void *arg);
void func_8000098C(void);
void func_80000AD8(void *arg);
void func_80000D00(void);
void func_800011A0(void);
void func_800012FC(void);
void func_80001328(void);
void func_80001498(void);
void func_80001614(void);
void func_800016E4(OSScTask *task, OSScMsg *msg, unsigned long long *ucode, unsigned long long *ucode_data, int done);

// clang-format off

// <<<<< data >>>>>
OSMesg D_800548D0 = NULL;

int D_800548D4 = 0;

int D_800548D8 = 0;

int D_800548DC = 0;

int D_800548E0 = 0;

int D_800548E4 = 0;

int D_800548E8 = 0;

unsigned short D_800548EC = 0;

unsigned short D_800548F0 = 0;

unsigned short D_800548F4 = 0;

// <<<<< bss >>>>>
unsigned long long  D_8007E020[0x2000 / sizeof(unsigned long long)];
OSThread            D_80080020;
unsigned long long  D_800801D0[0x4000 / sizeof(unsigned long long)];
OSThread            D_800841D0;
unsigned long long  D_80084380[0x4000 / sizeof(unsigned long long)];
OSThread            D_80088380;
unsigned long long  D_80088530[0x2000 / sizeof(unsigned long long)];
OSMesgQueue         D_8008A530;
OSMesg              D_8008A548[0xC8];
OSMesgQueue         D_8008A868;
OSMesg              D_8008A880[1];
OSMesgQueue         D_8008A888;
OSMesg              D_8008A8A0[8];
OSMesgQueue         D_8008A8C0;
OSMesg              D_8008A8D8[1];
OSScMsg             D_8008A8E0[2];
OSScTask            D_8008A920[2];
OSSched             D_8008A9F0;
unsigned long long  D_8008ACB0[0x2000 / sizeof(unsigned long long)];
OSMesgQueue        *D_8008CCB0;

// clang-format on

void func_80000450(void)
{
    osInitialize();
    osCreateThread(&D_80080020, 1, func_800004AC, NULL, &D_800841D0, 9);
    osStartThread(&D_80080020);
}

void func_800004AC(void *arg)
{
    osCreatePiManager(OS_PRIORITY_PIMGR, &D_8008A530, D_8008A548, 0xC8);
    osCreateThread(&D_800841D0, 3, func_80000580, arg, &D_80088380, 0xA);
    osStartThread(&D_800841D0);
    osCreateThread(&D_80088380, 4, func_80000AD8, arg, &D_8008A530, 9);
    osStartThread(&D_80088380);
    osSetThreadPri(NULL, 0);

    while (1) {
    }
}

void func_80000580(void *arg)
{
    OSScClient     client;
    OSScMsg       *msg   = NULL;
    unsigned int   delay = 0x300000;
    int            i;
    unsigned char *p;
    int            retraces;

    func_80004170();
    PRINTF(("SYSDW = %0x\n", g_sys));

    func_80001FE8();

    func_800016E4(D_8008A920, D_8008A8E0, D_80052680, D_8007D560, 0x8000);

    osCreateMesgQueue(&D_8008A868, D_8008A880, 1);
    osCreateMesgQueue(&D_8008A888, D_8008A8A0, 8);
    osCreateMesgQueue(&D_8008A8C0, D_8008A8D8, 1);

    func_80001C00(FILE_8, g_frame_buffers);
    func_80001C00(FILE_10, D_80304000);
    PRINTF(("DEBUG code[%p]-[%p]\n", g_frame_buffers, D_80304000));

    if (osTvType == OS_TV_MPAL) {
        osCreateScheduler(&D_8008A9F0, D_8008ACB0 + 0x2000 / sizeof(unsigned long long), 13, OS_VI_MPAL_LAN1, 1);
    } else {
        osCreateScheduler(&D_8008A9F0, D_8008ACB0 + 0x2000 / sizeof(unsigned long long), 13, OS_VI_NTSC_LAN1, 1);
    }

    g_sys->clear_depth_buffer     = 1;
    g_sys->retraces_per_game_step = 2;
    g_sys->current_graphics_pool  = 0;
    g_sys->frames_elapsed         = 0;
    g_sys->current_frame_buffer   = 1;
    g_sys->disable_graphics_tasks = 0;

    osScAddClient(&D_8008A9F0, &client, &D_8008A888);
    D_8008CCB0 = osScGetCmdQ(&D_8008A9F0);

    osViSetSpecialFeatures(OS_VI_GAMMA_OFF | OS_VI_GAMMA_DITHER_OFF | OS_VI_DIVOT_ON | OS_VI_DITHER_FILTER_ON);

    func_800049D0();

    PRINTF(("SOUND 1\n"));

    while (--delay != 0) {
    }

    func_800386E0();

    delay = 0x2FFFFF;
wait:
    if (--delay != 0) {
        goto wait;
    }

    PRINTF(("SOUND 2\n"));

    g_sys_real.is_controller_pak_connected = func_800231E0();
    if (g_sys_real.is_controller_pak_connected != 0 || func_800232EC() != 0 || func_80023410() != 0 ||
        func_80023480() != 0 || func_80023560(D_8015CC18) != 0) {
        p = D_8015CC18;
        i = 0;
        while (i < (int) sizeof(ContPakHeader)) {
            *p++ = 0;
            i++;
        }
    }

    while (1) {
        osRecvMesg(&D_8008A888, (OSMesg *) &msg, OS_MESG_BLOCK);

        switch (msg->type) {
            case 0:
                break;

            case OS_SC_RETRACE_MSG:
                g_sys_real.retrace_count++;

                retraces   = D_800548DC;
                D_800548DC = retraces + 1;

                if (D_800548EC == 0) {
                    D_800548D4++;
                    if (D_800548D4 >= g_sys->retraces_per_game_step && D_800548E8 == 0) {
                        osSendMesg(&D_8008A8C0, &D_800548D0, OS_MESG_NOBLOCK);
                        D_800548D4 = 0;
                    }
                } else {
                    func_80000D00();
                }
                break;

            case OS_SC_DONE_MSG:
                D_800548D8 = 0;
                if (D_800548EC == 0 && D_800548E0 == 0) {
                    func_8000098C();
                }
                break;

            case OS_SC_PRE_NMI_MSG:
                func_80038BC8(0xA);
                D_800548E4 = 0;
                D_800548EC = 1;
                break;
        }
    }
}

void func_8000098C(void)
{
    OSScTask *task;

    if (g_sys->disable_graphics_tasks == 0 && D_800548E4 != 0) {
        task               = &D_8008A920[g_sys->current_graphics_pool];
        task->frame_buffer = g_frame_buffers[g_sys->current_frame_buffer];
        D_800548D8         = 1;
        D_800548E4         = 0;
        D_800548DC         = 0;
        g_sys->current_graphics_pool ^= 1;
        g_sys->frames_elapsed++;
        g_sys->current_frame_buffer++;
        if (g_sys->current_frame_buffer >= 3) {
            g_sys->current_frame_buffer = 0;
        }
        osSendMesg(osScGetInterruptQ(&D_8008A9F0), task, OS_MESG_BLOCK);
    }
}

void func_80000AD8(void *arg)
{
    short i;

    while (1) {
        osRecvMesg(&D_8008A8C0, &D_800548D0, OS_MESG_BLOCK);
        D_800548E8 = 1;
        D_800548E0 = 1;
        osContStartReadData(&D_80167170);
        g_sys_glistp = (Gfx *) &g_sys->graphics_buffer[g_sys->current_graphics_pool];
        func_800011A0();
        func_800012FC();
        if (g_sys->clear_depth_buffer != 0) {
            func_80001614();
        }
        func_80001498();
        func_80004AF8();
        func_80002040();
        if (g_sys->dont_process_draw_lists == 0) {
            func_8000AAE8(g_sys->layers);
            func_8000AA00(g_sys->layers);
            anime_init_frame();
            if (g_sys_real.culling_disabled == 0) {
                func_8000AB74();
            }
            for (i = 0; i < 12; i++) {
                func_8000A99C(&g_sys->layers[i]);
                func_800087C4(&g_sys->layers[i]);
            }
            func_800012FC();
            func_8000433C();
            func_8000B8B0();
            func_8003EFB0();
            func_800379D0();
        }
        func_80001328();
        D_800548E0 = 0;
        D_8015C5D4 = 1;
        func_80005A64();
        D_8015C5D4 = 0;
        g_sys->game_loops_count++;
        D_800548E8 = 0;
    }
}

void func_80000D00(void)
{
    unsigned short x;

    if (D_800548F0 < 18) {
        D_800548F0++;
        if ((D_800548D8 | D_800548E8) == 0) {
            if (D_800548F4 == 0) {
                switch (g_sys->current_frame_buffer) {
                    case 0:
                        func_80004208(g_frame_buffers[0], g_frame_buffers[1], sizeof(g_frame_buffers[0]));
                        func_80004208(g_frame_buffers[0], g_frame_buffers[2], sizeof(g_frame_buffers[0]));
                        break;
                    case 1:
                        func_80004208(g_frame_buffers[1], g_frame_buffers[0], sizeof(g_frame_buffers[0]));
                        func_80004208(g_frame_buffers[1], g_frame_buffers[2], sizeof(g_frame_buffers[0]));
                        break;
                    case 2:
                        func_80004208(g_frame_buffers[2], g_frame_buffers[0], sizeof(g_frame_buffers[0]));
                        func_80004208(g_frame_buffers[2], g_frame_buffers[1], sizeof(g_frame_buffers[0]));
                        break;
                }
            }
            D_800548F4++;
            g_sys_glistp = (Gfx *) &g_sys->graphics_buffer[g_sys->current_graphics_pool];
            func_800011A0();
            func_800012FC();
            gDPSetScissor(g_sys_glistp++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            gDPPipeSync(g_sys_glistp++);
            gDPSetCycleType(g_sys_glistp++, G_CYC_FILL);
            gDPSetColorImage(g_sys_glistp++, G_IM_FMT_RGBA, g_sys->frame_buffer_bits_per_pixel, SCREEN_WIDTH,
                OS_K0_TO_PHYSICAL(g_frame_buffers[g_sys->current_frame_buffer]));
            gDPSetFillColor(g_sys_glistp++, GPACK_RGBA5551(0, 0, 0, 1) << 16 | GPACK_RGBA5551(0, 0, 0, 1));
            x = D_800548F4 * 10;
            if (x >= SCREEN_WIDTH / 2) {
                x = SCREEN_WIDTH / 2;
            }
            gDPFillRectangle(g_sys_glistp++, 0, 0, x, SCREEN_HEIGHT - 1);
            x = SCREEN_WIDTH - D_800548F4 * 10;
            if (x >= SCREEN_WIDTH) {
                x = SCREEN_WIDTH - 1;
            }
            if (x < SCREEN_WIDTH / 2 + 1) {
                x = SCREEN_WIDTH / 2;
            }
            gDPFillRectangle(g_sys_glistp++, x, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
            x = D_800548F4 * 10;
            if (x >= 118) {
                x = 118;
            }
            gDPFillRectangle(g_sys_glistp++, 0, 0, SCREEN_WIDTH - 1, x);
            x = SCREEN_HEIGHT - D_800548F4 * 10;
            if (x >= SCREEN_HEIGHT) {
                x = SCREEN_HEIGHT - 1;
            }
            if (x < 123) {
                x = 122;
            }
            gDPFillRectangle(g_sys_glistp++, 0, x, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
            gDPPipeSync(g_sys_glistp++);
            func_80001328();
            func_8000098C();
            D_800548D8 = 0;
        }
        if (D_800548F4 == 17) {
            osViSetYScale(1.0f);
            func_80038BC8(1);
            g_sys->fill_color_red   = 0;
            g_sys->fill_color_green = 0;
            g_sys->fill_color_blue  = 0;
            if (func_80037B10(0) == 0) {
                func_80037C20(0, 2, 0);
            }
        }
    }
}

void func_800011A0(void)
{
    gSPSegment(g_sys_glistp++, 0, 0);
    gSPSegment(g_sys_glistp++, 1, D_2D1800);
    gSPSegment(g_sys_glistp++, 2, OS_K0_TO_PHYSICAL(g_frame_buffers[g_sys->current_frame_buffer]));
    gSPSegment(g_sys_glistp++, 4, OS_K0_TO_PHYSICAL(&g_sys->graphics_buffer[g_sys->current_graphics_pool]));
    gSPSegment(g_sys_glistp++, 5, D_301000);
    gSPSegment(g_sys_glistp++, 6, 0x325800);
    gSPSegment(g_sys_glistp++, 9, 0x325800);
}

void func_800012FC(void)
{
    gSPDisplayList(g_sys_glistp++, D_8006D4E0);
}

void func_80001328(void)
{
    OSScTask *task;

    gDPFullSync(g_sys_glistp++);
    gSPEndDisplayList(g_sys_glistp++);
    osWritebackDCache(&g_sys->graphics_buffer[g_sys->current_graphics_pool], sizeof(GraphBuf));
    task                          = &D_8008A920[g_sys->current_graphics_pool];
    task->list.t.data_ptr         = (unsigned long long *) &g_sys->graphics_buffer[g_sys->current_graphics_pool];
    task->list.t.data_size        = (g_sys_glistp - (Gfx *) &g_sys->graphics_buffer[g_sys->current_graphics_pool]) * sizeof(Gfx);
    task->list.t.ucode_boot_size  = (unsigned int) D_80052680 - (unsigned int) D_800525B0;
    task->list.t.output_buff      = D_8015DDF0;
    task->list.t.output_buff_size = (unsigned long long *) ((unsigned int) D_8015DDF0 + 0x2380);
    task->flags                   = OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP | OS_SC_LAST_TASK | OS_SC_SWAPBUFFER;
    D_800548E4++;
    if (D_800548D8 == 0) {
        func_8000098C();
    }
}

void func_80001498(void)
{
    gDPPipeSync(g_sys_glistp++);
    gDPSetCycleType(g_sys_glistp++, G_CYC_FILL);
    gDPSetColorImage(g_sys_glistp++, G_IM_FMT_RGBA, g_sys->frame_buffer_bits_per_pixel, SCREEN_WIDTH,
        OS_K0_TO_PHYSICAL(g_frame_buffers[g_sys->current_frame_buffer]));
    gDPSetFillColor(g_sys_glistp++,
        GPACK_RGBA5551(g_sys->fill_color_red, g_sys->fill_color_green, g_sys->fill_color_blue, g_sys->fill_color_alpha) << 16 |
            GPACK_RGBA5551(g_sys->fill_color_red, g_sys->fill_color_green, g_sys->fill_color_blue, g_sys->fill_color_alpha));
    gDPFillRectangle(g_sys_glistp++, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    gDPPipeSync(g_sys_glistp++);
    gDPSetCycleType(g_sys_glistp++, G_CYC_1CYCLE);
}

void func_80001614(void)
{
    gSPDisplayList(g_sys_glistp++, D_8006E030);
}

void func_80001640(unsigned int rom, void *dst, int size)
{
    unsigned short i = 0x1000;
    OSIoMesg       io;
    OSMesg         msg = NULL;

    osInvalDCache(dst, size);
    osInvalICache(dst, size);
    osPiStartDma(&io, 0, 0, rom, dst, size, &D_8008A868);
    osRecvMesg(&D_8008A868, &msg, OS_MESG_BLOCK);
    while (i--) {
    }
}

void func_800016E4(OSScTask *task, OSScMsg *msg, unsigned long long *ucode, unsigned long long *ucode_data, int done)
{
    int i;

    for (i = 0; i != 2; i++) {
        task->frame_buffer            = g_frame_buffers[i];
        task->next                    = NULL;
        task->state                   = 0;
        task->flags                   = 0;
        task->list.t.type             = M_GFXTASK;
        task->list.t.flags            = OS_TASK_DP_WAIT;
        task->list.t.ucode_boot       = D_800525B0;
        task->list.t.ucode_boot_size  = 0;
        task->list.t.ucode            = ucode;
        task->list.t.ucode_size       = SP_UCODE_SIZE;
        task->list.t.ucode_data       = ucode_data;
        task->list.t.ucode_data_size  = SP_UCODE_DATA_SIZE;
        task->list.t.dram_stack       = D_80167450;
        task->list.t.dram_stack_size  = SP_DRAM_STACK_SIZE8;
        task->list.t.output_buff      = D_8015DDF0;
        task->list.t.output_buff_size = NULL;
        task->list.t.data_ptr         = NULL;
        task->list.t.data_size        = 0;
        task->list.t.yield_data_ptr   = D_8015CDF0;
        task->list.t.yield_data_size  = OS_YIELD_DATA_SIZE;
        task->msgQ                    = &D_8008A888;
        task->msg                     = &msg[i];
        task++;
    }
    if (done) {
        msg[0].type = OS_SC_DONE_MSG;
        msg[1].type = OS_SC_DONE_MSG;
    } else {
        msg[0].type = 0;
        msg[1].type = 0;
    }
}
