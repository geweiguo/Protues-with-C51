#ifndef __UART_H__
#define __UART_H__

#include <stdio.h>


void UartInit(void);
void SentByte(unsigned char dat);
void SendString(unsigned char *dat);
char putchar(char c);
#endif