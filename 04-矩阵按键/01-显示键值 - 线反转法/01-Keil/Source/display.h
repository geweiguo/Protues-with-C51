#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <reg52.h>
#include "delay.h"

#define GPIO_DIG   P1   //���� IO��
#define GPIO_PLACE P2   //λѡ IO��
#define N 4

unsigned char code leddata[]; 
unsigned char LEDBuf[];

void Display();

#endif


