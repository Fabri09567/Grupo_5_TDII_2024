/*
 * API_SM.h
 *
 *  Created on: Feb 24, 2025
 *      Author: Fabrizzio
 */

#ifndef API_INC_API_SM_H_
#define API_INC_API_SM_H_

#include "main.h"

// Definir el pin del sensor PIR
#define PIR_PIN GPIO_PIN_0
#define PIR_PORT GPIOA

// Funciones del driver
void PIR_Init(void);
uint8_t PIR_Read(void);

#endif /* API_INC_API_SM_H_ */
