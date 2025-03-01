/*
 * API_ALARMA.c
 *
 *  Created on: Feb 28, 2025
 *      Author: Fabrizzio
 */

#include "main.h"
#include "API_ALARMA.h"

static uint8_t alarma_activada = 0;
static uint8_t deteccion_movimiento = 0;
static uint8_t alarma_sonando = 0;

void Alarm_Init() {
    Ultrasonic_Init();
    Buzzer_Init();
    Button_Init();
}

void Alarm_Process() {
    if (Button_IsPressed()) {
        if (alarma_sonando) {
            Buzzer_Off();
            alarma_sonando = 0;
        } else if (!alarma_activada) {
            alarma_activada = 1;
            HAL_Delay(10000); // Espera 10 segundos
            uint32_t distancia = Ultrasonic_GetDistance();
            if (distancia < 150) { // Menos de 1.5m
                deteccion_movimiento = 1;
                HAL_Delay(10000); // Esperar otros 10s para desactivar
                if (!Button_IsPressed()) {
                    Buzzer_On();
                    alarma_sonando = 1;
                }
            }
        } else {
            alarma_activada = 0;
        }
    }
}
