/**
* @file		buttons.C
* @brief	Contains API source code for reading buttons.
*     		
* @version	1.0
* @date		3 Nov. 2016
* @author	Hugo Reis
**********************************************************************/
#include <button.h>
#include <timer.h>
#include <gpio.h>


static BUTTON_Controller __buttons;

uint32_t BUTTON_Capture(void){
	return (~GPIO_Read()) & BUTTON_MASK;  //common ground
}

void BUTTON_Init(){
	__buttons.cur  = BUTTON_EMPTY;
	__buttons.last = BUTTON_EMPTY;
	__buttons.events = BUTTON_EMPTY;
	GPIO_SetInputN(BUTTON_MASK);
}

int BUTTON_Hit(void){
uint32_t cur = BUTTON_Capture();
	
	// check if any buttons pressed
	if(cur == BUTTON_EMPTY){		
		//update lastkey pressed and events
		if(__buttons.cur != BUTTON_EMPTY){
			__buttons.last= __buttons.cur;
			__buttons.cur = BUTTON_EMPTY;
			__buttons.events = BUTTON_RELEASED;
		}
		return BUTTON_EMPTY;
	}
	//update lastkey pressed
	__buttons.last = __buttons.cur;
	__buttons.cur = cur;

	// if not the same key pressed, start timer
	if(__buttons.cur != __buttons.last){		
		__buttons.timer = TIMER0_GetValue();
		__buttons.events = BUTTON_PRESSED;
		return __buttons.cur;
	}
	
	//check for timeout and activate hold flag
	if(TicksToMs(TIMER0_Elapse(__buttons.timer)) > BUTTON_HOLD_TIME){
		__buttons.events = BUTTON_HOLD;
	}
	else
		__buttons.events = BUTTON_TIMING;
	
	return __buttons.cur;
}

int BUTTON_Read(void){
	while(BUTTON_Hit() == BUTTON_EMPTY);
	return __buttons.cur; 
}

int BUTTON_GetButtonEvents(void){
	BUTTON_Hit();
	return __buttons.events;
}

int BUTTON_GetButton(void){
	return __buttons.cur;
}



