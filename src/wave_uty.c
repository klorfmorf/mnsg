#include "common.h"

#define WAVE_DECODE_MAX 48

extern int func_80001E50_2A50(unsigned int);
extern int func_80001EB0_2AB0(unsigned short, int);
extern int func_80001C00_2800(unsigned short, int);

int   func_80013B14_14714(int);
void* func_80013C90_14890(unsigned short*, char);
int   func_800142BC_14EBC(unsigned short, int);

extern s32 D_8006ADC0_6B9C0;
extern s32 D_8006ADC4_6B9C4;
extern s32 D_8006ADC8_6B9C8;
extern s32 D_8006ADCC_6B9CC;
extern unsigned char* D_80168160_168D60;
extern WAVE_W D_80167FC0_168BC0[WAVE_DECODE_MAX]; // WAWE_W WaveMem[WAVE_DECODE_MAX];
extern u8 D_80168140_168D40[]; // The end of WaveMem
extern u8 D_80304000[];

void func_80013940_14540(void) 
{
    int i;
    
    for (i = 0; i < WAVE_DECODE_MAX; i++) { D_80167FC0_168BC0[i].data = D_80167FC0_168BC0[i].wave_no = 0; }

    D_80167FC0_168BC0[0].data = (int)&D_80304000;
    D_80167FC0_168BC0[0].wave_no = 0;
}

#if NON_MATCHING
void func_800139A4_145A4(unsigned short arg0) 
{
    WAVE_W* temp_v0;
    s32 temp_t6;
    s32 temp_t9;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v0;

    temp_t6 = arg0 & 0xFFFF;
    var_v0 = temp_t6 < 0x30;
    var_a0 = temp_t6;
    if (var_v0 != 0) {
        temp_t9 = (temp_t6 + 1) & 0xFFFF;
        D_80167FC0_168BC0[temp_t6].wave_no = 0;
        var_a0 = temp_t9;
        var_v0 = temp_t9 < 0x30;
    }
    var_a0_2 = (var_a0 + 1) & 0xFFFF;
    if (var_v0 != 0) {
        do {
            temp_v0 = &D_80167FC0_168BC0[var_a0_2];
            temp_v0->data = 0 & 0xFFFF;
            temp_v0->wave_no = 0;
            var_a0_2 = (var_a0_2 + 1) & 0xFFFF;
        } while (var_a0_2 < 0x30);
    }
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_800139A4_145A4.s")
#endif

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_80013A24_14624.s")

int func_80013AC4_146C4(unsigned short* wave_no_list) 
{
    int sp24;
    int wave_no;

    wave_no = *wave_no_list;
    while (wave_no != 0) {
        wave_no = wave_no & 0xFFFF;
        wave_no_list++;
        sp24 = func_80013B14_14714(wave_no);
        wave_no = *wave_no_list;
    }
    
    return sp24;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_80013B14_14714.s")

void func_80013C0C_1480C(unsigned short arg0) 
{
    WAVE_W* temp_v0;
    int temp_t8;

    temp_v0 = &D_80167FC0_168BC0[arg0];
    temp_t8 = temp_v0->data & 0xBFFFFFFF;
    func_80001C00_2800(temp_v0->wave_no, temp_t8);
    func_800142BC_14EBC(temp_v0->wave_no, temp_t8);
}

void func_80013C70_14870(unsigned short* arg0) 
{
    func_80013C90_14890(arg0, 4);
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_80013C90_14890.s")

int func_800141C4_14DC4(unsigned int wave_no)
{
    WAVE_W* entry = (WAVE_W*)&D_80167FC0_168BC0;

    if (wave_no == 0) {
        return 0;
    }
    
    while (entry->wave_no != 0) {
        if (entry->wave_no == wave_no) {
            return entry->data;
        }
        
        entry++;
    }

    return -1;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_80014218_14E18.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_800142BC_14EBC.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_800144E8_150E8.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_800145B4_151B4.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_80014698_15298.s")

void func_8001481C_1541C(TASK_W* task) 
{
    int data = task->wave.data;
    func_80001EB0_2AB0(task->wave.wave_no, data);
}

int func_80014840_15440(int arg0, unsigned int wave_no) 
{
    int data;

    if (arg0 > 0) {
        data = func_800141C4_14DC4(wave_no);

        if (data == -1) {
            *(int* )-1 = 0;
        }

        data = data & 0xBFFFFFFF;
        return (arg0 - (func_80001E50_2A50(wave_no) << 24)) + data;
    }

    return arg0;
}

void func_800148C0_154C0(AMEM_W* arg0, char* arg1, unsigned int arg2) 
{
    char* data;
    unsigned int i;

    i = 0;
    if (arg2 != 0) {
        data = arg1;
        do {
            i    += 1;
            *data = 0;
            data += 1;
        } while (i < arg2);
    }
    
    arg0->pt   = arg1;
    arg0->size = arg2;
    arg0->next = 0;
}

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_800148F0_154F0.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_80014A28_15628.s")

#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_80014B74_15774.s")

void func_80014C00_15800(AMEM_W* arg0) 
{
    AMEM_W* var_v0;

    var_v0 = arg0->next;
    while (var_v0 != 0) {
        var_v0 = var_v0->next;
    }
}

void func_80014C20_15820(unsigned char* arg0) 
{
    D_8006ADC0_6B9C0 = 0;
    D_8006ADC4_6B9C4 = 0;
    D_8006ADC8_6B9C8 = 8;
    D_8006ADCC_6B9CC = 0;
    D_80168160_168D60 = arg0;
    
    // Fake match, most likely some kind of debugging leftover
    if (arg0 && arg0)
    {
    }
}

#if NON_MATCHING
unsigned int func_80014C54_15854(void)
{
  unsigned char new_var;
  int temp_t7;
  unsigned int new_var2;
  unsigned char temp_t1;
  temp_t7 = D_8006ADC4_6B9C4;
  temp_t7 = temp_t7 - 1;
  D_8006ADC4_6B9C4 = temp_t7;
  if (temp_t7 >= 0)
  {
    return (((unsigned int) D_8006ADCC_6B9CC) >> temp_t7) & 1;
  }
  D_8006ADC4_6B9C4 = 7;
  temp_t1 = *D_80168160_168D60;
  D_80168160_168D60 += 1;
  if (D_8006ADCC_6B9CC)
  {
  }
  new_var2 = temp_t1;
  D_8006ADCC_6B9CC = new_var2;
  new_var = new_var2 >> 7;
  return new_var & 1;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_80014C54_15854.s")
#endif

#if NON_MATCHING
s32 func_80014CC4_158C4(s32 arg0) {
    s32 temp_t7;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;
    u8 temp_t4;

    var_a0 = arg0;
    var_a1 = D_8006ADC4_6B9C4;
    var_v1 = 0;
    if (var_a1 < var_a0) {
        do {
            var_a0 -= var_a1;
            temp_t4 = *D_80168160_168D60;
            var_v1 |= (D_8006ADCC_6B9CC & ((1 << var_a1) - 1)) << var_a0;
            D_80168160_168D60 += 1;
            D_8006ADC4_6B9C4 = 8;
            var_a1 = 8;
            D_8006ADCC_6B9CC = (s32) temp_t4;
        } while (var_a0 > 8);
    }
    temp_t7 = var_a1 - var_a0;
    D_8006ADC4_6B9C4 = temp_t7;
    return (((u32) D_8006ADCC_6B9CC >> temp_t7) & ((1 << var_a0) - 1)) | var_v1;
}
#else
#pragma GLOBAL_ASM("asm/usa/nonmatchings/wave_uty/func_80014CC4_158C4.s")
#endif
