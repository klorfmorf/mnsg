#ifndef BIT_H
#define BIT_H


#include "common.h"

void bitInit(unsigned char *arg0);
int  bitRead1(void);
#ifndef NO_PROTO_bitRead
int  bitRead(int n);
#endif

#endif // BIT_H
