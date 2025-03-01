/*
 * API_MOTOR.c
 *
 *  Created on: Feb 28, 2025
 *      Author: Fabrizzio
 */
#include "main.h"
#include "API_MOTOR.h"

#define STEP_DELAY 10  // Ajusta el tiempo entre pasos (ms)

#define MOTOR_PIN_1 GPIO_PIN_10
#define MOTOR_PIN_2 GPIO_PIN_11
#define MOTOR_PIN_3 GPIO_PIN_12
#define MOTOR_PIN_4 GPIO_PIN_13

#define MOTOR_PORT GPIOB

void Stepper_Init(void) {
    __HAL_RCC_GPIOB_CLK_ENABLE(); // Habilita el reloj del puerto B
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = MOTOR_PIN_1 | MOTOR_PIN_2 | MOTOR_PIN_3 | MOTOR_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MOTOR_PORT, &GPIO_InitStruct);
}


void Stepper_Step(int steps) {
    uint8_t step_sequence[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    int direction = (steps > 0) ? 1 : -1;
    steps = (steps > 0) ? steps : -steps;

    for (int i = 0; i < steps; i++) {
        for (int j = 0; j < 4; j++) {
            HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN_1, step_sequence[j][0]);
            HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN_2, step_sequence[j][1]);
            HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN_3, step_sequence[j][2]);
            HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN_4, step_sequence[j][3]);
            HAL_Delay(STEP_DELAY);
        }
    }
}
