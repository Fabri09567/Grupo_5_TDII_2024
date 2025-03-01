/*
 * API_Debounce.c
 *
 *  Created on: Feb 24, 2025
 *      Author: Fabrizzio
 */

#include "main.h"
#include "API_Debounce.h"

typedef enum {
	BUTTON_UP ,
	BUTTON_FALLING ,
	BUTTON_DOWN ,
	BUTTON_RISING
} debounceState_t;

delay_t tiempo_debounce;
debounceState_t estado_boton;
bool_t lectura_boton;

void debounceFSM_Init(){
	delayInit(&tiempo_debounce, 40);
	estado_boton = BUTTON_UP;
	lectura_boton = false;
	writeLedOff_GPIO(LD1_Pin);
	writeLedOff_GPIO(LD2_Pin);
	writeLedOff_GPIO(LD3_Pin);
}

void debounceFSM_Update(){
	switch(estado_boton){
	case BUTTON_UP:
		if(readButton_GPIO()){
			estado_boton = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		if(delayRead(&tiempo_debounce)){
			if(readButton_GPIO()){
				lectura_boton = true;
				estado_boton = BUTTON_DOWN;
			}else{
				estado_boton = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if(!readButton_GPIO()){
			estado_boton = BUTTON_RISING;
		}
		break;
	case BUTTON_RISING:
		if(delayRead(&tiempo_debounce)){
			if(!readButton_GPIO()){
				estado_boton = BUTTON_UP;
			}else{
				estado_boton = BUTTON_DOWN;
			}
		}
		break;
	default:
		Error_Handler();
		break;
	}
}

bool_t readKey(){
	if(lectura_boton){
		lectura_boton = false;
		return true;
	}else{
		return false;
	}
}

