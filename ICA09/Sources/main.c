/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     8 MHz
// Author:        Marcelo Sampaio
// Details:       ICA09


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
#include "pit.h"
#include "sw_led.h"
#include "clock.h"

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/

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
  //PIT_InitChannel(PIT_CH0,PIT_MT0, PIT_IDIS);
  PIT_SetmsDelay(PIT_CH0, PIT_MT0, 50); //50 ms non blocking event
  SWL_Init();
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    
    //PIT_Sleep(PIT_CH1,20); 20 ms blocking delay
    PIT_Sleep(PIT_CH1, 60); //60 ms Blocking delay
    if(PITTF & PIT_CH0){
      SWL_TOG(SWL_RED);
      PITTF = PIT_CH0;
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
////////////////////////////////////////////////////////////////////
//                  Conclusions:
// Part A:
//  When the Blocking delay is a smaller fraction of the event we 
// are waiting on we arrive late at to clear the flag resulting in a 40ms
// downtime and 60ms uptime which eventually switches to 60 up 40 down
// then switches back because they meet at some point in the code causing
// that switch. or because of the use of SWL_TOG, at some point it might
// enter the loop at a different state causing it to look as though it was
// switched but the daelays may still be running the same
//
//
//
//
//
//
//
//
