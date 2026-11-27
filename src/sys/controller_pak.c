#include "sys/controller_pak.h"
#include "sys/sys.h"
#include "sys/amem.h"
#include "sys/joypad.h"
#include "sys/scenario.h"
#include "sys/vibration_pak.h"

void func_80023ADC(int error);

// clang-format off

// <<<<< data >>>>>
unsigned int D_8006D170[4] = {
    0x26322C2D, 0x221C1A25, 0x0F272227, 0x231A0000,
};

// <<<<< bss >>>>>
unsigned char D_80168A00[8];
OSPfs         D_80168A08;
unsigned char D_80168A70[8];
MemPak        D_80168A78;
MemPak       *D_80168E84;

// clang-format on

int func_800231E0(void)
{
    int error;

    D_80168E84 = &D_80168A78;
    PRINTF(("pak_start: in \n"));
#ifdef JAPAN_0
    func_800049D0();
#endif
    if (D_80167190[2] & CONT_CARD_ON) {
        osPfsInitPak(&D_80167170, &D_80168E84->pfs, 0);
        error = osPfsInitPak(&D_80167170, &D_80168E84->pfs, 0);
        if (error == PFS_ERR_ID_FATAL && func_80037B10(0) == 0) {
            error = PAK_ERR_VIBRATION_PAK;
        }
        D_80168E84->no_pak = 0;
    } else {
        D_80168E84->no_pak = 1;
        error              = PFS_ERR_NOPACK;
    }
    D_80168A08 = D_80168E84->pfs;
    func_80023ADC(error);
    PRINTF(("pak_start: out \n"));
    D_80168E84->error = error;
    return D_80168E84->error;
}

int func_800232EC(void)
{
    unsigned char pattern;

    D_80168E84        = &D_80168A78;
    D_80168E84->pfs   = D_80168A08;
    D_80168E84->error = osPfsIsPlug(&D_80167170, &pattern);
    func_80023ADC(D_80168E84->error);
    return D_80168E84->error;
}

int func_8002338C(void)
{
    return 0;
}

int func_80023394(void)
{
    int error = osPfsAllocateFile(&D_80168E84->pfs, PAK_COMPANY_CODE, PAK_GAME_CODE, (unsigned char *) D_8006D170, D_80168A00,
        PAK_FILE_SIZE, &D_80168E84->file_no);

    PRINTF(("ret = %d, allocated %d\n", error, D_80168E84->file_no));
    if (error != 0) {
        func_80023ADC(error);
    }
    D_80168E84->error = error;
    return D_80168E84->error;
}

int func_80023410(void)
{
    int error = osPfsFindFile(&D_80168E84->pfs, PAK_COMPANY_CODE, PAK_GAME_CODE, (unsigned char *) D_8006D170, D_80168A00,
        &D_80168E84->file_no);

    func_80023ADC(error);
    PRINTF(("File found. descriptor = %d\n", D_80168E84->file_no));
    D_80168E84->error = error;
    return D_80168E84->error;
}

int func_80023480(void)
{
    int error = osPfsFileState(&D_80168E84->pfs, D_80168E84->file_no, &D_80168E84->files[D_80168E84->file_no]);

    func_80023ADC(error);
    PRINTF(("file info. %d\n", D_80168E84->file_no));
    PRINTF((" file size: %d\n", D_80168E84->files[D_80168E84->file_no].file_size));
    PRINTF((" game code: %08x\n", D_80168E84->files[D_80168E84->file_no].game_code));
    PRINTF((" company code: %04x\n", D_80168E84->files[D_80168E84->file_no].company_code));
    D_80168E84->error = error;
    return D_80168E84->error;
}

int func_800234D8(unsigned char *buffer, int slot)
{
    int error;

    D_80168E84->buffer = buffer;
    error              = osPfsReadWriteFile(&D_80168E84->pfs, D_80168E84->file_no, PFS_READ, slot * PAK_SLOT_SIZE + PAK_HEADER_SIZE,
        PAK_SLOT_SIZE, D_80168E84->buffer);
    func_80023ADC(error);
    PRINTF(("read file %d\n", slot));
    D_80168E84->error = error;
    return D_80168E84->error;
}

int func_80023560(unsigned char *buf)
{
    int           status;
    unsigned char data[PAK_HEADER_SIZE];

    PRINTF(("read shared\n"));
    status = osPfsReadWriteFile(&D_80168E84->pfs, D_80168E84->file_no, PFS_READ, 0, PAK_HEADER_SIZE, data);
    if (status == 0) {
        if (func_80023A1C(data + 4, sizeof(ContPakHeader)) != *(unsigned int *) data) {
            status = PAK_ERR_CRC;
        } else {
            status                 = 0;
            *(ContPakHeader *) buf = *(ContPakHeader *) (data + 4);
        }
    }
    func_80023ADC(status);
    D_80168E84->error = status;
    return D_80168E84->error;
}

int func_80023610(unsigned char *buffer, int slot)
{
    int error;

    D_80168E84->buffer = buffer;
    error              = osPfsReadWriteFile(&D_80168E84->pfs, D_80168E84->file_no, PFS_WRITE,
        slot * PAK_SLOT_SIZE + PAK_HEADER_SIZE, PAK_SLOT_SIZE, D_80168E84->buffer);
    func_80023ADC(error);
    D_80168E84->error = error;
    return D_80168E84->error;
}

int func_80023698(ContPakHeader *header)
{
    int            error;
    PakHeaderBlock block;
    unsigned int   checksum;
    int            status;
    ContPakHeader  check;
    unsigned char *written;
    unsigned char *read;
    int            i;

    block.header   = *header;
    checksum       = func_80023A1C((unsigned char *) &block.header, sizeof(ContPakHeader));
    block.checksum = checksum;
#ifndef JAPAN_0
    osWritebackDCache(&block, 16);
#endif
    PRINTF(("write shared\n"));
    error = osPfsReadWriteFile(&D_80168E84->pfs, D_80168E84->file_no, PFS_WRITE, 0, PAK_HEADER_SIZE, (unsigned char *) &block);
    if (error == 0) {
        status = func_80023560((unsigned char *) &check);
        if (status == 0) {
            written = (unsigned char *) &block.header;
            read    = (unsigned char *) &check;
            for (i = 0; i < (int) sizeof(ContPakHeader); i++) {
                if (*written++ != *read++) {
                    error = PFS_ERR_BAD_DATA;
                    break;
                }
            }
        }
    }
    func_80023ADC(error);
    D_80168E84->error = error;
    return D_80168E84->error;
}

int func_80023788(void)
{
    int error;
    s32 bytes;

    error = osPfsFreeBlocks(&D_80168E84->pfs, &bytes);
    func_80023ADC(error);
    D_80168E84->free_blocks = bytes / 256;
    PRINTF(("free blocks: %d\n", D_80168E84->free_blocks));
    D_80168E84->error = error;
    return D_80168E84->error;
}

int func_800237F0(void)
{
    int error = osPfsNumFiles(&D_80168E84->pfs, &D_80168E84->max_files, &D_80168E84->used_files);

    func_80023ADC(error);
    PRINTF(("num_files: max:%d, current:%d\n", D_80168E84->max_files, D_80168E84->used_files));
    D_80168E84->error = error;
    return D_80168E84->error;
}

int func_80023840(void)
{
    unsigned char pattern;

    if (osPfsIsPlug(&D_80167170, &pattern) == -1) {
        return -1;
    }
    return pattern & 1;
}

int func_80023880(void)
{
    osPfsRepairId(&D_80168E84->pfs);
    D_80168E84->error = osPfsInitPak(&D_80167170, &D_80168E84->pfs, 0);
    return D_80168E84->error;
}

int func_800238D0(void)
{
    int i;

    for (i = 0; i < 16; i++) {
        D_80168E84->file_errors[i] = osPfsFileState(&D_80168E84->pfs, i, &D_80168E84->files[i]);
        if (D_80168E84->file_errors[i] == PFS_ERR_CONTRFAIL || D_80168E84->file_errors[i] == PFS_ERR_NEW_PACK ||
            D_80168E84->file_errors[i] == PFS_ERR_INCONSISTENT) {
            D_80168E84->error = D_80168E84->file_errors[i];
            return D_80168E84->error;
        }
    }
    D_80168E84->error = 0;
    return D_80168E84->error;
}

int func_800239B8(int index)
{
    int error = osPfsDeleteFile(&D_80168E84->pfs, D_80168E84->files[index].company_code,
        D_80168E84->files[index].game_code, (unsigned char *) D_80168E84->files[index].game_name,
        (unsigned char *) D_80168E84->files[index].ext_name);

    func_80023ADC(error);
    D_80168E84->error = error;
    return error;
}

unsigned int func_80023A1C(unsigned char *data, int size)
{
    unsigned int crc = 0xFFFFFFFF;
    unsigned int i;
    int          bit;

    for (i = 0; i < size; i++) {
        crc ^= data[i] << 24;
        for (bit = 0; bit < 8; bit++) {
            if (crc & 0x80000000) {
                crc = (crc << 1) ^ 0x04C11DB7;
            } else {
                crc <<= 1;
            }
        }
    }
    return ~crc;
}

void func_80023ADC(int error)
{
    switch (error) {
        case 0:
            PRINTF(("No error\n"));
            break;
        case PFS_ERR_NOPACK:
            PRINTF(("No controller pak\n"));
            break;
        case PFS_ERR_NEW_PACK:
            PRINTF(("Controller pak changed to another one\n"));
            break;
        case PFS_ERR_INCONSISTENT:
            PRINTF(("File system inconsistent\n"));
            break;
        case PFS_ERR_CONTRFAIL:
            PRINTF(("Hardware CRC Error\n"));
            break;
        case PFS_ERR_INVALID:
            PRINTF(("Invalid parameter or file not found\n"));
            break;
        case PFS_ERR_BAD_DATA:
            PRINTF(("Bad data\n"));
            break;
        case PFS_DATA_FULL:
            PRINTF(("No free pages on ram pack\n"));
            break;
        case PFS_DIR_FULL:
            PRINTF(("No free directories on ram pack\n"));
            break;
        case PFS_ERR_EXIST:
            PRINTF(("File already exists\n"));
            break;
        case PFS_ERR_ID_FATAL:
            PRINTF(("Dead pak\n"));
            break;
        case PFS_ERR_DEVICE:
            PRINTF(("Wrong device type\n"));
            break;
        case PAK_ERR_NO_PAK:
            PRINTF(("No controller pak\n"));
            break;
        case PAK_ERR_NO_CONTROLLER:
            PRINTF(("No controller\n"));
            break;
        case PAK_ERR_CRC:
            PRINTF(("Software CRC check error\n"));
            break;
        case PAK_ERR_VIBRATION_PAK:
            PRINTF(("Vibration pak\n"));
            break;
        default:
            PRINTF(("Unknown error %d\n", error));
            break;
    }
}

void func_80023B60(void)
{
    int            error;
    unsigned int   crc;
    unsigned char *buffer = amemAlloc(g_sys->memory_blocks, D_80168E84->files[D_80168E84->file_no].file_size);
    int            offset;
    int            i;

    if (buffer == NULL) {
        PRINTF(("malloc error\n"));
        return;
    }
    
    error = func_800234D8(buffer, 0);
    for (offset = 0; offset < PAK_SLOT_SIZE; offset += 16) {
        PRINTF(("%04x: ", offset));
        for (i = 0; i < 16; i++) {
            PRINTF(("%02x ", buffer[offset + i]));
        }
        PRINTF(("\n"));
    }

    crc = func_80023A1C(D_80168E84->buffer, 1280);
    PRINTF(("CRC = %08x\n", crc));

    amemFree(g_sys->memory_blocks, buffer);

    PRINTF(("sc_pak_read end\n"));
}

void func_80023C14(void)
{
    unsigned char *buf;
    int            i;

    buf = amemAlloc(g_sys->memory_blocks, D_80168E84->files[D_80168E84->file_no].file_size);
    if (buf != 0) {
        for (i = 0; i < PAK_SLOT_SIZE; i++) { buf[i] = i & 0xFF; }
        func_80023610(buf, 0);
        amemFree(g_sys->memory_blocks, buf);
    } else {
        PRINTF(("malloc error\n"));
    }
}

void func_80023CC8(void)
{
    unsigned char *buffer = amemAlloc(g_sys->memory_blocks, D_80168E84->files[D_80168E84->file_no].file_size);
    int            i;

    if (buffer != NULL) {

        for (i = 0; i < PAK_SLOT_SIZE; i++) { buffer[i] = i & 0xFF; }
        buffer[PAK_SLOT_SIZE - 1] = 0;
        func_80023610(buffer, 0);
        amemFree(g_sys->memory_blocks, buffer);
    } else {
        PRINTF(("malloc error\n"));
    }
}

void func_80023D80(void)
{
    int i;
    int j;

    func_800238D0();
    for (i = 0; i < 16; i++) {
        PRINTF(("read dir: %d\n", i));
        PRINTF(("return value: %d\n", D_80168E84->file_errors[i]));
        PRINTF(("file size: 0x%08x\n", D_80168E84->files[i].file_size));
        PRINTF(("game code: 0x%08x\n", D_80168E84->files[i].game_code));
        PRINTF(("company code: 0x%04x\n", D_80168E84->files[i].company_code));
        PRINTF(("file name: "));
        for (j = 0; j < 16; j++) {
            PRINTF(("%02x ", D_80168E84->files[i].game_name[j]));
        }
        PRINTF(("\n"));
    }
}

void func_80023DC4(void)
{
    func_800239B8(D_801C7740);
}
