#include "main.h"
#include "stm32f4xx_hal.h"

#define LED1_PIN GPIO_PIN_0
#define LED2_PIN GPIO_PIN_7
#define LED3_PIN GPIO_PIN_14
#define LED_PORT GPIOB

GPIO_PinState leds[] = {LED1_PIN, LED2_PIN, LED3_PIN};

void delay_ms(uint32_t delay) {
    HAL_Delay(delay);
}

int main(void) {
    HAL_Init();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED1_PIN | LED2_PIN | LED3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

    while (1) {
        for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
            HAL_GPIO_WritePin(LED_PORT, leds[i], GPIO_PIN_SET);
            delay_ms(200);

            HAL_GPIO_WritePin(LED_PORT, leds[i], GPIO_PIN_RESET);
            delay_ms(200);
        }
    }
}
