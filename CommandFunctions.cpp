/*
 * CommandFunctions.cpp
 *
 * Created: 26.04.2017 14:54:45
 *  Author: a16007
 */

#include "CommandFunctions.h"
#include "External.h"
#include "../Secrets/secrets.h"
#include "ledHardware.h"
#include "../ComReceiver/cmultiStandardCommands.h"

COMMAND cnetCommands[NUM_COMMANDS] =
{
    cmultiStandardCommands
};

INFORMATION information[NUM_INFORMATION]=
{
  {"LB",'L','1','s',STRING,8,(void*)strStatusLuefterSoll,gotNewStatusLuefterSoll},
  {"LB",'L','1','a',STRING,8,(void*)strStatusLuefterIst,gotNewStatusLuefterIst},
  {"LB",'L','0','L',FLOAT,1,(void*)&fThreshLuefter1,NULL},
  {"LB",'L','0','G',FLOAT,1,(void*)&fThreshLuefter2,NULL},
  {"LB",'L','1','h',FLOAT,1,(void*)&fHystLuefter1,NULL},
  {"LB",'L','2','h',FLOAT,1,(void*)&fHystLuefter2,NULL},
  {"LB",'C','1','t',FLOAT,1,(void*)&fTemperaturIst,NULL},
  {"LB",'C','1','h',FLOAT,1,(void*)&fFeuchteIst,NULL},
  {"V1",'T','1','t',FLOAT,1,(void*)&fThreshTemp,NULL},
  {"V1",'T','1','h',FLOAT,1,(void*)&fThreshHyst,NULL},
  {"V1",'H','s','s',FLOAT,1,(void*)&u8StatusHeizungSoll,NULL},
  {"V1",'H','a','s',FLOAT,1,(void*)&u8StatusHeizungIst,NULL},
  {"DT",'t','1','s',FLOAT,1,(void*)&fMqttTime,gotNewMqttTime}
};

/* "2019-04-18-06-36-02" */
// https://stackoverflow.com/questions/5754315/c-convert-char-to-timestamp/5754417#5754417
// https://stackoverflow.com/questions/1859201/add-seconds-to-a-date
void gotNewMqttTime()
{
  cli();
  u32SecondsCounter = uint32_t(fMqttTime);
  LEDRGB_GRUEN_ON;
  sei();
}

void gotNewStatusLuefterSoll()
{
  u8StatusLuefterSoll = transformLuefterStatus(strStatusLuefterSoll);
}

void gotNewStatusLuefterIst()
{
  u8StatusLuefterIst = transformLuefterStatus(strStatusLuefterIst);
}

uint8_t transformLuefterStatus(char *toTransform)
{
	switch(toTransform[0])
	{
    case 'a':
      return FAN_STATUS_OFF;
    break;
    case 'S':
      if( toTransform[6]=='1' )
        return FAN_STATUS_1;
      else
        return FAN_STATUS_2;
    break;
    case 'A':
      return FAN_STATUS_AUTO;
    break;
	}

  return FAN_STATUS_AUTO;
}
