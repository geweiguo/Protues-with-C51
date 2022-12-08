/*****************************************************************************************************
�����ܣ� Ӧ�ö�ʱ�ж�T0+�����ж�ʵ�ֳ�ʱ����һ�����ݵı��ʵ��
����ʵ�֣�T0��1ms����ʱ�ж������ж��Ƿ�ʱ���ڲ�����9600ʱ��ÿ֡��SBUF��1��ʼλ+8λ����λ+1����λ������
              ����֮���ʱ����Ϊ����10bit*1000ms��/9600 �� 1.042ms��
          T1:�����ʷ����� 9600
    �����жϣ�RI/TI
*****************************************************************************************************/
#include <reg51.h>
#include "uart.h"


void Timer0Init(void)		//1����@11.0592MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
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
   if( Start_timer == 1)
   {
      timeCnt ++;    //1.�ۼӶ�ʱʱ��
      if(timeCnt > MAX_REV_TIME)  //2.�ж�ʱ���Ƿ񳬹�һ֡����ʱ�䣬������˵���ȴ�һ��ʱ���û���µ����ݣ�һ�����ݽ�����ɣ�
      {
        timeCnt = 0; //3.�����ʱ������ ���buf�����ݴ��������
        RecCnt  = 0;
        Recflag = 1;   
      }
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
        if(Recflag)
        {           
            Recflag = 0;
            Start_timer = 0;
            SendString(RecBuf);
            Cls(RecBuf); 
             
        }
         
    }

}