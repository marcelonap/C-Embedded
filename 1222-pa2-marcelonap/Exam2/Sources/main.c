/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Marcelo Napoleao
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
#include <string.h>

#include "sci.h"
#include "pit.h"
#include "sw_led.h"
#include "clock.h"

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/ 
int index = 0;
int pitIndex = 0;
unsigned int counter = 0;
 
unsigned char rxData;
unsigned char rxBuffer[40];
unsigned char txBuffer[40];
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
  SWL_Init();
  //Function i added to my library to set any ms event from the parameter i pass it, sent you it
  // on teams once.
  PIT_SetmsDelay(PIT_CH0, PIT_MT1, 25);

  PIT_Start();
  sci0_Init(115200, 0);
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
      if(sci0_rxByte(&rxData)){

        if(rxData == '\r'){
          switch(rxBuffer[0]){
            case 'y':
            case 'Y':         
              if(rxBuffer[1] =='1') SWL_ON(SWL_YELLOW);
              if(rxBuffer[1] =='0') SWL_OFF(SWL_YELLOW);
              break;
            case 'G':
            case 'g':           
              if(rxBuffer[1] =='1') SWL_ON(SWL_GREEN);
              if(rxBuffer[1] =='0') SWL_OFF(SWL_GREEN); 
              break;
            default:
            break;
          }
          (void)memset(rxBuffer, 0, sizeof(rxBuffer));
          index = 0;

        }else{
          rxBuffer[index++] =rxData;
        }

      }

    if(PITTF & PIT_CH0){
      PITTF = PIT_CH0;
      //using 40 bc 25ms * 40 = 1000 ms = 1s.
      if(++pitIndex > 39){
        (void)sprintf(txBuffer, "%04u\r", ++counter);
        sci0_txStr(txBuffer);
        pitIndex = 0;
      }
      SWL_TOG(SWL_RED);    
    }

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
