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
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim4;

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
	NRF24_read(received_data_from_gateway, 10); //store received data
	Print_Debug_Data(received_data_from_gateway);

	/*
	 //check the command and ACT accordingly
	 //	COMMAND LIST
	 COMMAND_WRITE_GPIO_ANALOG = 1,
	 COMMAND_READ_GPIO_DIGITAL = 2,
	 COMMAND_READ_GPIO_ANALOG = 3,
	 COMMAND_WRITE_RELAYS = 4
	 */
	char rcvd_node_id[2];
	uint8_t rcvd_command;

	rcvd_command = received_data_from_gateway[2] - '0';

	memcpy(rcvd_node_id, received_data_from_gateway, 2);
	//============CHECK IF NODE MATCH WITH ID======================//
	if (!(memcmp(rcvd_node_id, my_node_id, 2))) {
		Print_Debug_Data("\n NODE ID MATCHED");
		Print_Debug_Data("\n COMMAND ::> ");
		Print_Debug_Data((char*) rcvd_command);
	} else {
		return;
		Print_Debug_Data("NODE ID DOESNT MATCH");
	}
	uint8_t Actutate_GPIO = Get_GPIO_Num_For_Actuation(
			received_data_from_gateway);
	GPIO_PinState GPIO_STATE;
	uint8_t GPIO_STATE_INT = received_data_from_gateway[5] - '0';
	if (GPIO_STATE_INT) {

		GPIO_STATE = GPIO_PIN_SET;
	} else if (!GPIO_STATE_INT) {

		GPIO_STATE = GPIO_PIN_RESET;
	} else {
		Print_Debug_Data("\nERROR GATING GPIO STATE");
	}
	//===========CHECK FOR COMMAND AND ACT ACCORDINGLY=====//
	if (rcvd_command == COMMAND_WRITE_GPIO_ANALOG) {

		//SWITCH ON THE BASE OF GPIO NUM WRITE GPIO ANALOG
		if (((Actutate_GPIO == 1) || (Actutate_GPIO == 0))) {

			//TRY WRITING ANALOG DATA HERE WITH PWM / ANALOG IC
			//WORKING WITH PWM FOR NOW
			/*
			 * Read the VOLTAGE SCALE BETWEEN 0 - 12 VOLT
			 * WRITE IT TO CCR_RESPECTIVE_TIM
			 * */
			int PWM_Value_To_Write;
			switch (Actutate_GPIO) {
			case 1:
				PWM_Value_To_Write = Get_PWM_Val_To_Write(
						received_data_from_gateway);
				TIM4->CCR1 = PWM_Value_To_Write;
				break;
			case 2:
				PWM_Value_To_Write = Get_PWM_Val_To_Write(
						received_data_from_gateway);
				TIM4->CCR2 = PWM_Value_To_Write;
				break;
			}
		} else {
			Print_Debug_Data("\n Wrong GPIOI NUM FOR ANALOG WRITE");
		}
	}
	if (rcvd_command == COMMAND_WRITE_RELAYS) {
		//SWITCH ON THE BASE OF GPIO NUM READ GPIO ANALOG
		switch (Actutate_GPIO) {
		case 1:
			HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_STATE);
			break;
		case 2:
			HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, GPIO_STATE);
			break;
		case 3:
			HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, GPIO_STATE);
			break;
		default:
			break;
		}
	}
	if ((rcvd_command == COMMAND_READ_GPIO_DIGITAL)
			|| (rcvd_command == COMMAND_READ_GPIO_ANALOG)) {
		//RETURN DATA FOR READ COMMAND
		char Final_Return_String[32];
		memcpy(Final_Return_String, my_node_id, 2);	//copy the node id into it
		Final_Return_String[2] = received_data_from_gateway[2];	//copy the command as its 3rd byte
		Final_Return_String[3] = received_data_from_gateway[3];	//GPIO NUM 0
		Final_Return_String[4] = received_data_from_gateway[4];	//GPIO NUM 1
		if (rcvd_command == COMMAND_READ_GPIO_DIGITAL) {
			//SWITCH ON THE BASE OF GPIO NUM READ GPIO DIGITAL
			uint8_t GPIO_STATE = Read_Gpio_Digital(Actutate_GPIO);

			if (GPIO_STATE) {
				Final_Return_String[5] = '1';
			} else {
				Final_Return_String[5] = '0';
			}
		} else if (rcvd_command == COMMAND_READ_GPIO_ANALOG) {
			//SWITCH ON THE BASE OF GPIO NUM READ GPIO ANALOG

			uint32_t Analog_Value = Read_GPIO_ANALOG(Actutate_GPIO);
			//CONVERT UINT32_T INTO CHARACTER ARRAY AND COPY IT TO THE RETURN STRING
			char str[20];
			//The adc is of 12 bit, so the maximum value it can read is the 4096
			//SCALE THE READING IN THE SCALE OF 0-12 VOLT
			float Scaled_Value = ((float)Analog_Value / (float)4096);
			Scaled_Value = Scaled_Value * 12.0;
			sprintf(str, "%f", Scaled_Value);
			Final_Return_String[5] = str[0];
			Final_Return_String[6] = str[1];
			Final_Return_String[7] = str[2];
			Final_Return_String[8] = str[3];

		}
		Print_Debug_Data((char*) "\nReturning data ::> ");
		Print_Debug_Data((char*) Final_Return_String);

		Switch_to_Transmitt_mode();
		Transmitt_reply_to_gateway(Final_Return_String);
		Switch_to_Receiver_mode();
	}
}
/*
 @brief This function will take two chracter array and will return the gpio num
 */
uint8_t Get_GPIO_Num_For_Actuation(char received_data_from_gateway[]) {
	char GPIO_TO_WRITE[2];
	GPIO_TO_WRITE[0] = received_data_from_gateway[3];
	GPIO_TO_WRITE[1] = received_data_from_gateway[4];
	int GPIO_Num_For_Actuation = atoi(GPIO_TO_WRITE);
	return GPIO_Num_For_Actuation;
}
/*
 @brief This function will take two chracter array and will return the ANALOG_VOLTAGE TO WRITE
 */
int Get_PWM_Val_To_Write(char received_data_from_gateway[]) {
	char PWM_VAL_CHAR[2];
	PWM_VAL_CHAR[0] = received_data_from_gateway[5];
	PWM_VAL_CHAR[1] = received_data_from_gateway[6];
	int PWM_VAL = atoi(PWM_VAL_CHAR);
	/* SCALE IT WITH 0 - 1000
	 * SUBTRACT THE VALUE FROM 1000
	 * */
	float Temp = PWM_VAL;
	Temp = (float) PWM_VAL / 12; //MAXIMUNM VOLTAGE OF ANALOG WRITE
	Temp = Temp * 1000;
	int intValue = (int) Temp;
	intValue = 1000 - intValue;
	return intValue;
}

/*
 @brief This function will read the (Digital) GPIO number of input series and will return its current state
 */
uint8_t Read_Gpio_Digital(uint8_t GPIO_num) {

	Choose_Channel(GPIO_num);  //SELECT THE MUX
//	Read Its Digital State
	uint32_t ADC_VAL;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 10);
	ADC_VAL = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
//The adc is of 12 bit, so the maximum value it can read is the 4096
	if (ADC_VAL > 3600) {
		return 1;
	} else {
		return 0;
	}
}
uint32_t Read_GPIO_ANALOG(uint8_t GPIO_num) {
	Choose_Channel(GPIO_num);  //SELECT THE MUX
//	Read Its Digital State
	uint32_t ADC_VAL;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 10);
	ADC_VAL = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	return ADC_VAL;
}
void Transmitt_reply_to_gateway(char *msg) {
	HAL_UART_Transmit(&huart1,
			(uint8_t*) "\nTransmitting reply to gateway .. waiting for ack",
			strlen("\nTransmitting reply to gateway .. waiting for ack"), 10);
	char received_data_from_srvr1[40];
	memcpy(received_data_from_srvr1, msg, 32);
	for (int i = 0; i <= 10; i++) {
		if (!NRF24_write(received_data_from_srvr1, 32)) {
			NRF24_write(received_data_from_srvr1, 32);
			HAL_UART_Transmit(&huart1, (uint8_t*) ".", strlen("."), 10);
			HAL_Delay(400);
		} else {
			HAL_UART_Transmit(&huart1,
					(uint8_t*) "\nReply Transmitted to gateway successfully",
					strlen("\nReply Transmitted to gateway successfully"), 10);
			return;
		}
	}
	HAL_UART_Transmit(&huart1,
			(uint8_t*) "\nTransmission Failed, No acknowledgement received",
			strlen("\nTransmission Failed, No acknowledgement received"), 10);
}
