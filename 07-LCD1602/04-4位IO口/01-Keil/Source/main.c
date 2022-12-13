/****************************************
程序功能：四位IO口
*****************************************/
#include <reg51.h>
#include <stdio.h>
#include "delay.h"
#include "LCD1602.h"



void main()
{
    unsigned char code str[] = "Hello LCD 1602";
    unsigned char code str2[] = "Greg Ge 1982888";
    LCDInit();
    DelayXms(10);
    LEDShowStr(0,0,str);

    LEDShowStr(0,1,str2);
    DelayXms(10);

    while(1);

}

