/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     8 MHz
// Author:        Marcelo
// Details:       ICA08

// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Constant Defines
/********************************************************************/

/********************************************************************/         \
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
SwState StateCtr = Idle;
SwState StateLeft = Idle;
SwState StateRight = Idle;
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
  Clock_Set20MHZ();
  // PIT_InitChannel(PIT_CH0, PIT_MT1, PIT_IDIS);
  // PITMTLD1 = 0;
  // PITLD0 = 159;
  // PIT_Start();
 // PIT_Set1msDelay(PIT_CH0);
    //PIT_SetmsDelay(PIT_CH1, PIT_MT1, 1500);
    
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  { 

         if(Sw_Process(&StateLeft,SWL_LEFT) == Pressed){
        //Setting 100ms event
         PIT_SetmsDelay(PIT_CH0,PIT_MT1, 100);
        }
        if(StateLeft == Held){
          //Toglling led with 100ms delay
           SWL_TOG(SWL_RED);
           while(!(PITTF & PIT_CH0));
            PITTF = PIT_CH0;
        }
        if(StateLeft == Released){
          PIT_SetmsDelay(PIT_CH0, PIT_MT1,.500);
        }

        if(StateLeft == Idle && PITCE & PIT_CH0){
          SWL_TOG(SWL_RED);
           while(!(PITTF & PIT_CH0));
            PITTF = PIT_CH0;
        }

       
        //Same procedure for other 2  buttons
/////////////////////////////////////////////////////////////////////////////////
        if (Sw_Process(&StateRight, SWL_RIGHT) == Pressed){
          //Setting 475 ms event
          PIT_SetmsDelay(PIT_CH1, PIT_MT1, 500);
        }
         if(StateRight == Held){
          //Toggling led with 475ms delay
          SWL_TOG(SWL_GREEN);
           while(!(PITTF & PIT_CH1));
            PITTF = PIT_CH1;
        }
         if(StateRight == Released){
          PIT_SetmsDelay(PIT_CH1, PIT_MT1,43);
        }

        if(StateRight == Idle && PITCE & PIT_CH1){
          SWL_TOG(SWL_GREEN);
           while(!(PITTF & PIT_CH1));
            PITTF = PIT_CH1;
        }

           
///////////////////////////////////////////////////////////////////////////////////////////
           if(Sw_Process(&StateCtr,SWL_CTR) == Pressed){
        //Setting 480 us event
         PIT_SetmsDelay(PIT_CH2,PIT_MT1, .48);
        }
        if(StateCtr == Held){
          //Toggling led with 480 us delay
           SWL_TOG(SWL_YELLOW);
           while(!(PITTF & PIT_CH2));
            PITTF = PIT_CH2;
        }
         if(StateCtr == Released){
          PIT_SetmsDelay(PIT_CH2, PIT_MT1,12.345);
        }

        if(StateCtr == Idle && PITCE & PIT_CH2){
          SWL_TOG(SWL_YELLOW);
           while(!(PITTF & PIT_CH2));
            PITTF = PIT_CH2;
        }

  }
}