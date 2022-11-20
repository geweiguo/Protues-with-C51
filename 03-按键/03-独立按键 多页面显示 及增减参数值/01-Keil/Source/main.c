/*****************************************
程序功能：按键调整不同窗口参数
编写人：Greg Ge
修订日期：2022-11-18
*****************************************/
#include <reg51.h>
#include "display.h"
#include "Key.h"

unsigned int Param[] = {100,200,300,9999}; //四个窗口对应的参数
unsigned char i = 0;  

void InitDisplay();
void Wnd_Dispaly();
void dis_Service();

void main()
{   
        while(1)
        { 
            dis_Service();
            Wnd_Dispaly();                                     
        }
}

void dis_Service() 
{
    LEDBuf[0] = 20;
    LEDBuf[1] = i+1;
    LEDBuf[2] = 22;
    LEDBuf[3] = 22;
    LEDBuf[4] =  Param[i]/1000;
    LEDBuf[5] =  Param[i]/100%10;
    LEDBuf[6] =  Param[i]/10%10;
    LEDBuf[7] =  Param[i]%10; 
                 
    Display(); 
}

void Wnd_Dispaly()
{
    Key_Scan();

    if(1 == KeyNum)
    {   
          i++;
          if(i == 4 )
          {
              i = 0;
          }                                                       
    } 

    else if(2 == KeyNum || 3 == KeyNum || 4 == KeyNum) 
    {
      switch(KeyNum)
      {
        case 2:Param[i]++;if(Param[i]>9999) Param[i] = 0;break; 
        case 3:Param[i]--;if(Param[i]>9999) Param[i] = 9999;break; 
        case 4:Param[i] = 0;break;
        default: break;
       }     
    }
}