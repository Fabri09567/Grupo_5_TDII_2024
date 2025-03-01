/*
 * API_US.h
 *
 *  Created on: Feb 25, 2025
 *      Author: Fabrizzio
 */

#include "stm32f4xx_hal.h"
#include <stdbool.h>

#ifndef API_US_H
#define API_US_H

#define TRIGGER_PIN GPIO_PIN_1
#define TRIGGER_PORT GPIOB
#define ECHO_PIN GPIO_PIN_2
#define ECHO_PORT GPIOB

void Ultrasonic_Init();
uint32_t Ultrasonic_GetDistance();

#endif /* API_INC_API_US_H_ */
