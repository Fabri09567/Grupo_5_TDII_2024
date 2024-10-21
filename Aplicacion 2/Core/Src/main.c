/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

#include "main.h"
#include "stm32f4xx_hal.h"

#define LED1_PIN GPIO_PIN_0
#define LED2_PIN GPIO_PIN_7
#define LED3_PIN GPIO_PIN_14
#define BUTTON_PIN GPIO_PIN_13
#define LED_PORT GPIOB
#define BUTTON_PORT GPIOC

GPIO_PinState leds[] = {LED1_PIN, LED2_PIN, LED3_PIN};
int reverse = 0;

void delay_ms(uint32_t delay) {
    HAL_Delay(delay);
}

int main(void) {
    HAL_Init();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED1_PIN | LED2_PIN | LED3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);

    while (1) {
        if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_SET) {
            reverse = !reverse;
            HAL_Delay(300);
        }

        if (reverse) {
            for (int i = sizeof(leds) / sizeof(leds[0]) - 1; i >= 0; i--) {
                HAL_GPIO_WritePin(LED_PORT, leds[i], GPIO_PIN_SET);
                delay_ms(200);
                HAL_GPIO_WritePin(LED_PORT, leds[i], GPIO_PIN_RESET);
                delay_ms(200);
            }
        } else {
            for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
                HAL_GPIO_WritePin(LED_PORT, leds[i], GPIO_PIN_SET);
                delay_ms(200);
                HAL_GPIO_WritePin(LED_PORT, leds[i], GPIO_PIN_RESET);
                delay_ms(200);
            }
        }
    }
}
