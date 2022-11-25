/******************************************************************
功能：      开关实现门铃 700Hz  500Hz
实现方案：定时器0：产生 两个频率信号 及 一个 500ms延时功能
编写人：Greg Ge
修订日期：2022-11-25
修订版本：V01
*******************************************************************/
#include <reg51.h>
#include "Key.h"

unsigned int timerCnt = 0;
unsigned char Flag = 0;
unsigned char un700Hz = 0;
unsigned char un500Hz = 0;


sbit DoorBell = P3^7;

void Key_Service()
{
    Key_Scan();
    switch(KeyNum)
    {   
        case 1 :break;
        case 2 :break;
        case 3 :TR0 = ~TR0;break;
        case 4 :break;
        default:break;
    }
}

void Timer0Init(void)		//250微秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x06;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
    ET0 = 1;
    EA  = 1;
//	TR0 = 1;		//定时器0开始计时
}

void Timer0_ISR(void) interrupt 1
{
    timerCnt++;
    if(timerCnt >= 2000)    //500ms延时时间
    {   
       timerCnt = 0;
       Flag = ~Flag;
    }

    if(!Flag)
    {
      un700Hz ++; 
      if(un700Hz >= 3)  //250微秒 * 3 = 750微秒
      {  
         un700Hz = 0;   
         DoorBell = ~ DoorBell;
      }          
    } 
   
    if(Flag)
    {
      un500Hz ++; 
      if(un500Hz >= 4)
      {  
         un500Hz = 0;   
         DoorBell = ~ DoorBell;
       }          
    } 

    TL0 = 0x06;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
}



void main()
{
    Timer0Init();
    while(1)
    {
      Key_Service();
    }

}
