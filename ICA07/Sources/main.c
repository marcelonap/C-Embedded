/////////////////////////////////////////////////////////////////////////////
// 9S12X Program: ICA07 SCI library demo
// Processor:     MC9S12XDP512
// Bus Speed:     8 MHz
// Author:        Marcelo Sampaio
// Details:       ICA07 
// Date:          March-09-2023
// Revision History :
//  e

/////////////////////////////////////////////////////////////////////////////
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
// other system includes or your includes go here
//#include "pll.h"
//#include <stdlib.h>
//#include <stdio.h>
#include "sw_led.h"
#include "clock.h"
#include "sci.h"


/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
SwState StateCtr = Idle;
SwState StateLeft = Idle;
SwState StateRight = Idle;
char myMessage[] = "Hello World\n\r\0";
unsigned char rxData;

/////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Main Entry
/////////////////////////////////////////////////////////////////////////////
void main(void)
{
  // main entry point - these two lines must appear first
  _DISABLE_COP();
  //EnableInterrupts;
  
  /////////////////////////////////////////////////////////////////////////////
  // one-time initializations
  /////////////////////////////////////////////////////////////////////////////
  SWL_Init();
  Clock_Set20MHZ(); 

  //SCI set up
  //19200 baud rate, no INTERRUPT
   (void)sci0_Init(19200, 0);

  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {
   /////////////Part 1///////////////////////////////////////////////////////////////////
    //Check if a character is recevived and if so
    // //store it in rxData
    if(sci0_rxByte(&rxData))
    {
      //send it back to the sci
      sci0_txByte(rxData);
    }

/////////////////Part 2///////////////////////////////////////////////////////////////////////////////////////////// 
      //Checking if state of button is pressed while also processing the state of the button
      //for current iteration of program loop
       if(Sw_Process(&StateLeft,SWL_LEFT) == Pressed){
        //Toggling LED and printing pressed message
          SWL_TOG(SWL_RED);
          sci0_txStr("Left Button Pressed\n\r");
        }
        if (StateLeft == Released) //Checking if button was released
        {
          //Toggling LED and printing released message
          SWL_TOG(SWL_RED);
          sci0_txStr("Left Button Released\n\r");
        }
        //Same procedure for other 2  buttons
/////////////////////////////////////////////////////////////////////////////////
        if (Sw_Process(&StateRight, SWL_RIGHT) == Pressed)
        {
          SWL_TOG(SWL_GREEN);
          sci0_txStr("Right Button Pressed\n\r");
        }
        if (StateRight == Released)
        {
          SWL_TOG(SWL_GREEN);
          sci0_txStr("Right Button Released\n\r");
        }
///////////////////////////////////////////////////////////////////////////////////////////
        if (Sw_Process(&StateCtr, SWL_CTR) == Pressed)
        {
          SWL_TOG(SWL_YELLOW);
          sci0_txStr("Center Button Pressed\n\r");
        }
        if (StateCtr  == Released)
        {
          SWL_TOG(SWL_YELLOW);
          sci0_txStr("Center Button Released\n\r");
  
 
  }                   
 }
}
/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ICA07 Questions:
/////////////////////////////////////////////////////////////////////////////
//Part 1: Baud rate of 38400 works with 8 MHz as (8000000/(16x38400)) =13.02, which means 
// the program rounds it to 13 which is only .02 away meaning there is not a big margin of error
// between our desired baud rate and our real baud rate
// for 115200 with 8MHz, 8000000/(16x115200) = 4.34, which the computer has to round to 4, meaning we 
// are now .34 away from our actual setting value, which indicates a big margin of error, causing the 
// real baud rate produced to be significantly different from 115200 enough to compromise the communication
// between the micro and the console.
//
//
//
//
//
//
