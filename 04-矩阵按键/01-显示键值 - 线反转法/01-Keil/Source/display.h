#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <reg52.h>
#include "delay.h"

#define GPIO_DIG   P1   //断码 IO口
#define GPIO_PLACE P2   //位选 IO口
#define N 4

unsigned char code leddata[]; 
unsigned char LEDBuf[];

void Display();

#endif


