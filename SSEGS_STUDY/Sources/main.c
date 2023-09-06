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
#include "pit.h"
#include "segs.h"
#include "clock.h"
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned char count = 0;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  unsigned char interval = 0;
  unsigned int add = 3;
  unsigned char ten = 0;
  unsigned char hund= 0;
  unsigned char thou = 0;
  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // initializations
  /********************************************************************/
  Clock_Set20MHZ();
  
  Segs_Init();
  PIT_SetmsDelay(PIT_CH0, PIT_MT1, 100);

  Segs_16H(0x1234,1);
 
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    if (PITTF & PIT_CH0)
    {
      if(++interval > 9){
      count++;
      interval = 0;
      }
      PITTF = PIT_CH0;
    }
    if(count > 9){
      
      count=0;
      ten++;
      if (ten > 9)
      {
      ten = 0;
      hund++;
      if (hund > 9)
      {
        hund = 0;
        thou++;
        if(thou > 9){
          thou = 0;
          ten = 0;
          hund = 0;
          count = 0;
        }
        Segs_Normal(add - 3, thou, Segs_DP_OFF);
      }

      Segs_Normal(add - 2, hund, Segs_DP_OFF);
      }
      Segs_Normal(add - 1, ten, Segs_DP_OFF);
    }

   
   
    Segs_Normal(add,count, Segs_DP_OFF);
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
