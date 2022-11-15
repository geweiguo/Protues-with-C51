#include<reg51.h>
#include<stdio.h>
#include "delay.h"
#include "display.h"


unsigned char code leddataCA[]={ 
 
                0xC0,  //"0"
                0xF9,  //"1"
                0xA4,  //"2"
                0xB0,  //"3"
                0x99,  //"4"
                0x92,  //"5"
                0x82,  //"6"
                0xF8,  //"7"
                0x80,  //"8"
                0x90,  //"9"
                0x88,  //"A"
                0x83,  //"B"
                0xC6,  //"C"
                0xA1,  //"D"
                0x86,  //"E"
                0x8E,  //"F"
                0x89,  //"H"
                0xC7,  //"L"
                0xC8,  //"n"
                0xC1,  //"u"
                0x8C,  //"P"
                0xA3,  //"o"
                0xBF,  //"-"
                0xFF,  //熄灭
                         };   //共阳极
                       
unsigned char LEDBuf[] = {8,8,8,8,8,8,8,8};   //数据显示缓冲区
unsigned char code PLACE_CODE[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; //共阳，位选信号


void display()
{   
        unsigned char i;
        //1、送断码
 
    
        //2、送位选

    
        //3、延时1 ms  总循环<10ms
 
        
        //4、消隐
         switch(i)
         {
            case 0:
                    GPIO_DIG = leddataCA[LEDBuf[0]];
                    GPIO_PLACE = PLACE_CODE[0];
                    delay(1);
                    GPIO_PLACE = 0x00;
                    i++;break;
            case 1: 
                    GPIO_DIG = leddataCA[LEDBuf[1]];
                    GPIO_PLACE = PLACE_CODE[1];
                    delay(1);
                    GPIO_PLACE = 0x00;
                    i++;break;
            case 2: 
                    GPIO_DIG = leddataCA[LEDBuf[2]];
                    GPIO_PLACE = PLACE_CODE[2];
                    delay(1);
                    GPIO_PLACE = 0x00;
                    i++;break;
            case 3: 
                    GPIO_DIG = leddataCA[LEDBuf[3]];
                    GPIO_PLACE = PLACE_CODE[3];
                    delay(1);
                    GPIO_PLACE = 0x00;
                    i++;break;
            case 4: 
                    GPIO_DIG = leddataCA[LEDBuf[4]];
                    GPIO_PLACE = PLACE_CODE[4];
                    delay(1);
                    GPIO_PLACE = 0x00;
                    i++;break;
            case 5: 
                    GPIO_DIG = leddataCA[LEDBuf[5]];
                    GPIO_PLACE = PLACE_CODE[5];
                    delay(1);
                    GPIO_PLACE = 0x00;
                    i++;break;
            case 6: 
                    GPIO_DIG = leddataCA[LEDBuf[6]];
                    GPIO_PLACE = PLACE_CODE[6];
                    delay(1);
                    GPIO_PLACE = 0x00;
                    i++;break;
            case 7: 
                    GPIO_DIG = leddataCA[LEDBuf[7]];
                    GPIO_PLACE = PLACE_CODE[7];
                    delay(1);
                    GPIO_PLACE = 0x00;
                    i=0;break;

            default: if(i>8);
            break;
         
         
         }

       

}
