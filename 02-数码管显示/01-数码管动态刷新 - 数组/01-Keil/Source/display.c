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
                0xFF,  //Ϩ��
                         };   //������
                       
unsigned char LEDBuf[] = {8,8,8,8,8,8,8,8};   //������ʾ������
unsigned char code PLACE_CODE[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; //������λѡ�ź�


void display()
{   
        unsigned char i;
        //1���Ͷ���
        GPIO_DIG = leddataCA[LEDBuf[i]];
    
        //2����λѡ
        GPIO_PLACE = PLACE_CODE[i];
    
        //3����ʱ1 ms  ��ѭ��<10ms
        delay(1);
        
        //4������
        GPIO_DIG = 0xFF;

        i++;
        if(N == i)
            i = 0;
    
       

}
