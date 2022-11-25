#include <reg52.h>
#include "matrixkey.h"
#include "display.h"
#include "delay.h"

unsigned char KeypressFlag = 0;
unsigned char DisNumFlag = 0;
unsigned char AddFlag = 0;
unsigned char SubFlag = 0;
unsigned char MulNumFlag = 0;
unsigned char DivNumFlag = 0;
unsigned char Keyflag = 0;
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

   INT0_int();
   P1 = 0x0f;

   while(1)
   {    
       if(KeypressFlag == 1)
       {
          KeypressFlag = 0;
          
          switch(MatrixKey_Scan())
           {
              case 0:  temp = (temp*10 + MatrixKey_Scan());
                       Keyflag  = 1;
                       DisNumFlag = 22;
                       break;
              case 1:  
              case 2:  
              case 3:  
              case 4:  
              case 5:  
              case 6:  
              case 7:  
              case 8:  
              case 9:  if(0 == Keyflag) 
                           {temp = MatrixKey_Scan();Keyflag  = 1;}
                       else if(1 == Keyflag) 
                           {temp = temp*10 + MatrixKey_Scan(); }
                       DisNumFlag = 22;
                       break;
        
              case 10: Number1 = temp;
                       AddFlag = 1;                     
                       temp = 0;Keyflag  = 0;
                       DisNumFlag = 25;  //加法
                       break;
              case 11: Number1 = temp;
                       SubFlag = 1;
                       //Result = Number1 - temp; 
                       temp = 0;Keyflag  = 0;
                       DisNumFlag = 25;  //减法
                       break;
              case 13: Number1 = temp;
                       MulNumFlag = 1;
                       //Result = Number1 * temp; 
                       temp = 0;Keyflag  = 0;
                       DisNumFlag = 25;  //乘法
                       break;
              case 14: Number1 = temp;
                       DivNumFlag = 1;
                       //Result = Number1 / temp; 
                       temp = 0;Keyflag  = 0;
                       DisNumFlag = 25;  //除法
                       break;

              case 12: Number1 = 0; temp = 0;Keyflag  = 0;
                       DisNumFlag = 25; //清零
                       break;
    
              case 15: if(AddFlag == 1)
                          {
                            AddFlag = 0;
                            Result = Number1 + temp; 
                          }
                            
                       if(SubFlag == 1)
                           {
                            SubFlag = 0;
                            Result = Number1 - temp;
                           }
                            
                       if(MulNumFlag == 1)
                            {
                             MulNumFlag = 0;
                             Result = Number1 * temp; 
                            }
                            
                       if(DivNumFlag == 1)
                            {
                             DivNumFlag = 0;
                             Result = Number1 / temp; 
                            }
                                                        
                        Keyflag  = 0;
                        DisNumFlag = 30;
                       break;  //输出计算结果
        
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
       LEDBuf[0] = 23;
       LEDBuf[1] = 23;
       LEDBuf[2] = 23;

        if(temp >= 10000) { LEDBuf[3] = temp/10000%10;}
        else LEDBuf[3] = 23;

        if(temp >= 1000){LEDBuf[4] = temp/1000%10;}
        else LEDBuf[4] = 23;

        if(temp >= 100){ LEDBuf[5] = temp/100%10;}
        else LEDBuf[5] = 23;

        if(temp >= 10){ LEDBuf[6] = temp/10%10;}
        else LEDBuf[6] = 23;


       LEDBuf[7] = temp%10;

}
void DisNumber1_Service()
{
       LEDBuf[0] = 23;
       LEDBuf[1] = 23;
       LEDBuf[2] = 23;
              
       if(Number1 >= 10000)    
            {LEDBuf[3] = Number1/10000%10;}
       else   LEDBuf[3] = 23;
       
       if(Number1 >= 1000) 
            {LEDBuf[4] = Number1/1000%10;}
       else   LEDBuf[4] = 23;

       if(Number1 >= 100) 
            {LEDBuf[5] = Number1/100%10;}
       else   LEDBuf[5] = 23;

       if(Number1 >= 10) 
            {LEDBuf[6] = Number1/10%10;}
       else   LEDBuf[6] = 23;
       LEDBuf[7] = Number1%10;

}
void DisResult_Service()
{
       LEDBuf[0] = 23;
       LEDBuf[1] = 23;
       LEDBuf[2] = 23;
       
       if(Result >= 10000)    
            LEDBuf[3] = Result/10000%10;
       else   LEDBuf[3] = 23;
       
       if(Result >= 1000) 
            LEDBuf[4] = Result/1000%10;
       else   LEDBuf[4] = 23;

       if(Result >= 100) 
            LEDBuf[5] = Result/100%10;
       else   LEDBuf[5] = 23;

       if(Result >= 10) 
            LEDBuf[6] = Result/10%10;
       else   LEDBuf[6] = 23;
       LEDBuf[7] = Result%10;

}       



