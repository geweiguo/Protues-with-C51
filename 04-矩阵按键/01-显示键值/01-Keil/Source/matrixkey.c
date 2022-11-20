#include<reg51.h>
#include "matrixkey.h"
#include "delay.h"

unsigned char KEYIN = 0;
unsigned char KEYOUT = 0;

void MatrixKey_Scan(void)
{   

    KEYIN1 = 0; KEYIN2 = 0; KEYIN3 = 0; KEYIN4 = 0;
    KEYOUT1 = 1; KEYOUT2 = 1; KEYOUT3 = 1; KEYOUT4 = 1;

    if(!KEYOUT1 || !KEYOUT2 || !KEYOUT3 || !KEYOUT4 )
    {
       DelayXms(10);
       if(!KEYOUT1 || !KEYOUT2 || !KEYOUT3 || !KEYOUT4 )
       {
           if(!KEYOUT1)
            KEYOUT = 1;
           if(!KEYOUT2)
            KEYOUT = 2;    
           if(!KEYOUT3)
            KEYOUT = 3;
           if(!KEYOUT4)
            KEYOUT = 4;       
       }
      }

    KEYIN1 = 1; KEYIN2 = 1; KEYIN3 = 1; KEYIN4 = 1;
    KEYOUT1 = 0; KEYOUT2 = 0; KEYOUT3 = 0; KEYOUT4 = 0;

    if(!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
    {
       DelayXms(10);
       if(!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4)
       {
           if(!KEYIN1)
            KEYIN = 1;
           if(!KEYIN2 )
            KEYIN = 2;    
           if(!KEYIN3)
            KEYIN = 3;
           if(!KEYIN4)
            KEYIN = 4;
       }while(!KEYIN1 || !KEYIN2 || !KEYIN3 || !KEYIN4);
    }
}
