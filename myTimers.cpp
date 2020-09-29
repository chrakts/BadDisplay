#include "myTimers.h"
#include "BadDisplay.h"
#include "ledHardware.h"


// 1:  9.9  ms
// 2:  19.8 ms
// 5:  49.4 ms
//10:  99.0 ms
//101: 1000 ms

volatile TIMER MyTimers[MYTIMER_NUM]= {	{TM_START,RESTART_YES,101,0,sekundenTimer},
                                        {TM_START,RESTART_YES,10,0,led1Blinken},
                                        {TM_STOP,RESTART_NO,50,0,led2Blinken},
                                        {TM_START,RESTART_YES,500,0,displayOff}
};



void led1Blinken(uint8_t test)
{
	LEDROT_TOGGLE;
}

void led2Blinken(uint8_t test)
{
//	LED_KLINGEL_TOGGLE;
}

void displayOff(uint8_t test)
{
  ;
}

void sekundenTimer(uint8_t test)
{
  u32SecondsCounter++;
}


