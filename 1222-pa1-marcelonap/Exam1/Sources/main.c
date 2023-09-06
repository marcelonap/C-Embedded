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

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/

/********************************************************************/
// Constants
/********************************************************************/
unsigned int ten_ms = 11430;
unsigned int fifteen_ms = 13330;
unsigned int red_status ;
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
   //Assigning count variables with values that generate 10 and 15 ms
   unsigned int countOn = ten_ms;
   unsigned int countOff = fifteen_ms;
   //Recording the state of the red led
   
   //Recording how many buttons are being pressed currently
   unsigned char btnsPressed = SWL_BTNCOUNT();

    if( SWL_IS_ON(SWL_RED)){
      SWL_OFF(SWL_RED);
    }else{
      SWL_ON(SWL_RED);
    }

   red_status = SWL_IS_ON(SWL_RED);
    //Turning on green led and reverting the duty cycles when any 2  buttons are being pressed
    if(btnsPressed == 2){
      SWL_ON(SWL_GREEN);
      red_status = !red_status;
    }else{
      SWL_OFF(SWL_GREEN);     
    }

    //Setting how long led should stay on and off for
    if(red_status){
      
      while (countOn--)
      {
        /* code */
      }
     } else{
      
      while(countOff--){

      }
     }

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
