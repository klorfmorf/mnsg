#ifndef ROM_TRANS_H
#define ROM_TRANS_H

#include "common.h"
#include "structs.h"

#ifndef NO_PROTO_func_80001C00
int func_80001C00(unsigned int id, void *addr);
#endif
int func_80001D68(unsigned short id);
int func_80001D94(unsigned short id);
#ifndef NO_PROTO_func_80001DF4
int func_80001DF4(unsigned int id);
#endif
unsigned char func_80001E50(unsigned int id);
int           func_80001EB0(unsigned int id, int addr);
void          func_80001FE8(void);

extern unsigned short D_80054910[];
extern int            D_80054ACC[(LOAD_FILE_MAX - 1) * 2];
extern LoadRomTable   D_800573C8;

#endif // ROM_TRANS_H
