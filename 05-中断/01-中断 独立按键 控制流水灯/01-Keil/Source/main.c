#include <reg52.h>

    sbit LED  = P1^0;

void EX0_INT0(void)
{
    IT0 = 1;//�ⲿ�жϴ�����ʽΪ �½���
    EX0 = 1;//IE IT0���ش�
    EA  = 1;//IE �д��ܿ���

}

void EX0_ISR (void) interrupt 0
{

    LED = ~LED;
}   

void main()
{
    EX0_INT0();
    while(1)
    {
             ;
    }

}