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
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
usigned int count = 0;
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

 //PA0 and PA1 to outputs (DDR register)
  DDRA |= PORTA_PA1_MASK | PORTA_PA0_MASK; 
  //Set Entire port B to output
  DDRB = 0xFF;

  //CONTROL BYTE******************

  //Port B
  PORTB = 0b01011001;
/*          ||||||||_____Addr
            |||||________Bank A
            ||||_________Normal
            |||__________Decode  
            ||___________Decode as HEX
            |____________No Data coming
*/
  PORTB |= (addr &  0x7); //make addres only 3-lsb

  //Port A
  PORTA |= PORTA_PA1_MASK; //Set to Control Mode

  //LATCH
  PORTA &= ~PORTA_PA0_MASK;
  //Add delay for faster than 8MHZ
  PORTA |= PORTA_PA0_MASK;



  //Send DATA BYTE

  //Port B
  //PORTB = 0x4;
  //PORTB |= 0x80; //No decimal point


  //Port A
  PORTA &= ~PORTA_PA1_MASK; //Set to Data Mode

  //LATCH
  PORTA &= ~ PORTA_PA0_MASK;
  //Add delay for faster than 8MHZ
  PORTA |= PORTA_PA0_MASK;

PIT_SetmsDelay(PIT_CH0, PIT_MT1,1000);
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    if(PITTF & PIT_CH0){
      count++;
      PITTF = PIT_CH0;
    }
    PORTB = (unsigned char)(count % 10);
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

