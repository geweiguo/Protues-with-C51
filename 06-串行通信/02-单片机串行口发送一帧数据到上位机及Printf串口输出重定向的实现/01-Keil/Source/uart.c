#include <reg51.h>
#include "uart.h"

sfr AUXR =0x8E;

void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1

}

void SentByte(unsigned char dat)
{
    SBUF = dat;
    while(!TI);
    TI = 0;
}

void SendString(unsigned char *dat) //Hello World!
{
    while(*dat != '\0')
    {
       SentByte(*dat++); 
    }

}

char putchar(char c)
{
     SentByte(c);
     return c;
}