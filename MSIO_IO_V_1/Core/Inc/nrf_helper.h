/*
 * nrf_helper.h
 *
 *  Created on: Aug 8, 2023
 *      Author: sunil
 *
 *
 *      USAGE: UART2 & SPI1
 */

#ifndef INC_NRF_HELPER_H_
#define INC_NRF_HELPER_H_

#include <string.h>
#include <stdio.h>
#include "main.h"
#include "stm32f1xx_hal.h"
#include "MY_NRF24.h"

void nrf_init(void);
void TRANSMITT_UPDATE_TO_GATEWAY(char my_tx_data[]);;
void RECEIVED_MESSAGE_FROM_GATEWAY_IF_AVAILABLE(void);

#endif /* INC_NRF_HELPER_H_ */
