#include <reg51.h>
#include <intrins.h>
#include "display.h"

unsigned char sec = 60;
unsigned char timer;
unsigned char temp = 0xfe;

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



void Timer1Init(void)		//50����@12.000MHz
{
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0xB0;		//���ö�ʱ��ֵ
	TH1 = 0x3C;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
    ET1 = 1;
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
}


void Timer0Init_ISR(void) interrupt 1  //�������1msƵ��ˢ��
{
    TR0 = 0;
    Display();
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
    TR0 = 1;
}

void Timer1Init_ISR(void) interrupt 3  //1s�ӵ���ʱ
{
    TR1 = 0;
    timer ++;
    if( timer == 20)    //�����ʱ 20�� 50ms = 1s
      {
        //LED��ˮ��

        P1 = temp;
        temp = _crol_(temp,1);

        //60s����ʱ
        sec--;
        if(sec == 0)
            {
             sec = 60;
            } 
        timer = 0; 
      }
    
	TL1 = 0xB0;		//���ö�ʱ��ֵ
	TH1 = 0x3C;		//���ö�ʱ��ֵ
    TR1 = 1;
}

void main()
{    
    Timer0Init();  // �����ˢ��
    Timer1Init();  // 1s�ӵ���ʱ
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