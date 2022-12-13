/****************************************
程序功能：四位IO口
*****************************************/
#include <reg51.h>
#include <stdio.h>
#include "delay.h"
#include "LCD1602.h"
#include "Key.h"

void StartMenu();
void SubmeunOne();
void SubmeunTwo();
void SubmeunThree();
void SubmeunFour();
void SubmeunAlam();
void KeyService();
void LCDShowService();

int TEMPbuf[] = {125,126,127,128,223,224,225,226,334,335,336,337,421,423,424,425};
void ShowTempData(unsigned char x,unsigned char y,int *buf,unsigned char num);
unsigned char menu;

void main()
{
    LCDInit();
    DelayXms(10);
    StartMenu();
    DelayXms(2000);
    LCDWriteCmd(LCD_SCREEN_CLR);
    while(1)
    {  
       KeyService();
       LCDShowService();
    }
}
void LCDShowService()
{
    switch(menu)
    {
        case 0: SubmeunOne();break;
        case 1: SubmeunTwo();break;
        case 2: SubmeunThree();break;
        case 3: SubmeunFour();break;
        case 4: SubmeunAlam();break;
        default:break;
    }


}
void KeyService()
{
   Key_Scan();
   switch(KeyNum)
    {
      case 1:menu++; if(menu == 4) menu = 0;break;
      case 2:menu--; if(menu > 4) menu = 3;break;
      case 3:menu = 0; break;  
      case 4:menu = 4; LCDWriteCmd(LCD_SCREEN_CLR);break;     
      default:break;
    }

}

void StartMenu()
{
    LEDShowStr(1,0,"The DAS of TEMP");
    LEDShowStr(6,1,"v1.0");
}

void SubmeunOne()
{    
    LEDShowStr(0,0,"CH0:");
    ShowTempData(4,0,TEMPbuf,0);

    LEDShowStr(8,0,"CH1:");
    ShowTempData(12,0,TEMPbuf,1);

    LEDShowStr(0,1,"CH2:");
    ShowTempData(4,1,TEMPbuf,2);

    LEDShowStr(8,1,"CH3:");
    ShowTempData(12,1,TEMPbuf,3);
}

void ShowTempData(unsigned char x,unsigned char y,int *buf,unsigned char num)
{
    LCDSetPosition(x,y);
    LCDWritedata(*(buf+num)/100 + '0');
    LCDWritedata(*(buf+num)/10%10 + '0');
    LCDWritedata('.' );
    LCDWritedata(*(buf+num)%10 + '0');
}

void SubmeunTwo()
{    
    LEDShowStr(0,0,"CH4:");
    ShowTempData(4,0,TEMPbuf,4);

    LEDShowStr(8,0,"CH5:");
    ShowTempData(12,0,TEMPbuf,5);

    LEDShowStr(0,1,"CH6:");
    ShowTempData(4,1,TEMPbuf,6);

    LEDShowStr(8,1,"CH7:");
    ShowTempData(12,1,TEMPbuf,7);
}

void SubmeunThree()
{    
    LEDShowStr(0,0,"CH8:");
    ShowTempData(4,0,TEMPbuf,8);

    LEDShowStr(8,0,"CH9:");
    ShowTempData(12,0,TEMPbuf,9);

    LEDShowStr(0,1,"CHA:");
    ShowTempData(4,1,TEMPbuf,10);

    LEDShowStr(8,1,"CHB:");
    ShowTempData(12,1,TEMPbuf,11);
}

void SubmeunFour()
{    
    LEDShowStr(0,0,"CHC:");
    ShowTempData(4,0,TEMPbuf,12);

    LEDShowStr(8,0,"CHD:");
    ShowTempData(12,0,TEMPbuf,13);

    LEDShowStr(0,1,"CHE:");
    ShowTempData(4,1,TEMPbuf,14);

    LEDShowStr(8,1,"CHF:");
    ShowTempData(12,1,TEMPbuf,15);
}

void SubmeunAlam()
{   

    LEDShowStr(3,0,"ALARM MENU");

}