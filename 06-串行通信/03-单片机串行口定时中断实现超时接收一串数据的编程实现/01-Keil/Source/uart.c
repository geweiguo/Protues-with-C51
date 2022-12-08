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
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
    ES  = 1;        //�����жϴ�
	TR1 = 1;		//������ʱ��1

}

void SentByte(unsigned char dat)   //����һ���ֽ�
{
    SBUF = dat;
    while(!TI);
    TI = 0;
}

void SendString(unsigned char *dat) //����һ���ַ� Hello World!
{
    while(*dat != '\0')
    {
       SentByte(*dat++); 
    }

}

char putchar(char c)   //printf �����ض���
{
     SentByte(c);
     return c;
}

/***************************************************************
1���жϷ�����һ����һ��û�з���ֵ�ĺ�����
2���жϷ�����һ����û�в����ĺ�����
3���жϷ���������������ؼ��� interrupt ��n��  
4��n���ж�������ڵ�ֵַ��nȡֵ��0~4 ��5���ж�Դ 8*n + 0003H
                                                   0   0003H INT0
                                                   1   000BH T0
                                                   2   0013H INT1
                                                   3   001BH T1
                                                   4   0023H ES
5���жϷ��������ܱ����������������������
6��n�����using m ��0-3�������Ĵ�����
***************************************************************/

void Rec_ISR() interrupt 4
{
    
    if(RI)
    {   
        RI = 0;
        Start_timer = 1;   //1��ÿ���յ�һ֡���ݣ��򿪶�ʱ����ȥ����         
        if(RecCnt < MAXREC)
        {
           RecBuf[RecCnt] = SBUF;//2.�������ݵ���������ע�⻺������С
           RecCnt ++; 
        }

        else 
        {
           RecCnt = MAXREC;
        }
        timeCnt = 0;  //3��ÿ����һ֡���ݣ��ǵðѶ�ʱ�������� �൱��ι��
                      //�����ڶ�ʱ�ж��л᲻���ۼ�
    
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