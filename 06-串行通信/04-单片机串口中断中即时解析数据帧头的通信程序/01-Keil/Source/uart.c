#include <reg51.h>
#include <stdio.h>
#include "uart.h"

unsigned char RecBuf[MAXREC] = 0;
unsigned char RecCnt = 0;
unsigned char Recflag = 0;
unsigned char machine_Step = 0;
unsigned int temp_data;
unsigned int led_Cnt;
unsigned int beep_Cnt;
unsigned char flageLED = 0;
unsigned char flageBEEP = 0;

void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
//	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
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
        switch(machine_Step)
        {
         case 0: RecBuf[0] = SBUF;
                if(RecBuf[0] == 0x55)
                {
                  machine_Step = 1; 
                  
                } 
                else
                {
                  machine_Step = 0;
                }
            break;
          case 1:RecBuf[1] = SBUF;
                if(RecBuf[1] == 0xAA)
                {
                  machine_Step = 2;
                  RecCnt = 2; 
                  
                } 
                else
                {
                  machine_Step = 0;
                }
             break;
          case 2: RecBuf[RecCnt] = SBUF; 
                  RecCnt++;
                  if(RecCnt > 4)// 自定义数据协议：帧头：55 AA 数据类型：01 LED/02 Beep  数据长度：20 20 ；共计5帧数据，>4 说明数据接收完毕；                    
                   {
                     machine_Step = 3; 
                                          
                   }
                  else
                   {
                     machine_Step = 2;
                     
                   }

                  break;
            case 3: RecBuf[RecCnt] = SBUF;
                    if(RecBuf[RecCnt] == 0x0D)
                    {
                       switch(RecBuf[2])
                        {
                          case 1: 
                                  temp_data = RecBuf[3];
                                  temp_data = temp_data << 8;
                                  temp_data = temp_data + RecBuf[4];
                                  led_Cnt = 0; 
                                  
                            break;
                          case 2: 
                                  temp_data = RecBuf[3];
                                  temp_data = temp_data << 8;
                                  temp_data = temp_data + RecBuf[4];
                                  beep_Cnt = temp_data;
                                                                                                                    
                            break;
                          default:break; 
                                                  
                        }
                    }
                 machine_Step = 0;
                 RecCnt = 0;
                 SendString(RecBuf);
                 Cls(RecBuf);                 
                 break;
                             
        }
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