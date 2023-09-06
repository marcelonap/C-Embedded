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
unsigned long ten_ms = 12901;

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  // main entry point
  _DISABLE_COP();
  //EnableInterrupts;

  /********************************************************************/
  // initializations
  /********************************************************************/
  //Clock_Set24MHZ();
  //Clock_Set20MHZ();
  SWL_Init();
  
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  { 
   
   unsigned long countOn = ten_ms;
 

    if( SWL_IS_ON(SWL_RED)){
      SWL_OFF(SWL_RED);
    }else{
      SWL_ON(SWL_RED);
    }

     while (countOn--)
      {
        /* code */
      }
  
   
  

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
//Answers:
//Per iteration times:
// For 8MHZ: 100ms/12901 =~ .0077 ms
// For 20MHZ: 40ms/12901 =~ .0031 ms
// For 24MHZ: 33.333ms/12901 =~ .0026ms
//
//
//Second question:
// It is possible. We would set it to 40MHZ in order to 
// fit more instructions in a shorter period of time, in counterpart
// it would also need more voltage to operate, which could 
// make it hot and compromise functionality. So it is a balance
// between executing instructions faster but requiring more voltage
// to do so and making sure your temperature will be under control.