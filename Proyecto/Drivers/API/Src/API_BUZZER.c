/*
 * API_BUZZER.c
 *
 *  Created on: Feb 28, 2025
 *      Author: Fabrizzio
 */
#include "main.h"
#include "API_BUZZER.h"

void Buzzer_Init() {
		__HAL_RCC_GPIOB_CLK_ENABLE();
	    GPIO_InitTypeDef GPIO_InitStruct = {0};
	    GPIO_InitStruct.Pin = BUZZER_PIN;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
}

void Buzzer_On() {
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
}

void Buzzer_Off() {
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}
