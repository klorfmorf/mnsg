#include "sys/rom_queue.h"
#include "sys/sys.h"
#include "sys/rom_trans.h"

unsigned char *func_80005A20(WaveReq *req)
{
    WaveReq **slot = &g_sys->file_requests_table[g_sys->file_requests_count++];

    *slot = req;
    return req->data;
}

void func_80005A64(void)
{
    WaveReq     **slot;
    WaveReq      *req;
    unsigned char i;

    for (i = 0; i < 8; i++) {
        slot = &g_sys->file_requests_table[i];
        if (*slot != NULL) {
            req = *slot;
            while (1) {
                if (req->wave_no & 0x20000000) {
                    while (g_sys->current_graphics_pool == g_sys->file_loader_working_graphics_pool) {
                    }
                }
                func_80001C00(req->wave_no & 0x0FFFFFFF, req->data);
                if (req->wave_no & 0x40000000) {
                    break;
                }
                req++;
            }
            *slot = NULL;
        }
    }
    g_sys->file_requests_count = 0;
}
