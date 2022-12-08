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
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
//	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
//	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
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
                  if(RecCnt > 4)// �Զ�������Э�飺֡ͷ��55 AA �������ͣ�01 LED/02 Beep  ���ݳ��ȣ�20 20 ������5֡���ݣ�>4 ˵�����ݽ�����ϣ�                    
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