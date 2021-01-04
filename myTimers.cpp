#include "myTimers.h"
#include "BadDisplay.h"
#include "ledHardware.h"


// 1:  9.9  ms
// 2:  19.8 ms
// 5:  49.4 ms
//10:  99.0 ms
//101: 1000 ms

volatile TIMER MyTimers[MYTIMER_NUM]= {	{TM_START,RESTART_YES,101,0,sekundenTimer},   // TIMER_SEKUNDE
                                        {TM_STOP,RESTART_YES,101,0,led1Blinken},     // TIMER_LEDBLINK1
                                        {TM_STOP,RESTART_YES,50,0,led2Blinken},        // TIMER_LEDBLINK2
                                        {TM_STOP,RESTART_NO,5000,0,displayOff},      // TIMER_DISPLAY_OFF
                                        {TM_START,RESTART_NO,101,0,NULL}             // TIMER_TOUCH
};



void led1Blinken(uint8_t test)
{
	LEDRGB_ROT_TOGGLE;
}

void led2Blinken(uint8_t test)
{
//	LED_KLINGEL_TOGGLE;
}

void displayOff(uint8_t test)
{
  displayStatus=DISPLAY_SLEEP;
  MyTimers[TIMER_LEDBLINK1].state = TM_STOP;
  initDisplayClock(true);
}

void sekundenTimer(uint8_t test)
{
  u32SecondsCounter++;
}


