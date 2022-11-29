/*********************************************************
程序功能：电子时钟，实现分 秒 时调整
程序实现：T0 用于数码管刷新
          T1 产生时间 基准时间秒 > 分 > 时
          INT0 用于KEY1 调整页面切换
          INT1 用于KEY2 调整参数
编写人 ：Greg Ge
修订日期：2022-11-27
修订版本：V01
*********************************************************/
#include <reg51.h>
#include "display.h"

unsigned char timer = 0;
unsigned char sec = 0;
unsigned char min = 0;
unsigned char hour = 0;
unsigned char state = 0;

//配置T0 用于数码管刷新  1毫秒
void Timer0Init(void)		//1毫秒@12.000MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
    ET0 = 1;
	TR0 = 1;		//定时器0开始计时
}

//T0服务函数
void Timer0_ISR(void) interrupt 1
{
   TR0 = 0; 
   Display();
   TL0 = 0x18;		//设置定时初值
   TH0 = 0xFC;		//设置定时初值
   TR0 = 1; 

}

//配置T1 产生时间 基准时间秒 > 分 > 时
void Timer1Init(void)		//50毫秒@12.000MHz
{
//	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0xB0;		//设置定时初值
	TH1 = 0x3C;		//设置定时初值
	TF1 = 0;		//清除TF1标志
    ET1 = 1;
}
//T1服务函数
void Timer1_ISR(void) interrupt 3
{
   timer ++;
   if(timer >= 20)
   {
       timer = 0;
       sec ++;
       if(sec >=60)
       {
         sec = 0;
         min++;
         if(min >=60)
         {
            min = 0;
            hour ++;
            if(hour >= 24)
            {
               hour = 0; 
            }         
         }  
       }    
   }

   TL1 = 0xB0;		//设置定时初值
   TH1 = 0x3C;		//设置定时初值   
}

void INT0init()
{
    IT0 = 1;//下降沿触发
    EX0 = 1;
}
void INT0_ISR() interrupt 0   //KEY1 进行页面切换
{
    state ++;
    if(state >4)
       state = 0; 
}
void INT1init()
{
    IT1 = 1;//下降沿触发
    EX1 = 1;
}
void INT1_ISR() interrupt 2   //KEY1 进行页面切换
{
    switch(state)
    {
        case 0:break;
        case 1:sec++;if(sec>=60) sec = 0;break;
        case 2:min++;if(min>=60) min = 0;break;
        case 3:hour++;if(hour>=60) hour = 0;break;
    } 
}

void shownomal()
{
    LEDBuf[0] = 23;
    LEDBuf[1] = 23;
    LEDBuf[2] = hour/10;
    LEDBuf[3] = hour%10;
    LEDBuf[4] = min/10;
    LEDBuf[5] = min%10;
    LEDBuf[6] = sec/10;
    LEDBuf[7] = sec%10;
}

void showsec()
{
    LEDBuf[0] = 23;
    LEDBuf[1] = 23;
    LEDBuf[2] = 23;
    LEDBuf[3] = 23;
    LEDBuf[4] = 23;
    LEDBuf[5] = 23;
    LEDBuf[6] = sec/10;
    LEDBuf[7] = sec%10;
}

void showmin()
{
    LEDBuf[0] = 23;
    LEDBuf[1] = 23;
    LEDBuf[2] = 23;
    LEDBuf[3] = 23;
    LEDBuf[4] = min/10;
    LEDBuf[5] = min%10;
    LEDBuf[6] = 23;
    LEDBuf[7] = 23;
}

void showhour()
{
    LEDBuf[0] = 23;
    LEDBuf[1] = 23;
    LEDBuf[2] = hour/10;
    LEDBuf[3] = hour%10;
    LEDBuf[4] = 23;
    LEDBuf[5] = 23;
    LEDBuf[6] = 23;
    LEDBuf[7] = 23;
}
void main()
{       
    EA = 1;
    Timer0Init();
    Timer1Init();
    INT0init();
    INT1init();

    while(1)
    {
      switch(state)
      {
        case 0:TR1 = 1;shownomal();break;
        case 1:TR1 = 0;showsec();break; //调秒
        case 2:TR1 = 0;showmin();break; //调分
        case 3:TR1 = 0;showhour();break; //调时
      
      }        
    }
}