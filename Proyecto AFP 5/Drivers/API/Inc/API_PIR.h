/*
 * API_PIR.h
 *
 *  Created on: Mar 4, 2025
 *      Author: Fabrizzio
 */

#ifndef API_INC_API_PIR_H_
#define API_INC_API_PIR_H_

#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "API_liquidcrystal_i2c.h"
#include "stm32f4xx_hal.h"
#include "string.h"

void led_on(void);
void led_off(void);
void alarma_desactivada(void);

#endif /* API_INC_API_PIR_H_ */
