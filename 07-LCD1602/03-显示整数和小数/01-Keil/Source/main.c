/****************************************
�����ܣ���ʾ������С��
*****************************************/
#include <reg51.h>
#include <stdio.h>
#include "delay.h"
#include "LCD1602.h"



void main()
{
    long dat = -12345;
    unsigned char str[11];  //���� ������
    unsigned char floatbuf[10]; //������������ 
    unsigned char floatbuf2[10]; //������������ 
    float num = 3.14159;
    float num2 = 12.5;
    LCDInit();
    DelayXms(20);
//  ��ʾ����   
    IntegerToStr(dat,str);   //��ʾ-12345
    LEDShowStr(0,0,str);

//  ��ʾС��num2
    sprintf(floatbuf2,"%0.1f",num2);   //�����͸�ʽ�������ͷ�ļ� stdio.h
    LEDShowStr(0,1,floatbuf2);

//  ��ʾС��num
    sprintf(floatbuf,"%0.5f",num);   //�����͸�ʽ�������ͷ�ļ� stdio.h
    LEDShowStr(7,1,floatbuf);

    while(1);

}

