/*
 * API_GPIO.h
 *
 *  Created on: Oct 31, 2024
 *      Author: Fabrizzio
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_

#include <stdint.h>
#include <stdbool.h>

uint8_t secuencia1(uint16_t* vector_leds);
uint8_t secuencia2(uint16_t* vector_leds);

typedef uint16_t led_t;
typedef bool buttonStatus_t;

#define CANT_LEDS 3
#define delay_ms 200

void MX_GPIO_Init(void);
void writeLedOn_GPIO (led_t LDx);
void writeLedOff_GPIO (led_t LDx);
void toggleLed_GPIO (led_t LDx);

buttonStatus_t readButton_GPIO(void);
#endif /* API_INC_API_GPIO_H_ */
