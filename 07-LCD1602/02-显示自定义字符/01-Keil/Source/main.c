#include <reg51.h>
#include <string.h>
#include "delay.h"
#include "LCD1602.h"


void main()
{
    //unsigned char str[] = "Hello LCD 1602";
    unsigned char str1[] = "Greg Ge 666";
    unsigned char code str[] = {0x00,0x00,0x00,0x00,0x1f,0x00,0x00,0x00};
    unsigned char code str2[] = {0x00,0x00,0x04,0x1F,0x04,0x0A,0x11,0x00};
    LCDInit();
    DelayXms(10);

   // LCDWriteCGRAM();
    LCDSetChar(7,0,0,str2); //自定义字符显示函数
    LEDShowStr(0,1,str1);  //字符串显示

    while(1)
    {
           LCDWriteCmd(LCD_CUR_MOVE_LEFT); //光标左移
           DelayXms(800);
    }

}