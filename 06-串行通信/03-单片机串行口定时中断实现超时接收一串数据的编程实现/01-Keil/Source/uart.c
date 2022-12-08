#include <reg51.h>
#include <stdio.h>
#include "uart.h"

unsigned char RecBuf[MAXREC] = 0;
unsigned char timeCnt = 0;
unsigned char RecCnt = 0;
unsigned char Recflag = 0;
unsigned char Start_timer = 0;

void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
    ES  = 1;        //串口中断打开
	TR1 = 1;		//启动定时器1

}

void SentByte(unsigned char dat)   //发送一个字节
{
    SBUF = dat;
    while(!TI);
    TI = 0;
}

void SendString(unsigned char *dat) //发送一串字符 Hello World!
{
    while(*dat != '\0')
    {
       SentByte(*dat++); 
    }

}

char putchar(char c)   //printf 函数重定向
{
     SentByte(c);
     return c;
}

/***************************************************************
1、中断服务函数一定是一个没有返回值的函数；
2、中断服务函数一定是没有参数的函数；
3、中断服务函数函数名后跟关键字 interrupt “n”  
4、n是中断向量入口地址值，n取值：0~4 共5个中断源 8*n + 0003H
                                                   0   0003H INT0
                                                   1   000BH T0
                                                   2   0013H INT1
                                                   3   001BH T1
                                                   4   0023H ES
5、中断服务函数不能被主程序或其它程序所调用
6、n后面跟using m （0-3）工作寄存器组
***************************************************************/

void Rec_ISR() interrupt 4
{
    
    if(RI)
    {   
        RI = 0;
        Start_timer = 1;   //1、每接收第一帧数据，打开定时器，去计数         
        if(RecCnt < MAXREC)
        {
           RecBuf[RecCnt] = SBUF;//2.接收数据到缓冲区，注意缓冲区大小
           RecCnt ++; 
        }

        else 
        {
           RecCnt = MAXREC;
        }
        timeCnt = 0;  //3、每接收一帧数据，记得把定时计数清零 相当于喂狗
                      //但是在定时中断中会不断累加
    
    }
    if(TI)
    {
        TI = 0;    
    }
}

void Cls(unsigned char* buf)
{
    unsigned char i = 0;
    for(i = 0;i < MAXREC;i++)
    {
        buf[i] = 0;    
    }

}