/*
 * API_PIR.c
 *
 *  Created on: Mar 4, 2025
 *      Author: Fabrizzio
 */

#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "API_liquidcrystal_i2c.h"
#include "stm32f4xx_hal.h"
#include "string.h"

#define SENSOR_PIR_PIN GPIO_PIN_1  // Pin de entrada del sensor PIR (PB1)
#define LED_PIN GPIO_PIN_15			// pin de salida de led

extern uint32_t tiempoUltimoMovimiento;


void led_on(void){
	HAL_GPIO_WritePin(GPIOD, LED_PIN, GPIO_PIN_SET); // Encender led
	tiempoUltimoMovimiento = HAL_GetTick();
}

void led_off(void){
	HAL_GPIO_WritePin(GPIOD, LED_PIN, GPIO_PIN_RESET);
}

void alarma_desactivada(void){
	HD44780_Clear();
	HD44780_SetCursor(0,0);
	HD44780_PrintStr("Alarma");
	HD44780_SetCursor(0,1);
	HD44780_PrintStr("Desactivada");
	HAL_Delay(100);
}
