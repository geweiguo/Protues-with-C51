/*************************************************

*************************************************/
#include <reg51.h>
#include "delay.h"

void UartInit(void)		//4800bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
//	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}


unsigned char temp = 0;


void SentByte(unsigned char dat)
{
      SBUF = dat;
      while(!TI);
      TI = 0;

}


void main()
{


    UartInit();
    while(1)
    {
      SentByte('8');
      DelayXms(500);
    }
}
