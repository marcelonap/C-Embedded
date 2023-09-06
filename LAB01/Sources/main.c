/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     8 MHz
// Author:        Marcelo Sampaio
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
#include "sw_led.h"
#include "clock.h"
#include "pit.h"
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
  unsigned int count = 0;     //Decimal Counter
  unsigned int hcount = 0xf;  //HexaDecimal Counter
  unsigned int index = 0;     //1 Second interval index
  unsigned int dp_index = 0;  //Decimal Point clearing index
  unsigned int flag = 0;      //Decimal/ Hex control flag
  //Button States
  SwState CTRState = Idle;    
  SwState DOWNState = Idle;
  SwState UPState = Idle;
  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // initializations
  /********************************************************************/
  Clock_Set20MHZ();
  SWL_Init();
  PIT_SetmsDelay(PIT_CH0, PIT_MT0, 100);
  Segs_Init();
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    //PIT timer non blocking event
    if(PITTF & PIT_CH0){
      PITTF = PIT_CH0;
      //Counting every 1 second
      if(++index > 9){
        index = 0;
        hcount =  ++count; 
        //Turning off Decimal Points
        for(; dp_index < 4; dp_index++){
          Segs_Custom(4+dp_index, NO_DP);
        }
        dp_index = 0;
      } 
      //Turning on decimal points every 200ms
      if(index % 2 == 0){
        Segs_Custom(3+(index/2), SEG_DP);
        //dp_index = 0;
      }
    }
   
    //If Down button is pressed, switch to Decimal and turn on only green LED
    if(Sw_Process(&DOWNState, SWL_DOWN) == Pressed){
        SWL_OFF(SWL_ALL);
        SWL_ON(SWL_GREEN);
        flag = 0;
    }
    // If Up button is pressed, switch to HexaDecimal and turn on only yellow LED
    if (Sw_Process(&UPState, SWL_UP) == Pressed)
    {
        SWL_OFF(SWL_ALL);
        SWL_ON(SWL_YELLOW);
        flag = 1;
     }

    if(flag){
      Segs_16H(hcount, Segs_LineTop);
    }else{
      Segs_16D(count, Segs_LineTop);
    }

    // Reseting counter if ctr button is pressed or if it reaches 9999
    if (Sw_Process(&CTRState, SWL_CTR) == Pressed || count == 9999)
    {
      count = 0;
      hcount = 0;
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
