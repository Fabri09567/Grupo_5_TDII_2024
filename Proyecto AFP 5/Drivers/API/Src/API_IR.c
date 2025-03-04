/*
 * API_IR.c
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

#define SENSOR_IR_PIN GPIO_PIN_0   // Pin de entrada del sensor IR (PA0)
#define BUZZER_PIN GPIO_PIN_0      // Pin de salida del buzzer (PB0)

extern uint32_t tiempoDeteccionIR;
extern uint8_t modoIR;
extern uint8_t zumbadorActivadoIR;
extern uint8_t conteoIRIniciado;

void activando_alarma(void){
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Activando alarma");
	HAL_Delay(3000);
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Alarma activada");
	HAL_Delay(100);
}

void alarma_sonando(void){
	HAL_GPIO_WritePin(GPIOB, BUZZER_PIN, GPIO_PIN_SET); //encender el zumbador.
	HD44780_Clear();
	HD44780_SetCursor(0, 0);
	HD44780_PrintStr("Alarma Sonando");
	HAL_Delay(100);
}

void alarma_conteo(void){
	if (HAL_GetTick() - tiempoDeteccionIR >= 3000) {
		// 3 segundos transcurridos, verificar si se cambió a modo PIR
		if (modoIR) {
		zumbadorActivadoIR = 1;
		}
		conteoIRIniciado = 0;
	}
}
