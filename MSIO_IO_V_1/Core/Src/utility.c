/*
 * utility.c
 *
 *  Created on: Dec 25, 2023
 *      Author: sunil
 */
#include "utility.h"

#include "nrf_helper.h"

char my_node_id[2] = "01";
extern UART_HandleTypeDef huart1;

void Print_Debug_Data(char *Debug_Msg) {
	HAL_UART_Transmit(&huart1, (uint8_t*) Debug_Msg, strlen(Debug_Msg), 100);
}
void Choose_Channel(uint8_t Channel_Num) {
	switch (Channel_Num) {
	case 0:
		HAL_GPIO_WritePin(U1_74HC_S0_GPIO_Port, U1_74HC_S0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S1_GPIO_Port, U1_74HC_S1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S2_GPIO_Port, U1_74HC_S2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S3_GPIO_Port, U1_74HC_S3_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(U1_74HC_S0_GPIO_Port, U1_74HC_S0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S1_GPIO_Port, U1_74HC_S1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S2_GPIO_Port, U1_74HC_S2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S3_GPIO_Port, U1_74HC_S3_Pin, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(U1_74HC_S0_GPIO_Port, U1_74HC_S0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S1_GPIO_Port, U1_74HC_S1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S2_GPIO_Port, U1_74HC_S2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S3_GPIO_Port, U1_74HC_S3_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(U1_74HC_S0_GPIO_Port, U1_74HC_S0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S1_GPIO_Port, U1_74HC_S1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S2_GPIO_Port, U1_74HC_S2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S3_GPIO_Port, U1_74HC_S3_Pin, GPIO_PIN_RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(U1_74HC_S0_GPIO_Port, U1_74HC_S0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S1_GPIO_Port, U1_74HC_S1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S2_GPIO_Port, U1_74HC_S2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S3_GPIO_Port, U1_74HC_S3_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(U1_74HC_S0_GPIO_Port, U1_74HC_S0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S1_GPIO_Port, U1_74HC_S1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S2_GPIO_Port, U1_74HC_S2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S3_GPIO_Port, U1_74HC_S3_Pin, GPIO_PIN_RESET);
		break;
	case 6:
		HAL_GPIO_WritePin(U1_74HC_S0_GPIO_Port, U1_74HC_S0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(U1_74HC_S1_GPIO_Port, U1_74HC_S1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S2_GPIO_Port, U1_74HC_S2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S3_GPIO_Port, U1_74HC_S3_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(U1_74HC_S0_GPIO_Port, U1_74HC_S0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S1_GPIO_Port, U1_74HC_S1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S2_GPIO_Port, U1_74HC_S2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S3_GPIO_Port, U1_74HC_S3_Pin, GPIO_PIN_RESET);
		break;
	default:
		HAL_GPIO_WritePin(U1_74HC_S0_GPIO_Port, U1_74HC_S0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S1_GPIO_Port, U1_74HC_S1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S2_GPIO_Port, U1_74HC_S2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(U1_74HC_S3_GPIO_Port, U1_74HC_S3_Pin, GPIO_PIN_SET);
		break;
	}
}

void Manage_NRF_Data(void) {
	char received_data_from_gateway[50] = "";
	Print_Debug_Data("\n DATA RECEIVED FROM NRF::>> ");
	NRF24_read(received_data_from_gateway, 5); //store received data
	Print_Debug_Data(received_data_from_gateway);

	/*
	 //check the command and ACT accordingly
	 //	COMMAND LIST
	 0 = WRITE GPIO
	 1 = WRITE ANALOG
	 2 = READ GPIO
	 3 = READ ANALOG
	 */

	char rcvd_node_id[2];
	char rcvd_command;
	memcpy(rcvd_node_id, received_data_from_gateway, 2);
	rcvd_command = received_data_from_gateway[2];

	//============CHECK IF NODE MATCH WITH ID======================//
	if (!(memcmp(rcvd_node_id, my_node_id, 2))) {
		Print_Debug_Data("\n NODE ID MATCHED");
		Print_Debug_Data("\n COMMAND ::> ");
		Print_Debug_Data(rcvd_command);
	}

	else {
		return;
	}

	if (rcvd_command == COMMAND_WRITE_GPIO_DIGITAL) {
		char GPIO_TO_WRITE[2];
		GPIO_TO_WRITE[0] = received_data_from_gateway[3];
		GPIO_TO_WRITE[1] = received_data_from_gateway[4];
		int value = atoi(GPIO_TO_WRITE);
		//SWITCH ON THE BASE OF GPIO NUM WRITE GPIO DIGITAL
	}
	if (rcvd_command == COMMAND_WRITE_ANALOG) {
		char GPIO_TO_WRITE[2];
		GPIO_TO_WRITE[0] = received_data_from_gateway[3];
		GPIO_TO_WRITE[1] = received_data_from_gateway[4];
		int value = atoi(GPIO_TO_WRITE);
		//SWITCH ON THE BASE OF GPIO NUM WRITE GPIO ANALOG
	}
	if (rcvd_command == READ_GPIO_DIGITAL) {
		char GPIO_TO_WRITE[2];
		GPIO_TO_WRITE[0] = received_data_from_gateway[3];
		GPIO_TO_WRITE[1] = received_data_from_gateway[4];
		int value = atoi(GPIO_TO_WRITE);
		//SWITCH ON THE BASE OF GPIO NUM READ GPIO DIGITAL
	}
	if (rcvd_command == READ_ANALOG_ANALOG) {
		char GPIO_TO_WRITE[2];
		GPIO_TO_WRITE[0] = received_data_from_gateway[3];
		GPIO_TO_WRITE[1] = received_data_from_gateway[4];
		int value = atoi(GPIO_TO_WRITE);
		//SWITCH ON THE BASE OF GPIO NUM READ GPIO ANALOG
	}
}
