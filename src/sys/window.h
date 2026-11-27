#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"
#include "structs.h"

void func_8000B880(void);
void func_8000B8A4(WindowStyle *arg0);
void func_8000B8B0(void);
void func_8000C260(int id, int x, int y, int from_x, int from_y, int style, int effect);
int  func_8000C314(int arg0);
void func_8000C3A0(int arg0);
void func_8000C3EC(int arg0);
void func_8000C430(int arg0, int arg1);
void func_8000C454(int arg0);
void func_8000C488(int arg0);
void func_8000C53C(int arg0, int arg1);
void func_8000C568(int arg0, float arg1);
void func_8000C570(int id);
void func_8000C5A4(int id);
void func_8000C5E4(int arg0, float arg1);
void func_8000C60C(int id);
void func_8000C640(int id);
void func_8000C838(void);
void func_8000C878(int id);
int  func_8000D060(int id, int code);
void func_8000D2C0(int arg0);

extern unsigned char D_8005BB10[96];
extern WindowStyle   D_800627F0[12];
extern unsigned char D_800629A0[2432];
extern unsigned int  D_80063320[];
extern unsigned int  D_80063360[];
extern unsigned int  D_800633A0[];
extern unsigned int  D_800633E0[];
extern unsigned int  D_80063420[];
extern Window       *D_80167C48[3];

#endif // WINDOW_H
