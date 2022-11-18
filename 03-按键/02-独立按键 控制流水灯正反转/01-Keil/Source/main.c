#include <reg51.h>
#include <intrins.h>
#include "delay.h"
#include "key.h"

bit startflag = 0; //������ֹͣ��־λ
bit updownflag = 0; //����ת��־λ
unsigned char Temp = 0xfe;

void Key_Service()
{
   Key_Scan();

   switch(KeyNum)
   {
     case 1: startflag = 1;break; //����1������ 
     case 2: startflag = 0;break; //����2��ֹͣ
     case 3: updownflag = 0;break; //����3����ת
     case 4: updownflag = 1;break; //����4����ת
     default:break;     

   }
}

void LEDWorking_Service()
{


    if(startflag )
    {        
        P1 = Temp;  //��0xfe��1111 1110�� ��ֵ��P1�� 
        if(updownflag )
        {

          Temp = _cror_(Temp,1);  //P1�� ��0xfeֵѭ������
         }

        else
        {

          Temp = _crol_(Temp,1);//P1�� ��0xfeֵѭ������
         }            
        DelayXms(500);

    }

     else if(0 == startflag )     
     {
       P1 = 0xff;
     }

}

void main()
{

    while(1)
    {
      Key_Service();

      LEDWorking_Service();
        
    }
}