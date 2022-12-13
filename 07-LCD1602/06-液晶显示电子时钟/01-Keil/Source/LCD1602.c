#include "LCD1602.h"
#include <string.h>

//unsigned char code str[] = {0x00,0x00,0x00,0x00,0x1f,0x00,0x00,0x00};
/***************************************************************
  函数名称：LCDReadBF
  输入参数：无
  输出参数：无
  函数功能：1602读忙检测
****************************************************************/
#ifndef LCD1602_4PINS
void LCDReadBF()
{
    unsigned char state;
    unsigned char i = 0;
    LCD1602_DB = 0xFF;//IO口置1 做输入
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
    LCD1602_DB |= 0xF0;//高四位IO口置1 低四位保持不变
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    do
    {
        LCD1602_EN = 1;
        state =  LCD1602_DB & 0xF0;//读高四位
        LCD1602_EN = 0;

        LCD1602_EN = 1;
        state |=  (LCD1602_DB & 0x0F) >> 4;//读低四位,数据右移四位为低四位
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
  函数名称：LCDWriteCmd
  输入参数：cmd - 待写命令
  输出参数：无
  函数功能：LCD1602写命令
****************************************************************/
#ifndef LCD1602_4PINS
void LCDWriteCmd(unsigned char cmd)
{   
    LCDReadBF(); //等待忙检测，不忙时操作
    LCD1602_RS = 0;
    LCD1602_RW = 0;
    LCD1602_DB = cmd; 
    LCD1602_EN = 1;
    LCD1602_EN = 0;
}
#else
void LCDWriteCmd(unsigned char cmd)
{   
    LCDReadBF(); //等待忙检测，不忙时操作
    LCD1602_RS = 0;  //LCD1602_RS = 0：命令
    LCD1602_RW = 0;  //写
    LCD1602_DB = cmd; //第一次发的高四位
    DelayXms(5);
    LCD1602_EN = 1;
    LCD1602_EN = 0;

    LCD1602_DB = cmd << 4; //读低四位
    DelayXms(1);
    LCD1602_EN = 1;
    LCD1602_EN = 0;
}
#endif
/***************************************************************
  函数名称：LCDWritedata
  输入参数：dat - 待写入数据
  输出参数：无
  函数功能：LCD1602写数据
****************************************************************/
#ifndef LCD1602_4PINS
void LCDWritedata(unsigned char dat)
{   
    LCDReadBF(); //等待忙检测
    LCD1602_RS = 1;
    LCD1602_RW = 0;
    LCD1602_DB = dat; 
    LCD1602_EN = 1;
    LCD1602_EN = 0;
}
#else
void LCDWritedata(unsigned char dat)
{   
    LCDReadBF(); //等待忙检测
    LCD1602_RS = 1;  //LCD1602_RS = 1：数据
    LCD1602_RW = 0;  //写
    LCD1602_DB = dat;//第一次发的高四位
    DelayXms(1); 
    LCD1602_EN = 1;
    LCD1602_EN = 0;

    LCD1602_DB = dat << 4; //读低四位
    DelayXms(1); 
    LCD1602_EN = 1;
    LCD1602_EN = 0;
}
#endif
/***************************************************************
  函数名称：LCDInit
  输入参数：无
  输出参数：无
  函数功能：LCD1602初始化
****************************************************************/
#ifndef LCD1602_4PINS
void LCDInit()
{
    LCDWriteCmd(LCD_MODE_PIN8);      //显示莫斯设置 两行 5*8点阵
    LCDWriteCmd(LCD_DIS_ON);        //显示开 光标关
    LCDWriteCmd( LCD_CURSOR_RIGHT ); //  光标右移，显示不移动
    LCDWriteCmd( LCD_SCREEN_CLR  );  // 清屏
}
#else
void LCDInit()
{   
    LCDWriteCmd(0x33);
    DelayXms(1);
    LCDWriteCmd(0x32);
    LCDWriteCmd(LCD_MODE_PIN4);      //4位数据口  两行显示  5*8点阵字符
    LCDWriteCmd(LCD_DIS_ON);        //显示开 光标关
    LCDWriteCmd( LCD_CURSOR_RIGHT ); //  光标右移，显示不移动
    LCDWriteCmd( LCD_SCREEN_CLR  );  // 清屏
}
#endif
/***************************************************************
  函数名称：LCDSetPosition   x:0-15  y:0-1
  输入参数：x-列，y-行
  输出参数：无
  函数功能：LCD1602定坐标 用于字符显示
****************************************************************/
void  LCDSetPosition(unsigned char x,unsigned char y)  //x 横向坐标 y 纵向坐标
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
  函数名称：LEDShowStr
  输入参数：x-列，y-行 *str-待显示字符数据
  输出参数：无
  函数功能：显示字符
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
//第一种
/***************************************************************
  函数名称：LCDWriteCGRAM
  输入参数：*str-待显示字符数据
  输出参数：无
  函数功能：显示自定义字符
****************************************************************/
void LCDWriteCGRAM(unsigned char *str)
{
    unsigned char i;
    LCDWriteCmd(0x40); //1、构造自定义字符，CGRAM起始地址
    for(i = 0;i< 8;i++)
    {
       LCDWritedata(str[i]); 
    
    }
    //2.显示字符
    LCDWriteCmd(0x80 | 0x05);
    LCDWritedata(0x00); 
}

//第二种
/***************************************************************
  函数名称：LCDSetChar
  输入参数：x-列，y-行  pos-CGRAM位置 *str-自定义字符数据
  输出参数：无
  函数功能：显示自定义字符
****************************************************************/
void LCDSetChar(unsigned x,unsigned char y,unsigned char pos,unsigned char *str)
{
    unsigned char i;
    //先构造自定义字符 确定位置CGRAM
    for(i = 0; i<8;i++)
    {
        LCDWriteCmd(0x40 + pos*8 +i); 
        LCDWritedata(*(str+i));    
    }
    //第二步 显示
    LCDSetPosition(x,y);
    LCDWritedata(0x00 + pos); 

}
/***************************************************************
  函数名称：IntegerToStr 
  输入参数：dat-整型数，*str-字符数据
  输出参数：len- 字符数组的字符个数 
  函数功能：整型转字符串
****************************************************************/
unsigned char IntegerToStr(long dat,unsigned char *str)
{
   unsigned char i;
   unsigned char len;
   unsigned char buf[11];

   if(dat < 0)
       {
          dat = -dat; //如果是负数，取绝对值
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
