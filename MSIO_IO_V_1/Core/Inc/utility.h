/*
 * utility.h
 *
 *  Created on: Dec 25, 2023
 *      Author: sunil
 */

#ifndef INC_UTILITY_H_
#define INC_UTILITY_H_

#include "main.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define Debug_Data_Port huart1

enum COMMAND_LIST {
	COMMAND_WRITE_GPIO_DIGITAL = 0,
	COMMAND_WRITE_ANALOG = 1,
	READ_GPIO_DIGITAL = 2,
	READ_ANALOG_ANALOG = 3
};

void Print_Debug_Data(char *Debug_Msg);
void Choose_Channel(uint8_t Channel_Num);
void Manage_NRF_Data(void);

#endif /* INC_UTILITY_H_ */
