#ifndef __UART_H__
#define __UART_H__

#include <stdio.h>

#define MAXREC 10
#define MAX_REV_TIME 5

//sfr AUXR =0x8E;

extern unsigned char RecBuf[MAXREC];
extern unsigned char RecCnt;
extern unsigned char Recflag;
extern unsigned int temp_data;
extern unsigned int led_Cnt;
extern unsigned int beep_Cnt;

void UartInit(void);
void SentByte(unsigned char dat);
void SendString(unsigned char *dat);
char putchar(char c);
void Cls(unsigned char* buf);
#endif