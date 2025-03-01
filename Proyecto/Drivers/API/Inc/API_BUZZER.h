/*
 * API_BUZZER.h
 *
 *  Created on: Feb 28, 2025
 *      Author: Fabrizzio
 */

#ifndef API_INC_API_BUZZER_H_
#define API_INC_API_BUZZER_H_

#include "main.h"

#define BUZZER_PIN GPIO_PIN_3
#define BUZZER_PORT GPIOB

void Buzzer_Init();
void Buzzer_On();
void Buzzer_Off();

#endif /* API_INC_API_BUZZER_H_ */
