#ifndef __KEY_H__
#define __KEY_H__
#include <reg51.h>


sbit KEY1 = P3^0;
sbit KEY2 = P3^1;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

void Key_Scan();
extern unsigned char KeyNum;

#endif