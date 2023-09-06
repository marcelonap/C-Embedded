/********************************************************************/
// HC12 Program:  Exam 3 Winter, 2023 
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Marcelo Napoleao Sampaio
// Details:       LAB EXAM 3

                  
// Date:          April 24th, 2023
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
#include "lcd.h"
#include "pit.h"
#include "clock.h"
#include "sw_led.h"
#include "segs.h"

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
int count = 9500;
unsigned char sum = 0;
int run = 1;
SwState ctrState,upState,downState = Idle;
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
Segs_Init();
SWL_Init();
lcd_Init();

lcd_StringXY(10,3,"M. SAMPAIO");

PIT_SetmsDelay(PIT_CH0, PIT_MT0, 30);
Segs_Custom(7,0b10011101);
  /********************************************************************/
  // main program loop
  /********************************************************************/
  for (;;)
  { 
  //recording and displaying sum of last 2 digits
  sum = ((count/1000) % 10) + ((count/100)%10);
  Segs_8H(4,sum);
  //debug
  // Segs_Normal(4,count/1000,Segs_DP_OFF);
  //  Segs_Normal(5,(count/100)%10,Segs_DP_OFF);
    if(PITTF & PIT_CH0){
      PITTF = PIT_CH0;
      if(run){
      count++;
      if(count > 9999){
        count = 0;
      }
       Segs_16D(count, Segs_LineTop);

      }
      SWL_TOG(SWL_RED);
     
      PIT_Sleep(PIT_CH2, 10);

    SWL_ON(SWL_GREEN);
    PIT_Sleep(PIT_CH3,5);
    SWL_OFF(SWL_GREEN);

    }

  //Ctr button processing
    if(Sw_Process(&ctrState, SWL_CTR) == Released){
        run ^= 1;
        Segs_Custom(7,0b10001011);

        if(run){
           Segs_Custom(7,0b10011101);
        }
    }
  //up button processing
    if(Sw_Process(&upState,SWL_UP) == Pressed){
      count++;
      if(count > 9999){
        count = 0;
      }
       Segs_16D(count, Segs_LineTop);
    }
  //down button processing
    if(Sw_Process(&downState,SWL_DOWN) == Pressed){
      count--;
      if(count < 0){
        count = 9999;
      }
       Segs_16D(count, Segs_LineTop);
    }
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/


/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
//Interrput + vector name + function

