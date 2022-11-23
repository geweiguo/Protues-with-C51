#ifndef __MATRIXKEY_H__
#define __MATRIXKEY_H__

#include<reg52.h>
#include "delay.h"

#define KEYPort P0
void MatrixKey_Scan(void);

extern unsigned char KeyNum;

#endif

