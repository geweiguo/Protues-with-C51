/*****************************************************************************************************
程序功能： 应用定时中断T0+串口中断实现超时接收一串数据的编程实现
程序实现：T0：1ms；定时中断用于判断是否超时，在波特率9600时，每帧（SBUF是1起始位+8位数据位+1结束位）数据
              数据之间的时间间隔为：（10bit*1000ms）/9600 ≈ 1.042ms；
          T1:波特率发生器 9600
    串口中断：RI/TI
*****************************************************************************************************/
#include <reg51.h>
#include "uart.h"


void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
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
   if( Start_timer == 1)
   {
      timeCnt ++;    //1.累加定时时间
      if(timeCnt > MAX_REV_TIME)  //2.判断时间是否超过一帧数据时间，超过则说明等待一段时间后没有新的数据，一包数据接收完成；
      {
        timeCnt = 0; //3.清除定时计数器 清除buf（数据处理完后处理）
        RecCnt  = 0;
        Recflag = 1;   
      }
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
        if(Recflag)
        {           
            Recflag = 0;
            Start_timer = 0;
            SendString(RecBuf);
            Cls(RecBuf); 
             
        }
         
    }

}