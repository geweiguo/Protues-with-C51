#include <reg51.h>
#include <intrins.h>
#include "display.h"

unsigned char sec = 60;
unsigned char timer;
unsigned char temp = 0xfe;

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



void Timer1Init(void)		//50毫秒@12.000MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0xB0;		//设置定时初值
	TH1 = 0x3C;		//设置定时初值
	TF1 = 0;		//清除TF1标志
    ET1 = 1;
	TR1 = 1;		//定时器1开始计时
}


void Timer0Init_ISR(void) interrupt 1  //数码管以1ms频率刷新
{
    TR0 = 0;
    Display();
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
    TR0 = 1;
}

void Timer1Init_ISR(void) interrupt 3  //1s钟倒计时
{
    TR1 = 0;
    timer ++;
    if( timer == 20)    //软件计时 20次 50ms = 1s
      {
        //LED流水灯

        P1 = temp;
        temp = _crol_(temp,1);

        //60s倒计时
        sec--;
        if(sec == 0)
            {
             sec = 60;
            } 
        timer = 0; 
      }
    
	TL1 = 0xB0;		//设置定时初值
	TH1 = 0x3C;		//设置定时初值
    TR1 = 1;
}

void main()
{    
    Timer0Init();  // 数码管刷新
    Timer1Init();  // 1s钟倒计时
    EA = 1;

    while(1)
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
}