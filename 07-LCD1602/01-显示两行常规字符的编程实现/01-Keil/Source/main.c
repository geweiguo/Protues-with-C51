#include <reg51.h>
#include <string.h>
#include "delay.h"
#include "LCD1602.h"


void main()
{
    unsigned char str[] = "Hello LCD 1602";
    unsigned char str1[] = "Greg Ge 666";
    unsigned char i;
    LCDInit();
    DelayXms(10);

       //确定DDRAM地址
        LCDWriteCmd(0x80);    // 命令：设置数据存储器（DDRAM）地址； 第一行
        for(i = 0;i < strlen(str);i++)   // DDRAM地址从0开始到str长度结束；
        {
            LCDWritedata(str[i]);
            
        }
        
        LCDWriteCmd(0xC0);   // 命令：设置数据存储器（DDRAM）地址； 第二行  C是由 8 + 4 = C 得来；
        for(i= 0 ;i < strlen(str1);i++)   // DDRAM地址从40开始到str长度结束；
        {
            LCDWritedata(str1[i]);
          
        }

    while(1)
    {
           LCDWriteCmd(LCD_CUR_MOVE_LEFT); //光标左移
           DelayXms(800);
    }

}