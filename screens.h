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
void initDisplaySetValue(const char *text,double min,double max, double step,double *oldValue,char job);
uint8_t displayTouched();
void addSetValue();
void subSetValue();
void setSetValue();
void updateDisplaySetValue();

#endif // SCREENS_H_INCLUDED
