/**
* @file		led.c
* @brief	Contains API source code for controlling a single led on any pin.
*     		
* @version	1.0
* @date		3 Nov. 2016
* @author	Hugo Reis
**********************************************************************/
#include <led.h>

int __pinmask;
int __state;


void LED_Init(int pinId, int state){
	__pinmask = (1 << pinId);
	GPIO0->DIR |= __pinmask;
	LED_SetState(state);
}


int LED_GetState(void){
	return __state;
}


void LED_SetState(int state){
	__state = state & 1;

	if(!__state)				// led is connected in common Anode configuration
		GPIO0->SET = __pinmask;
	else
		GPIO0->CLR = __pinmask;
}

