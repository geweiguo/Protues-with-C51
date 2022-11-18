#include <reg51.h>
#include <intrins.h>
#include "delay.h"
#include "key.h"

bit startflag = 0; //启动与停止标志位
bit updownflag = 0; //正反转标志位
unsigned char Temp = 0xfe;

void Key_Service()
{
   Key_Scan();

   switch(KeyNum)
   {
     case 1: startflag = 1;break; //按键1：启动 
     case 2: startflag = 0;break; //按键2：停止
     case 3: updownflag = 0;break; //按键3：正转
     case 4: updownflag = 1;break; //按键4：反转
     default:break;     

   }
}

void LEDWorking_Service()
{


    if(startflag )
    {        
        P1 = Temp;  //将0xfe（1111 1110） 赋值给P1口 
        if(updownflag )
        {

          Temp = _cror_(Temp,1);  //P1口 将0xfe值循环右移
         }

        else
        {

          Temp = _crol_(Temp,1);//P1口 将0xfe值循环左移
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