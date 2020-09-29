#ifndef SCREENS_H_INCLUDED
#define SCREENS_H_INCLUDED


#include <inttypes.h>
#include <string.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "dogGraphic.h"


void updateDisplayMain(bool forceUpdate);
void initDisplayClock();
void initDisplaySetup();
void initDisplaySetValue();

#endif // SCREENS_H_INCLUDED
