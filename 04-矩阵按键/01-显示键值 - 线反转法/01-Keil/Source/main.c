/**********************************************
程序功能：矩阵键盘 数码管显示 键值 (线反转法)
编写人：  Greg Ge
修订日期：2022-11-19
修订版本：V01
**********************************************/
#include <reg52.h>
#include "matrixkey.h"
#include "display.h"


void main()
{
    while(1)
    {
//        MatrixKey_Scan();
//
//        LEDBuf[0] = 22;
//        LEDBuf[1] = 22;
//        LEDBuf[2] = 22;
//        LEDBuf[3] = 22;
//        LEDBuf[4] = 22;
//        LEDBuf[5] = 22;
//        LEDBuf[6] = 22;
//        LEDBuf[7] = KeyNum;

        Display();
    }
}

