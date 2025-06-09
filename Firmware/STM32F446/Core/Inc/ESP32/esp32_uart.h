
#ifndef INC_ESP32_UART_H_
#define INC_ESP32_UART_H_

#include "macros.h"
#include "main.h"
#include "stdint.h"
#include "stdio.h"
#include <string.h>

void ESP32_initCommunication(UART_HandleTypeDef * _uart);
HAL_StatusTypeDef ESP32_sendData();
HAL_StatusTypeDef ESP32_receiveData();

#endif /* INC_ESP32_UART_H_ */
