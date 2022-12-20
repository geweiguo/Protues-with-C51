#include "LCD1602.h"
#include <string.h>

//unsigned char code str[] = {0x00,0x00,0x00,0x00,0x1f,0x00,0x00,0x00};
/***************************************************************
  �������ƣ�LCDReadBF
  �����������
  �����������
  �������ܣ�1602��æ���
****************************************************************/
#ifndef LCD1602_4PINS
void LCDReadBF()
{
    unsigned char state;
    unsigned char i = 0;
    LCD1602_DB = 0xFF;//IO����1 ������
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    do
    {
        LCD1602_EN = 1;
        state =  LCD1602_DB;
        LCD1602_EN = 0;
        i++;
        if(i>50)
            break;
    }
    while(state & 0x80);
    DelayXms(1);
}
#else 
void LCDReadBF()
{
    unsigned char state;
    unsigned char i = 0;
    LCD1602_DB |= 0xF0;//����λIO����1 ����λ���ֲ���
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    do
    {
        LCD1602_EN = 1;
        state =  LCD1602_DB & 0xF0;//������λ
        LCD1602_EN = 0;

        LCD1602_EN = 1;
        state |=  (LCD1602_DB & 0x0F) >> 4;//������λ,����������λΪ����λ
        LCD1602_EN = 0;
        i++;
        if(i>50)
            break;
    }
    while(state & 0x80);
    DelayXms(1);
}
#endif
/***************************************************************
  �������ƣ�LCDWriteCmd
  ���������cmd - ��д����
  �����������
  �������ܣ�LCD1602д����
****************************************************************/
#ifndef LCD1602_4PINS
void LCDWriteCmd(unsigned char cmd)
{   
    LCDReadBF(); //�ȴ�æ��⣬��æʱ����
    LCD1602_RS = 0;
    LCD1602_RW = 0;
    LCD1602_DB = cmd; 
    LCD1602_EN = 1;
    LCD1602_EN = 0;
}
#else
void LCDWriteCmd(unsigned char cmd)
{   
    LCDReadBF(); //�ȴ�æ��⣬��æʱ����
    LCD1602_RS = 0;  //LCD1602_RS = 0������
    LCD1602_RW = 0;  //д
    LCD1602_DB = cmd; //��һ�η��ĸ���λ
    DelayXms(5);
    LCD1602_EN = 1;
    LCD1602_EN = 0;

    LCD1602_DB = cmd << 4; //������λ
    DelayXms(1);
    LCD1602_EN = 1;
    LCD1602_EN = 0;
}
#endif
/***************************************************************
  �������ƣ�LCDWritedata
  ���������dat - ��д������
  �����������
  �������ܣ�LCD1602д����
****************************************************************/
#ifndef LCD1602_4PINS
void LCDWritedata(unsigned char dat)
{   
    LCDReadBF(); //�ȴ�æ���
    LCD1602_RS = 1;
    LCD1602_RW = 0;
    LCD1602_DB = dat; 
    LCD1602_EN = 1;
    LCD1602_EN = 0;
}
#else
void LCDWritedata(unsigned char dat)
{   
    LCDReadBF(); //�ȴ�æ���
    LCD1602_RS = 1;  //LCD1602_RS = 1������
    LCD1602_RW = 0;  //д
    LCD1602_DB = dat;//��һ�η��ĸ���λ
    DelayXms(1); 
    LCD1602_EN = 1;
    LCD1602_EN = 0;

    LCD1602_DB = dat << 4; //������λ
    DelayXms(1); 
    LCD1602_EN = 1;
    LCD1602_EN = 0;
}
#endif
/***************************************************************
  �������ƣ�LCDInit
  �����������
  �����������
  �������ܣ�LCD1602��ʼ��
****************************************************************/
#ifndef LCD1602_4PINS
void LCDInit()
{
    LCDWriteCmd(LCD_MODE_PIN8);      //��ʾĪ˹���� ���� 5*8����
    LCDWriteCmd(LCD_DIS_ON);        //��ʾ�� ����
    LCDWriteCmd( LCD_CURSOR_RIGHT ); //  ������ƣ���ʾ���ƶ�
    LCDWriteCmd( LCD_SCREEN_CLR  );  // ����
}
#else
void LCDInit()
{   
    LCDWriteCmd(0x33);
    DelayXms(1);
    LCDWriteCmd(0x32);
    LCDWriteCmd(LCD_MODE_PIN4);      //4λ���ݿ�  ������ʾ  5*8�����ַ�
    LCDWriteCmd(LCD_DIS_ON);        //��ʾ�� ����
    LCDWriteCmd( LCD_CURSOR_RIGHT ); //  ������ƣ���ʾ���ƶ�
    LCDWriteCmd( LCD_SCREEN_CLR  );  // ����
}
#endif
/***************************************************************
  �������ƣ�LCDSetPosition   x:0-15  y:0-1
  ���������x-�У�y-��
  �����������
  �������ܣ�LCD1602������ �����ַ���ʾ
****************************************************************/
void  LCDSetPosition(unsigned char x,unsigned char y)  //x �������� y ��������
{         
    if(0 == y)
    {
        LCDWriteCmd(0x80 | x);
    }
    else
    {
        LCDWriteCmd(0x80 | (0x40 + x));
    }
}
/***************************************************************
  �������ƣ�LEDShowStr
  ���������x-�У�y-�� *str-����ʾ�ַ�����
  �����������
  �������ܣ���ʾ�ַ�
****************************************************************/
void LEDShowStr(unsigned char x,unsigned char y,unsigned char *Str)
{
    unsigned char i;
    unsigned char strerr[] = "err:LEDShowStr()";
    
    if((0 == y || 1 == y)&&(x>=0 && x<=15))
    { 
        LCDSetPosition(x,y);
        while(*Str != '\0')
        {
            LCDWritedata(*Str++);            
        }   
    }
 
    else
    {
      LCDWriteCmd(0x80);
     
      for(i = 0;i<strlen(strerr);i++)
      {
        LCDWritedata(strerr[i]);
        DelayXms(100);
      }        
    }    
}
//��һ��
/***************************************************************
  �������ƣ�LCDWriteCGRAM
  ���������*str-����ʾ�ַ�����
  �����������
  �������ܣ���ʾ�Զ����ַ�
****************************************************************/
void LCDWriteCGRAM(unsigned char *str)
{
    unsigned char i;
    LCDWriteCmd(0x40); //1�������Զ����ַ���CGRAM��ʼ��ַ
    for(i = 0;i< 8;i++)
    {
       LCDWritedata(str[i]); 
    
    }
    //2.��ʾ�ַ�
    LCDWriteCmd(0x80 | 0x05);
    LCDWritedata(0x00); 
}

//�ڶ���
/***************************************************************
  �������ƣ�LCDSetChar
  ���������x-�У�y-��  pos-CGRAMλ�� *str-�Զ����ַ�����
  �����������
  �������ܣ���ʾ�Զ����ַ�
****************************************************************/
void LCDSetChar(unsigned x,unsigned char y,unsigned char pos,unsigned char *str)
{
    unsigned char i;
    //�ȹ����Զ����ַ� ȷ��λ��CGRAM
    for(i = 0; i<8;i++)
    {
        LCDWriteCmd(0x40 + pos*8 +i); 
        LCDWritedata(*(str+i));    
    }
    //�ڶ��� ��ʾ
    LCDSetPosition(x,y);
    LCDWritedata(0x00 + pos); 

}
/***************************************************************
  �������ƣ�IntegerToStr 
  ���������dat-��������*str-�ַ�����
  ���������len- �ַ�������ַ����� 
  �������ܣ�����ת�ַ���
****************************************************************/
unsigned char IntegerToStr(long dat,unsigned char *str)
{
   unsigned char i;
   unsigned char len;
   unsigned char buf[11];

   if(dat < 0)
       {
          dat = -dat; //����Ǹ�����ȡ����ֵ
          *str++ = '-';
          len++;
       }
    
   do
       {
          buf[i++] = dat%10 + '0';     
          dat /= 10;
    
       } while(dat > 0); 
   
   len += i;

   while(i-- > 0)
       {        
         *str++ = buf[i];
       } 

   *str = '\0';
   return len;
}
