#include "AddCal.h"
#include "matrixkey.h"

int Number1 = 0;
int Result = 0;
unsigned char Addflag = 0;
unsigned char Resflag = 0;
int temp = 0;

void AddCal ()
{

    MatrixKey_Scan();

    switch(KeyNum)
    {
      case 0:  if(!Addflag) {temp = 0;Addflag ++;}
               else if(Addflag) {temp = temp*10 + KeyNum;} ;break;
      case 1:  if(!Addflag) {temp = 1;Addflag ++;}
               else if(Addflag) {temp = temp*10 + KeyNum;} ;break;
      case 2:  if(!Addflag) {temp = 2;Addflag ++;}
               else if(Addflag) {temp = temp*10 + KeyNum;} ;break;
      case 3:  if(!Addflag) {temp = 3;Addflag ++;}
               else if(Addflag) {temp = temp*10 + KeyNum;} ;break;
      case 4:  if(!Addflag) {temp = 4;Addflag ++;}
               else if(Addflag) {temp = temp*10 + KeyNum;} ;break;
      case 5:  if(!Addflag) {temp = 5;Addflag ++;}
               else if(Addflag) {temp = temp*10 + KeyNum;} ;break;
      case 6:  if(!Addflag) {temp = 6;Addflag ++;}
               else if(Addflag) {temp = temp*10 + KeyNum;} ;break;
      case 7:  if(!Addflag) {temp = 7;Addflag ++;}
               else if(Addflag) {temp = temp*10 + KeyNum;} ;break;
      case 8:  if(!Addflag) {temp = 8;Addflag ++;}
               else if(Addflag) {temp = temp*10 + KeyNum;} ;break;
      case 9:  if(!Addflag) {temp = 9;Addflag ++;}
               else if(Addflag) {temp = temp*10 + KeyNum;} ;break;

      case 10: Number1 = temp; temp = 0;Addflag  = 0;break;
      case 15: Result = Number1 + temp ;Addflag  = 0;break;

      default: break;
    
    }
    
}