/****************************************
程序功能：四位IO口
*****************************************/
#include <reg51.h>
#include <stdio.h>
#include "delay.h"
#include "LCD1602.h"
#include "Key.h"

void StartMenu();
void LCDShowService();
void LCDShowSec();
void LCDShowMin();
void LCDShowHour();
void Timer0Init();
void Timer0ISR();
void Init();
void INT0_ISR();
void INT1_ISR();
void LCDShowSecBlink();
void LCDShowMinBlink();
void LCDShowHourBlink();
unsigned char state = 0;
unsigned char Sec  = 0;
unsigned char Min  = 0;
unsigned char Hour = 0;
unsigned timerCnt  = 0;

void main()
{   
    Timer0Init();
    Init();
    LCDInit();
    DelayXms(10);
    StartMenu();
    DelayXms(2000);
    LCDWriteCmd(LCD_SCREEN_CLR);
    while(1)
    {  
        LCDShowService();
    }
}
void LCDShowService()
{
    switch(state)
    {
        case 0: TR0 = 1;LCDShowSec();LCDShowMin();LCDShowHour();break;
        case 1: TR0 = 0;LCDShowSecBlink();break;
        case 2: TR0 = 0;LCDShowMinBlink();LCDShowSec();break;
        case 3: TR0 = 0;LCDShowHourBlink();LCDShowSec();LCDShowMin();break;
        default:break;
    }

    LEDShowStr(2,0,"Current Temp");

}

//开始菜单
void StartMenu()
{
    LEDShowStr(1,0,"The DAS of TEMP");
    LEDShowStr(2,1,"v1.0 by Greg");
}

void LCDShowSec()
{
      LCDSetPosition(10,1);
      LCDWritedata(Sec/10 + '0');
      LCDWritedata(Sec%10 + '0');
}
void LCDShowSecBlink()
{
      LCDSetPosition(10,1);
      LCDWritedata(Sec/10 + '0');
      LCDWritedata(Sec%10 + '0');
      DelayXms(350);
      LEDShowStr(10,1,"  "); 
      DelayXms(200);
}

void LCDShowMin()
{
       LCDSetPosition(7,1);
       LCDWritedata(Min/10 + '0');
       LCDWritedata(Min%10 + '0');
       LCDWritedata(':');
}
void LCDShowMinBlink()
{
       LCDSetPosition(7,1);
       LCDWritedata(Min/10 + '0');
       LCDWritedata(Min%10 + '0');
       LCDWritedata(':');
       DelayXms(350);
       LEDShowStr(7,1,"  "); 
       DelayXms(200);
}
void LCDShowHour()
{
        LCDSetPosition(4,1);
        LCDWritedata(Hour/10 + '0');
        LCDWritedata(Hour%10 + '0');
        LCDWritedata(':');    
}
void LCDShowHourBlink()
{
        LCDSetPosition(4,1);
        LCDWritedata(Hour/10 + '0');
        LCDWritedata(Hour%10 + '0');
        LCDWritedata(':'); 
        DelayXms(350); 
        LEDShowStr(4,1,"  ");
        DelayXms(200);  
}
void Timer0Init(void)		//1毫秒@11.0592MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
    ET0 = 1;
    EA  = 1;
}
void Timer0ISR() interrupt 1
{
    TR0 = 0;
    timerCnt++;
    if(timerCnt >= 1000)
    {
       timerCnt = 0;
       Sec++; 
       if(Sec >= 60)
       {
          Sec = 0;
          Min++;
          if(Min >= 60)
          {
             Min = 0;
             Hour++;
             if(Hour >= 24)
             {
               Hour = 0; 
             }          
          }      
       }    
    }

	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
    TR0 = 1;
}


void Init()//外部中断INT0 INT1初始化
{
    IT0 = 1;
    IT1 = 1;
    EX0  = 1;
    EX1  = 1;
}

void INT0_ISR() interrupt 0
{
   if(P3^2 == 0)
   {  
      DelayXms(5);
      if(P3^2 == 0)
      {               
          state++;
           if(state > 3)
           {
             state = 0;
           }       
      }  
        
   }
}

void INT1_ISR() interrupt 2
{
   DelayXms(10);
   if(P3^3 == 0)
   {
       switch(state)
       {
         case 1:Sec++;if(Sec >= 60) Sec = 0;break;
         case 2:Min++;if(Min >= 60) Min = 0;break;
         case 3:Hour++;if(Hour >= 24) Hour = 0;break;
         default:break;   
       }
   }

}
 
