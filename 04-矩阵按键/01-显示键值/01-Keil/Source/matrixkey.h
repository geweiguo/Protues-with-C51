#ifndef __MATRIXKEY_H__
#define __MATRIXKEY_H__

sbit KEYIN1 = P1^0;
sbit KEYIN2 = P1^1;
sbit KEYIN3 = P1^2;
sbit KEYIN4 = P1^3;
sbit KEYOUT1 = P1^4;
sbit KEYOUT2 = P1^5;
sbit KEYOUT3 = P1^6;
sbit KEYOUT4 = P1^7;

void MatrixKey_Scan(void);

extern unsigned char KEYIN;
extern unsigned char KEYOUT;

#endif

