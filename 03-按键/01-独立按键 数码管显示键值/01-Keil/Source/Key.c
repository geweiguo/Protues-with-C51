#include "Key.h"
#include "delay.h"

unsigned char KeyNum = 0;
                      
void Key_Scan(void)
{

    KeyNum = 0;
    KEY1 = 1; KEY2 = 1; KEY3 = 1; KEY4 = 1;

    if(!KEY1 || !KEY2 || !KEY3 || !KEY4)
    {
       DelayXms(10);
       if(!KEY1 || !KEY2 || !KEY3 || !KEY4)
       {
           if(!KEY1)
            KeyNum = 1;
           if(!KEY2)
            KeyNum = 2;    
           if(!KEY3)
            KeyNum = 3;
           if(!KEY4)
            KeyNum = 4;
       }while(!KEY1 || !KEY2 || !KEY3 || !KEY4); 

    
    }





//   if(0 == KEY1)
//   {
//      DelayXms(10);
//      if(0 == KEY1)
//      {
//        KeyNum = 1; 
//      }while(0 == KEY1);
//       
//   }
//
//   if(0 == KEY2)
//   {
//      DelayXms(10);
//      if(0 == KEY2)
//      {
//        KeyNum = 2; 
//      }while(0 == KEY2);  
//   }
   
}