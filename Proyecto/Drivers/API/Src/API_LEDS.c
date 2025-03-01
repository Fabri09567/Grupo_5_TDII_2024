/*
 * API_LEDS.c
 *
 *  Created on: Feb 28, 2025
 *      Author: Fabrizzio
 */

#include "API_LEDS.h"
#include "main.h"

void LED_Init(void)
{
    __HAL_RCC_GPIOG_CLK_ENABLE(); // Habilitar el reloj para el puerto G

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

// Encender todos los LEDs
void LED_On(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED1_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_PORT, LED2_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_PORT, LED3_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_PORT, LED4_PIN, GPIO_PIN_SET);
}

// Apagar todos los LEDs
void LED_Off(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_PORT, LED2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_PORT, LED3_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_PORT, LED4_PIN, GPIO_PIN_RESET);
}

// Alternar el estado de todos los LEDs
void LED_Toggle(void)
{
    HAL_GPIO_TogglePin(LED_PORT, LED1_PIN);
    HAL_GPIO_TogglePin(LED_PORT, LED2_PIN);
    HAL_GPIO_TogglePin(LED_PORT, LED3_PIN);
    HAL_GPIO_TogglePin(LED_PORT, LED4_PIN);
}
