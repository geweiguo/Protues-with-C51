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
    LCDSetChar(7,0,0,str2); //�Զ����ַ���ʾ����
    LEDShowStr(0,1,str1);  //�ַ�����ʾ

    while(1)
    {
           LCDWriteCmd(LCD_CUR_MOVE_LEFT); //�������
           DelayXms(800);
    }

}