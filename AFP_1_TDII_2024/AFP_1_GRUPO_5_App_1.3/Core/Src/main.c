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

// Definir los pines de los LEDs onboard
#define LED1_PIN GPIO_PIN_0
#define LED2_PIN GPIO_PIN_1
#define LED3_PIN GPIO_PIN_2
#define LED_PORT GPIOB  // Asumiendo que los LEDs están conectados al puerto GPIOB

// Variables globales
uint8_t tiempo_actual = 1;  // Inicia con el tiempo 1
uint32_t delay_tiempo = 100;  // Tiempo de alternancia inicial en ms
uint8_t boton_presionado = 0;

// Función para configurar LEDs y el botón
void Configuracion_Leds_Boton(void) {
    __HAL_RCC_GPIOB_CLK_ENABLE();  // Habilitar reloj para GPIOB
    __HAL_RCC_GPIOC_CLK_ENABLE();  // Habilitar reloj para GPIOC (botón)

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configuración de los LEDs como salida
    GPIO_InitStruct.Pin = LED1_PIN | LED2_PIN | LED3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

    // Configuración del botón como entrada
    GPIO_InitStruct.Pin = GPIO_PIN_13;  // Botón onboard (PA0 o PC13 según la placa)
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

// Función para cambiar los tiempos de alternancia
void Cambiar_Tiempo(void) {
    // Avanza al siguiente tiempo
    tiempo_actual++;
    if (tiempo_actual > 4) {
        tiempo_actual = 1;  // Reinicia al tiempo 1
    }

    // Establecer el tiempo de alternancia según la secuencia
    switch (tiempo_actual) {
        case 1:
            delay_tiempo = 100;
            break;
        case 2:
            delay_tiempo = 250;
            break;
        case 3:
            delay_tiempo = 500;
            break;
        case 4:
            delay_tiempo = 1000;
            break;
        default:
            break;
    }
}

// Función principal de parpadeo de LEDs
void Parpadeo_LEDs(void) {
    HAL_GPIO_TogglePin(LED_PORT, LED1_PIN | LED2_PIN | LED3_PIN);  // Parpadeo simultáneo
    HAL_Delay(delay_tiempo);
}

// Función principal
int main(void) {
    HAL_Init();
    Configuracion_Leds_Boton();

    while (1) {
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET && !boton_presionado) {
            // Si el botón es presionado (nivel bajo), cambiar tiempo
            Cambiar_Tiempo();
            boton_presionado = 1;
        } else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
            boton_presionado = 0;  // Resetear cuando se suelte el botón
        }

        Parpadeo_LEDs();  // Ejecutar el parpadeo según el tiempo actual
    }
}
