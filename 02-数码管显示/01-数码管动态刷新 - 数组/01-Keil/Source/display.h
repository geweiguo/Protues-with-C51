#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <reg51.h>
#include "delay.h"

#define GPIO_DIG   P1   //���� IO��
#define GPIO_PLACE P2   //λѡ IO��
#define N 8

unsigned char code leddataCA[]; 
unsigned char LEDBuf[];

void display();

#endif


