#include <reg52.h>
#include "matrixkey.h"
#include "display.h"
#include "delay.h"

unsigned char KeypressFlag = 0;
unsigned char DisNumFlag = 0;
unsigned char Num = 0; 
unsigned int temp = 0;
unsigned int Number1 = 0;
unsigned int Result = 0;

void Distemp_Service();
void DisNumber1_Service();
void DisResult_Service();

void INT0_int()
{
    IT0 = 1;
    EX0 = 1;
    EA  = 1;

}

void ESR_INT0() interrupt 0
{
   DelayXms(10);
   if(0 == INT0)
   {
      KeypressFlag = 1;
   }
  

}


void main()
{  
   unsigned char Addflag = 0;
   INT0_int();
   P1 = 0x0f;

   while(1)
   {    
       if(KeypressFlag == 1)
       {
          KeypressFlag = 0;
          
          switch(MatrixKey_Scan())
           {
              case 0:  if(1 == Addflag) {temp = 0;}
                       else {temp = temp*10 + MatrixKey_Scan(); }DisNumFlag = 22;Addflag  = 1;break;
              case 1:  if(!Addflag) {temp = 1;Addflag  = 1;}
                       else {temp = temp*10 + MatrixKey_Scan(); }DisNumFlag = 22;break;
              case 2:  if(!Addflag) {temp = 2;Addflag  = 1;}
                       else {temp = temp*10 + MatrixKey_Scan(); }DisNumFlag = 22;break;
              case 3:  if(!Addflag) {temp = 3;Addflag  = 1;}
                       else {temp = temp*10 + MatrixKey_Scan(); }DisNumFlag = 22;break;
              case 4:  if(!Addflag) {temp = 4;Addflag  = 1;}
                       else {temp = temp*10 + MatrixKey_Scan(); }DisNumFlag = 22;break;
              case 5:  if(!Addflag) {temp = 5;Addflag  = 1;}
                       else {temp = temp*10 + MatrixKey_Scan(); }DisNumFlag = 22;break;
              case 6:  if(!Addflag) {temp = 6;Addflag  = 1;}
                       else {temp = temp*10 + MatrixKey_Scan(); }DisNumFlag = 22;break;
              case 7:  if(!Addflag) {temp = 7;Addflag  = 1;}
                       else {temp = temp*10 + MatrixKey_Scan(); }DisNumFlag = 22;break;
              case 8:  if(!Addflag) {temp = 8;Addflag  = 1;}
                       else {temp = temp*10 + MatrixKey_Scan(); }DisNumFlag = 22;break;
              case 9:  if(!Addflag) {temp = 9;Addflag  = 1;}
                       else {temp = temp*10 + MatrixKey_Scan(); }DisNumFlag = 22;break;
        
              case 12: Number1 = temp; temp = 0;Addflag  = 0;
                       DisNumFlag = 25;
                       break;
              case 14: Number1 = 0; temp = 0;Addflag  = 0;
                       DisNumFlag = 25;
                       break;
    
              case 15: Result = Number1 + temp; Addflag  = 0;
                       DisNumFlag = 30;
                       break;
        
              default: break;       
            }
            
                             
            if(22 == DisNumFlag) 
                {
                 Distemp_Service(); 
                } 
            if(25 == DisNumFlag) 
                {
                 DisNumber1_Service(); 
                } 
            if(30 == DisNumFlag) 
                {
                 DisResult_Service(); 
                }  
       
       }
                        
       Display(); 
        
    }
}

void Distemp_Service()
{
       LEDBuf[0] = 22;
       LEDBuf[1] = temp/1000000;
       LEDBuf[2] = temp/100000%10;
       LEDBuf[3] = temp/10000%10;
       LEDBuf[4] = temp/1000%10;
       LEDBuf[5] = temp/100%10;
       LEDBuf[6] = temp/10%10;
       LEDBuf[7] = temp%10;

}
void DisNumber1_Service()
{
       LEDBuf[0] = 22;
       LEDBuf[1] = Number1/1000000;
       LEDBuf[2] = Number1/100000%10;
       LEDBuf[3] = Number1/10000%10;
       LEDBuf[4] = Number1/1000%10;
       LEDBuf[5] = Number1/100%10;
       LEDBuf[6] = Number1/10%10;
       LEDBuf[7] = Number1%10;

}
void DisResult_Service()
{
       LEDBuf[0] = 22;
       LEDBuf[1] = Result/1000000;
       LEDBuf[2] = Result/100000%10;
       LEDBuf[3] = Result/10000%10;
       LEDBuf[4] = Result/1000%10;
       LEDBuf[5] = Result/100%10;
       LEDBuf[6] = Result/10%10;
       LEDBuf[7] = Result%10;

}       



