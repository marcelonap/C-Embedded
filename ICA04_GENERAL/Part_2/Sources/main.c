/********************************************************************/
// HC12 Program:  Part 2 ICA04
// Processor:     MC9S12XDP512
// Bus Speed:     8 MHz
// Author:        Marcelo Sampaio
// Details:       toggle red led every iteration of for(;;)
                  
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Constant Defines
/********************************************************************/

/********************************************************************/
#include <hidef.h>      /* com  mon defines and macros */
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
    unsigned long counter = 500000;
   SWL_TOG(SWL_RED);

   while (counter--)
    {
      /* code */
    }
    
  }                   
}
/********************************************************************/
//part 2: The LED is now toggling on and off with intervals of about 5 seconds
//
//An int cannot store big enough numbers and would cause loss of data when trying to use 500 000
//causing the led to toggle on and off very fast, the program takes longer to go through all the bits
//in a long variable since it has more bits than an int variable and therefore produces a bigger interval
//between each toggle.

  

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
 