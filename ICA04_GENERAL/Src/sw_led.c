#include "sw_led.h"
#include "derivative.h"

void SWL_Init(void){
    // 3 most sig. bits->outputs (1). 5 least bits are inputs (0)
    DDR1AD1 = 0b11100000;
    // Enable switches
    ATD1DIEN1 |= 0b00011111;
}

void SWL_ON(SWL_LEDColour led){
    PT1AD1 |= led;
}

void SWL_OFF(SWL_LEDColour led){
    PT1AD1 &= ~led;
}

void SWL_TOG(SWL_LEDColour led){
    PT1AD1 ^= led;
}

int SWL_Pushed(SWL_SwitchPos pos){
    return PT1AD1 & pos;
}

int SWL_Any(void){
    return PT1AD1 & SWL_ANY;
}