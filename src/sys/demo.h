#ifndef DEMO_H
#define DEMO_H

#include "common.h"
#include "structs.h"

void func_80005B90(void);
void func_80005FFC(unsigned short stage, short x, short y, short z, unsigned short angle, unsigned short posi_extra, unsigned short keys_file, int keys_addr);
void func_800060D4(unsigned short stage, short x, short y, short z, unsigned short angle, unsigned short posi_extra, unsigned short keys_file, int keys_addr);
void func_80006140(unsigned char index, unsigned short keys_file, int keys_addr);
void func_800061B0(unsigned char index, unsigned short keys_file, int keys_addr);
void func_80006220(unsigned char index, unsigned short keys_file, int keys_addr);
void func_80006298(void);
int  func_8000631C(void);

#endif // DEMO_H
