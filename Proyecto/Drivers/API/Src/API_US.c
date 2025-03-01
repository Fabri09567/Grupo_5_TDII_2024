/*
 * API_US.c
 *
 *  Created on: Feb 25, 2025
 *      Author: Fabrizzio
 */

#include "API_US.h"
#include "main.h"

void Ultrasonic_Init() {
    // Configuración inicial si fuera necesaria
}

uint32_t Ultrasonic_GetDistance() {
    uint32_t tiempo;

    // Enviar pulso de trigger
    HAL_GPIO_WritePin(TRIGGER_PORT, TRIGGER_PIN, GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(TRIGGER_PORT, TRIGGER_PIN, GPIO_PIN_RESET);

    // Medir el tiempo del pulso de ECHO
    while (!HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN)); // Espera HIGH
    tiempo = HAL_GetTick();
    while (HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN)); // Espera LOW
    tiempo = HAL_GetTick() - tiempo;

    // Convertir tiempo a distancia (en cm)
    return (tiempo * 0.0343) / 2;
}
