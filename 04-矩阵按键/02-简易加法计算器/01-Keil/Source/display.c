#include<reg51.h>
#include "delay.h"
#include "display.h"


unsigned char code leddataCC[]={ 
 
                0x3F,  //"0"  
                0x06,  //"1"  
                0x5B,  //"2"  
                0x4F,  //"3"
                0x66,  //"4"
                0x6D,  //"5"
                0x7D,  //"6"
                0x07,  //"7"
                0x7F,  //"8"
                0x6F,  //"9"
                0x77,  //"A"   10
                0x7C,  //"B"   11
                0x39,  //"C"   12
                0x5E,  //"D"   13
                0x79,  //"E"   14
                0x71,  //"F"   15
                0x76,  //"H"   16
                0x38,  //"L"   17
                0x37,  //"n"   18
                0x3E,  //"u"   19
                0x73,  //"P"   20
                0x5C,  //"o"   21
                0x40,  //"-"   22
                0x00,  //熄灭  23
                0x00  //自定义 24
 
                         };  //共阴数码管

                       
unsigned char LEDBuf[] = {23,23,23,23,23,23,23,0};   //数据显示缓冲区
unsigned char code PLACE_CODE[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; //共阴，位选信号


void Display()
{   
        unsigned char i;
        //1、送断码
 
    
        //2、送位选

    
        //3、延时1 ms  总循环<10ms
 
        
        //4、消隐
         switch(i)
         {
            case 0:
                    GPIO_DIG = leddataCC[LEDBuf[0]];
                    GPIO_PLACE = PLACE_CODE[0];
                    DelayXms(1);
                    GPIO_PLACE = 0xFF;
                    i++;break;
            case 1: 
                    GPIO_DIG = leddataCC[LEDBuf[1]];
                    GPIO_PLACE = PLACE_CODE[1];
                    DelayXms(1);
                    GPIO_PLACE = 0xFF;
                    i++;break;
            case 2: 
                    GPIO_DIG = leddataCC[LEDBuf[2]];
                    GPIO_PLACE = PLACE_CODE[2];
                    DelayXms(1);
                    GPIO_PLACE = 0xFF;
                    i++;break;
            case 3: 
                    GPIO_DIG = leddataCC[LEDBuf[3]];
                    GPIO_PLACE = PLACE_CODE[3];
                    DelayXms(1);
                    GPIO_PLACE = 0xFF;
                    i++;break;
            case 4:
                    GPIO_DIG = leddataCC[LEDBuf[4]];
                    GPIO_PLACE = PLACE_CODE[4];
                    DelayXms(1);
                    GPIO_PLACE = 0xFF;
                    i++;break;
            case 5: 
                    GPIO_DIG = leddataCC[LEDBuf[5]];
                    GPIO_PLACE = PLACE_CODE[5];
                    DelayXms(1);
                    GPIO_PLACE = 0xFF;
                    i++;break;
            case 6: 
                    GPIO_DIG = leddataCC[LEDBuf[6]];
                    GPIO_PLACE = PLACE_CODE[6];
                    DelayXms(1);
                    GPIO_PLACE = 0xFF;
                    i++;break;
            case 7: 
                    GPIO_DIG = leddataCC[LEDBuf[7]];
                    GPIO_PLACE = PLACE_CODE[7];
                    DelayXms(1);
                    GPIO_PLACE = 0xFF;
                    i=0;break;

            default: if(i>N);
            break;
         
         
         }

}
