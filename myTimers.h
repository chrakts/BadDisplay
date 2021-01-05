/*
 * MyTimer.h
 *
 * Created: 11.02.2016 20:20:03
 *  Author: Christof
 */


#ifndef MYTIMERS_H_
#define MYTIMERS_H_

#include "timer.h"
#include "External.h"
#include "myConstants.h"

#define MYTIMER_NUM	6


enum{TIMER_SEKUNDE,TIMER_LEDBLINK1,TIMER_LEDBLINK2,TIMER_DISPLAY_OFF,TIMER_TOUCH,TIMER_BEEP};


void led1Blinken(uint8_t test);
void led2Blinken(uint8_t test);
void displayOff(uint8_t test);
void sekundenTimer(uint8_t test);
void beepTimer(uint8_t test);

extern volatile TIMER MyTimers[MYTIMER_NUM];

#endif /* MYTIMERS_H_ */
