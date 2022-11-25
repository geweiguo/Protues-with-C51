/*****************************************************************
程序功能：使用T1实现 外部脉冲计数和测频
程序实现：1、T0 数显数码管 动态显示
          2、T1 TMOD 设置为计数功能 GATE C/T M1 MO ----  0 1 0 1
编写人：  Greg Ge
修订日期：2022-11-25
修订版本：V01
******************************************************************/
#include <reg51.h>
#include "display.h"
unsigned int dataCnt = 0;
unsigned int Flag;

void Timer0Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
    ET0 = 1;
	TR0 = 1;		//定时器0开始计时
}

void Timer0_ISR(void) interrupt 1
{
   	TR0 = 0;

    Flag++;
    if(Flag >= 1000) //每过一秒钟取下dataCnt中的值 即 频率；
        {
         TR1 = 0;
         dataCnt = TH1*256 + TL1 ;
         Flag = 0; 
         TH1 = TL1 = 0; 
         TR1 = 1;        
        } 
    Display();
   	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
    TR0 = 1;
}

void Timer1Init(void)
{
   	TMOD &= 0x0F;		//设置计数器模式 GATE C/T M1 MO ----  0 1 0 1
	TMOD |= 0x50;		//设置计数器模式
	TL1 = 0;		//设置计数初值 0
	TH1 = 0;		//设置计数初值 0
	TF1 = 0;		//清除TF1标志
    ET1 = 1;
    TR1 = 1;		//计数器1开始计时
}

void Dis_Service()
{
        LEDBuf[0] = dataCnt/100000;
        LEDBuf[1] = dataCnt/10000%10;
        LEDBuf[2] = dataCnt/1000%10;
        LEDBuf[3] = dataCnt/100%10;
        LEDBuf[4] = dataCnt/10%10;
        LEDBuf[5] = dataCnt%10;   
}
void main()
{
    EA = 1;
    Timer0Init();
    Timer1Init();
    while(1)
    {   

        Dis_Service();
    }

}