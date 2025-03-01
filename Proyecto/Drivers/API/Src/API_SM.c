/*
 * API_SM.c
 *
 *  Created on: Feb 24, 2025
 *      Author: Fabrizzio
 */

#include "API_SM.h"
#include "main.h"

// Inicializar el pin del sensor PIR
void PIR_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Habilitar el reloj para el puerto A

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = PIR_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(PIR_PORT, &GPIO_InitStruct);
}

// Leer el estado del sensor PIR
uint8_t PIR_Read(void)
{
    return HAL_GPIO_ReadPin(PIR_PORT, PIR_PIN);
}
