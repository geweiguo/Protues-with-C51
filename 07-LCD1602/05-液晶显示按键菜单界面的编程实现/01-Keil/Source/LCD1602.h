/********************************************
程序名称；LCD1602.h
作者：Greg Ge
日期：2022-12-08
********************************************/

#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <reg51.h>
#include "delay.h"

//#define LCD1602_4PINS //如果声明LCD_1602_4PINS就代表采用4位IO并行接口方式，否则为8位IO并行接口方式


void LCDInit();
void LCDWritedata(unsigned char dat);
void LCDWriteCmd(unsigned char cmd);
void LCDWriteCGRAM(unsigned char *str);
void LEDShowStr(unsigned char x,unsigned char y,unsigned char *Str);
void LCDSetChar(unsigned x,unsigned char y,unsigned char pos,unsigned char *str);
void LCDSetPosition(unsigned char x,unsigned char y);
unsigned char IntegerToStr(long dat,unsigned char *longstr);
unsigned char code str[];


//I/O接口的声明
#define LCD1602_DB  P0
sbit LCD1602_RS = P2^6;
sbit LCD1602_RW = P2^5;
sbit LCD1602_EN = P2^7;

//LCD1602指令

// 显示模式设置指令（置功能）
// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   1   DL   N  F   *   *
// DL = 1, 8位数据口；    DL = 0， 4位数据口。
// N  = 1，两行显示；     N  = 0,  单行显示。
// F  = 1, 5*10点阵字符； F  = 0， 5*8点阵字符。

#define   LCD_MODE_PIN8        0x38  // 8位数据口  两行显示  5*8点阵字符
#define   LCD_MODE_PIN4        0x28  // 4位数据口  两行显示  5*8点阵字符

#define   LCD_SCREEN_CLR       0x01  // 清屏
#define   LCD_CURSOR_RST       0x02  // 光标复位

//显示开关控制指令
#define   LCD_DIS_CUR_BLK_ON   0x0F  //  显示开 光标开 光标闪烁
#define   LCD_DIS_CUR_ON       0x0E  //  显示开 光标开 光标不闪烁
#define   LCD_DIS_ON           0x0C  //  显示开 光标关
#define   LCD_DIS_OFF          0x08  //  显示关

//显示模式控制
#define   LCD_CURSOR_RIGHT     0x06  //  光标右移，显示不移动
#define   LCD_CURSOR_LEFT      0x04  //  光标左移，显示不移动
#define   LCD_DIS_MODE_LEFT    0x07  //  操作后，AC自增，画面平移
#define   LCD_DIS_MODE_RIGHT   0x05  //  操作后，AC自减，画面平移

//光标、显示移动指令
#define   LCD_CUR_MOVE_LEFT    0x10  //  光标左移
#define   LCD_CUR_MOVE_RIGHT   0x14  //  光标右移
#define   LCD_DIS_MOVE_LEFT    0x18  //  显示左移
#define   LCD_DIS_MOVE_RIGHT   0x1C  //  显示右移

// CGRAM 地址设置，character generator RAM  (0~3FH)
// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   1   A5  A4  A3  A2  A1  A0

// DDRAM地址设置
// DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 1   A6  A5  A4  A3  A2  A1  A0
// N = 0,单行显示 A6 ~A0 = 00H ~4FH
// N = 1,首行显示 A6 ~A0 = 00H ~27H
//       次行显示 A6 ~A0 = 40H ~67H

// 读BF、AC值（BF：Busy Flag.）
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0  1   BF  A6  A5  A4  A3  A2  A1  A0

// 写数据
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 1  0   A7  A6  A5  A4  A3  A2  A1  A0

// 写命令
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0  0   A7  A6  A5  A4  A3  A2  A1  A0

#endif