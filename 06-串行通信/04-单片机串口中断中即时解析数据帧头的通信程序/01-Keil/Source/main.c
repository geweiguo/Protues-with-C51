/*****************************************************************************************************
程序功能： 应用定时中断T0+串口中断实现超时接收一串数据的编程实现
程序实现：T0：1ms；
          T1:波特率发生器 9600
    串口中断：RI/TI
*****************************************************************************************************/
#include <reg51.h>
#include "uart.h"

sbit LED = P1^0;
sbit BEEP = P3^7;

void Timer0Init(void)		//1毫秒@11.0592MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
    ET0 = 1;
	TR0 = 1;		//定时器0开始计时
}

void Timer0_ISR(void) interrupt 1
{
   TR0 = 0;
   if(led_Cnt < temp_data)
   {          
        led_Cnt++;
        LED = 0;           
   }
   else LED = 1; 
   
   
   if(beep_Cnt != 0)
   {
        beep_Cnt--;
        BEEP = ~BEEP;
   }

   TL0 = 0x66;		//设置定时初值
   TH0 = 0xFC;	
   TR0 = 1; 

}

void main()
{
    Timer0Init();
    UartInit();
    EA = 1; //打开中断总开关
    printf("wait for serial Communication Test Start. \r\n");
    printf("please Send a string of data:\r\n ");

    while(1)
    {         
        
    }

}