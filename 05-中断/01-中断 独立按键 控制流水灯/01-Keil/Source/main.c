#include <reg52.h>

    sbit LED  = P1^0;

void EX0_INT0(void)
{
    IT0 = 1;//外部中断触发方式为 下降沿
    EX0 = 1;//IE IT0开关打开
    EA  = 1;//IE 中打开总开关

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