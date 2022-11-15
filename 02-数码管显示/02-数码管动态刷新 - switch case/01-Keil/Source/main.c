#include<reg51.h>
#include "delay.h"
#include "display.h"

unsigned char wnd;
unsigned int parm1 = 2088;
unsigned int parm2 = 1999;
unsigned int parm3 = 1982;
unsigned int parm4 = 822; 
 
void dis_Service()
{ 
  unsigned int i;  
  switch(wnd)
   {
    case 0:
            LEDBuf[0] = 1;
            LEDBuf[1] = 22;
            LEDBuf[2] = 23;
            LEDBuf[3] = 23;
            LEDBuf[4] = parm1/1000;
            LEDBuf[5] = parm1/100%10;
            LEDBuf[6] = parm1/10%10;
            LEDBuf[7] = parm1%10;
            for(i = 0;i<2000;i++)
            {
                display();
            }
            wnd++;
            break;

      case 1:
            LEDBuf[0] = 2;
            LEDBuf[1] = 22;
            LEDBuf[2] = 23;
            LEDBuf[3] = 23;
            LEDBuf[4] = parm2/1000;
            LEDBuf[5] = parm2/100%10;
            LEDBuf[6] = parm2/10%10;
            LEDBuf[7] = parm2%10;
            for(i = 0;i<2000;i++)
            {
                display();
            }
            wnd++;
            break;
            
      case 2:
            LEDBuf[0] = 3;
            LEDBuf[1] = 22;
            LEDBuf[2] = 23;
            LEDBuf[3] = 23;
            LEDBuf[4] = parm3/1000;
            LEDBuf[5] = parm3/100%10;
            LEDBuf[6] = parm3/10%10;
            LEDBuf[7] = parm3%10;
            for(i = 0;i<2000;i++)
            {
                display();
            }
            wnd++;
            break;
                                
      case 3:
            LEDBuf[0] = 4;
            LEDBuf[1] = 22;
            LEDBuf[2] = 23;
            LEDBuf[3] = 23;
            LEDBuf[4] = parm4/1000;
            LEDBuf[5] = parm4/100%10;
            LEDBuf[6] = parm4/10%10;
            LEDBuf[7] = parm4%10;
            for(i = 0;i<2000;i++)
            {
                display();
            }
            wnd=0;
            break;
        default: break;
            
      }
}

void main()
{
    unsigned int i;
    for(i=0;i<2000;i++)
    {
        display();
    }

    while(1)
    {
        dis_Service();
    
    }
}


