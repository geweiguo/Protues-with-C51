#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <reg51.h>

#define GPIO_DIG   P0   //断码 IO口
#define GPIO_PLACE P2   //位选 IO口
#define N 6

unsigned char code leddataCC[]; 
unsigned char LEDBuf[];

void Display();

#endif


