/*********************************************************
�����ܣ�����ʱ�ӣ�ʵ�ַ� �� ʱ����
����ʵ�֣�T0 ���������ˢ��
          T1 ����ʱ�� ��׼ʱ���� > �� > ʱ
          INT0 ����KEY1 ����ҳ���л�
          INT1 ����KEY2 ��������
��д�� ��Greg Ge
�޶����ڣ�2022-11-27
�޶��汾��V01
*********************************************************/
#include <reg51.h>
#include "display.h"

unsigned char timer = 0;
unsigned char sec = 0;
unsigned char min = 0;
unsigned char hour = 0;
unsigned char state = 0;

//����T0 ���������ˢ��  1����
void Timer0Init(void)		//1����@12.000MHz
{
//	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
    ET0 = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

//T0������
void Timer0_ISR(void) interrupt 1
{
   TR0 = 0; 
   Display();
   TL0 = 0x18;		//���ö�ʱ��ֵ
   TH0 = 0xFC;		//���ö�ʱ��ֵ
   TR0 = 1; 

}

//����T1 ����ʱ�� ��׼ʱ���� > �� > ʱ
void Timer1Init(void)		//50����@12.000MHz
{
//	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0xB0;		//���ö�ʱ��ֵ
	TH1 = 0x3C;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
    ET1 = 1;
}
//T1������
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

   TL1 = 0xB0;		//���ö�ʱ��ֵ
   TH1 = 0x3C;		//���ö�ʱ��ֵ   
}

void INT0init()
{
    IT0 = 1;//�½��ش���
    EX0 = 1;
}
void INT0_ISR() interrupt 0   //KEY1 ����ҳ���л�
{
    state ++;
    if(state >4)
       state = 0; 
}
void INT1init()
{
    IT1 = 1;//�½��ش���
    EX1 = 1;
}
void INT1_ISR() interrupt 2   //KEY1 ����ҳ���л�
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
        case 1:TR1 = 0;showsec();break; //����
        case 2:TR1 = 0;showmin();break; //����
        case 3:TR1 = 0;showhour();break; //��ʱ
      
      }        
    }
}