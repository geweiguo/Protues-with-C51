#include <reg51.h>
#include <string.h>
#include "delay.h"
#include "LCD1602.h"


void main()
{
    unsigned char str[] = "Hello LCD 1602";
    unsigned char str1[] = "Greg Ge 666";
    unsigned char i;
    LCDInit();
    DelayXms(10);

       //ȷ��DDRAM��ַ
        LCDWriteCmd(0x80);    // ����������ݴ洢����DDRAM����ַ�� ��һ��
        for(i = 0;i < strlen(str);i++)   // DDRAM��ַ��0��ʼ��str���Ƚ�����
        {
            LCDWritedata(str[i]);
            
        }
        
        LCDWriteCmd(0xC0);   // ����������ݴ洢����DDRAM����ַ�� �ڶ���  C���� 8 + 4 = C ������
        for(i= 0 ;i < strlen(str1);i++)   // DDRAM��ַ��40��ʼ��str���Ƚ�����
        {
            LCDWritedata(str1[i]);
          
        }

    while(1)
    {
           LCDWriteCmd(LCD_CUR_MOVE_LEFT); //�������
           DelayXms(800);
    }

}