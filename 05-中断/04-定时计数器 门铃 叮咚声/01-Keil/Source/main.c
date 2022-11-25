/******************************************************************
���ܣ�      ����ʵ������ 700Hz  500Hz
ʵ�ַ�������ʱ��0������ ����Ƶ���ź� �� һ�� 500ms��ʱ����
��д�ˣ�Greg Ge
�޶����ڣ�2022-11-25
�޶��汾��V01
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

void Timer0Init(void)		//250΢��@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x06;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
    ET0 = 1;
    EA  = 1;
//	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer0_ISR(void) interrupt 1
{
    timerCnt++;
    if(timerCnt >= 2000)    //500ms��ʱʱ��
    {   
       timerCnt = 0;
       Flag = ~Flag;
    }

    if(!Flag)
    {
      un700Hz ++; 
      if(un700Hz >= 3)  //250΢�� * 3 = 750΢��
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

    TL0 = 0x06;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
}



void main()
{
    Timer0Init();
    while(1)
    {
      Key_Service();
    }

}
