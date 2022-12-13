/****************************************
程序功能：显示整数和小数
*****************************************/
#include <reg51.h>
#include <stdio.h>
#include "delay.h"
#include "LCD1602.h"



void main()
{
    long dat = -12345;
    unsigned char str[11];  //整数 缓冲区
    unsigned char floatbuf[10]; //浮点数缓冲区 
    unsigned char floatbuf2[10]; //浮点数缓冲区 
    float num = 3.14159;
    float num2 = 12.5;
    LCDInit();
    DelayXms(20);
//  显示整数   
    IntegerToStr(dat,str);   //显示-12345
    LEDShowStr(0,0,str);

//  显示小数num2
    sprintf(floatbuf2,"%0.1f",num2);   //浮点型格式化输出，头文件 stdio.h
    LEDShowStr(0,1,floatbuf2);

//  显示小数num
    sprintf(floatbuf,"%0.5f",num);   //浮点型格式化输出，头文件 stdio.h
    LEDShowStr(7,1,floatbuf);

    while(1);

}

