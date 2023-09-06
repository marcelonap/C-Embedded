/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     8 MHz
// Author:        This B. You
// Details:       A more detailed explanation of the program is entered here

// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Constant Defines
/********************************************************************/

/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
/********************************************************************/
// Library includes
/********************************************************************/
// your includes go here
#include "stdlib.h"
#include "stdio.h"

#include "segs.h"
#include "sw_led.h"
#include "pit.h"
#include "clock.h"
/********************************************************************/
// Local Prototypes
/********************************************************************/
void NibbleUpdate(Seg16Typedef *num, char addr, char inc_dec);
int NibbleReturn(Seg16Typedef *num, char addr);
int WordReturn(Seg16Typedef *num);
unsigned int ConvertToDecimal(int num);
/********************************************************************/
// Global Variables
/********************************************************************/
Seg16Typedef count;
unsigned int buffer = 0x0;
unsigned int counter = 0;
unsigned int addr = 0;
SwState swLeft, swRight, swUp, swDown = Idle;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // initializations
  /********************************************************************/
  SWL_Init();
  Segs_Init();
  Clock_Set20MHZ();
  count.Word = 0;
  /********************************************************************/
  // main program loop
  /********************************************************************/

  Segs_16D(count.Word, Segs_LineTop);
   Segs_Normal(addr, NibbleReturn(&count, addr), Segs_DP_ON);
  for (;;)
  {

    
    if(Sw_Process(&swUp, SWL_UP) == Pressed){
    
      
      if ((NibbleReturn(&count, addr) < 9))
        NibbleUpdate(&count, addr, 1);
        else NibbleUpdate(&count, addr, -9);
            //(void)sprintf(buffer, "%04", counter);
            Segs_Normal(addr, NibbleReturn(&count, addr), Segs_DP_ON);

      //Segs_16D(counter, Segs_LineTop);
    }

    if (Sw_Process(&swDown, SWL_DOWN) == Pressed)
    {
            
        if ((NibbleReturn(&count, addr) > 0))
        NibbleUpdate(&count, addr, -1);
        else NibbleUpdate(&count, addr, 9);

            //(void)sprintf(buffer, "%04", counter);
            Segs_Normal(addr, NibbleReturn(&count, addr), Segs_DP_ON);
    }

    if(Sw_Process(&swLeft, SWL_LEFT) == Pressed){
       if(addr >0) addr--;
       Segs_Normal(addr+1,NibbleReturn(&count, addr+1), Segs_DP_OFF);
       Segs_Normal(addr, NibbleReturn(&count, addr), Segs_DP_ON);
    }

    if (Sw_Process(&swRight, SWL_RIGHT) == Pressed)
    {
       if (addr <3) addr++;
       Segs_Normal(addr - 1, NibbleReturn(&count, addr - 1), Segs_DP_OFF);
       Segs_Normal(addr, NibbleReturn(&count, addr), Segs_DP_ON);
    }

    //(void)sscanf(buffer, "%d", &counter);

   Segs_16H(ConvertToDecimal(count.Word), Segs_LineBottom);
    // Segs_8H(6,count.Byte.Byte0 );
    // Segs_8H(4,count.Byte.Byte1 );
  PIT_Sleep(PIT_CH0, 50);
  }
}

/********************************************************************/
// Functions
/********************************************************************/
int NibbleReturn(Seg16Typedef *num, char addr){
  switch (addr)
  {
  case 0:
    return num->Nibble.Nibble3 ;
    break;

  case 1:
    return num->Nibble.Nibble2;
    break;

  case 2:
   return num->Nibble.Nibble1;
    break;

  case 3:
    return num->Nibble.Nibble0;
    break;

  default:
    break;
  }
}
void NibbleUpdate(Seg16Typedef *num, char addr, int inc_dec)
{
  switch (addr)
  {
  case 0:
    num->Nibble.Nibble3 += inc_dec;
    break;

  case 1:
    num->Nibble.Nibble2 += inc_dec;
    break;

  case 2:
    num->Nibble.Nibble1 += inc_dec;
    break;

  case 3:
    num->Nibble.Nibble0 += inc_dec;
    break;

  default:
    break;
  }
}
int WordReturn(Seg16Typedef *num){
  return (num->Nibble.Nibble3 * 1000) + 
          (num->Nibble.Nibble2 * 100) +
          (num->Nibble.Nibble1 * 10) +
          (num->Nibble.Nibble0);
}

unsigned int ConvertToDecimal(int num){
  unsigned int result = 0;
  unsigned int val = 0;
  unsigned int i = 0 ;
  for(i = 0; i < 4; i++){
        val = num>>4*i;   //Moving characters left to right
        val &= 0xf;         //Recording the right most character
        result+= val * pow(10,i);
    }
 return result;
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
