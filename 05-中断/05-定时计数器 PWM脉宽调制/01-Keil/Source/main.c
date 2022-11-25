/******************************************************************
���ܣ�1��PWM �������ʵ��LED�����ȵ��ڣ���ͨ���������ʾPWMռ�ձȡ�
      2������ʵ�� �ƵĿ��� �� ռ�ձȵ��л���

ʵ�ַ�������ʱ��0������ܶ�̬ˢ����ʾ
          ��ʱ��1������PWM�� 
          �ⲿ�ж�0�������л� 

PWM����Ҫ����������1��ռ�ձ�  2������Ƶ�ʣ�����100 Hz��
��д�ˣ�Greg Ge
�޶����ڣ�2022-11-25
�޶��汾��V01
*******************************************************************/
#include <reg51.h>
#include "display.h"

unsigned char PWM_Duty = 0;
unsigned char PWM_Cnt = 0;
sbit LED = P1^0;

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

void Timer0Init_ISR(void) interrupt 1
{
    TR0 = 0; 
    Display();
    TL0 = 0x18;		//���ö�ʱ��ֵ
    TH0 = 0xFC;		//���ö�ʱ��ֵ
    TR0 = 1; 
}

void Timer1Init(void)		//100΢��@12.000MHz
{
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0x9C;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
    ET1 = 1;
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
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
 	TL1 = 0x9C;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ
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
