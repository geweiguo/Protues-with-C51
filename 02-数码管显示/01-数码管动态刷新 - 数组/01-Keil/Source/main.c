#include<reg51.h>
#include "delay.h"
#include "display.h"

void main()
{
    unsigned int year = 2010;
    unsigned int month_day = 716;
    unsigned int times = 62535;
    unsigned int Tempture = 30;

    unsigned int i;
    unsigned int j;

    for(j=0;j<5;j++)
    {
       for(i=0;i<400;i++)
        {
             display();         
        }
        GPIO_PLACE = 0x00;
        delay(400); 
    
    }

    
  
         

    while(1)
    {
       LEDBuf[0] = year/1000;
       LEDBuf[1] = year/100%10;
       LEDBuf[2] = year/10%10;
       LEDBuf[3] = year%10;
       LEDBuf[4] = month_day/1000%10;
       LEDBuf[5] = month_day/100%10;
       LEDBuf[6] = month_day/10%10;
       LEDBuf[7] = month_day%10;
       
       for(i = 0;i < 2000;i++)
       {
           display();
       }
            
//       month_day = month_day + 1;
//       if(month_day  > 731)
//          month_day = 701;     
       
       delay(500);      
       
       
       LEDBuf[0] = 23;
       LEDBuf[1] = 23;
       LEDBuf[2] = 23;
       LEDBuf[3] = times/10000%10;
       LEDBuf[4] = times/1000%10;
       LEDBuf[5] = times/100%10;
       LEDBuf[6] = times/10%10;
       LEDBuf[7] = times%10;
       for(i = 0;i < 2000;i++)
       {
           display();
       }
       delay(500);
       
       LEDBuf[0] = 23;
       LEDBuf[1] = 23;
       LEDBuf[2] = 23;
       LEDBuf[3] = 23;
       LEDBuf[4] = 23;
       LEDBuf[5] = 23;
       LEDBuf[6] = Tempture/10%10;
       LEDBuf[7] = Tempture%10;
       for(i = 0;i < 2000;i++)
       {
           GPIO_PLACE = 0x03;
           display();
       }
       delay(500);
    }
}

