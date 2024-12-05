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

typedef uint16_t led_t;
typedef uint32_t ms;
typedef bool buttonStatus_t;

#define CANT_LEDS 3
#define tiempos 4
uint8_t secuencia(uint16_t* vector_leds, uint16_t tiempo, uint8_t caso);

void MX_GPIO_Init(void);
void writeLedOn_GPIO (led_t LDx);
void writeLedOff_GPIO (led_t LDx);
void toggleLed_GPIO (led_t LDx);
void delay_ms (uint32_t ms);
buttonStatus_t readButton_GPIO(void);
#endif /* API_INC_API_GPIO_H_ */
