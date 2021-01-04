/*
 * Globals.cpp
 *
 * Created: 19.03.2017 09:24:37
 *  Author: Christof
 */
#define EXTERNALS_H_

#include "BadDisplay.h"

const char *Node = "DB";

const char *fehler_text[]={"memory errors","parameter error","unknown job","no transmission","command not allowed","CRC error","no active sensor"};



char     strStatusLuefterSoll[10];
char     strStatusLuefterIst[10];
uint8_t  u8StatusLuefterSoll   = FAN_STATUS_1;
uint8_t  u8StatusLuefterIst    = FAN_STATUS_1;
uint8_t  u8StatusHeizungSoll   = HEAT_AUTO;
uint8_t  u8StatusHeizungIst    = HEAT_AUTO;
double   fThreshLuefter1       = 50.0;
double   fThreshLuefter2       = 50.0;
double   fHystLuefter1         = 5.0;
double   fHystLuefter2         = 5.0;
double   fThreshTemp           = 22.0;
double   fThreshHyst           = 5.0;
double   fTemperaturIst        = 23.44896;
double   fFeuchteIst           = 60.568;
double   fMqttTime             = 1111111111;
uint32_t u32SecondsCounter     = 1545264000+3600+900;

uint8_t displayStatus = DISPLAY_MAIN;
uint8_t oldDisplayStatus = DISPLAY_NONSENSE;


Communication cmulti(0,Node,5,USE_BUSY_0);
ComReceiver cmultiRec( &cmulti,Node,cnetCommands,NUM_COMMANDS,information,NUM_INFORMATION,"",NULL );

SPI_Master_t spiDisplay;

AR1021 *pTouch;

