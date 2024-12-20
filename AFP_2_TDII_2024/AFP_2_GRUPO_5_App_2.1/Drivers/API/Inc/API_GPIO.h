/*
 * API_GPIO.h
 *
 *  Created on: Oct 31, 2024
 *      Author: Fabrizzio
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

#include <stdint.h>

typedef uint16_t led_t;
typedef uint32_t ms;

#define CANT_LEDS 3

void MX_GPIO_Init(void);
void writeLedOn_GPIO (led_t LDx);
void writeLedOff_GPIO (led_t LDx);
void toggleLed_GPIO (led_t LDx);
void delay_ms (uint32_t ms);

#endif /* API_INC_API_GPIO_H_ */
