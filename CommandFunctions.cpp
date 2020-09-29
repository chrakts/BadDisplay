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
  {"LB",'L','s','s',UINT_8,1,(void*)&u8StatusLuefterSoll,NULL},
  {"LB",'L','a','s',UINT_8,1,(void*)&u8StatusLuefterIst,NULL},
  {"LB",'L','1','t',FLOAT,1,(void*)&fThreshLuefter1,NULL},
  {"LB",'L','2','t',FLOAT,1,(void*)&fThreshLuefter2,NULL},
  {"LB",'L','1','h',FLOAT,1,(void*)&fHystLuefter1,NULL},
  {"LB",'L','2','h',FLOAT,1,(void*)&fHystLuefter2,NULL},
  {"LB",'T','1','a',FLOAT,1,(void*)&fTemperaturIst,NULL},
  {"LB",'H','1','a',FLOAT,1,(void*)&fFeuchteIst,NULL},
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
  sei();
}

