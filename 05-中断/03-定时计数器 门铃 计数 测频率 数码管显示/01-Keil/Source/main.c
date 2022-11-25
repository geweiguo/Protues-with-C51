/*****************************************************************
�����ܣ�ʹ��T1ʵ�� �ⲿ��������Ͳ�Ƶ
����ʵ�֣�1��T0 ��������� ��̬��ʾ
          2��T1 TMOD ����Ϊ�������� GATE C/T M1 MO ----  0 1 0 1
��д�ˣ�  Greg Ge
�޶����ڣ�2022-11-25
�޶��汾��V01
******************************************************************/
#include <reg51.h>
#include "display.h"
unsigned int dataCnt = 0;
unsigned int Flag;

void Timer0Init(void)		//1����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
    ET0 = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer0_ISR(void) interrupt 1
{
   	TR0 = 0;

    Flag++;
    if(Flag >= 1000) //ÿ��һ����ȡ��dataCnt�е�ֵ �� Ƶ�ʣ�
        {
         TR1 = 0;
         dataCnt = TH1*256 + TL1 ;
         Flag = 0; 
         TH1 = TL1 = 0; 
         TR1 = 1;        
        } 
    Display();
   	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
    TR0 = 1;
}

void Timer1Init(void)
{
   	TMOD &= 0x0F;		//���ü�����ģʽ GATE C/T M1 MO ----  0 1 0 1
	TMOD |= 0x50;		//���ü�����ģʽ
	TL1 = 0;		//���ü�����ֵ 0
	TH1 = 0;		//���ü�����ֵ 0
	TF1 = 0;		//���TF1��־
    ET1 = 1;
    TR1 = 1;		//������1��ʼ��ʱ
}

void Dis_Service()
{
        LEDBuf[0] = dataCnt/100000;
        LEDBuf[1] = dataCnt/10000%10;
        LEDBuf[2] = dataCnt/1000%10;
        LEDBuf[3] = dataCnt/100%10;
        LEDBuf[4] = dataCnt/10%10;
        LEDBuf[5] = dataCnt%10;   
}
void main()
{
    EA = 1;
    Timer0Init();
    Timer1Init();
    while(1)
    {   

        Dis_Service();
    }

}