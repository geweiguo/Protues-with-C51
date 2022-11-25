/******************************************************************
功能：1、PWM 脉宽调制实现LED灯亮度调节，并通过数码管显示PWM占空比。
      2、开关实现 灯的开关 及 占空比的切换；

实现方案：定时器0：数码管动态刷新显示
          定时器1：产生PWM波 
          外部中断0：开关切换 

PWM波主要两个参数：1、占空比  2、基础频率（采用100 Hz）
编写人：Greg Ge
修订日期：2022-11-25
修订版本：V01
*******************************************************************/
#include <reg51.h>
#include "display.h"

unsigned char PWM_Duty = 0;
unsigned char PWM_Cnt = 0;
sbit LED = P1^0;

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

void Timer0Init_ISR(void) interrupt 1
{
    TR0 = 0; 
    Display();
    TL0 = 0x18;		//设置定时初值
    TH0 = 0xFC;		//设置定时初值
    TR0 = 1; 
}

void Timer1Init(void)		//100微秒@12.000MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x9C;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
	TF1 = 0;		//清除TF1标志
    ET1 = 1;
	TR1 = 1;		//定时器1开始计时
}

void Timer1_ISR(void) interrupt 3
{
    TR1 = 0;
    PWM_Cnt ++;
    if(PWM_Cnt > 100)
    {   
        PWM_Cnt = 0;
        
    }
    if(PWM_Cnt < PWM_Duty)
    {
       LED = 1;     
    }
    if(PWM_Cnt > PWM_Duty)
    {
       LED = 0;     
    }
 	TL1 = 0x9C;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
    TR1 = 1;
}

void  EX0_Int0()
{
    IT0 = 1;
    EX0 = 1;
}

void  EX0_ISR()	interrupt 0
{
    static unsigned char KeyCnt = 0;
    KeyCnt ++;
    switch(KeyCnt)
    {
      case 1 : PWM_Duty = 25;break; 
      case 2 : PWM_Duty = 50;break; 
      case 3 : PWM_Duty = 75;break; 
      case 4 : PWM_Duty = 80;break; 
      case 5 : PWM_Duty = 100;break; 
      case 6 : PWM_Duty = 0;KeyCnt = 0;break; 
    
    }

}

void main()
{

    Timer0Init();
    Timer1Init(); 
    EX0_Int0();
    EA = 1;

    while(1)
    {
        LEDBuf[0] = 23;
        LEDBuf[1] = 23;
        LEDBuf[2] = 23;
        LEDBuf[3] = 23;
        LEDBuf[4] = 23;
        LEDBuf[5] =  PWM_Duty/100;
        LEDBuf[6] =  PWM_Duty/10%10;
        LEDBuf[7] =  PWM_Duty%10;
    }

}
