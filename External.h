/*
 * External.h
 *
 * Created: 03.04.2017 21:04:41
 *  Author: Christof
 */



#ifndef EXTERNAL_H_
#define EXTERNAL_H_
#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "uartHardware.h"
#include "myTimers.h"
#include "CRC_Calc.h"
#include "spi_driver.h"
#include "ar1021.h"
#include "../ComReceiver/ComReceiver.h"

extern char const *Node;

extern char     strStatusLuefterSoll[10];
extern char     strStatusLuefterIst[10];
extern uint8_t  u8StatusLuefterSoll;
extern uint8_t  u8StatusLuefterIst;
extern uint8_t  u8StatusHeizungSoll;
extern uint8_t  u8StatusHeizungIst;
extern double   fThreshLuefter1;
extern double   fThreshLuefter2;
extern double   fHystLuefter1;
extern double   fHystLuefter2;
extern double   fThreshTemp;
extern double   fThreshHyst;
extern double   fTemperaturIst;
extern double   fFeuchteIst;
extern double   fMqttTime;
extern uint32_t u32SecondsCounter;

extern uint8_t displayStatus;
extern uint8_t oldDisplayStatus;

class Communication;   // Forward declaration
extern Communication cmulti;
class ComReceiver;
extern ComReceiver cmultiRec;

extern SPI_Master_t spiDisplay;
extern AR1021 *pTouch;


#endif /* EXTERNAL_H_ */
