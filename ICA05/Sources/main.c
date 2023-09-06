 /********************************************************************/
// HC12 Program:  ICA05 - Tier 3
// Processor:     MC9S12XDP512
// Bus Speed:     8 MHz
// Author:        Marcelo Napoleao
// Details:       A program that allows the user to turn on 2 leds at a time
//                then turn them all off using the top and bottom buttons.
                  
// Date:          02/08/2023
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

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/

/********************************************************************/
// Constants
/********************************************************************/
const int LED_LIMIT = 2; //Maximum number of leds to be on at once

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
  SWL_Init();
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    //Checks if the number of LED's has reached its limit or if the program
    //should still turn on an led at the push of the button
   if(SWL_ONCOUNT()<LED_LIMIT){
      
      //turns on red led when left button is pushed
      if(SWL_Pushed(SWL_LEFT)){
        SWL_ON(SWL_RED);
      }
      //turns on yellow led when centre button is pushed 
      if(SWL_Pushed(SWL_CTR)){
        SWL_ON(SWL_YELLOW);
      }
      //turns on green led when right button is pushed
      if(SWL_Pushed(SWL_RIGHT)){
        SWL_ON(SWL_GREEN);
      }
    }
    //if up button is pushed or down button is pushed, turn off all leds.
    if(SWL_Pushed(SWL_UP) || SWL_Pushed(SWL_DOWN)){
      SWL_OFF(SWL_ALL);
    }
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
