/********************************************************************/
// HC12 Program:  Lab 4 LCD String functions, dynamic output
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Marcelo Sampaio
// Details:                 
// Date:          April 21th, 2023
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Constant Defines
/********************************************************************/
#define Lx_LIMIT 2
#define Rx_LIMIT 18
#define BUFFER_SIZE 40
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"
#include "clock.h"
#include "pit.h"
#include "segs.h"
#include "lcd.h"
#include <stdio.h>

/********************************************************************/
// Library includes
/********************************************************************/
// your includes go here

/********************************************************************/
// Local Prototypes
/********************************************************************/

/*********************************************************************/
// Global Variables
/********************************************************************/
SwState leftState, rightState, midState;

float countIndex = 0.0;
int counter = 0, counterRun = 1;

char txBuffer[BUFFER_SIZE];
char tog[1];
int placeHolder = 0;
int iX, iMaskShift;
unsigned int mask;
unsigned int number = 0;
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
  Segs_Init();
  lcd_Init();

  PIT_InitChannel(PIT_CH0, PIT_MT0, 0);
  //100[ms] event -> 20E6 x 100E-3 = 2,000,000
  //2,000,000 = 40 x 50,000
  PITMTLD0 = 39;
  PITLD0 = 49999;
  PIT_Start();

  lcd_DispControl(1,1);
  (void)sprintf(txBuffer, "DEC: %d", number);
  lcd_StringXY(0,1, txBuffer);

  (void)sprintf(txBuffer, "HEX: %04X", number);
  lcd_StringXY(0,2, txBuffer);

  lcd_StringXY(2,3, "0000000000000000");
  iX = 2;
  iMaskShift = 17 - iX; //When the index is 2, the mask is 15 (2^15)
  Segs_16D(iMaskShift, Segs_LineBottom); //display iMask (0-15)
  lcd_AddrXY(iX,3);

  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  {
    if(Sw_Process(&leftState, SWL_LEFT) == Pressed)
    {
      if(--iX < 2)
      {
        iX = 2;
      }
      iMaskShift = 17 - iX;
      Segs_16D(iMaskShift, Segs_LineBottom);
      lcd_AddrXY(iX, 3);
    }
    if (Sw_Process(&rightState, SWL_RIGHT) == Pressed)
    {
      if(++iX > 17)
      {
        iX = 17;
      }
      iMaskShift = 17 - iX;
      Segs_16D(iMaskShift, Segs_LineBottom);
      lcd_AddrXY(iX, 3);
    }

    if(Sw_Process(&midState, SWL_CTR) == Pressed)
    {
      //Here is where you will have to use the mask shift
      mask = 1 << iMaskShift;
      //At this point you have the mask you need
      
      // You have to do some bit operation with the mask and the actual number.

      number ^= mask;
    
        if(number & mask) lcd_Data('1');
        else   lcd_Data('0');

      // Once you do that, the number can be re-displayed in decimal and Hex.

      (void)sprintf(txBuffer, "DEC: %05u\0", number);
      
      lcd_StringXY(0,1, txBuffer);

      (void)sprintf(txBuffer, "HEX: %04X", number);
      lcd_StringXY(0,2, txBuffer);

      // As for displaying a 1 or 0 in the binary number (line 3), you'll just 
      // have to mask the bit you just changed and write a "1" or "0" acordingly,
      

      // then go back to the previous address as the address gets incremented automatically.

      lcd_AddrXY(iX, 3);


    }
    
    // This part is just for displaying a counter
    // that has nothing to do with what is going on
    // on the LCD
    if(PITTF & PITTF_PTF0_MASK)
    {
      PITTF = PITTF_PTF0_MASK;
      countIndex += 0.1;

      if(counterRun)
      {
        if(countIndex > 9999)
        {
          countIndex = 0;
        }
        (void)sprintf(txBuffer, "Counter: %07.1f", countIndex);
        lcd_StringXY(0,0,txBuffer);
        lcd_AddrXY(iX, 3);
        Segs_16D(counter, Segs_LineTop);
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
