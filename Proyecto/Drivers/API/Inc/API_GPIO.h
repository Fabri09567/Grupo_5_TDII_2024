/*
 * API_GPIO.h
 *
 *  Created on: Feb 24, 2025
 *      Author: Fabrizzio
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"


typedef uint16_t led_t;
typedef uint32_t ms;
typedef bool buttonStatus_t;

#define BUTTON_PIN GPIO_PIN_0
#define BUTTON_PORT GPIOA

void MX_GPIO_Init(void);
void writeLedOn_GPIO (led_t LDx);
void writeLedOff_GPIO (led_t LDx);
void toggleLed_GPIO (led_t LDx);
void delay_ms (uint32_t ms);
buttonStatus_t readButton_GPIO(void);

void Button_Init();
uint8_t Button_IsPressed();

#endif /* API_INC_API_GPIO_H_ */
