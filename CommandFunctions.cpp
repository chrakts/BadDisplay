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
  {"LB",'L','1','L',FLOAT,1,(void*)&fThreshLuefter1,NULL},
  {"LB",'L','1','G',FLOAT,1,(void*)&fThreshLuefter2,NULL},
  {"LB",'L','1','H',FLOAT,1,(void*)&fHystLuefter1,NULL},
  {"LB",'L','1','I',FLOAT,1,(void*)&fHystLuefter2,NULL},
  {"LB",'C','1','t',FLOAT,1,(void*)&fTemperaturIst,NULL},
  {"LB",'C','1','h',FLOAT,1,(void*)&fFeuchteIst,NULL},
  {"V1",'V','0','D',FLOAT,1,(void*)&fThreshTempDay,NULL},
  {"V1",'V','0','N',FLOAT,1,(void*)&fThreshTempNight,NULL},
  {"V1",'V','0','H',FLOAT,1,(void*)&fThreshHyst,NULL},
  {"V1",'V','0','s',STRING,8,(void*)strStatusHeizungSoll,gotNewStatusHeizungSoll},
  {"V1",'H','0','S',FLOAT,1,(void*)&u8StatusHeizungIst,NULL},
  {"DT",'t','1','s',FLOAT,1,(void*)&fMqttTime,gotNewMqttTime},
  {"DT",'t','1','N',STRING,5,(void*)&strStatusNight,gotNewStatusNight}
};

void gotNewStatusNight()
{
  if(strStatusNight[1]=='n')
    u8StatusNight = true;
  else
    u8StatusNight = false;
}

/* "2019-04-18-06-36-02" */
// https://stackoverflow.com/questions/5754315/c-convert-char-to-timestamp/5754417#5754417
// https://stackoverflow.com/questions/1859201/add-seconds-to-a-date
void gotNewMqttTime()
{
  cli();
  u32SecondsCounter = uint32_t(fMqttTime);
  sei();
}

void gotNewStatusHeizungSoll()
{
  u8StatusHeizungSoll = transformHeizungStatus(strStatusHeizungSoll);
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

uint8_t transformHeizungStatus(char *toTransform)
{
	switch(toTransform[0])
	{
    case 'a':
      return HEAT_OFF;
    break;
    case 'e':
      return HEAT_ON;
    break;
    case 'A':
      return HEAT_AUTO;
    break;
	}

  return FAN_STATUS_AUTO;
}
