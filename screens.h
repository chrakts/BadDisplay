#ifndef SCREENS_H_INCLUDED
#define SCREENS_H_INCLUDED


#include <inttypes.h>
#include <string.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "dogGraphic.h"
#include "External.h"
#include "ar1021.h"

void updateDisplayMain(bool forceUpdate);
void initDisplayClock(bool forceUpdate);
void initDisplaySetup();
void initDisplaySetValue();
uint8_t displayTouched();

#endif // SCREENS_H_INCLUDED
