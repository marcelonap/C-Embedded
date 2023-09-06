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
#include <stdio.h>
#include "stdlib.h"
#include "lcd.h"
#include "pit.h"
#include "sci.h"
#include "clock.h"
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned char rxData;
unsigned int index = 0;
unsigned int second = 0;
int counter = 0;
unsigned char txBuffer[40];
unsigned char rxBuffer[40];

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
    Clock_Set20MHZ();
  sci0_Init(115200,0);

  PIT_SetmsDelay(PIT_CH0, PIT_MT0,25);
  lcd_Init();
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
      if(sci0_rxByte(&rxData)){
        if(rxData == '\r'){
            (void)sscanf(rxBuffer, "%d", &counter);
            (void)memset(rxBuffer, 0, sizeof(rxBuffer));
            index = 0;
        }else{
          rxBuffer[index++] = rxData;
        }
      }

      if(PITTF & PIT_CH0){
        PITTF = PIT_CH0;
        if(++second > 39){
          second = 0;
          (void)sprintf(txBuffer, "Counter: %04d", counter++);
          lcd_Clear();
          lcd_String(txBuffer);   
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
