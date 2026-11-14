#ifndef DATA_LOAD_H
#define DATA_LOAD_H


#include "common.h"

#define LOAD_FILE_MAX 0x520

#define LOAD_VRAM_START(id) D_80054ACC[(unsigned int) (((id) - 1) * 2) + 0]
#define LOAD_VRAM_END(id)   D_80054ACC[(unsigned int) (((id) - 1) * 2) + 1]
#define LOAD_ROM_START(id)  (D_800573C8.offsets[(id) - 1] & 0x7FFFFFFF)
#define LOAD_ROM_END(id)    (D_800573C8.offsets[(id) - 1 + 1] & 0x7FFFFFFF)

typedef struct LoadRomTable {
    /* 0x0000 */ char         name[16];
    /* 0x0010 */ unsigned int offsets[LOAD_FILE_MAX];
} LoadRomTable; // size = 0x1490

#ifndef NO_PROTO_func_80001C00
int           func_80001C00(unsigned int id, void *addr);
#endif
int           func_80001D68(unsigned short id);
int           func_80001D94(unsigned short id);
int           func_80001DC0(unsigned int id);
#ifndef NO_PROTO_func_80001DF4
int           func_80001DF4(unsigned int id);
#endif
unsigned char func_80001E50(unsigned int id);
int           func_80001EB0(unsigned int id, int addr);
void          func_80001FE8(void);

extern unsigned short D_80054910[];
extern int            D_80054ACC[(LOAD_FILE_MAX - 1) * 2];
extern LoadRomTable   D_800573C8;
extern char           D_8015C5D4;

#endif // DATA_LOAD_H
