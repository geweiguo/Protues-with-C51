/*****************************************************************************************************
�����ܣ� Ӧ�ö�ʱ�ж�T0+�����ж�ʵ�ֳ�ʱ����һ�����ݵı��ʵ��
����ʵ�֣�T0��1ms��
          T1:�����ʷ����� 9600
    �����жϣ�RI/TI
*****************************************************************************************************/
#include <reg51.h>
#include "uart.h"

sbit LED = P1^0;
sbit BEEP = P3^7;

void Timer0Init(void)		//1����@11.0592MHz
{
//	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
    ET0 = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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

   TL0 = 0x66;		//���ö�ʱ��ֵ
   TH0 = 0xFC;	
   TR0 = 1; 

}

void main()
{
    Timer0Init();
    UartInit();
    EA = 1; //���ж��ܿ���
    printf("wait for serial Communication Test Start. \r\n");
    printf("please Send a string of data:\r\n ");

    while(1)
    {         
        
    }

}