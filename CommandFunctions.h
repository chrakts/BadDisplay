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
#define NUM_INFORMATION 13

extern COMMAND cnetCommands[];
extern INFORMATION information[];

void gotNewMqttTime();

#endif /* COMMANDFUNCTIONS_H_ */
