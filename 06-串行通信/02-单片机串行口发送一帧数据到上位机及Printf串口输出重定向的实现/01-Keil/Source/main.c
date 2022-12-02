/*************************************************

*************************************************/
#include <reg51.h>
#include "delay.h"
#include "uart.h"



void main()
{
    unsigned char dat1 = 88;
    unsigned int dat2 = 1982;
    float dat3 = 3.14;
    
        
    UartInit();
   
    while(1)
    {
//        SentByte(0x88);
//        SentByte('\r');
//        SentByte('\n');
//        SendString("Hello World!\r\n");

       printf("Hello World \r\n");
       printf("dat1 = %bu \r\n" ,dat1);
       printf("dat2 = %u \r\n" ,dat2);
       printf("dat3 = %.2f \r\n" ,dat3);
       DelayXms(1000);

    }
}
