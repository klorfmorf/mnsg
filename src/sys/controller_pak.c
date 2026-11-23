#include "sys/controller_pak.h"
#include "sys/sys.h"
#include "sys/wave_uty.h"

unsigned int func_80023A1C(void *data, int size);
void         func_80023ADC(int error);

// clang-format off

// <<<<< data >>>>>
unsigned int D_8006D170[4] = {
    0x26322C2D, 0x221C1A25, 0x0F272227, 0x231A0000,
};

// <<<<< rodata >>>>>
#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/D_8007BCA0.s")

// <<<<< bss >>>>>
unsigned char D_80168A00[8];
unsigned char D_80168A08[112];
unsigned char D_80168A78[1036];
MemPak       *D_80168E84;
// clang-format on

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_800231E0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_800232EC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_8002338C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023394.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023410.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023480.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_800234D8.s")

int func_80023560(unsigned char *buf)
{
    int           status;
    unsigned char data[0x100];

    status = osPfsReadWriteFile(&D_80168E84->pfs, D_80168E84->fileNo, PFS_READ, 0, 0x100, data);
    if (status == 0) {
        if (func_80023A1C(data + 4, 0xC) != *(unsigned int *) data) {
            status = 0x102;
        } else {
            status                = 0;
            *(MemPakHeader *) buf = *(MemPakHeader *) (data + 4);
        }
    }
    func_80023ADC(status);
    D_80168E84->error = status;
    return D_80168E84->error;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023610.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023698.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023788.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_800237F0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023840.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023880.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_800238D0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_800239B8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023A1C.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023ADC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023B60.s")

void func_80023C14(void)
{
    unsigned char *buf;
    int            i;

    buf = amemAlloc(g_sys->memory_blocks, D_80168E84->files[D_80168E84->fileNo].file_size);
    if (buf != 0) {
        for (i = 0; i < 0x500; i++) { buf[i] = i & 0xFF; }
        func_80023610(buf, 0);
        amemFree(g_sys->memory_blocks, buf);
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023CC8.s")

void func_80023D80(void)
{
    int i;
    int j;

    func_800238D0();
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {}
    }
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/sys/controller_pak/func_80023DC4.s")
