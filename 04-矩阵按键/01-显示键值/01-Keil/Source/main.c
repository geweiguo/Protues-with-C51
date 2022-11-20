/**********************************************
程序功能：矩阵键盘 数码管显示 键值
编写人：  Greg Ge
修订日期：2022-11-19
修订版本：V01
**********************************************/

#include <reg51.h>
#include "matrixkey.h"
#include "display.h"

void Dis_Service();
void MatrixKey_Service();

unsigned char X = 0;
unsigned char Y = 0;
unsigned char KeyNum = 22;

void main()
{
    while(1)
    {
      MatrixKey_Service(); 
      Dis_Service(); 
    }
}

void Dis_Service()
{
    LEDBuf[0] = 22;
    LEDBuf[1] = 22;
    LEDBuf[2] = 22;
    LEDBuf[3] = 22;
    LEDBuf[4] = 22;
    LEDBuf[5] = 22;
    LEDBuf[6] = KeyNum;
    LEDBuf[7] = 22;

    Display();
}

void MatrixKey_Service()
{
   MatrixKey_Scan();
   switch(KEYIN)
   {
      case 0: break;
      case 1: X = 1;break;
      case 2: X = 2;break;  
      case 3: X = 3;break;
      case 4: X = 4;break;
      default:break;
   } 
   switch(KEYOUT)
   {
      case 0: break;
      case 1: Y = 1;break;
      case 2: Y = 2;break;  
      case 3: Y = 3;break;
      case 4: Y = 4;break;
      default:break;
   } 
   if(1 == X && 1 == Y)
     KeyNum = 1;
   if(2 == X && 1 == Y)
     KeyNum = 2;
   if(3 == X && 1 == Y)
     KeyNum = 3;
   if(4 == X && 1 == Y)
     KeyNum = 4;
   if(1 == X && 2 == Y)
     KeyNum = 5;
   if(2 == X && 2 == Y)
     KeyNum = 6;
   if(3 == X && 2 == Y)
     KeyNum = 7;
   if(4 == X && 2 == Y)
     KeyNum = 8;
   if(1 == X && 3 == Y)
     KeyNum = 9;
   if(2 == X && 3 == Y)
     KeyNum = 0;
   if(3 == X && 3 == Y)
     KeyNum = 10;
   if(4 == X && 3 == Y)
     KeyNum = 11;
   if(1 == X && 4 == Y)
     KeyNum = 12;
   if(2 == X && 4 == Y)
     KeyNum = 13;
   if(3 == X && 4 == Y)
     KeyNum = 14;
   if(4 == X && 4 == Y)
     KeyNum = 15;
}