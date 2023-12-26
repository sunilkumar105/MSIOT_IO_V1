/*
 * nrf_helper.c
 *
 *  Created on: Aug 8, 2023
 *      Author: sunil
 */

#include "nrf_helper.h"

uint64_t node_pipe_addr = 0x11223344aa;
uint8_t node_channel_addr = 52;

uint64_t target_pipe_addr = 0x11223344aa;
uint8_t target_channel_addr = 52;

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void nrf_init(void) {
	NRF24_begin(NRF_CE_GPIO_Port, NRF_CSN_Pin, NRF_CE_Pin, hspi1);
	nrf24_DebugUART_Init(huart1);
	NRF24_setChannel(node_channel_addr);
	NRF24_setPayloadSize(32);
	NRF24_openReadingPipe(1, node_pipe_addr);
	NRF24_startListening();
	printRadioSettings();
}
void Switch_to_Transmitt_mode() {
	NRF24_stopListening();
	NRF24_openWritingPipe(target_pipe_addr);
	NRF24_setChannel(target_channel_addr);
}
void Switch_to_Receiver_mode(void) {
	NRF24_stopListening();
	NRF24_setChannel(node_channel_addr);
	NRF24_openReadingPipe(1, node_pipe_addr);
	NRF24_startListening();
}
void TRANSMITT_UPDATE_TO_GATEWAY(char my_tx_data[]) {
	Switch_to_Transmitt_mode();
	for (int i = 0; i < +10; i++) {
		if (!NRF24_write(my_tx_data, 32)) {
			NRF24_write(my_tx_data, 32);
			HAL_UART_Transmit(&huart2,
					(uint8_t*) "Transmitt_update waiting for ack\n",
					strlen("Transmitt_update waiting for ack\n"), 10);
			HAL_Delay(200);
		} else {
			HAL_UART_Transmit(&huart2,
					(uint8_t*) "Transmitt_update Transmitted successfully\n",
					strlen("Transmitt_update Transmitted successfully\n"), 10);
			HAL_Delay(100);
			break;
		}
	}
	Switch_to_Receiver_mode();
}
