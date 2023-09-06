/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Marcelo Napoleao Sampaio
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
unsigned int WordReturn(Seg16Typedef *num);
/********************************************************************/
// Global Variables
/********************************************************************/
Seg16Typedef count;
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

    //Incrementing digit selected by decimal point
    if(Sw_Process(&swUp, SWL_UP) == Pressed){
      //Wraping it to around 9
      if ((NibbleReturn(&count, addr) < 9))
        NibbleUpdate(&count, addr, 1);
        else NibbleUpdate(&count, addr, -9);  
            Segs_Normal(addr, NibbleReturn(&count, addr), Segs_DP_ON);

      
    }
    //Decrementing digit selected by decimal point
    if (Sw_Process(&swDown, SWL_DOWN) == Pressed)
    {
        //Wrapping it around 9
        if ((NibbleReturn(&count, addr) > 0))
        NibbleUpdate(&count, addr, -1);
        else NibbleUpdate(&count, addr, 9);
            Segs_Normal(addr, NibbleReturn(&count, addr), Segs_DP_ON);
    }
    //Decrementing address where decimal point should be
    if(Sw_Process(&swLeft, SWL_LEFT) == Pressed){
       if(addr >0) addr--;
       //Clearing decimal point from previous location and moving it to new one
       Segs_Normal(addr+1,NibbleReturn(&count, addr+1), Segs_DP_OFF);
       Segs_Normal(addr, NibbleReturn(&count, addr), Segs_DP_ON);
    }
    //Incrementing address where decimal point should be
    if (Sw_Process(&swRight, SWL_RIGHT) == Pressed)
    {
       if (addr <3) addr++;
        //Clearing decimal point from previous location and moving it to new one
       Segs_Normal(addr - 1, NibbleReturn(&count, addr - 1), Segs_DP_OFF);
       Segs_Normal(addr, NibbleReturn(&count, addr), Segs_DP_ON);
    }
  //Displayuing hex representation of number on top row
   Segs_16H(WordReturn(&count), Segs_LineBottom);
   

  PIT_Sleep(PIT_CH0, 50);
  }
}

/********************************************************************/
// Functions
/********************************************************************/
//Function that returns the value of one nibble
//@param: num Seg16Typedef variable
//@param addr address of nibble to return
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
//Function that updates a specific nibble by a given value
//@param num Seg16Typedef variable
//@param addr address of nibble to update
//@param inc_dec number to be added to nibble
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
//Function that returns a decimal representation of a Seg16Tyepdef number
unsigned int WordReturn(Seg16Typedef *num){
  return (num->Nibble.Nibble3 * 1000) + 
          (num->Nibble.Nibble2 * 100) +
          (num->Nibble.Nibble1 * 10) +
          (num->Nibble.Nibble0);
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
