/*
 * API_IR.h
 *
 *  Created on: Mar 4, 2025
 *      Author: Fabrizzio
 */

#ifndef API_INC_API_IR_H_
#define API_INC_API_IR_H_

#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "API_liquidcrystal_i2c.h"
#include "stm32f4xx_hal.h"
#include "string.h"

void activando_alarma(void);
void alarma_sonando(void);
void alarma_conteo(void);

#endif /* API_INC_API_IR_H_ */
