/*
 * API_LEDS.h
 *
 *  Created on: Feb 28, 2025
 *      Author: Fabrizzio
 */

#ifndef API_INC_API_LEDS_H_
#define API_INC_API_LEDS_H_

#include "main.h"

// Definir los pines de los LEDs
#define LED1_PIN GPIO_PIN_12
#define LED2_PIN GPIO_PIN_13
#define LED3_PIN GPIO_PIN_14
#define LED4_PIN GPIO_PIN_15
#define LED_PORT GPIOG

// Funciones del driver
void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);

#endif /* API_INC_API_LEDS_H_ */
