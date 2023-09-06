/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     8 MHz
// Author:        Marcelo Napoleao
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
#include "segs.h"
#include "pit.h"
#include "sw_led.h"
#include "clock.h"
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
SwState stateLeft = Idle;
SwState stateRight = Idle;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{  
  unsigned int indexr = 0;        //Index for right button hold
  unsigned int indexl = 0;        //Index for left button hold
  unsigned char current = SEG_A;  //Initializing our segment setting
  unsigned char addr = 0;         //Initializing variable to hold address of our animation
  unsigned int moveCount = 0x0;   //Initializing hex counter of moves
  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // initializations
  /********************************************************************/
SWL_Init();
Clock_Set20MHZ();
Segs_Init();


  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  { 
    //Animating seggs driven by a blocking 100 ms delay
    PIT_Sleep(PIT_CH0,100);
    switch (current)
    {
    case SEG_A:
      current = SEG_B;
      break;
    case SEG_B:
      current = SEG_C;
      break;
    case SEG_C:
      current = SEG_D;
      break;
    case SEG_D:
      current = SEG_E;
      break;
    case SEG_E: 
      current = SEG_F;
      break;
    case SEG_F:
      current = SEG_A;
      break;
    default:
      break;
    }
    //Processing the hold of the button to then move our animation
    // while keeping on the top line and only moving if button was held long enough and with
    // no interruptions

    //Right button
    if(Sw_Process(&stateRight, SWL_RIGHT) == Pressed){
      indexr=1;
    }
    if(stateRight == Released || stateRight == Idle){
      indexr= 0;
    }
    if(stateRight == Held && indexr != 0 ){
      indexr++;
    }

    if(indexr > 9 && addr < 3){
      moveCount++;
      indexr = 0;
      Segs_Custom(addr, NO_DP);
      addr++;
    }
    //Left Button
    if (Sw_Process(&stateLeft, SWL_LEFT) == Pressed)
    {
      indexl = 1;
    }
    if (stateLeft == Released || stateLeft == Idle)
    {
      indexl = 0;
    }
    if (stateLeft == Held && indexl != 0)
    {
      indexl++;
    }

    if (indexl > 9 && addr >0 )
    { 
      moveCount++;
      indexl = 0;
      Segs_Custom(addr, NO_DP);
      addr--;
    }
    //Updating seggs
    Segs_Custom(addr, current | NO_DP);
    Segs_16H(moveCount, Segs_LineBottom);

  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
