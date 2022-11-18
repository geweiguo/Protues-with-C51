#include <reg51.h>
#include "display.h"
#include "Key.h"


void main()
{
    unsigned int NumCut; 
    while(1)
    {  
       Key_Scan();
    
       LEDBuf[0] =  NumCut/1000;
       LEDBuf[1] =  NumCut/100%10;
       LEDBuf[2] =  NumCut/10%10;
       LEDBuf[3] =  NumCut%10;
    
       switch(KeyNum)
        {
            case 0:break;
    
            case 1:NumCut++;if(NumCut>9999) NumCut = 0;break; 
    
            case 2:NumCut--;if(NumCut>9999) NumCut = 9999;break; 
    
            case 3:NumCut = 0;break;
    
            case 4:NumCut = 1982;break;
    
            default:
                    break;
        
        }
        Display();
    }
}