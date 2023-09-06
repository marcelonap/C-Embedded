/********************************************************************/
// HC12 Program:  Lab3
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Marcelo Napoleao
// Details:       Lab3     
// Date:          Apr 18, 2023
// Revision History :
// 

/********************************************************************/
// Constant Defines
/********************************************************************/

/********************************************************************/
// your includes go here
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"
#include "clock.h"
#include "pit.h"
#include "segs.h"
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h> //For random generetion

/********************************************************************/
// Library includes
/********************************************************************/


/********************************************************************/
// Local Prototypes
/********************************************************************/
// void SetAddr(char);
// unsigned char GetAddr();
/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int counter = 0;


SwState leftState, rightState, upState, downState, ctrState;
int iX = 0, iY = 0;
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
  EnableInterrupts;
  /********************************************************************/
  // initializations
  /********************************************************************/
  Clock_Set20MHZ();
  SWL_Init();
  Segs_Init();
  lcd_Init();

 

  lcd_DispControl(1,0);

  
  lcd_AddrXY(iX, iY);
  Segs_16D(counter,Segs_LineTop);  
  
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  { 
    SWL_OFF(SWL_RED);
    Segs_16D(counter, Segs_LineTop);  

    
    if (Sw_Process(&ctrState, SWL_CTR) == Pressed){
        lcd_Data(rand()%26 + 'A');
        lcd_AddrXY(iX,iY);
        if(++counter> 14){
          lcd_Home();
          lcd_Clear();
          counter = 0;
          iY = 0;
          iX = 0;
        }
    }
      if (Sw_Process(&leftState, SWL_LEFT) == Pressed)
      {
        if (--iX < 0)
        {
          SWL_ON(SWL_RED);
          iX = 0;
        }
        lcd_AddrXY(iX, iY);
    
      }

    if(Sw_Process(&rightState, SWL_RIGHT) ==  Pressed)
    {
      if(++iX > 19)
      {
        SWL_ON(SWL_RED);
        iX = 19;
      }
      
      lcd_AddrXY(iX, iY);
     
    }

    if(Sw_Process(&upState, SWL_UP) ==  Pressed)
    {
      if(--iY < 0)
      {
        SWL_ON(SWL_RED);
        iY = 0;
      }
      lcd_AddrXY(iX, iY);
  
    }

    if(Sw_Process(&downState, SWL_DOWN) ==  Pressed)
    {
      if(++iY > 3)
      {
        SWL_ON(SWL_RED);
        iY = 3;
      }
      lcd_AddrXY(iX, iY);
 
    }

    PIT_Sleep(PIT_CH0, 50);
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
