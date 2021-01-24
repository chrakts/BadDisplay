/*
 * CommandFunctions.h
 *
 * Created: 26.04.2017 14:55:18
 *  Author: a16007
 */


#ifndef COMMANDFUNCTIONS_H_
#define COMMANDFUNCTIONS_H_

#include "BadDisplay.h"

#define NUM_COMMANDS 10
#define NUM_INFORMATION 15

extern COMMAND cnetCommands[];
extern INFORMATION information[];

void gotNewStatusNight();
void gotNewStatusHeizungSoll();
void gotNewMqttTime();
void gotNewStatusLuefterSoll();
void gotNewStatusLuefterIst();
uint8_t transformLuefterStatus(char *toTransform);
uint8_t transformHeizungStatus(char *toTransform);
#endif /* COMMANDFUNCTIONS_H_ */
