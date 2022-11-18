#include<reg51.h>
#include<stdio.h>
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
                0x77,  //"A"
                0x7C,  //"B"
                0x39,  //"C"
                0x5E,  //"D"
                0x79,  //"E"
                0x71,  //"F"
                0x76,  //"H"
                0x38,  //"L"
                0x37,  //"n"
                0x3E,  //"u"
                0x73,  //"P"
                0x5C,  //"o"
                0x40,  //"-"
                0x00,  //熄灭
                0x00  //自定义
 
                         };  //共阴数码管

                       
unsigned char LEDBuf[] = {8,8,8,8};   //数据显示缓冲区
unsigned char code PLACE_CODE[] = {0xfe,0xfd,0xfb,0xf7}; //共阴，位选信号


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
                    i=0;break;


            default: if(i>4);
            break;
         
         
         }

       

}
