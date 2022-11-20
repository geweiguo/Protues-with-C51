#ifndef __MATRIXKEY_H__
#define __MATRIXKEY_H__

#include<reg51.h>
#include "delay.h"

#define KEYPort P1
void MatrixKey_Scan(void);

extern unsigned char KeyNum;

#endif

