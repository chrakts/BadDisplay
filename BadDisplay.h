/*
 * BadDisplay.h
 *
 * Created: 26.09.2020
 *  Author: Christof
 */


#ifndef BADDISPLAY_H_
#define BADDISPLAY_H_

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

#include "myConstants.h"
#include "Serial.h"
#include "External.h"
#include "myTimers.h"
#include "ComReceiver.h"
#include "CommandFunctions.h"
#include "Communication.h"
#include "secrets.h"
#include "ledHardware.h"
#include "spi_driver.h"
#include "spiHardware.h"
#include "External.h"
#include "xmegaClocks.h"
#include "font.h"
#include "dogGraphic.h"
#include "timer.h"
#include "screens.h"


#endif /* BADDISPLAY_H_ */
