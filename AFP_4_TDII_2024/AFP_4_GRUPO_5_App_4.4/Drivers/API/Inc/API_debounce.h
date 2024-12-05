/*
 * API_debounce.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Fabrizzio
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include "main.h"
#include "API_GPIO.h"
#include "API_Delay.h"

void debounceFSM_Init();
void debounceFSM_Update();
bool_t readKey();

#endif /* API_INC_API_DEBOUNCE_H_ */

