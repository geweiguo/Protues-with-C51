#include "matrixkey.h"

unsigned char KeyNum = 22;
unsigned char Temp1 = 0; //高4位
unsigned char Temp2 = 0;

void MatrixKey_Scan(void)
{   
   KEYPort = 0xf0;//4行做输出  4列做输入  输出“0”  输入 “1”
   Temp1 = KEYPort;
   if(KEYPort != 0xf0)
   {
        DelayXms(10);
        if(KEYPort != 0xf0)
        {
            Temp1 = KEYPort & 0xf0;     //示例Temp1： 1110 0000 、1101 0000 、1011 0000 、0111 0000
            KEYPort = 0x0f;
            Temp2 = KEYPort & 0x0f;    //示例Temp2： 0000 1110 、0000 1101 、0000 1011 、0000 0111 
        }   
   }

   switch (Temp1 + Temp2)     
   {
      case 0xee: KeyNum = 1;break;
      case 0xed: KeyNum = 2;break;
      case 0xeb: KeyNum = 3;break;
      case 0xe7: KeyNum = 4;break;
      case 0xde: KeyNum = 5;break;
      case 0xdd: KeyNum = 6;break;
      case 0xdb: KeyNum = 7;break;
      case 0xd7: KeyNum = 8;break;
      case 0xbe: KeyNum = 9;break;
      case 0xbd: KeyNum = 0;break;
      case 0xbb: KeyNum = 10;break;
      case 0xb7: KeyNum = 11;break;
      case 0x7e: KeyNum = 12;break;
      case 0x7d: KeyNum = 13;break;
      case 0x7b: KeyNum = 14;break;
      case 0x77: KeyNum = 15;break; 
      default:break;  
   }
}
