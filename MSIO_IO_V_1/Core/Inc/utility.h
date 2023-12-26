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
	COMMAND_WRITE_GPIO_ANALOG = 1,
	COMMAND_READ_GPIO_DIGITAL = 2,
	COMMAND_READ_GPIO_ANALOG = 3,
	COMMAND_WRITE_RELAYS = 4
};

uint8_t Get_GPIO_Num_For_Actuation(char received_data_from_gateway[]);
void Print_Debug_Data(char *Debug_Msg);
void Choose_Channel(uint8_t Channel_Num);
void Manage_NRF_Data(void);
uint8_t Read_Gpio_Digital(uint8_t GPIO_num);
uint32_t Read_GPIO_ANALOG(uint8_t GPIO_num);
#endif /* INC_UTILITY_H_ */
