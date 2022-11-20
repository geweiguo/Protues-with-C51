#include <reg51.h>
#include "matrixkey.h"
#include "display.h"

void Distemp_Service();
void DisNumber1_Service();
void DisResult_Service();

unsigned char temp = 0;
unsigned char Number1 = 0;
unsigned char Result = 0;

void main()
{   
    unsigned char Addflag = 0;

    while(1)
    {
        MatrixKey_Scan();
        
        switch(KeyNum)
        {
          case 0:  if(!Addflag) {temp = 0;Addflag  = 1;}
                   else {temp = temp*10 + KeyNum; KeyNum = 22;}break;
          case 1:  if(!Addflag) {temp = 1;Addflag  = 1;}
                   else {temp = temp*10 + KeyNum; KeyNum = 22;}break;
          case 2:  if(!Addflag) {temp = 2;Addflag  = 1;}
                   else {temp = temp*10 + KeyNum; KeyNum = 22;}break;
          case 3:  if(!Addflag) {temp = 3;Addflag  = 1;}
                   else {temp = temp*10 + KeyNum; KeyNum = 22;}break;
          case 4:  if(!Addflag) {temp = 4;Addflag  = 1;}
                   else {temp = temp*10 + KeyNum; KeyNum = 22;}break;
          case 5:  if(!Addflag) {temp = 5;Addflag  = 1;}
                   else {temp = temp*10 + KeyNum; KeyNum = 22;}break;
          case 6:  if(!Addflag) {temp = 6;Addflag  = 1;}
                   else {temp = temp*10 + KeyNum; KeyNum = 22;}break;
          case 7:  if(!Addflag) {temp = 7;Addflag  = 1;}
                   else {temp = temp*10 + KeyNum; KeyNum = 22;}break;
          case 8:  if(!Addflag) {temp = 8;Addflag  = 1;}
                   else {temp = temp*10 + KeyNum; KeyNum = 22;}break;
          case 9:  if(!Addflag) {temp = 9;Addflag  = 1;}
                   else {temp = temp*10 + KeyNum; KeyNum = 22;}break;
    
          case 10: Number1 = temp; temp = 0;Addflag  = 0;KeyNum = 25;break;
          case 15: Result = Number1 + temp ;Addflag  = 0;KeyNum = 30;break;
    
          default: break;       
        }
        if(22 == KeyNum) 
            {
                 Distemp_Service(); 
            } 
        if(25 == KeyNum) 
            {
             DisNumber1_Service(); 
        } 
        if(30 == KeyNum) 
        {
             DisResult_Service(); 
        }     
    }
}

void DisResult_Service()
{
        LEDBuf[0] = 23;
        LEDBuf[1] = 23;
        LEDBuf[2] = 23;
        LEDBuf[3] = 23;
        LEDBuf[4] = Result/1000;
        LEDBuf[5] = Result/100%10;
        LEDBuf[6] = Result/10%10;
        LEDBuf[7] = Result%10;

        Display(); 
}

void DisNumber1_Service()
{
        LEDBuf[0] = 23;
        LEDBuf[1] = 23;
        LEDBuf[2] = 23;
        LEDBuf[3] = 23;
        LEDBuf[4] = Number1/1000;
        LEDBuf[5] = Number1/100%10;
        LEDBuf[6] = Number1/10%10;
        LEDBuf[7] = Number1%10;

        Display(); 
}

void Distemp_Service()
{
        LEDBuf[0] = 23;
        LEDBuf[1] = 23;
        LEDBuf[2] = 23;
        LEDBuf[3] = 23;
        LEDBuf[4] = temp/1000;
        LEDBuf[5] = temp/100%10;
        LEDBuf[6] = temp/10%10;
        LEDBuf[7] = temp%10;

        Display(); 
}